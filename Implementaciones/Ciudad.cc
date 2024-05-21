/** @file Ciudad.cc
    @brief Implementación de Ciudad.
*/

#include "Ciudad.hh"

// Constructro vacío
Ciudad::Ciudad(){

}

bool Ciudad::poner_prod_c(Cjt_Productos& Productos, int id_producto, int unidades_poseidas, int unidades_necesarias){
    // Comprobamos que el producto exista
    if ((id_producto <= 0) or (id_producto >= Productos.consultar_num() + 1)) {
        error_notification(1);
        // Información no válida con errores
        return false;
    }
    // Buscamos el producto
    this->_it_Inventario = this->_Inventario.find(id_producto);
    // Si el producto ya está en el inventario levantamos bandera de error por ya existencia del producto
    if (this->_it_Inventario != this->_Inventario.end()) {
        error_notification(4);
        // Información no válida con errores
        return false;
    }
    else { // De lo contrario, el producto no existe el inventario de la ciudad
        // Pair del producto (peso y volumen del producto)
        pair<int,int> peso_volumen_del_producto = Productos.consultar_producto_del_conjunto(id_producto);
        //Incrementamos el peso y volumen total
        this->_peso_total += peso_volumen_del_producto.first * unidades_poseidas;
        this->_volumen_total += peso_volumen_del_producto.second * unidades_poseidas;

        // Introducimos el pair de las unidades poseídas y necesarias del producto
        this->_Inventario[id_producto] = make_pair(unidades_poseidas,unidades_necesarias);
        // Incrementamos el size
        this->_num_de_productos ++;
        // Información válida sin errores
        return true;
    }
}

bool Ciudad::modificar_prod_c(Cjt_Productos& Productos,int id_producto, int unidades_poseidas, int unidades_necesarias, bool notificacion_de_errores){
    // Comprobamos que el producto exista
    if ((id_producto <= 0) or (id_producto >= Productos.consultar_num() + 1)) {
        if (notificacion_de_errores) error_notification(1);
        // Información no válida con errores
        return false;
    }
    // Buscamos el producto
    this->_it_Inventario = this->_Inventario.find(id_producto);

    // Si el producto no está en el inventario levantamos bandera de error por no existencia del producto si está habilitada el error
    if (this->_it_Inventario == this->_Inventario.end()) {
        if (notificacion_de_errores) error_notification(5);
        // Información no válida con errores
        return false;
    }
    else {
        // Pair del producto (peso y volumen del producto)
        pair<int,int> peso_volumen_del_producto = Productos.consultar_producto_del_conjunto(id_producto);
        // Decrementamos el peso y volumen de los parámetros anteriores
        this->_peso_total -= peso_volumen_del_producto.first * (this->_it_Inventario->second.first);
        this->_volumen_total -= peso_volumen_del_producto.second * (this->_it_Inventario->second.first);

        // Incrementamos el peso y volumen total con los nuevos parámetros
        this->_peso_total += peso_volumen_del_producto.first * unidades_poseidas;
        this->_volumen_total += peso_volumen_del_producto.second * unidades_poseidas;

        // Introducimos el pair modificado de las unidades poseídas y necesarias del producto
        this->_Inventario[id_producto] = make_pair(unidades_poseidas,unidades_necesarias);
        // Información válida sin errores
        return true;
    }
}

bool Ciudad::quitar_prod_c(Cjt_Productos& Productos,int id_producto){
    // Comprobamos que el producto exista
    this->_it_Inventario = this->_Inventario.find(id_producto);
    // Si el producto no está en el inventario levantamos bandera de error por no existencia del producto si está habilitada el error
    if (this->_it_Inventario == this->_Inventario.end()) {
        error_notification(5);
        // Información no válida con errores
        return false;
    }
    else {
        // Pair del producto (peso y volumen del producto)
        pair<int,int> peso_volumen_del_producto = Productos.consultar_producto_del_conjunto(id_producto);
        // Decrementamos el peso y volumen de los parámentros anteriores
        this->_peso_total -= peso_volumen_del_producto.first * (this->_it_Inventario->second.first);
        this->_volumen_total -= peso_volumen_del_producto.second * (this->_it_Inventario->second.first);

        // Eliminamos el producto
        this->_Inventario.erase(this->_it_Inventario);
        // Decrementamos el size
        this->_num_de_productos --;
        // Información válida sin errores
        return true;
    }
}

int Ciudad::consultar_peso_total() const{
    // Retornamos el peso total del inventario
    return this->_peso_total;
}

int Ciudad::consultar_volumen_total() const{
    // Retornamos el volumen total del inventario
    return this->_volumen_total;
}

bool Ciudad::consultar_prod_c(int id_producto, pair<int,int>& info_producto, bool notificacion_de_errores) const{
    // Creamos un "iterator" para buscar el producto deseado dentro del inventario
    map<int,pair<int,int>>::const_iterator aux_it_Inventario = this->_Inventario.find(id_producto);

    if (aux_it_Inventario == this->_Inventario.end()) {
        if (notificacion_de_errores) error_notification(5);
        // Información no válida con errores
        return false;
    }
    else {
        // Proporcionamos la información de la cantidad de producto que tiene y la que necesita
        info_producto = aux_it_Inventario->second;
        // Información válida sin errores
        return true;
    }
}

void Ciudad::comerciar_c(Cjt_Productos& Productos, Ciudad& ciudad_con_la_que_comerciaremos){
    // Creamos un "iterator" que apunta al primer elemento del inventario
    this->_it_Inventario = this->_Inventario.begin();
    // Recordemos el inventario
    while (this->_it_Inventario != this->_Inventario.end())
    {
        // Miramos si el producto se encuentra dentro del inventario contrario
        ciudad_con_la_que_comerciaremos._it_Inventario = ciudad_con_la_que_comerciaremos._Inventario.find(this->_it_Inventario->first);
        // En caso afirmativo
        if (ciudad_con_la_que_comerciaremos._it_Inventario != ciudad_con_la_que_comerciaremos._Inventario.end()){
            // Calculamos la diferencia de productos de uno y el otro
            int diferencia_ciudad_1 = this->_it_Inventario->second.second - this->_it_Inventario->second.first;
            int diferencia_ciudad_2 = ciudad_con_la_que_comerciaremos._it_Inventario->second.second - ciudad_con_la_que_comerciaremos._it_Inventario->second.first;
            // En caso de que una ciudad necesite productos que a la otra le sobran
            if (diferencia_ciudad_1 * diferencia_ciudad_2 < 0){
                // Si la ciudad 2 necesita productos que nuestra ciudad le sobran
                if (diferencia_ciudad_1 < 0){ // #Venta
                    if (diferencia_ciudad_2 > 0){
                        // En caso de que tenemos más productos de los que necesita la ciudad 2
                        if (abs(diferencia_ciudad_1) >= abs(diferencia_ciudad_2)){
                            // Consultamos las unidades poseídas y necesarias del producto que queremos comerciar
                            pair<int,int> producto = Productos.consultar_producto_del_conjunto(this->_it_Inventario->first);
                            // Decrementamos en nuestra ciudad las unidades que necesita la ciudad 2
                            this->_it_Inventario->second.first -= abs(diferencia_ciudad_2);
                            this->_peso_total -= abs(diferencia_ciudad_2) * producto.first;
                            this->_volumen_total -= abs(diferencia_ciudad_2) * producto.second;
                            // Incrementamos en la ciudad 2 las unidades que otorgamos la nuestra ciudad
                            ciudad_con_la_que_comerciaremos._it_Inventario->second.first += abs(diferencia_ciudad_2);
                            ciudad_con_la_que_comerciaremos._peso_total += abs(diferencia_ciudad_2) * producto.first;
                            ciudad_con_la_que_comerciaremos._volumen_total += abs(diferencia_ciudad_2) * producto.second;
                        }
                        else { // En caso de que tenemos menos productos de los que necesita la ciudad 2
                            // Consultamos las unidades poseídas y necesarias del producto que queremos comerciar
                            pair<int,int> producto = Productos.consultar_producto_del_conjunto(this->_it_Inventario->first);
                            // Decrementamos en nuestra ciudad todas las unidades sobrantes
                            this->_it_Inventario->second.first -= abs(diferencia_ciudad_1);
                            this->_peso_total -= abs(diferencia_ciudad_1) * producto.first;
                            this->_volumen_total -= abs(diferencia_ciudad_1) * producto.second;
                            // Incrementamos en la ciudad 2 las unidades que sobran de nuestra ciudad
                            ciudad_con_la_que_comerciaremos._it_Inventario->second.first += abs(diferencia_ciudad_1);
                            ciudad_con_la_que_comerciaremos._peso_total += abs(diferencia_ciudad_1) * producto.first;
                            ciudad_con_la_que_comerciaremos._volumen_total += abs(diferencia_ciudad_1) * producto.second;
                        }
                    }
                }
                // Si a nuestra ciudad necesita productos que la ciudad 2 le sobran
                else if (diferencia_ciudad_2 < 0){ // #Compra
                    if (diferencia_ciudad_1 > 0){
                        // En caso de que la ciudad 2 tiene más productos de los que necesita nuestra ciudad
                        if (abs(diferencia_ciudad_1) <= abs(diferencia_ciudad_2)){
                            // Consultamos las unidades poseídas y necesarias del producto que queremos comprar
                            pair<int,int> producto = Productos.consultar_producto_del_conjunto(this->_it_Inventario->first);
                            // Incrementamos a nuestra ciudad todos los productos que nos faltaban 
                            this->_it_Inventario->second.first += abs(diferencia_ciudad_1);
                            this->_peso_total += abs(diferencia_ciudad_1) * producto.first;
                            this->_volumen_total += abs(diferencia_ciudad_1) * producto.second;
                            // Decrementamos en la ciudad 2 las unidades necesarias por nuestra ciudad
                            ciudad_con_la_que_comerciaremos._it_Inventario->second.first -= abs(diferencia_ciudad_1);
                            ciudad_con_la_que_comerciaremos._peso_total -= abs(diferencia_ciudad_1) * producto.first;
                            ciudad_con_la_que_comerciaremos._volumen_total -= abs(diferencia_ciudad_1) * producto.second;
                        }
                        else { // En caso de que la ciudad 2 tiene menos productos de los que necesita nuestra ciudad
                            // Consultamos las unidades poseídas y necesarias del producto que queremos comprar
                            pair<int,int> producto = Productos.consultar_producto_del_conjunto(this->_it_Inventario->first);
                            // Incrementamos a nuestra ciudad los productos que le sobra a la ciudad 2 
                            this->_it_Inventario->second.first += abs(diferencia_ciudad_2);
                            this->_peso_total += abs(diferencia_ciudad_2) * producto.first;
                            this->_volumen_total += abs(diferencia_ciudad_2) * producto.second;
                            // Decrementamos en la ciudad 2 las unidades sobrantes por esta ciudad
                            ciudad_con_la_que_comerciaremos._it_Inventario->second.first -= abs(diferencia_ciudad_2);
                            ciudad_con_la_que_comerciaremos._peso_total -= abs(diferencia_ciudad_2) * producto.first;
                            ciudad_con_la_que_comerciaremos._volumen_total -= abs(diferencia_ciudad_2) * producto.second;
                        }
                    }
                }
            }
        }
        // Consultamos el siguiente producto
        _it_Inventario++;
    }
}


void Ciudad::escribir_ciudad_c() const{
    // Creamos un "iterator" para consultar los productos del inventario
    map<int,pair<int,int>>::const_iterator aux_it_Inventario = this->_Inventario.begin();
    // Mientras no lleguemos al final del inventario
    while (aux_it_Inventario != this->_Inventario.end())
    {
        // Imprimimos los productos del inventario
        cout <<aux_it_Inventario->first <<" "<<aux_it_Inventario->second.first << " " << aux_it_Inventario->second.second <<endl;
        aux_it_Inventario++; // Consultamos el siguiente producto
    }
    // Imprimimos el peso y volumen total
    cout << this->_peso_total <<" "<< this->_volumen_total <<endl;
}

void Ciudad::limpiar_inventario(){
    this->_it_Inventario = this->_Inventario.begin();

    while (this->_it_Inventario != this->_Inventario.end())
    {
        this->_it_Inventario = this->_Inventario.erase(this->_it_Inventario);
    }
    
    this->_peso_total = 0;
    this->_volumen_total = 0;
    this->_num_de_productos = 0;
}
