/** @file Cuenca.cc
    @brief Implementación de Cuenca.
*/

#include "Cuenca.hh"


//FUNCIONES PRIVADAS

//########## VIAJAR ########################################
BinTree<pair<int,int>> Cuenca::obtener_arbol_de_beneficios(int id_prod_a_comprar, int id_prod_a_vender, int productos_a_comprar, int productos_a_vender, const BinTree<string>& nodo){
    // Caso Base ########################################################################################
    
    // Si el nodo es vacío
    if (nodo.empty()) return BinTree<pair<int,int>>();

    // No hay más productos que vender
    if (productos_a_comprar + productos_a_vender == 0) return BinTree<pair<int,int>>();

    // Paso Inductivo ###################################################################################

    // Buscamos la ciudad actual
    this->_it_mapa_ciudad = this->_mapa_ciudades.find(nodo.value()); 

    // Obtenemos la ciudad actual
    Ciudad ciudad_seleccionada = this->_it_mapa_ciudad->second; 

    // Obtenemos las cantidades poseídas y necesarias del producto que el barco quiere comprar y vender.
    pair<int,int> info_produ_comprar;
    bool proceder_c = ciudad_seleccionada.consultar_prod_c(id_prod_a_comprar,info_produ_comprar, false);

    pair<int,int> info_produ_vender;
    bool proceder_v = ciudad_seleccionada.consultar_prod_c(id_prod_a_vender,info_produ_vender, false);
    //-------------------------------------------------------------------------------------------------

    // Variable de productos comprados y vendidos
    int total_productos_comprados = 0;
    int total_productos_vendidos = 0;
    //-------------------------------------------

    // Procedemos los cálculos:

    // Cálculo de productos comprados en cada ciudad
    if ((proceder_c) and (productos_a_comprar > 0))
    {
        // Obtenemos la cantidad que sobra
        int productos_sobrantes = info_produ_comprar.first - info_produ_comprar.second; 
        // Sí sobran productos a la ciudad
        if (productos_sobrantes > 0){
            // Si podemos comprar todos los productos que barco quiere en una ciudad, entonces compramos todo lo que necesitamos
            if (productos_sobrantes >= productos_a_comprar){
                total_productos_comprados = productos_a_comprar;
                productos_a_comprar = 0;
            }
            else { // De lo contrario compraremos los productos que podamos
                total_productos_comprados = productos_sobrantes;
                productos_a_comprar -= productos_sobrantes;
            }
        }
    }

    // Cálculo de productos vendidos en cada ciudad
    if ((proceder_v) and (productos_a_vender > 0))
    {
        // Obtenemos la cantidad que necesita
        int productos_neccesarios = info_produ_vender.second - info_produ_vender.first; 
        // Si podemos vender todos los productos que barco quiere en una ciudad, entonces venderemos todo lo que neccesite
        if (productos_neccesarios > 0){
            if (productos_neccesarios >= productos_a_vender){
                total_productos_vendidos = productos_a_vender;
                productos_a_vender = 0;
            }
            else { // De lo contrario venderemos los productos que podamos
                total_productos_vendidos = productos_neccesarios;
                productos_a_vender -= productos_neccesarios;
            }
        }
    }

    // Construimos un "pair" con las compras y ventas realizadas en la ciudad
    pair<int,int> beneficio;

    beneficio.first = total_productos_comprados;
    beneficio.second = total_productos_vendidos;
    //-----------------------------------------------------------------------

    // Realizamos el recorrido recursivo por la izquierda y después por la derecha
    BinTree<pair<int,int>> arbol_izqueirda = obtener_arbol_de_beneficios(id_prod_a_comprar,id_prod_a_vender,productos_a_comprar,productos_a_vender,nodo.left());
    BinTree<pair<int,int>> arbol_derecha = obtener_arbol_de_beneficios(id_prod_a_comprar,id_prod_a_vender,productos_a_comprar,productos_a_vender,nodo.right());

    // Devolvemos un árbol con el beneficio conseguido en la ciudad y con su árbol izquierdo y derecho
    return BinTree<pair<int,int>>(beneficio,arbol_izqueirda,arbol_derecha);
}


list<pair<char,int>> Cuenca::recorrido_con_max_beneficio(const BinTree<pair<int,int>>& nodo){
    // Caso Base ########################################################################################

    // Si el nodo es vacío
    if (nodo.empty()) return list<pair<char,int>>();

    // Paso Inductivo ###################################################################################

    // Construimos las listas postorden
    list<pair<char,int>> recorido_izquierda = recorrido_con_max_beneficio(nodo.left());
    list<pair<char,int>> recorido_derecha = recorrido_con_max_beneficio(nodo.right());
    //---------------------------------

    // Inicializamos los beneficios por ruta
    int beneficio_izquierda = 0, beneficio_derecha = 0;

    // Beneficios por ruta
    if (!recorido_izquierda.empty()) beneficio_izquierda = recorido_izquierda.front().second;
    if (!recorido_derecha.empty()) beneficio_derecha = recorido_derecha.front().second;
    //--------------------

    // Calculamos el beneficio en nuestra posición
    int beneficio_nodo_actual = nodo.value().first + nodo.value().second;

    // Distinguimos por diferentes casos:

    // En caso de que el beneficio de la parte izquierda y la parte derecha sea 0, entonces finalizamos la función
    if (beneficio_izquierda + beneficio_derecha == 0) {
        // Devolvemos la lista formada únicamente por un elemento
        list<pair<char,int>> lista_unica;
        // Char u -> Representa una única ciudad en la lista
        lista_unica.push_front(make_pair('u',beneficio_nodo_actual));
        return lista_unica;
    }

    // Si el beneficio de la derecha es mayor que el de la izquierda
    if (beneficio_derecha > beneficio_izquierda){
        // Si beneficio_derecha és mayor que beneficio_izquierda quiere decir que es mayor que 0 en el peor de los casos cosa que quiere decir que existe.

        // Incrementamos el beneficio
        beneficio_nodo_actual += recorido_derecha.front().second;
        // Añadimos el nuevo nodo y la dirección por la que debemos ir
        recorido_derecha.push_front(make_pair('d',beneficio_nodo_actual));
        // Devolvemos el recorrido hecho
        return recorido_derecha;

    } // Si el beneficio de la izquierda es mayor que el de la derecha
    else if (beneficio_derecha < beneficio_izquierda){
        // Si beneficio_izquierda és mayor que beneficio_izquierda quiere decir que es mayor que 0 en el peor de los casos cosa que quiere decir que existe.

        // Incrementamos el beneficio
        beneficio_nodo_actual += recorido_izquierda.front().second;
        // Añadimos el nuevo nodo y la dirección por la que debemos ir
        recorido_izquierda.push_front(make_pair('i',beneficio_nodo_actual));
        // Devolvemos el recorrido hecho
        return recorido_izquierda;
    }
    else { // Si el beneficio de la izquierda es igual que el de la derecha
        // Miramos el recorrido más corto de los dos, si son iguales escogeremos el de la izquierda
        // Si el recorrido de la derecha es más pequeño que el de la izquierda
        if (recorido_derecha.size() < recorido_izquierda.size()){
            // Entonces, como existe el recorrido por la derecha: (Explicado arriba)
            // Incrementamos el beneficio
            beneficio_nodo_actual += recorido_derecha.front().second; //Incrementamos el beneficio
            // Añadimos el nuevo nodo y la dirección por la que debemos ir
            recorido_derecha.push_front(make_pair('d',beneficio_nodo_actual));
            // Devolvemos el recorrido hecho
            return recorido_derecha;
        }
        else { // Si el recorrido de la izquierda es más pequeño o igual que el de la derecha
            // Entonces, si existe el recorrido por la izquierda
            // Incrementamos el beneficio
            if (!recorido_izquierda.empty()) beneficio_nodo_actual += recorido_izquierda.front().second; //Incrementamos el beneficio
            // Añadimos el nuevo nodo y la dirección por la que debemos ir
            recorido_izquierda.push_front(make_pair('i',beneficio_nodo_actual));
            // Devolvemos el recorrido hecho
            return recorido_izquierda;
        }
    }
}

void Cuenca::aux_viajar(Cjt_Productos &Productos,Barco& Barco, int id_prod_a_comprar, int id_prod_a_vender){
    // Consultamos las cantidades a comprar y vender
    int productos_a_comprar = Barco.consultar_cantidad_a_comprar();
    int productos_a_vender = Barco.consultar_cantidad_a_vender();
    //----------------------------------------------
    // Obtenemos el árbol de beneficios
    BinTree<pair<int,int>> Arbol_de_ventas = this->obtener_arbol_de_beneficios(id_prod_a_comprar, id_prod_a_vender,productos_a_comprar,productos_a_vender,this->_cuenca);
    // A partir del árbol de beneficios obtenemos la ruta más beneficiosa
    list<pair<char,int>> ruta = recorrido_con_max_beneficio(Arbol_de_ventas);
    // Creamos un "iterdador" para consultar la ruta obtenida
    list<pair<char,int>> ::const_iterator it_list = ruta.begin();

    // Auxiliares que representan los productos que el barco quiere comprar y vender
    int aux_productos_a_comprar = productos_a_comprar;
    int aux_productos_a_vender = productos_a_vender;
    //------------------------------------------------------------------------------
    // Beneficio total de la ruta
    int beneficio_total = 0;
    // Primera ciudad a consultar
    BinTree<string> nodo_actual = this->_cuenca;
    // Última ciudad consultada
    string ultima_ciudad = "#";

    // Bucle dedicado a la modificación de los productos de las ciudades de la ruta
    //|Si aún hay productos que comprar y vender en el barco| |No hemos llegado al final de la ruta| |El nodo actual existe|
    while ((aux_productos_a_comprar + aux_productos_a_vender > 0) and (it_list != ruta.end()) and (!nodo_actual.empty()))
    {
        // Actualizamos la última ciudad consultada
        ultima_ciudad = nodo_actual.value();

        // Buscamos la ciudad cuyo nombre lo contiene el nodo
        this->_it_mapa_ciudad = this->_mapa_ciudades.find(nodo_actual.value()); //Buscamos la ciudad actual

        // Obtenemos la informacion necesaria del producto a comprar y vender
        pair<int,int> info_produ_comprar;
        bool proceder_c = this->_it_mapa_ciudad->second.consultar_prod_c(id_prod_a_comprar,info_produ_comprar, false);
        

        pair<int,int> info_produ_vender;
        bool proceder_v = this->_it_mapa_ciudad->second.consultar_prod_c(id_prod_a_vender,info_produ_vender, false);  
        
        //-------------------------------------------------------------------
        // Si el producto a comprar existe y lo tiene la ciudad
        if ((proceder_c) and (aux_productos_a_comprar > 0))
        {
            // Obtenemos la cantidad que sobra de la ciudad
            int productos_sobrantes = info_produ_comprar.first - info_produ_comprar.second; 
            // Si a la ciudad le sobra el producto
            if (productos_sobrantes > 0){
                // Si la cantidad que sobra es mayor a la que podemos comprar compraremos todo lo que podamos
                if (productos_sobrantes >= aux_productos_a_comprar){
                    // Modificamos las cantidades del inventario de la ciudad
                    this->_it_mapa_ciudad->second.modificar_prod_c(Productos,id_prod_a_comprar,info_produ_comprar.first - aux_productos_a_comprar,info_produ_comprar.second, false);
                    // Incrementamos el beneficio total
                    beneficio_total += aux_productos_a_comprar;
                    // Como hemos comprado todo lo que necesitamos ya no compraremos más
                    aux_productos_a_comprar = 0;
                }
                else { // Si la cantidad que sobra es menor a la que podemos comprar compraremos todo el producto que sobre
                    // Incrementamos el beneficio total
                    beneficio_total += productos_sobrantes;
                    // Modificamos las cantidades del inventario de la ciudad
                    this->_it_mapa_ciudad->second.modificar_prod_c(Productos,id_prod_a_comprar,info_produ_comprar.first - productos_sobrantes,info_produ_comprar.second, false);
                    // Decrementamos la cantidad que hemos comprado
                    aux_productos_a_comprar -= productos_sobrantes;
                }
            }
        }

        // Cálculo de productos vendidos en cada ciudad
        if (proceder_v and (aux_productos_a_vender > 0)){   
            // Obtenemos la cantidad que necesita
            int productos_neccesarios = info_produ_vender.second - info_produ_vender.first; 
            // Si a la ciudad necesita el producto
            if (productos_neccesarios > 0){
                // Si la cantidad que necesita es mayor a la que podemos vender venderemos todo lo que podamos
                if (productos_neccesarios >= aux_productos_a_vender){
                    // Modificamos las cantidades del inventario de la ciudad
                    this->_it_mapa_ciudad->second.modificar_prod_c(Productos,id_prod_a_vender,info_produ_vender.first + aux_productos_a_vender,info_produ_vender.second, false);
                    // Incrementamos el beneficio total
                    beneficio_total += aux_productos_a_vender;
                    // Como hemos vendido todo lo que queríamos ya no venderemos más
                    aux_productos_a_vender = 0;
                }
                else { // Si la cantidad que necesita es menor a la que podemos vender venderemos todo el producto que necesita
                    // Modificamos las cantidades del inventario de la ciudad
                    this->_it_mapa_ciudad->second.modificar_prod_c(Productos,id_prod_a_vender,info_produ_vender.first + productos_neccesarios,info_produ_vender.second, false);
                    // Incrementamos el beneficio total
                    beneficio_total += productos_neccesarios;
                    // Decrementamos la cantidad que hemos vendido
                    aux_productos_a_vender -= productos_neccesarios;
                }
            }
        }

        // Seguimos por la ruta, si el char es 'i' iremos por la izquierda, de lo contrario por la derecha. 
        // Si no es ni 'i' ni 'd' entonces es 'u' y esto significa que es una lista de única ciudad, es decir,
        // finalizamos la ruta.

        if (it_list->first == 'i'){
            nodo_actual = nodo_actual.left();
            // Incrementamos el iterador
            it_list++;
        }
        else if (it_list->first == 'd'){
            nodo_actual = nodo_actual.right();
            // Incrementamos el iterador
            it_list++;
        }
        else if (it_list->first == 'u'){
            it_list = ruta.end();
        }
    }
    // Imprimimos el beneficio total
    cout << beneficio_total <<endl;
    // Si el beneficio es 0 quiere decir que el barco no modifica a ninguna ciudad y no tendremos que
    // añadir ninguna ciudad al registro del barco
    if (beneficio_total > 0) Barco.agregar_ultima_ciudad_consultada(ultima_ciudad);

}
//############# VIAJAR #########################################

void Cuenca::aux_redistribuir(Cjt_Productos& Productos, const BinTree<string>& arbol_cuenca){
    // Si el nodo actual es vacío -> Finalizamos
    if (arbol_cuenca.empty()) return;
    // Si el árbol izquierdo existe, entonces podemos comerciar con este
    if (!arbol_cuenca.left().empty()){
        // Comerciamos con el árbol izquierdo
        comerciar(Productos,arbol_cuenca.value(),arbol_cuenca.left().value());
        // Redistribuimos desde el árbol izquierdo a sus hijos
        aux_redistribuir(Productos,arbol_cuenca.left());
    }
    // Si el árbol derecho existe, entonces podemos comerciar con este
    if (!arbol_cuenca.right().empty()){
        // Comerciamos con el árbol derecho
        comerciar(Productos,arbol_cuenca.value(),arbol_cuenca.right().value());
        // Redistribuimos desde el árbol derecho a sus hijos
        aux_redistribuir(Productos,arbol_cuenca.right());
    }
}

BinTree<string> Cuenca::aux_lectura_rio(const Cjt_Productos& Productos,map<string,Ciudad>& new_map){
    // Obtenemos el nombre de la ciudad a introducir
    string id_ciudad;
    cin >> id_ciudad;
    //--------------------------------------------
    // Caso Base #################################

    // Si el nombre de la ciudad es # entonces no existe
    if (id_ciudad == "#") return BinTree<string>();
    
    // Caso Inductivo ############################

    // Obtenemos las ciudades de la izquierda y derecha del nodo
    BinTree<string> izqueirda = aux_lectura_rio(Productos,new_map);
    BinTree<string> derecha = aux_lectura_rio(Productos,new_map);
    //-------------------------------------------------------------------------
    // Ponemos en el "map" nuestra nueva ciudad
    new_map[id_ciudad] = Ciudad();
    // Devolvemos nuestro árbol
    return BinTree<string>(id_ciudad,izqueirda,derecha);

}

//FUNCIONES PUBLICAS

// Constructor vacío
Cuenca::Cuenca(){

}

void Cuenca::leer_rio(const Cjt_Productos& Productos ,Barco& Barco){
    // Creamos un nuevo "map"
    map<string,Ciudad> new_map;
    // Leemos el árbol de entrada y llenamos el "map"
    this->_cuenca = aux_lectura_rio(Productos,new_map);
    // Hacemos que el "map" obtenido sea nuestro "map"
    this->_mapa_ciudades = new_map;
    // Borramos el registro de ciudades
    Barco.borrar_registro_ciudades();
}

void Cuenca::leer_inventario(Cjt_Productos& Productos,string id_ciudad){
    // Buscamos la ciudad a la cual queremos leer el inventario
    this->_it_mapa_ciudad = this->_mapa_ciudades.find(id_ciudad);
    // Los datos leidos tienen valideza
    bool procedemos = true; 
    // Si la ciudad no existe
    if (this->_it_mapa_ciudad == this->_mapa_ciudades.end()) {
        // Notificamos el error
        error_notification(2);
        // Subimos la bandera de error
        procedemos = false;
    }


    if (procedemos) {
        // Limpiamos el inventrio
        _it_mapa_ciudad->second.limpiar_inventario();
    }

    // Número de elementos a introducir en el inventario de la ciudad
    int numero_de_elementos;
    // ID del producto, unidades poseídas y necesarias
    int id_producto, unidades_poseidas, unidades_necesarias;
    // Entrada del número de elementos
    cin >> numero_de_elementos;
    
    // Bucle que introduce los <numero_de_elementos> elementos dentó del inventario de la ciudad
    for (int i = 0; i < numero_de_elementos; i++)
    {
        // Entrada de valores
        cin >> id_producto;
        cin >> unidades_poseidas >> unidades_necesarias;
        //------------------
        // Si la ciudad existe
        if (procedemos){
            // Si las unidades necesarias son superiores a 0
            if (unidades_necesarias > 0){
                // Introducimos en la ciudad el producto
                _it_mapa_ciudad->second.poner_prod_c(Productos, id_producto,unidades_poseidas,unidades_necesarias);
            }
            else { // En caso contrario
                // Notificamos del error obtenido
                error_notification(6); 
            }
        }
    }
}

void Cuenca::leer_inventarios(Cjt_Productos& Productos){
    string id;
    // Con la entrada de ID's introduciremos los productos en los inventarios de las ciudades
    // Si el ID es '#' finalizamos el proceso
    while (cin >> id and id!="#")
    {
        leer_inventario(Productos, id);
    }
    //---------------------------------------------------------------------------------------
}

void Cuenca::poner_prod(Cjt_Productos& Productos, string id_ciudad, int id_producto){
    // Unidades poseidas y necesarias
    int unidades_poseidas, unidades_necesarias;
    // Introducimos las unidades poseídas y necesarias
    cin >> unidades_poseidas >> unidades_necesarias;
    // Buscamos la ciudad deseada
    this->_it_mapa_ciudad = this->_mapa_ciudades.find(id_ciudad);
    // Si las unidades necesarias son estrictamente positiva
    if (unidades_necesarias > 0){
        
        bool proceder = false;
        // Si la ciudad existe
        if (_it_mapa_ciudad != this->_mapa_ciudades.end())
            // Ponemos el producto deseado y confirmamos la operacion
            proceder = _it_mapa_ciudad->second.poner_prod_c(Productos,id_producto,unidades_poseidas,unidades_necesarias);
        else { // En caso contrario
            // Si el producto no existe imprimimos el error de no existencia
            if ((id_producto <= 0) or (id_producto >= Productos.consultar_num() + 1)) error_notification(1);
            else error_notification(2); // En caso contrario imprimimos el error de no existencia de ciudad
        }

        if (proceder) { // Si la operacion se ha echo con exito
            // Si la ciudad no existe
            if (_it_mapa_ciudad == this->_mapa_ciudades.end()) {
                // Imprimimos el error de ciudad no existe
                error_notification(2);
            }
            else { // En caso contrario, la ciudad existe
                //Imprimimos el peso y volumen total
                cout << _it_mapa_ciudad->second.consultar_peso_total();
                cout <<" ";
                cout << _it_mapa_ciudad->second.consultar_volumen_total();
                cout<<endl;
                //----------------------------------
            }
        }
    }
    else { // En caso contrario imprimimos un error 
        error_notification(6);
    }
}

void Cuenca::modificar_prod(Cjt_Productos& Productos, string id_ciudad, int id_producto){
    // Unidades poseidas y necesarias
    int unidades_poseidas, unidades_neccesarias;
    // Introducimos las unidades poseídas y necesarias
    cin >> unidades_poseidas >> unidades_neccesarias;
    // Buscamos la ciudad deseada
    this->_it_mapa_ciudad = this->_mapa_ciudades.find(id_ciudad);
    // Si las unidades necesarias son estrictamente positiva
    if (unidades_neccesarias > 0){
        bool proceder = false;
        // Si la ciudad existe
        if (_it_mapa_ciudad != this->_mapa_ciudades.end())
            // Modificamos el producto deseado y confirmamos la operacion
            proceder = _it_mapa_ciudad->second.modificar_prod_c(Productos,id_producto,unidades_poseidas,unidades_neccesarias, true);
        else { // En caso contrario
            // Si el producto no existe imprimimos el error de no existencia
            if ((id_producto <= 0) or (id_producto >= Productos.consultar_num() + 1)) error_notification(1);
            else error_notification(2); // En caso contrario imprimimos el error de no existencia de ciudad
        }

        if (proceder){ // Si la operacion se ha echo con exito
            // Si la ciudad no existe
            if (_it_mapa_ciudad == this->_mapa_ciudades.end()) {
                // Imprimimos el error de ciudad no existe
                error_notification(2);
            }
            else { // En caso contrario, la ciudad existe
                //Imprimimos el peso y volumen total 
                cout << _it_mapa_ciudad->second.consultar_peso_total();
                cout <<" ";
                cout << _it_mapa_ciudad->second.consultar_volumen_total();
                cout<<endl;
                //----------------------------------
            }
        }
    }
    else { // En caso contrario imprimimos un error 
        error_notification(6);
    }

}

void Cuenca::quitar_prod(Cjt_Productos& Productos, string id_ciudad, int id_producto){
    // Si el producto no existe
    if ((id_producto <= 0) or (id_producto >= Productos.consultar_num() + 1)) {
        // Imprimimos el error de producto no existene
        error_notification(1);
        //Informacion no valida con errores
        return;
    }
    // Buscamos la ciudad deseada
    this->_it_mapa_ciudad = this->_mapa_ciudades.find(id_ciudad);

    // Si la ciudad no existe
    if (_it_mapa_ciudad == this->_mapa_ciudades.end()) {
        // Imprimimos el error de ciudad no existente y finalizamos
        error_notification(2);
        return;
    }

    // Si la ciudad existe
    // Intentamos quitar el producto 
    bool proceder = _it_mapa_ciudad->second.quitar_prod_c(Productos,id_producto);
    // Si la operación se realiza con éxito procedemos
    if (proceder){
        //Imprimimos el peso y volumen total 
        cout << _it_mapa_ciudad->second.consultar_peso_total();
        cout <<" ";
        cout << _it_mapa_ciudad->second.consultar_volumen_total();
        cout<<endl;
        //----------------------------------
    }
}

void Cuenca::consultar_prod(const Cjt_Productos& Productos, string id_ciudad, int id_producto){
    // Si el producto no existe
    if ((id_producto <= 0) or (id_producto >= Productos.consultar_num() + 1)) {
        // Imprimimos el error de producto no existene
        error_notification(1);
        //Informacion no valida con errores
        return;
    }
    // Buscamos la ciudad deseada
    this->_it_mapa_ciudad = this->_mapa_ciudades.find(id_ciudad);

    // Si la ciudad no existe
    if (_it_mapa_ciudad == this->_mapa_ciudades.end()) {
        // Imprimimos el error de ciudad no existente y finalizamos
        error_notification(2);
        return;
    }
    // Si la ciudad existe
    // Creamos el "pair" que contendrá la información del producto
    pair<int,int> pair_unidades_poseidas_necesarias;
    // Intentamos consultar el producto 
    bool proceder = this->_it_mapa_ciudad->second.consultar_prod_c(id_producto,pair_unidades_poseidas_necesarias, true);
    // Si la operación se realiza con éxito procedemos
    if (proceder){
        //Imprimimos las unidades disponibles y neccesarias 
        cout << pair_unidades_poseidas_necesarias.first;
        cout <<" ";
        cout << pair_unidades_poseidas_necesarias.second;
        cout<<endl;
        //-------------------------------------------------
    }
}

void Cuenca::escribir_ciudad(string id_ciudad) const{
    // Creamos un "iterator" para buscar la ciudad
    map<string,Ciudad> ::const_iterator _it_mapa_ciudad_aux;
    // Buscamos la ciudad
    _it_mapa_ciudad_aux = this->_mapa_ciudades.find(id_ciudad);
    // Si la ciudad no existe
    if (_it_mapa_ciudad_aux == this->_mapa_ciudades.end()) {
        // Imprimimos el error de ciudad no existente
        error_notification(2);
        return;
    }
    // Escribimos la ciudad deseada
    _it_mapa_ciudad_aux->second.escribir_ciudad_c();
}

void Cuenca::comerciar(Cjt_Productos& Productos, string id_ciudad_1, string id_ciudad_2){
    // Buscamos la ciudad 1
    this->_it_mapa_ciudad = this->_mapa_ciudades.find(id_ciudad_1);
    // Buscamos la ciudad 2
    map<string,Ciudad> ::iterator it_mapa_ciudad_2 = this->_mapa_ciudades.find(id_ciudad_2);
    // Si la ciudad 1 no existe
    if (this->_it_mapa_ciudad == this->_mapa_ciudades.end()){
        // Imprimimos error de ciudad no existente
        error_notification(2);
        return;
    }
    // Si la ciudad 2 no existe
    if (it_mapa_ciudad_2 == this->_mapa_ciudades.end()){
        // Imprimimos error de ciudad no existente
        error_notification(2);
        return;
    }
    // Si la ciudad 1 es la ciudad 2 entonces obtendremos un error
    if (id_ciudad_1 == id_ciudad_2){
        // Imprimimos error de ciudad 1 igual a ciudad 2
        error_notification(9);
        return;
    }
    // Hacemos que las ciudades comercien
    this->_it_mapa_ciudad->second.comerciar_c(Productos,it_mapa_ciudad_2->second);
}

void Cuenca::hacer_viaje(Cjt_Productos& Productos, Barco& Barco){
    // Hacemos el vaije
    this->aux_viajar(Productos,Barco,Barco.cons_id_producto_a_comprar(),Barco.cons_id_producto_a_vender());
}

void Cuenca::redistribuir(Cjt_Productos& Productos){
    // Hacemos la redistribución
    aux_redistribuir(Productos, this->_cuenca);
}
