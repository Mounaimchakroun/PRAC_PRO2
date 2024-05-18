/** @file Cjt_Productos.cc
    @brief Implementación de Cjt_Productos.
*/

#include "Cjt_Productos.hh"
// Constructor vacío
Cjt_Productos::Cjt_Productos(){
    
}

void Cjt_Productos::agregar_producto(int peso, int volumen){
    // Agregamos en el "map" el nuevo producto con su correspondiente ID
    this->_map_productos[this->_num_productos_actuales + 1] = pair<int,int>(peso,volumen);
    // Incrementamos el número de productos del conjunto
    this->_num_productos_actuales ++;
}

void Cjt_Productos::agregar_productos(int num_productos){
    // Agregamos <num_productos> productos a nuestro conjunto
    int peso, volumen;
    for (int i = 0; i < num_productos; i++)
    {
        cin >> peso >> volumen;
        agregar_producto(peso, volumen);
    }
}

int Cjt_Productos::consultar_num() const{
    // Obtenemos en número de productos que tiene nuestro conjunto
    return this-> _num_productos_actuales;
}

pair<int,int> Cjt_Productos::consultar_producto_del_conjunto(int id_producto){
    // Buscamos en nuestro conjunto el producto deseado
    // NOTA: No tenemos sistemas de protección, ya que en la PRE pedimos que ya exista
    this->_it_map_productos = this->_map_productos.find(id_producto);
    return this->_it_map_productos->second;
}

void Cjt_Productos::escribir_producto(int id_producto){
    // Nos aseguramos que exista el producto deseado
    if ((id_producto <= 0) or (id_producto >= this->_num_productos_actuales + 1)){
        error_notification(1); // Notificamos del error
        return; // Finalizamos la función, ya que el producto no existe
    }
    // En caso de que el producto exista en nuestro inventario
    this->_it_map_productos = this->_map_productos.find(id_producto);
    // Imprimimos por el canal de salida información de este
    cout << id_producto  <<" "<< this->_it_map_productos->second.first <<" "<< this->_it_map_productos->second.second <<endl;
}
