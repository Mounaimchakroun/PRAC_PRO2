/** @file Barco.cc
    @brief Implementación de Barco.
*/

#include "Barco.hh"

//FUNCIONES PUBLICAS
Barco::Barco(){

}

void Barco::modificar_barco(Cjt_Productos& Productos){
    int id_producto_a_comprar;
    int id_producto_a_vender;

    int cantidad_producto_a_comprar;
    int cantidad_producto_a_vender;

    bool exist_producto_a_comprar = false;
    bool exist_producto_a_vender = false;

    cin >> id_producto_a_comprar >> cantidad_producto_a_comprar;

    if (id_producto_a_comprar <= 0 or id_producto_a_comprar > Productos.consultar_num() + 1) {
        error_notification(1);
        exist_producto_a_comprar = false;
    }
    else {
        exist_producto_a_comprar = true;
    }
    
    cin >> id_producto_a_vender >> cantidad_producto_a_vender;

    if ((exist_producto_a_comprar) and (id_producto_a_vender <= 0 or id_producto_a_vender > Productos.consultar_num() + 1)) {//Error
        error_notification(1);
        exist_producto_a_vender = false;
    }
    else {
        exist_producto_a_vender = true;
    }

    if (id_producto_a_comprar == id_producto_a_vender){
        error_notification(8);
        return;
    }
    else {
        if (exist_producto_a_comprar and exist_producto_a_vender){
            this->_id_producto_a_comprar = id_producto_a_comprar;
            this->_cantidad_producto_a_comprar = cantidad_producto_a_comprar;

            this->_id_producto_a_vender = id_producto_a_vender;
            this->_cantidad_producto_a_vender = cantidad_producto_a_vender;
        }
    }
}

void Barco::agregar_ultima_ciudad_consultada(string ciudad){
    this->_viajes_realizados.push_back(ciudad);
}

void Barco::borrar_registro_ciudades(){
    this->_viajes_realizados = list<string>();   
}

void Barco::escribir_barco(){
    cout << this->_id_producto_a_comprar <<" "<< this->_cantidad_producto_a_comprar <<" ";
    cout << this->_id_producto_a_vender <<" "<< this->_cantidad_producto_a_vender <<endl;
    
    list<string>::iterator it_viajes_realizados = this->_viajes_realizados.begin();

    while (it_viajes_realizados != this->_viajes_realizados.end())
    {
        cout << *(it_viajes_realizados) <<endl;
        it_viajes_realizados++;
    }
}

int Barco::cons_id_producto_a_vender() const{
    return this->_id_producto_a_vender;
}

int Barco::cons_id_producto_a_comprar() const{
    return this->_id_producto_a_comprar;
}

int Barco::consultat_cantidad_a_vender() const{
    return this->_cantidad_producto_a_vender;
}

int Barco::consultat_cantidad_a_comprar() const{
    return this->_cantidad_producto_a_comprar;
}

