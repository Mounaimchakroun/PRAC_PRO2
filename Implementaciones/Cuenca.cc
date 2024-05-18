/** @file Cuenca.cc
    @brief Implementación de Cuenca.
*/

#include "Cuenca.hh"


//FUNCIONES PRIVADAS
//#####################################################

BinTree<pair<int,int>> Cuenca::Obtener_arbol_de_ventas(int id_prod_a_comprar, int id_prod_a_vender, int productos_a_comprar, int productos_a_vender, const BinTree<string>& nodo){
    // Caso Base ########################################################################################
    if (nodo.empty()) return BinTree<pair<int,int>>(); //Si el nodo es vacío
    if (productos_a_comprar == 0 and productos_a_vender == 0) return BinTree<pair<int,int>>(); //No hay mas productos que vender

    this->_it_mapa_ciudad = this->_mapa_ciudades.find(nodo.value()); //Buscamos la ciudad actual

    Ciudad ciudad_seleccionada = this->_it_mapa_ciudad->second; //Obtenemos la ciudad actual

    //Obtenemos las cantidades poseidas y neccesarias del producto que el barco quiere comprar y vender.
    pair<int,int> info_produ_comprar;
    bool proceder_c = ciudad_seleccionada.consultar_prod_c_sin_notificacion_de_errores(id_prod_a_comprar,info_produ_comprar);

    pair<int,int> info_produ_vender;
    bool proceder_v = ciudad_seleccionada.consultar_prod_c_sin_notificacion_de_errores(id_prod_a_vender,info_produ_vender);

    //Variable de productos comprados y vendidos
    int total_productos_comprados = 0;
    int total_productos_vendidos = 0;
    //Prodedemos los calculos

    //Calculo de productos comprados en cada ciudad
    if (proceder_c)
    {
        int productos_sobrantes = info_produ_comprar.first - info_produ_comprar.second; //Obtenemos la cantidad que sobra
        if (productos_sobrantes > 0){
            if (productos_sobrantes >= productos_a_comprar){
                total_productos_comprados = productos_a_comprar;
                productos_a_comprar = 0;
            }
            else {
                total_productos_comprados = productos_sobrantes;
                productos_a_comprar -= productos_sobrantes;
            }
        }
    }

    //Calculo de productos vendidos en cada ciudad
    if (proceder_v)
    {
        int productos_neccesarios = info_produ_vender.second - info_produ_vender.first; //Obtenemos la cantidad que neccesita
        if (productos_neccesarios > 0){
            if (productos_neccesarios >= productos_a_vender){
                total_productos_vendidos = productos_a_vender;
                productos_a_vender = 0;
            }
            else {
                total_productos_vendidos = productos_neccesarios;
                productos_a_vender -= productos_neccesarios;
            }
        }
    }

    pair<int,int> beneficio;
    beneficio.first = total_productos_comprados;
    beneficio.second = total_productos_vendidos;

    BinTree<pair<int,int>> arbol_izqueirda = Obtener_arbol_de_ventas(id_prod_a_comprar,id_prod_a_vender,productos_a_comprar,productos_a_vender,nodo.left());
    BinTree<pair<int,int>> arbol_derecha = Obtener_arbol_de_ventas(id_prod_a_comprar,id_prod_a_vender,productos_a_comprar,productos_a_vender,nodo.right());

    return BinTree<pair<int,int>>(beneficio,arbol_izqueirda,arbol_derecha);
}


list<pair<char,int>> recorido_arbol(const BinTree<pair<int,int>>& nodo){
    if (nodo.empty()) return list<pair<char,int>>();

    list<pair<char,int>> recorido_izquierda = recorido_arbol(nodo.left());
    list<pair<char,int>> recorido_derecha = recorido_arbol(nodo.right());

    int beneficio_izquierda = 0, beneficio_derecha = 0;
    //beneficios por ruta
    if (!recorido_izquierda.empty()) beneficio_izquierda = recorido_izquierda.front().second;
    if (!recorido_derecha.empty()) beneficio_derecha = recorido_derecha.front().second;
    //###################

    int beneficio_nodo_actual = nodo.value().first + nodo.value().second;

    if (beneficio_izquierda + beneficio_derecha == 0) {
        list<pair<char,int>> lista_unica;
        lista_unica.push_front(make_pair('d',beneficio_nodo_actual));
        return lista_unica;
    }

    if (beneficio_derecha > beneficio_izquierda){
        if (!recorido_derecha.empty()) beneficio_nodo_actual += recorido_derecha.begin()->second; //Incrementamos el beneficio
        recorido_derecha.push_front(make_pair('d',beneficio_nodo_actual));
        return recorido_derecha;
    }
    else if (beneficio_derecha < beneficio_izquierda){
        if (!recorido_izquierda.empty()) beneficio_nodo_actual += recorido_izquierda.begin()->second; //Incrementamos el beneficio
        recorido_izquierda.push_front(make_pair('i',beneficio_nodo_actual));
        return recorido_izquierda;
    }
    else {
        if (recorido_derecha.size() < recorido_izquierda.size()){
            if (!recorido_derecha.empty()) beneficio_nodo_actual += recorido_derecha.begin()->second; //Incrementamos el beneficio
            recorido_derecha.push_front(make_pair('d',beneficio_nodo_actual));
            return recorido_derecha;
        }
        else {
            if (!recorido_izquierda.empty()) beneficio_nodo_actual += recorido_izquierda.begin()->second; //Incrementamos el beneficio
            recorido_izquierda.push_front(make_pair('i',beneficio_nodo_actual));
            return recorido_izquierda;
        }
    }
}


void Cuenca::aux_viajar(Cjt_Productos &Productos,Barco& Barco, int id_prod_a_comprar, int id_prod_a_vender){
    int productos_a_comprar = Barco.consultat_cantidad_a_comprar();
    int productos_a_vender = Barco.consultat_cantidad_a_vender();
    Productos.consultar_num();
    BinTree<pair<int,int>> Arbol_de_ventas = this->Obtener_arbol_de_ventas(id_prod_a_comprar, id_prod_a_vender,productos_a_comprar,productos_a_vender,this->_cuenca);
    list<pair<char,int>> ruta = recorido_arbol(Arbol_de_ventas);

    list<pair<char,int>> ::iterator it_list = ruta.begin();

    int aux_productos_a_comprar = productos_a_comprar;
    int aux_productos_a_vender = productos_a_vender;

    int beneficio_total = 0;

    BinTree<string> nodo_actual = this->_cuenca;
    string ultima_ciudad = "#";

    while ((aux_productos_a_comprar + aux_productos_a_vender > 0) and (it_list != ruta.end()) and (!nodo_actual.empty()))
    {
        ultima_ciudad = nodo_actual.value();
        this->_it_mapa_ciudad = this->_mapa_ciudades.find(nodo_actual.value()); //Buscamos la ciudad actual

        pair<int,int> info_produ_comprar;
        bool proceder_c = this->_it_mapa_ciudad->second.consultar_prod_c_sin_notificacion_de_errores(id_prod_a_comprar,info_produ_comprar);

        pair<int,int> info_produ_vender;
        bool proceder_v = this->_it_mapa_ciudad->second.consultar_prod_c_sin_notificacion_de_errores(id_prod_a_vender,info_produ_vender);

        if (proceder_c)
        {
            int productos_sobrantes = info_produ_comprar.first - info_produ_comprar.second; //Obtenemos la cantidad que sobra
            if (productos_sobrantes > 0){
                if (productos_sobrantes >= productos_a_comprar){
                    this->_it_mapa_ciudad->second.modificar_prod_c_sin_notificacion_de_error(Productos,id_prod_a_comprar,info_produ_comprar.first - productos_a_comprar,info_produ_comprar.second);
                    beneficio_total += productos_a_comprar;
                    aux_productos_a_comprar = 0;
                }
                else {
                    beneficio_total += productos_a_comprar;
                    this->_it_mapa_ciudad->second.modificar_prod_c_sin_notificacion_de_error(Productos,id_prod_a_comprar,info_produ_comprar.first - productos_sobrantes,info_produ_comprar.second);
                    aux_productos_a_comprar -= productos_sobrantes;
                }
            }
        }

        //Calculo de productos vendidos en cada ciudad
        if (proceder_v)
        {
            int productos_neccesarios = info_produ_vender.second - info_produ_vender.first; //Obtenemos la cantidad que neccesita
            if (productos_neccesarios > 0){
                if (productos_neccesarios >= productos_a_vender){
                    this->_it_mapa_ciudad->second.modificar_prod_c_sin_notificacion_de_error(Productos,id_prod_a_vender,info_produ_vender.first + productos_a_vender,info_produ_vender.second);
                    beneficio_total += productos_a_vender;
                    aux_productos_a_vender = 0;
                }
                else {
                    this->_it_mapa_ciudad->second.modificar_prod_c_sin_notificacion_de_error(Productos,id_prod_a_vender,info_produ_vender.first + productos_neccesarios,info_produ_vender.second);
                    beneficio_total += productos_neccesarios;
                    aux_productos_a_vender -= productos_neccesarios;
                }
            }
        }

        if (it_list->first == 'i'){
            nodo_actual = nodo_actual.left();
        }
        else {
            nodo_actual = nodo_actual.right();
        }
        it_list++;
    }

    cout << beneficio_total <<endl;
    if (beneficio_total > 0) Barco.agregar_ultima_ciudad_consultada(ultima_ciudad);

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
    this->aux_viajar(Productos,Barco,Barco.cons_id_producto_a_comprar(),Barco.cons_id_producto_a_vender());
}

void Cuenca::redistribuir(Cjt_Productos& Productos){
    aux_redistribuir(Productos, this->_cuenca);
}
