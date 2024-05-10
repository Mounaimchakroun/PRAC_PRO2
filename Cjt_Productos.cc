#include "Cjt_Productos.hh"

Cjt_Productos::Cjt_Productos(){
    
}

void Cjt_Productos::agregar_producto(int peso, int volumen){
    this->_map_productos[this->_num_productos_actuales + 1] = pair<int,int>(peso,volumen);
    this->_num_productos_actuales ++;
}

void Cjt_Productos::agregar_productos(int num_productos){
    int peso, volumen;
    for (int i = 0; i < num_productos; i++)
    {
        cin >> peso >> volumen;
        agregar_producto(peso, volumen);
    }
}

int Cjt_Productos::consultar_num() const{
    return this-> _num_productos_actuales;
}

pair<int,int> Cjt_Productos::consultar_producto_del_conjunto(int id_producto){
    this->_it_map_productos = this->_map_productos.find(id_producto);
    return this->_it_map_productos->second;
}

void Cjt_Productos::escribir_producto(int id_producto){

    if ((id_producto <= 0) or (id_producto >= this->_num_productos_actuales + 1)){
        error_notification(1);
        return;
    }
    this->_it_map_productos = this->_map_productos.find(id_producto);

    if (this->_it_map_productos != this->_map_productos.end()){
    cout << id_producto  <<" "<< this->_it_map_productos->second.first <<" "<< this->_it_map_productos->second.second <<endl;
    }
}
