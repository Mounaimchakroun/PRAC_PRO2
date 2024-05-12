/** @file Ciudad.cc
    @brief Implementación de Ciudad.
*/

#include "Ciudad.hh"

Ciudad::Ciudad(){

}

bool Ciudad::poner_prod_c(Cjt_Productos& Productos, int id_producto, int unidades_poseidas, int unidades_necesarias){
    
    if ((id_producto <= 0) or (id_producto >= Productos.consultar_num() + 1)) {
        error_notification(1);
        //Informacion no valida con errores
        return false;
    }

    this->_it_Inventario = this->_Inventario.find(id_producto);

    if (this->_it_Inventario != this->_Inventario.end()) {
        error_notification(4);
        //Informacion no valida con errores
        return false;
    }
    else {
        // Pair del producto (peso y volumen del producto)
        pair<int,int> peso_volumen_del_producto = Productos.consultar_producto_del_conjunto(id_producto);
        //Incrementamos el peso y volumen total 
        this->_peso_total += peso_volumen_del_producto.first * unidades_poseidas;
        this->_volumen_total += peso_volumen_del_producto.second * unidades_poseidas;

        //Introducimos el pair de las unidades poseidas y necesarias del producto
        this->_Inventario[id_producto] = make_pair(unidades_poseidas,unidades_necesarias);
        //Incrementamos el size
        this->_num_de_productos ++;
        //Informacion valida sin errores
        return true;
    }
}

bool Ciudad::modificar_prod_c(Cjt_Productos& Productos,int id_producto, int unidades_poseidas, int unidades_necesarias){
    if ((id_producto <= 0) or (id_producto >= Productos.consultar_num() + 1)) {
        error_notification(1);
        //Informacion no valida con errores
        return false;
    }
    
    this->_it_Inventario = this->_Inventario.find(id_producto);

    if (this->_it_Inventario == this->_Inventario.end()) {
        error_notification(5);
        return false;
    }
    else {
        // Pair del producto (peso y volumen del producto)
        pair<int,int> peso_volumen_del_producto = Productos.consultar_producto_del_conjunto(id_producto);
        //Decrementamos el peso y volumen de los paramentros anteriores
        this->_peso_total -= peso_volumen_del_producto.first * (this->_it_Inventario->second.first);
        this->_volumen_total -= peso_volumen_del_producto.second * (this->_it_Inventario->second.first);

        //Incrementamos el peso y volumen total con los nuevos parametros
        this->_peso_total += peso_volumen_del_producto.first * unidades_poseidas;
        this->_volumen_total += peso_volumen_del_producto.second * unidades_poseidas;

        //Introducimos el pair modificado de las unidades poseidas y necesarias del producto
        this->_Inventario[id_producto] = make_pair(unidades_poseidas,unidades_necesarias);
        //Informacion valida sin errores
        return true;
    }
}

bool Ciudad::quitar_prod_c(Cjt_Productos& Productos,int id_producto){
    
    this->_it_Inventario = this->_Inventario.find(id_producto);

    if (this->_it_Inventario == this->_Inventario.end()) {
        error_notification(5);
        //Informacion no valida con errores
        return false;
    }
    else {
        // Pair del producto (peso y volumen del producto)
        pair<int,int> peso_volumen_del_producto = Productos.consultar_producto_del_conjunto(id_producto);
        //Decrementamos el peso y volumen de los paramentros anteriores
        this->_peso_total -= peso_volumen_del_producto.first * (this->_it_Inventario->second.first);
        this->_volumen_total -= peso_volumen_del_producto.second * (this->_it_Inventario->second.first);

        //Eliminamos el producto
        this->_Inventario.erase(this->_it_Inventario);
        //Decrementamos el size
        this->_num_de_productos --;
        //Informacion valida sin errores
        return true;
    }
}

int Ciudad::consultar_peso_total() const{
    return this->_peso_total;
}

int Ciudad::consultar_volumen_total() const{
    return this->_volumen_total;
}

bool Ciudad::consultar_prod_c(int id_producto, pair<int,int>& info_producto) const{

    map<int,pair<int,int>>::const_iterator aux_it_Inventario = this->_Inventario.find(id_producto);

    if (aux_it_Inventario == this->_Inventario.end()) {
        error_notification(5);
        //Informacion no valida con errores
        return false;
    }
    else {
        //Proporcionamos la informacion de la cantidad de producto que tiene y la que necesita
        info_producto = aux_it_Inventario->second;
        //Informacion valida sin errores
        return true;
    }
}

void Ciudad::comerciar_c(Cjt_Productos& Productos, Ciudad& ciudad_con_la_que_comerciaremos){
    this->_it_Inventario = this->_Inventario.begin();

    while (this->_it_Inventario != this->_Inventario.end())
    {
        //canviar algoritmo para encontrar el de manera eficciente PRO1---
        ciudad_con_la_que_comerciaremos._it_Inventario = ciudad_con_la_que_comerciaremos._Inventario.find(this->_it_Inventario->first);
        //--------
        if (ciudad_con_la_que_comerciaremos._it_Inventario != ciudad_con_la_que_comerciaremos._Inventario.end()){

            int diferencia_ciudad_1 = this->_it_Inventario->second.second - this->_it_Inventario->second.first;
            int diferencia_ciudad_2 = ciudad_con_la_que_comerciaremos._it_Inventario->second.second - ciudad_con_la_que_comerciaremos._it_Inventario->second.first;

            if (diferencia_ciudad_1 * diferencia_ciudad_2 < 0){

                if (diferencia_ciudad_1 < 0){ //Venta
                    if (diferencia_ciudad_2 > 0){
                        pair<int,int> producto = Productos.consultar_producto_del_conjunto(this->_it_Inventario->first);

                        this->_it_Inventario->second.first -= abs(diferencia_ciudad_1);
                        this->_peso_total -= abs(diferencia_ciudad_1) * producto.first;
                        this->_volumen_total -= abs(diferencia_ciudad_1) * producto.second;

                        ciudad_con_la_que_comerciaremos._it_Inventario->second.first += abs(diferencia_ciudad_1); 
                        ciudad_con_la_que_comerciaremos._peso_total += abs(diferencia_ciudad_1) * producto.first;
                        ciudad_con_la_que_comerciaremos._volumen_total += abs(diferencia_ciudad_1) * producto.second;
                    }
                }
                else if (diferencia_ciudad_2 < 0){ //Compra
                    if (diferencia_ciudad_1 > 0){
                        pair<int,int> producto = Productos.consultar_producto_del_conjunto(this->_it_Inventario->first);

                        this->_it_Inventario->second.first += abs(diferencia_ciudad_2);
                        this->_peso_total += abs(diferencia_ciudad_2) * producto.first;
                        this->_volumen_total += abs(diferencia_ciudad_2) * producto.second;

                        ciudad_con_la_que_comerciaremos._it_Inventario->second.first -= abs(diferencia_ciudad_2); 
                        ciudad_con_la_que_comerciaremos._peso_total -= abs(diferencia_ciudad_2) * producto.first;
                        ciudad_con_la_que_comerciaremos._volumen_total -= abs(diferencia_ciudad_2) * producto.second;
                    }
                }
            }
        }
        
        _it_Inventario++;
    }
}

void Ciudad::escribir_ciudad_c() const{
    map<int,pair<int,int>>::const_iterator aux_it_Inventario = this->_Inventario.begin();
    
    while (aux_it_Inventario != this->_Inventario.end())
    {
        cout <<aux_it_Inventario->first <<" "<<aux_it_Inventario->second.first << " " << aux_it_Inventario->second.second <<endl;
        aux_it_Inventario++;
    }

    cout << this->_peso_total <<" "<< this->_volumen_total <<endl;
}

