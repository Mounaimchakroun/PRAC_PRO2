/** @file Cuenca.cc
    @brief Implementación de Cuenca.
*/

#include "Cuenca.hh"


//FUNCIONES PRIVADAS
//#####################################################
BinTree<pair<string,pair<int,int>>> Cuenca::Obtener_arbol_de_ventas(int id_prod_a_comprar, int id_prod_a_vender, int productos_comprados, int productos_vendidos, const BinTree<string>& nodo){
    // Caso Base ########################################################################################
    if (nodo.empty()) return BinTree<pair<string,pair<int,int>>>();
    // Paso Inductivo ###################################################################################

    if ((productos_comprados > 0) and (productos_vendidos > 0)){
        string id_ciudad = nodo.value(); //Id de ciudad actual

        this->_it_mapa_ciudad = this->_mapa_ciudades.find(id_ciudad);

        pair<int,int> info_prod_a_comprar;
        bool proceder_c = this->_it_mapa_ciudad->second.consultar_prod_c_sin_notificacion_de_errores(id_prod_a_comprar,info_prod_a_comprar);

        pair<int,int> info_prod_a_vender;
        bool proceder_v = this->_it_mapa_ciudad->second.consultar_prod_c_sin_notificacion_de_errores(id_prod_a_vender,info_prod_a_vender);

        //###################################################################################################
        if (productos_comprados > 0 and proceder_c){
            int provisional = info_prod_a_comprar.first - info_prod_a_comprar.second;
            
            if (productos_comprados <= provisional){
                productos_comprados = 0; 
            }
            else {
                productos_comprados -= provisional; //Productos que sobran
            }
        }
        if (productos_vendidos > 0 and proceder_v){
            int provisional = info_prod_a_vender.second - info_prod_a_vender.first;

            if (productos_vendidos <= provisional){
                productos_vendidos = 0; 
            }
            else {
                productos_vendidos -= provisional; //Productos que necesita
            }
        }
        //###################################################################################################

        BinTree<pair<string,pair<int,int>>> izquierda = Obtener_arbol_de_ventas(id_prod_a_comprar,id_prod_a_vender,productos_comprados,productos_vendidos, nodo.left());
        BinTree<pair<string,pair<int,int>>> derecha = Obtener_arbol_de_ventas(id_prod_a_comprar,id_prod_a_vender,productos_comprados,productos_vendidos, nodo.right());

        return BinTree<pair<string,pair<int,int>>>(make_pair(id_ciudad,make_pair(productos_comprados,productos_vendidos)),izquierda,derecha);
    }
    else {
        return BinTree<pair<string,pair<int,int>>>();
    }
} 

vector<pair<string,pair<int,int>>> recorido_arbol(const BinTree<pair<string,pair<int,int>>>& nodo){
    if (nodo.empty()) return vector<pair<string,pair<int,int>>>();

    vector<pair<string,pair<int,int>>> recorido_izquierda = recorido_arbol(nodo.left());
    vector<pair<string,pair<int,int>>> recorido_derecha = recorido_arbol(nodo.right());

    int beneficio_izquierda = 0, beneficio_derecha = 0;
    //beneficios por ruta
    if (!recorido_izquierda.empty())
        beneficio_izquierda = recorido_izquierda[recorido_izquierda.size()-1].second.first + recorido_izquierda[recorido_izquierda.size()-1].second.second;
    if (!recorido_derecha.empty())
        beneficio_derecha = recorido_derecha[recorido_derecha.size()-1].second.first + recorido_derecha[recorido_derecha.size()-1].second.second;
    //###################
   
    if (beneficio_derecha < beneficio_izquierda){
        recorido_derecha.push_back(nodo.value());
        return recorido_derecha;
    }
    else if (beneficio_derecha > beneficio_izquierda){
        recorido_izquierda.push_back(nodo.value());
        return recorido_izquierda;
    }
    else {
        if (recorido_derecha.size() < recorido_izquierda.size()){
            recorido_derecha.push_back(nodo.value());
            return recorido_derecha;
        }
        else {
            recorido_izquierda.push_back(nodo.value());
            return recorido_izquierda;
        }
    }
}


void Cuenca::aux_viajar(Cjt_Productos &Productos,Barco& Barco, int id_prod_a_comprar, int id_prod_a_vender, int productos_comprados, int productos_vendidos){
    BinTree<pair<string,pair<int,int>>> Arbol_de_ventas = this->Obtener_arbol_de_ventas(id_prod_a_comprar, id_prod_a_vender, productos_comprados, productos_vendidos, this->_cuenca);

    vector<pair<string,pair<int,int>>> ruta = recorido_arbol(Arbol_de_ventas);
    /*
    this->_cuenca.setInputOutputFormat(3);
    cout << _cuenca <<endl;

    for (int i = 0; i < ruta.size(); i++)
    {
        cout <<ruta[i].first <<": "<<ruta[i].second.first <<": "<<ruta[i].second.second<<endl;
    }
    */
    int aux_productos_a_comprar = productos_comprados;
    int aux_productos_a_vender = productos_vendidos;

    for (unsigned int i = 0; i < ruta.size(); i++)
    {
        pair<string,pair<int,int>> ciudad_actual = ruta[i];
        //cout << "CITY: " << ruta[i].first << endl;
        this->_it_mapa_ciudad = this->_mapa_ciudades.find(ciudad_actual.first);

        pair<int,int> info_prod_a_comprar;
        bool proceder_c = this->_it_mapa_ciudad->second.consultar_prod_c_sin_notificacion_de_errores(id_prod_a_comprar,info_prod_a_comprar);

        pair<int,int> info_prod_a_vender;
        bool proceder_v = this->_it_mapa_ciudad->second.consultar_prod_c_sin_notificacion_de_errores(id_prod_a_vender,info_prod_a_vender);

        if (proceder_c){
            if (aux_productos_a_comprar >= info_prod_a_comprar.second - info_prod_a_comprar.first){
                this->_it_mapa_ciudad->second.modificar_prod_c_sin_notificacion_de_error(Productos,id_prod_a_comprar,info_prod_a_comprar.second,info_prod_a_comprar.second);
                aux_productos_a_comprar -= info_prod_a_comprar.second - info_prod_a_comprar.first;
            }
            else {
                this->_it_mapa_ciudad->second.modificar_prod_c_sin_notificacion_de_error(Productos,id_prod_a_comprar,info_prod_a_comprar.first - aux_productos_a_comprar,info_prod_a_comprar.second);
                aux_productos_a_comprar = 0;
            }
        }
        if (proceder_v){
            if (aux_productos_a_vender >= info_prod_a_comprar.first - info_prod_a_comprar.second){
                this->_it_mapa_ciudad->second.modificar_prod_c_sin_notificacion_de_error(Productos,id_prod_a_comprar,info_prod_a_comprar.second,info_prod_a_comprar.second);
                aux_productos_a_vender -= info_prod_a_comprar.first - info_prod_a_comprar.second;
            }
            else {
                this->_it_mapa_ciudad->second.modificar_prod_c_sin_notificacion_de_error(Productos,id_prod_a_comprar,info_prod_a_comprar.first + aux_productos_a_vender,info_prod_a_comprar.second);
                aux_productos_a_vender = 0;
            }
        }
    }

    if (!ruta.empty()){
        Barco.agregar_ultima_ciudad_consultada(ruta[0].first);
    }

    cout << (productos_comprados - aux_productos_a_comprar) <<" "<< (productos_vendidos - aux_productos_a_vender) <<endl;
}
//#####################################################
void Cuenca::aux_redistribuir(Cjt_Productos& Productos, const BinTree<string>& arbol_cuenca){
    if (arbol_cuenca.empty()) return;

    if (!arbol_cuenca.left().empty()){
        comerciar(Productos,arbol_cuenca.value(),arbol_cuenca.left().value());
        aux_redistribuir(Productos,arbol_cuenca.left());
    }

    if (!arbol_cuenca.right().empty()){
        comerciar(Productos,arbol_cuenca.value(),arbol_cuenca.right().value());
        aux_redistribuir(Productos,arbol_cuenca.right());
    }
}

BinTree<string> Cuenca::aux_lectura_rio(const Cjt_Productos& Productos,map<string,Ciudad>& new_map){ 
    string id_ciudad;
    cin >> id_ciudad;

    // Caso Base
    if (id_ciudad == "#") return BinTree<string>();

    // Caso Inductivo

    BinTree<string> izqueirda = aux_lectura_rio(Productos,new_map);
    BinTree<string> derecha = aux_lectura_rio(Productos,new_map);
    new_map[id_ciudad] = Ciudad();
    return BinTree<string>(id_ciudad,izqueirda,derecha);

}

//FUNCIONES PUBLICAS
Cuenca::Cuenca(){

}

void Cuenca::leer_rio(const Cjt_Productos& Productos ,Barco& Barco){

    map<string,Ciudad> new_map;

    this->_cuenca = aux_lectura_rio(Productos,new_map);

    this->_mapa_ciudades = new_map;
    Barco.borrar_registro_ciudades();
}

void Cuenca::leer_inventario(Cjt_Productos& Productos,string id_ciudad){
    this->_it_mapa_ciudad = this->_mapa_ciudades.find(id_ciudad);
    bool procedemos = true; //Los datos leidos tienen valideza

    if (this->_it_mapa_ciudad == this->_mapa_ciudades.end()) {
        error_notification(2);
        procedemos = false;
    }
    
    int numero_de_elementos;
    int id_producto, unidades_poseidas, unidades_necesarias;

    cin >> numero_de_elementos;

    for (int i = 0; i < numero_de_elementos; i++)
    {
        cin >> id_producto;
        cin >> unidades_poseidas >> unidades_necesarias; 
        
        if (procedemos){
            if (unidades_necesarias > 0){
                _it_mapa_ciudad->second.poner_prod_c(Productos, id_producto,unidades_poseidas,unidades_necesarias);
            }
            else {
                error_notification(6);
            }
        }
    }
    
}

void Cuenca::leer_inventarios(Cjt_Productos& Productos){
    string id;

    while (cin >> id and id!="#")
    {
        leer_inventario(Productos, id);
    }
    
}

void Cuenca::poner_prod(Cjt_Productos& Productos, string id_ciudad, int id_producto){
    int unidades_poseidas, unidades_neccesarias;

    cin >> unidades_poseidas >> unidades_neccesarias;

    this->_it_mapa_ciudad = this->_mapa_ciudades.find(id_ciudad);

    if (unidades_neccesarias > 0){  
        bool proceder = false;

        if (_it_mapa_ciudad != this->_mapa_ciudades.end())
            proceder = _it_mapa_ciudad->second.poner_prod_c(Productos,id_producto,unidades_poseidas,unidades_neccesarias);
        else {
            if ((id_producto <= 0) or (id_producto >= Productos.consultar_num() + 1)) error_notification(1);
            else error_notification(2);
        }

        if (proceder) {
            if (_it_mapa_ciudad == this->_mapa_ciudades.end()) {
                error_notification(2);
            }
            else {
                //Imprimimos el peso y volumen total (PROVISIONAL)
                cout << _it_mapa_ciudad->second.consultar_peso_total();
                cout <<" ";
                cout << _it_mapa_ciudad->second.consultar_volumen_total();
                cout<<endl;
            }
        } 
    }
    else {
        error_notification(6);
    }
}

void Cuenca::modificar_prod(Cjt_Productos& Productos, string id_ciudad, int id_producto){

    int unidades_poseidas, unidades_neccesarias;

    cin >> unidades_poseidas >> unidades_neccesarias;

    this->_it_mapa_ciudad = this->_mapa_ciudades.find(id_ciudad);
    
    if (unidades_neccesarias > 0){
        bool proceder = false;

        if (_it_mapa_ciudad != this->_mapa_ciudades.end())
            proceder = _it_mapa_ciudad->second.modificar_prod_c(Productos,id_producto,unidades_poseidas,unidades_neccesarias);
        else {
            if ((id_producto <= 0) or (id_producto >= Productos.consultar_num() + 1)) error_notification(1);
            else error_notification(2);
        }

        if (proceder){
            if (_it_mapa_ciudad == this->_mapa_ciudades.end()) {
                error_notification(2);
            }
            else {
                //Imprimimos el peso y volumen total (PROVISIONAL)
                cout << _it_mapa_ciudad->second.consultar_peso_total();
                cout <<" ";
                cout << _it_mapa_ciudad->second.consultar_volumen_total();
                cout<<endl;
            }
        }
    }
    else {
        error_notification(6);
    }
    
}

void Cuenca::quitar_prod(Cjt_Productos& Productos, string id_ciudad, int id_producto){

    if ((id_producto <= 0) or (id_producto >= Productos.consultar_num() + 1)) {
        error_notification(1);
        //Informacion no valida con errores
        return;
    }
    
    this->_it_mapa_ciudad = this->_mapa_ciudades.find(id_ciudad);
    
    if (_it_mapa_ciudad == this->_mapa_ciudades.end()) {
        error_notification(2);
        return;
    }

    bool proceder = _it_mapa_ciudad->second.quitar_prod_c(Productos,id_producto);
    
    if (proceder){
        //Imprimimos el peso y volumen total (PROVISIONAL)
        cout << _it_mapa_ciudad->second.consultar_peso_total();
        cout <<" ";
        cout << _it_mapa_ciudad->second.consultar_volumen_total();
        cout<<endl;
    }   
}

void Cuenca::consultar_prod(const Cjt_Productos& Productos, string id_ciudad, int id_producto){

    if ((id_producto <= 0) or (id_producto >= Productos.consultar_num() + 1)) {
        error_notification(1);
        //Informacion no valida con errores
        return;
    }

    this->_it_mapa_ciudad = this->_mapa_ciudades.find(id_ciudad);

    if (_it_mapa_ciudad == this->_mapa_ciudades.end()) {
        error_notification(2);
        return;
    }

    pair<int,int> pair_unidades_poseidas_necesarias;
    bool proceder = this->_it_mapa_ciudad->second.consultar_prod_c(id_producto,pair_unidades_poseidas_necesarias);

    if (proceder){
        //Imprimimos las unidades disponibles y neccesarias (PROVISIONAL)
        cout << pair_unidades_poseidas_necesarias.first;
        cout <<" ";
        cout << pair_unidades_poseidas_necesarias.second;
        cout<<endl;
    }   
}

void Cuenca::consultar_prod_c_sin_notificacion_de_errores(const Cjt_Productos& Productos, string id_ciudad, int id_producto){

    if ((id_producto <= 0) or (id_producto >= Productos.consultar_num() + 1)) {
        //Informacion no valida con errores
        return;
    }

    this->_it_mapa_ciudad = this->_mapa_ciudades.find(id_ciudad);

    if (_it_mapa_ciudad == this->_mapa_ciudades.end()) {
        return;
    }

    pair<int,int> pair_unidades_poseidas_necesarias;
    this->_it_mapa_ciudad->second.consultar_prod_c_sin_notificacion_de_errores(id_producto,pair_unidades_poseidas_necesarias);
}

void Cuenca::escribir_ciudad(string id_ciudad) const{
    map<string,Ciudad> ::const_iterator _it_mapa_ciudad_aux;

    _it_mapa_ciudad_aux = this->_mapa_ciudades.find(id_ciudad);

    if (_it_mapa_ciudad_aux == this->_mapa_ciudades.end()) {
        error_notification(2);
        return;
    }
   
    _it_mapa_ciudad_aux->second.escribir_ciudad_c();
}

void Cuenca::comerciar(Cjt_Productos& Productos, string id_ciudad_1, string id_ciudad_2){
    this->_it_mapa_ciudad = this->_mapa_ciudades.find(id_ciudad_1);
    map<string,Ciudad> ::iterator it_mapa_ciudad_2 = this->_mapa_ciudades.find(id_ciudad_2);

    if (this->_it_mapa_ciudad == this->_mapa_ciudades.end()){
        error_notification(2);
        return;
    }

    if (it_mapa_ciudad_2 == this->_mapa_ciudades.end()){
        error_notification(2);
        return;
    }

    if (id_ciudad_1 == id_ciudad_2){
        error_notification(9);
        return;
    }
    
    this->_it_mapa_ciudad->second.comerciar_c(Productos,it_mapa_ciudad_2->second);
}

void Cuenca::hacer_viaje(Cjt_Productos& Productos, Barco& Barco){
    int productos_comprados = Barco.consultat_cantidad_a_comprar();
    int productos_vendidos = Barco.consultat_cantidad_a_vender();

    this->aux_viajar(Productos,Barco,Barco.cons_id_producto_a_comprar(),Barco.cons_id_producto_a_vender(),productos_comprados,productos_vendidos);
}

void Cuenca::redistribuir(Cjt_Productos& Productos){
    aux_redistribuir(Productos, this->_cuenca);
}
