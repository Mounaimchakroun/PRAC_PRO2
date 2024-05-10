#include "Cuenca.hh"


//FUNCIONES PRIVADAS

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
/*
list<string> Cuenca::recorido_con_max_veneficio(const Cjt_Productos& Productos, const BinTree<string>& arbol_cuenca, const Barco& Barco){
    if (arbol_cuenca.empty()) return list<string>(); //Cas Base

    bool proceder_1_c = false; bool proceder_1_v = false;
    bool proceder_2_c = false; bool proceder_2_v = false;
    int productos_transferidos_derecha, productos_transferidos_izquierda;

    list<string> recorido_izquiera =  recorido_con_max_veneficio(Productos,arbol_cuenca.left(),Barco);

    list<string> recorido_derecha = recorido_con_max_veneficio(Productos,arbol_cuenca.right(),Barco);

    if (!arbol_cuenca.left().empty()){
        int veneficio_compra = 0;   int veneficio_venta = 0;
        
        pair<int,int> pair_unidades_poseidas_necesarias;
        this->_it_mapa_ciudad = this->_mapa_ciudades.find(arbol_cuenca.left().value());

        proceder_1_c = this->_it_mapa_ciudad->second.consultar_prod_c(Productos,Barco.cons_id_producto_a_comprar(),pair_unidades_poseidas_necesarias);
        
        if (proceder_1_c) veneficio_compra = pair_unidades_poseidas_necesarias.first - pair_unidades_poseidas_necesarias.second; //Producto que le sobra

        proceder_1_v = this->_it_mapa_ciudad->second.consultar_prod_c(Productos,Barco.cons_id_producto_a_vender(),pair_unidades_poseidas_necesarias);
        if (proceder_1_v) veneficio_venta = pair_unidades_poseidas_necesarias.second - pair_unidades_poseidas_necesarias.first; //Producto que neccesita

        productos_transferidos_izquierda = veneficio_compra + veneficio_venta;
    }
    
    if (!arbol_cuenca.right().empty()){
        int veneficio_compra = 0;   int veneficio_venta = 0;
        
        pair<int,int> pair_unidades_poseidas_necesarias;
        this->_it_mapa_ciudad = this->_mapa_ciudades.find(arbol_cuenca.right().value());

        proceder_1_c = this->_it_mapa_ciudad->second.consultar_prod_c(Productos,Barco.cons_id_producto_a_comprar(),pair_unidades_poseidas_necesarias);
        
        if (proceder_1_c) veneficio_compra = pair_unidades_poseidas_necesarias.first - pair_unidades_poseidas_necesarias.second; //Producto que le sobra

        proceder_1_v = this->_it_mapa_ciudad->second.consultar_prod_c(Productos,Barco.cons_id_producto_a_vender(),pair_unidades_poseidas_necesarias);
        if (proceder_1_v) veneficio_venta = pair_unidades_poseidas_necesarias.second - pair_unidades_poseidas_necesarias.first; //Producto que neccesita

        productos_transferidos_derecha = veneficio_compra + veneficio_venta;
    }
    
    if (!arbol_cuenca.right().empty() and !arbol_cuenca.left().empty()){

    
        if (productos_transferidos_izquierda < productos_transferidos_derecha){
            recorido_derecha.push_front(arbol_cuenca.right().value());
            return recorido_derecha;
        }
        else if (productos_transferidos_izquierda == productos_transferidos_derecha){
            if (recorido_izquiera.size() < recorido_derecha.size()) {
                recorido_derecha.push_front(arbol_cuenca.right().value());
                return recorido_derecha;
            }
            else {
                recorido_izquiera.push_front(arbol_cuenca.left().value());
                return recorido_izquiera;
            }
        }
        else {
            recorido_izquiera.push_front(arbol_cuenca.left().value());
            return recorido_izquiera;
        }
    }
    else if (!arbol_cuenca.right().empty()){
        recorido_derecha.push_front(arbol_cuenca.right().value());
        return recorido_derecha;
    }
    else if (!arbol_cuenca.left().empty()){
        recorido_izquiera.push_front(arbol_cuenca.left().value());
        return recorido_izquiera;
    }
    
    return list<string>();
}
*/
void Cuenca::aux_viajar(const BinTree<string>& arbol, vector<string>& my_vector, int id_prod_a_comprar, int id_prod_a_vender, int& productos_comprados, int& productos_vendidos){

    if (arbol.empty()) return;
    //Si obtenemos un false -> no hay productos que vender ni espacio para comprar productos
    if (productos_comprados + productos_vendidos > 0){ 
        
        this->_it_mapa_ciudad = this->_mapa_ciudades.find(arbol.value());
        pair<int,int> info_prod_comp;   pair<int,int> info_prod_vend;

        bool existe_prod_comp = this->_it_mapa_ciudad->second.consultar_prod_c(id_prod_a_comprar,info_prod_comp);
        bool existe_prod_vend = this->_it_mapa_ciudad->second.consultar_prod_c(id_prod_a_vender,info_prod_vend);

        int prod_comp_desp_ciudad = productos_comprados, prod_vend_desp_ciudad = productos_vendidos;

        if (existe_prod_comp){
            int diferencia_comp = info_prod_comp.first - info_prod_comp.second;
            if (diferencia_comp > 0){
                prod_comp_desp_ciudad -= diferencia_comp;
            }
        }

        if (existe_prod_vend){
            int diferencia_vent = info_prod_vend.second - info_prod_vend.first;
            if (diferencia_vent > 0){
                prod_vend_desp_ciudad -= diferencia_vent;
            }
        }
        //------
        cout << prod_comp_desp_ciudad <<" "<< prod_vend_desp_ciudad<<endl;
        //------
        my_vector.push_back(arbol.value());

        vector<string> vect_iz, vect_der;
        int productos_comprados_iz = prod_comp_desp_ciudad, productos_vendidos_iz = prod_vend_desp_ciudad;
        int productos_comprados_der = prod_comp_desp_ciudad, productos_vendidos_der = prod_vend_desp_ciudad;

        aux_viajar(arbol.left(),vect_iz,id_prod_a_comprar,id_prod_a_vender,productos_comprados_iz,productos_vendidos_iz);
        aux_viajar(arbol.right(),vect_der,id_prod_a_comprar,id_prod_a_vender,productos_comprados_der,productos_vendidos_der);

        if (productos_comprados_iz + productos_vendidos_iz < productos_comprados_der + productos_vendidos_der){
            int pos_i = 0;

            while (pos_i < vect_iz.size())
            {
                my_vector.push_back(vect_iz[pos_i]);
                pos_i++;
            }
            return;
        }
        else if (productos_comprados_iz + productos_vendidos_iz > productos_comprados_der + productos_vendidos_der){
            int pos_i = 0;

            while (pos_i < vect_der.size())
            {
                my_vector.push_back(vect_der[pos_i]);
                pos_i++;
            }
            return;
        }
        else { //iguals
            if (vect_iz.size() > vect_der.size()){
                int pos_i = 0;

                while (pos_i < vect_der.size())
                {
                    my_vector.push_back(vect_der[pos_i]);
                    pos_i++;
                }
                return;
            }
            else {
                int pos_i = 0;

                while (pos_i < vect_iz.size())
                {
                    my_vector.push_back(vect_iz[pos_i]);
                    pos_i++;
                }
                return;
            }
        }
        
    }
    return;

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
    
    this->_it_mapa_ciudad->second.comerciar_c(Productos,it_mapa_ciudad_2->second);
}

void Cuenca::hacer_viaje(const Cjt_Productos& Productos, const Barco& Barco){
    //----------
    int i = Productos.consultar_num();
    i++;
    //---------
    vector<string> ruta;
    int prod_comp = Barco.consultat_cantidad_a_comprar();
    int prod_venta = Barco.consultat_cantidad_a_vender(); 

    aux_viajar(this->_cuenca,ruta,Barco.cons_id_producto_a_comprar(),Barco.cons_id_producto_a_vender(),prod_comp,prod_venta);
    
    for (int i = 0; i < ruta.size(); i++)
    {
        cout << ruta[i]<<endl;
    }
    
}

void Cuenca::redistribuir(Cjt_Productos& Productos){
    aux_redistribuir(Productos, this->_cuenca);
}

