#ifndef HEADERFILE_CIUDAD
#define HEADERFILE_CIUDAD

#include "Cjt_Productos.hh"
#include <map>

class Ciudad
{
private:
    // Peso total de la ciudad
    int _peso_total = 0;
    // Volumen total de la ciudad
    int _volumen_total = 0;
    //Inventario
    // Inventario.first = unidades disponibles | Inventario.second = unidades neccesarias
    map<int,pair<int,int>> _Inventario;
    //Map Iterator
    map<int,pair<int,int>>::iterator _it_Inventario;
    //Numero de productos en el inventario
    int _num_de_productos = 0;

public:
    //CONSTRUCTORES / DESTRUCTORES:
 
    /**PRE: Cierto.
       POST: Obtenemos una ciudad
    */
    Ciudad();

    //MODIFICADORES:

    /**PRE:

      POST: 
    */
    bool poner_prod_c(Cjt_Productos& Productos, int id_producto, int unidades_poseidas, int unidades_necesarias);

    /**PRE:

      POST: 
    */
    bool modificar_prod_c(Cjt_Productos& Productos,int id_producto, int unidades_poseidas, int unidades_necesarias);

    /**PRE:

      POST: 
    */
    bool quitar_prod_c(Cjt_Productos& Productos,int id_producto);

    /**PRE:

      POST: 
    */
    void comerciar_c(Cjt_Productos& Productos, Ciudad& ciudad_con_la_que_comerciaremos);

    //CONSULTORES

    /**PRE:

      POST: 
    */
    bool consultar_prod_c(int id_producto, pair<int,int>& info_producto) const;

    /**PRE:

      POST: 
    */
    int consultar_peso_total() const;

    /**PRE:

      POST: 
    */
    int consultar_volumen_total() const;

    //ESCRITURA

    /**PRE:

      POST: 
    */
    void escribir_ciudad_c() const;
};

#endif