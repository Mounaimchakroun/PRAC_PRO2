/** @file Barco.cc
    @brief Implementación de Barco.
*/

#include "Barco.hh"

//FUNCIONES PUBLICAS
//Constructor vacío
Barco::Barco(){

}

void Barco::modificar_barco(Cjt_Productos& Productos){
    // Variables que contendrán los ID de los productos que compraremos y venderemos
    int id_producto_a_comprar;
    int id_producto_a_vender;

    // Variables que contendrán las cantidades de los productos que compraremos y venderemos
    int cantidad_producto_a_comprar;
    int cantidad_producto_a_vender;

    // Banderas para saber si existen los productos que queremos comprar y vender
    bool exist_producto_a_comprar = false;
    bool exist_producto_a_vender = false;

    // Introducimos el ID del producto a comprar y la cantidad
    cin >> id_producto_a_comprar >> cantidad_producto_a_comprar;

    // Comprobamos que exista el producto, en caso contrario notificamos el error y subimos la bandera de no existencia
    if (id_producto_a_comprar <= 0 or id_producto_a_comprar > Productos.consultar_num() + 1) {
        error_notification(1);
        exist_producto_a_comprar = false;
    }
    else { // En caso contrario subimos la bandera de existencia
        exist_producto_a_comprar = true;
    }
    
    // Introducimos el ID del producto a vender y la cantidad
    cin >> id_producto_a_vender >> cantidad_producto_a_vender;
    
    // Comprovamos que exista el producto, en caso contrario notificamos el error y subimos la bandera de no existencia
    if ((exist_producto_a_comprar) and (id_producto_a_vender <= 0 or id_producto_a_vender > Productos.consultar_num() + 1)) {//Error
        error_notification(1); 
        exist_producto_a_vender = false;
    }
    else { // En caso contrario subimos la bandera de existencia
        exist_producto_a_vender = true;
    }

    // Comprobamos que no sean la misma ciudad
    if (id_producto_a_comprar == id_producto_a_vender){
        error_notification(8);
        return;
    }
    else { // En caso contrario procedemos a la modificación del barco
        // En este punto nos hemos asegurado de que los datos son correctos
        // Miramos las banderas de existencia, si los dos productos existen procedemos a la modificación del barco
        if (exist_producto_a_comprar and exist_producto_a_vender){
            // Cambiamos los ID de compra y venta y las cantidades
            // # Compra
            this->_id_producto_a_comprar = id_producto_a_comprar;
            this->_cantidad_producto_a_comprar = cantidad_producto_a_comprar;
            // # Venta
            this->_id_producto_a_vender = id_producto_a_vender;
            this->_cantidad_producto_a_vender = cantidad_producto_a_vender;
        }
        return;
    }
}
            
void Barco::agregar_ultima_ciudad_consultada(string ciudad){
    // Hacemos push_back a la última ciudad consultada
    this->_viajes_realizados.push_back(ciudad);
}

void Barco::borrar_registro_ciudades(){
    // Reinicializamos el registro de viajes
    this->_viajes_realizados = list<string>();   
}
            
void Barco::escribir_barco() const{
    // Imprimimos 
    cout << this->_id_producto_a_comprar <<" "<< this->_cantidad_producto_a_comprar <<" ";
    cout << this->_id_producto_a_vender <<" "<< this->_cantidad_producto_a_vender <<endl;
    // Creamos un "iterator" para navegar por la lista
    list<string>::const_iterator it_viajes_realizados = this->_viajes_realizados.begin();
    // Navegamos por la lista e imprimimos los valores de las ciudades que hemos atracado por última vez
    while (it_viajes_realizados != this->_viajes_realizados.end())
    {
        cout << *(it_viajes_realizados) <<endl;
        it_viajes_realizados++;
    }
}

int Barco::cons_id_producto_a_vender() const{
    // Obtenemos el ID del producto que vendemos
    return this->_id_producto_a_vender;
}

int Barco::cons_id_producto_a_comprar() const{
    // Obtenemos el ID del producto que compramos
    return this->_id_producto_a_comprar;
}

int Barco::consultar_cantidad_a_vender() const{
    // Obtenemos la cantidad del producto que vendemos
    return this->_cantidad_producto_a_vender;
}
    
int Barco::consultar_cantidad_a_comprar() const{
    // Obtenemos la cantidad del producto que compramos
    return this->_cantidad_producto_a_comprar;
}

