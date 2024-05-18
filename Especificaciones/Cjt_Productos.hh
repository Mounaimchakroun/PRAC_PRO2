/** @file Cjt_Productos.hh
    @brief Especificación de la clase Cjt_Productos.
*/

#ifndef HEADERFILE_CJT_PRODUCTOS
#define HEADERFILE_CJT_PRODUCTOS

#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#include "Error_Module.hh"
#endif

using namespace std;

/**
 * @class Cjt_Productos
 * @brief Representa un conjunto de productos.
 *
 * La clase Cjt_Productos mantiene una estructura de datos que almacena información sobre varios productos.
 */
class Cjt_Productos {
private:
    /**
     * @brief Mapa de productos.
     *
     * El mapa utiliza como clave el ID del producto y como valor un par de enteros donde:
     * - first: cantidad disponible del producto.
     * - second: cantidad necesaria del producto.
     */
    map<int, pair<int, int>> _map_productos;

    /// Iterador constante para recorrer el mapa de productos.
    map<int, pair<int, int>>::const_iterator _it_map_productos;

    /// Número actual de productos en el conjunto.
    int _num_productos_actuales = 0;

public:
    // CONSTRUCTORES / DESTRUCTORES:

    /**
     * @brief Constructor de Cjt_Productos.
     * 
     * @pre Se proporciona la cantidad de productos máximo deseada.
     * @post Se obtiene un conjunto de productos vacío con la cantidad deseada.
     */
    Cjt_Productos();

    // MODIFICADORES:

    /**
     * @brief Agrega un nuevo producto al conjunto de productos.
     * 
     * @pre Se tiene un conjunto de productos, vacío o no, y se proporciona el peso y volumen del producto a agregar.
     * @post Se agrega un nuevo producto al conjunto de productos.
     * 
     * @param peso Peso del nuevo producto.
     * @param volumen Volumen del nuevo producto.
     */
    void agregar_producto(int peso, int volumen);

    /**
     * @brief Agrega varios nuevos productos al conjunto de productos.
     * 
     * @pre Se tiene un conjunto de productos, vacío o no, y se proporciona un valor n (entero) seguido de n pares de pesos y volúmenes para cada producto.
     * @post Se agregan n nuevos productos al conjunto de productos.
     * 
     * @param num_productos Número de productos a agregar.
     */
    void agregar_productos(int num_productos);

    // CONSULTORES

    /**
     * @brief Obtiene el número actual de productos en el conjunto.
     * 
     * @pre Se tiene un conjunto de productos.
     * @post Se obtiene el número actual de productos.
     * 
     * @return Número actual de productos.
     */
    int consultar_num() const;

    /**
     * @brief Consulta los datos de un producto específico.
     * 
     * @pre Se proporciona el ID de un producto existente.
     * @post Se devuelve el peso y volumen del producto deseado.
     * 
     * @param id_producto ID del producto a consultar.
     * @return Par que contiene el peso y el volumen del producto.
     */
    pair<int, int> consultar_producto_del_conjunto(int id_producto);

    // ESCRITURA:

    /**
     * @brief Escribe los datos de un producto específico.
     * 
     * @pre Se proporciona el ID de un producto existente.
     * @post Se escribe por el canal de salida el producto deseado.
     * 
     * @param id_producto ID del producto a escribir.
     */
    void escribir_producto(int id_producto);
};

#endif // HEADERFILE_CJT_PRODUCTOS
