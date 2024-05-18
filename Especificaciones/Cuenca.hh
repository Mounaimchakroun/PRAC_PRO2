/** @file Cuenca.hh
    @brief Especificación de la clase Cuenca.
*/

#ifndef HEADERFILE_CUENCA
#define HEADERFILE_CUENCA

#include "Ciudad.hh"
#include "Barco.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#endif

/**
 * @class Cuenca
 * @brief Representa una cuenca fluvial con ciudades y la capacidad de gestionar comercio entre ellas.
 */
class Cuenca {
private:
    /// Árbol binario que representa el río y las ciudades a lo largo de él
    BinTree<string> _cuenca;
    /// Mapa que relaciona nombres de ciudades con objetos Ciudad
    map<string, Ciudad> _mapa_ciudades;
    /// Iterador del mapa de la ciudad
    map<string, Ciudad>::iterator _it_mapa_ciudad;

    /**
     * @brief Redistribuye productos entre nodos de un árbol de cuenca.
     * 
     * @param Productos Conjunto de productos a redistribuir.
     * @param arbol_cuenca Árbol binario que representa la cuenca.
     * 
     * @pre Se proporciona el árbol binario de la cuenca.
     * @post Las ciudades de la cuenca comercian con sus nodos hijos.
     */
    void aux_redistribuir(Cjt_Productos& Productos, const BinTree<string>& arbol_cuenca);

    /**
     * @brief Lee el árbol binario de la cuenca y el mapa de ciudades desde el canal de entrada.
     * 
     * @param Producto Conjunto de productos.
     * @param new_map Mapa de ciudades.
     * @return Árbol binario que representa la cuenca.
     * 
     * @pre Se proporciona un nuevo mapa y la entrada de un árbol binario por el canal de entrada.
     * @post Se obtiene el árbol binario de la cuenca y el mapa que relaciona cada ID con su ciudad correspondiente.
     */
    BinTree<string> aux_lectura_rio(const Cjt_Productos& Producto, map<string, Ciudad>& new_map);

    /**
     * @brief Obtiene la ruta más beneficiosa para el barco.
     * 
     * @param nodo Árbol binario que representa la ciudad donde estamos localizados.
     *
     * @return Lista de nombres de ciudades.
     * 
     * @pre Se proporciona el árbol binario de la cuenca.
     * @post Se obtiene la ruta más beneficiosa para el barco.
     */
    list<pair<char,int>> recorrido_con_max_beneficio(const BinTree<pair<int,int>>& nodo);

    /**
     * @brief Obtiene un árbol de ventas basado en los productos a comprar y vender.
     * 
     * @param id_prod_a_comprar ID del producto a comprar.
     * @param id_prod_a_vender ID del producto a vender.
     * @param productos_a_comprar Cantidad de productos a comprar.
     * @param productos_a_vender Cantidad de productos a vender.
     * @param nodo Nodo del árbol binario de la cuenca.
     * @return Árbol binario de ventas.
     * 
     * @pre Tenemos un río con ciudades.
     * @post Se obtiene un árbol binario que representa las ventas basadas en los productos a comprar y vender.
     */
    BinTree<pair<int,int>> obtener_arbol_de_ventas(int id_prod_a_comprar, int id_prod_a_vender, int productos_a_comprar, int productos_a_vender, const BinTree<string>& nodo);

    /**
     * @brief Realiza un viaje comercial con un barco.
     * 
     * @param Productos Conjunto de productos.
     * @param Barco Objeto Barco.
     * @param id_prod_a_comprar ID del producto a comprar.
     * @param id_prod_a_vender ID del producto a vender.
     * 
     * @pre Cierto.
     * @post El barco realiza un viaje comercial comprando y vendiendo productos.
     */
    void aux_viajar(Cjt_Productos &Productos, Barco& Barco, int id_prod_a_comprar, int id_prod_a_vender);

public:
    // CONSTRUCTORES / DESTRUCTORES:

    /**
     * @brief Constructor de la clase Cuenca.
     * 
     * @pre Cierto.
     * @post Se crea una cuenca fluvial.
     */
    Cuenca();

    // MODIFICADORES:

    /**
     * @brief Lee la forma del río.
     * 
     * @param Productos Conjunto de productos.
     * @param Barco Objeto Barco.
     * 
     * @pre Se dispone de una cuenca fluvial, productos y un barco.
     * @post Se lee la forma del río.
     */
    void leer_rio(const Cjt_Productos& Productos, Barco& Barco);

    /**
     * @brief Lee los inventarios de las ciudades.
     * 
     * @param Productos Conjunto de productos.
     * 
     * @pre Se dispone de un conjunto de productos y nombres de ciudades en el canal de entrada.
     * @post Se actualizan los inventarios de las ciudades con los productos disponibles.
     */
    void leer_inventarios(Cjt_Productos& Productos);

    /**
     * @brief Lee el inventario de una ciudad.
     * 
     * @param Productos Conjunto de productos.
     * @param id_ciudad Nombre de la ciudad.
     * 
     * @pre Se dispone de un conjunto de productos, el nombre de una ciudad y la cantidad de productos a depositar en el inventario.
     * @post Se actualiza el inventario de la ciudad con los productos indicados.
     */
    void leer_inventario(Cjt_Productos& Productos, string id_ciudad);

    /**
     * @brief Hace comerciar dos ciudades.
     * 
     * @param Productos Conjunto de productos.
     * @param id_ciudad_1 Nombre de la primera ciudad.
     * @param id_ciudad_2 Nombre de la segunda ciudad.
     * 
     * @pre Se dispone del nombre de dos ciudades y un conjunto de productos.
     * @post Las dos ciudades comercian entre sí.
     */
    void comerciar(Cjt_Productos& Productos, string id_ciudad_1, string id_ciudad_2);

    /**
     * @brief Redistribuye productos entre las ciudades a lo largo del río.
     * 
     * @param Productos Conjunto de productos.
     * 
     * @pre Se dispone de un río con ciudades.
     * @post Se redistribuyen los productos entre las ciudades para intentar satisfacer las necesidades requeridas.
     */
    void redistribuir(Cjt_Productos& Productos);

    /**
     * @brief Pone un producto en el inventario de una ciudad si es posible.
     * 
     * @param Productos Conjunto de productos.
     * @param id_ciudad Nombre de la ciudad.
     * @param id_producto Identificador del producto.
     * 
     * @pre Se dispone de un conjunto de productos, el nombre de una ciudad y el identificador de un producto.
     * @post Si es posible, se añade el producto al inventario de la ciudad.
     */
    void poner_prod(Cjt_Productos& Productos, string id_ciudad, int id_producto);

    /**
     * @brief Modifica un producto en el inventario de una ciudad si es posible.
     * 
     * @param Productos Conjunto de productos.
     * @param id_ciudad Nombre de la ciudad.
     * @param id_producto Identificador del producto.
     * 
     * @pre Se dispone de un conjunto de productos, el nombre de una ciudad y el identificador de un producto.
     * @post Si es posible, se modifica el producto en el inventario de la ciudad.
     */
    void modificar_prod(Cjt_Productos& Productos, string id_ciudad, int id_producto);

    /**
     * @brief Quita un producto del inventario de una ciudad si es posible.
     * 
     * @param Productos Conjunto de productos.
     * @param id_ciudad Nombre de la ciudad.
     * @param id_producto Identificador del producto.
     * 
     * @pre Se dispone de un conjunto de productos, el nombre de una ciudad y el identificador de un producto.
     * @post Si es posible, se elimina el producto del inventario de la ciudad.
     */
    void quitar_prod(Cjt_Productos& Productos, string id_ciudad, int id_producto);

    /**
     * @brief Realiza un viaje con un barco buscando la ruta más beneficiosa.
     * 
     * @param Productos Conjunto de productos.
     * @param Barco Objeto Barco.
     * 
     * @pre Se dispone de un río con ciudades y un barco.
     * @post El barco busca la ruta con máximo beneficio y recorre dicha ruta vendiendo y comprando los productos indicados.
     */
    void hacer_viaje(Cjt_Productos& Productos, Barco& Barco);

    // ESCRITURA

    /**
      * @brief Consulta la información de un producto en el inventario de una ciudad avisando de fallos
      * 
      * @param Productos Conjunto de productos
      * @param id_ciudad ID de la ciudad
      * @param id_producto ID del producto
      * 
      * @pre Tenemos un conjunto de productos, el ID de una ciudad y el ID de un producto
      * @post Imprimimos por el canal de salida la información de dicho producto en el inventario de la ciudad
    */
    void consultar_prod(const Cjt_Productos& Productos, string id_ciudad, int id_producto);
    
    /**
      * @brief Escribe la información de una ciudad si existe
      * 
      * @param id_ciudad ID de la ciudad
      * 
      * @pre Tenemos un río con ciudades y el ID de una ciudad
      * @post Escribimos por el canal de salida la información de dicha ciudad si existe
    */
    void escribir_ciudad(string id_ciudad) const;
};

#endif // HEADERFILE_CUENCA
