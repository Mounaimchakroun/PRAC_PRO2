/** @file Cuenca.hh
    @brief Especificación de Cuenca.
*/

#ifndef HEADERFILE_CUENCA
#define HEADERFILE_CUENCA

#include "Ciudad.hh"
#include "Barco.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#endif

class Cuenca      
{
private:
    /// Arbol de id de las ciudades
    BinTree<string> _cuenca;
    /// Mapa de las ciudades
    map<string, Ciudad> _mapa_ciudades;
    /// "Iterator" del mapa de la ciudad
    map<string, Ciudad>::iterator _it_mapa_ciudad;

    /**
      * @brief Función privada para redistribuir productos entre nodos de un árbol
      * @param Productos Conjunto de productos a redistribuir
      * @param arbol_cuenca Árbol binario del río
      * @pre Introducimos el árbol binario del río
      * @post Hace que comercien cada nodo con sus hijos
    */
    void aux_redistribuir(Cjt_Productos& Productos, const BinTree<string>& arbol_cuenca);

    /**
      * @brief Función privada para leer el árbol binario del río y el mapa de ciudades desde el canal de entrada 
      * @param Producto Conjunto de productos
      * @param new_map Mapa de ciudades
      * @return Árbol binario del río
      * @pre Introducimos un nuevo mapa y la entrada de un árbol binario por el canal de entrada
      * @post Obtenemos el árbol binario del río y el mapa que relaciona cada ID con su ciudad correspondiente
    */
    BinTree<string> aux_lectura_rio(const Cjt_Productos& Producto, map<string, Ciudad>& new_map);
    
    /**
      * @brief Función para obtener la lista de nombres de ciudades formando la ruta más beneficiosa para el barco
      * @param Productos Conjunto de productos
      * @param arbol_cuenca Árbol binario del río
      * @param Barco Objeto Barco
      * @return Lista de nombres de ciudades
      * @pre Introducimos el árbol binario del río y el barco
      * @post Nos proporciona la lista de nombres de ciudades donde estas forman la ruta más beneficiosa para el barco
    */
    list<string> recorido_con_max_beneficio(const Cjt_Productos& Productos, const BinTree<string>& arbol_cuenca, const Barco& Barco);
    
    /**
       Pre:
       Post:
    */
    BinTree<pair<string,pair<int,int>>> Obtener_arbol_de_ventas(int id_prod_a_comprar, int id_prod_a_vender, int productos_comprados, int productos_vendidos, const BinTree<string>& nodo);
    
    /**
       Pre:
       Post:
    */
    void aux_viajar(Cjt_Productos &Productos, Barco& Barco, int id_prod_a_comprar, int id_prod_a_vender, int productos_comprados, int productos_vendidos);
    
public:
    // CONSTRUCTORES / DESTRUCTORES:

    /**
      * @brief Constructor de la clase Cuenca
      * @pre Cierto
      * @post Obtenemos una cuenca fluvial
    */
    Cuenca();

    // MODIFICADORES:

    /**
      * @brief Lee la forma del río
      * @param Productos Conjunto de productos
      * @param Barco Objeto Barco
      * @pre Tenemos una cuenca fluvial, productos y un barco
      * @post Leemos la forma del río
    */
    void leer_rio(const Cjt_Productos& Productos, Barco& Barco);

    /**
      * @brief Lee los inventarios de las ciudades
      * @param Productos Conjunto de productos
      * @pre Tenemos un conjunto de productos y k nombres de ciudades en el canal de entrada
      * @post Proporcionamos a las ciudades citadas elementos de nuestro repertorio de productos disponibles
    */
    void leer_inventarios(Cjt_Productos& Productos);

    /**
      * @brief Lee el inventario de una ciudad
      * @param Productos Conjunto de productos
      * @param id_ciudad Nombre de la ciudad
      * @pre Tenemos un conjunto de ciudades y el nombre de una ciudad en la entrada de la función, y un número n que representa la cantidad de productos que queremos depositar en el inventario
      * @post Depositamos en el inventario de esta ciudad con los n elementos depositados
    */
    void leer_inventario(Cjt_Productos& Productos, string id_ciudad);

    /**
      * @brief Hace comerciar dos ciudades
      * @param Productos Conjunto de productos
      * @param id_ciudad_1 Nombre de la primera ciudad
      * @param id_ciudad_2 Nombre de la segunda ciudad
      * @pre Disponemos del nombre de dos ciudades y un conjunto de productos
      * @post Hacemos que comercien las dos ciudades
    */
    void comerciar(Cjt_Productos& Productos, string id_ciudad_1, string id_ciudad_2);

    /**
      * @brief Redistribuye productos entre las ciudades a lo largo del río 
      * @param Productos Conjunto de productos
      * @pre Tenemos un río con ciudades
      * @post Redistribuimos los productos entre las ciudades desde la desembocadura hasta los nacimientos de forma que intentemos que las ciudades cumplan las cantidades necesarias requeridas, si es posible
    */
    void redistribuir(Cjt_Productos& Productos);

    /**
      * @brief Pone un producto en el inventario de una ciudad si es posible
      * @param Productos Conjunto de productos
      * @param id_ciudad Nombre de la ciudad
      * @param id_producto Identificador del producto
      * @pre Tenemos un conjunto de productos, el nombre de una ciudad y el identificador de un producto
      * @post Si es posible pondremos el producto deseado dentro del inventario de la ciudad
    */
    void poner_prod(Cjt_Productos& Productos, string id_ciudad, int id_producto);

    /**
      * @brief Modifica un producto en el inventario de una ciudad si es posible 
      * @param Productos Conjunto de productos
      * @param id_ciudad Nombre de la ciudad
      * @param id_producto Identificador del producto
      * @pre Tenemos un conjunto de productos, el nombre de una ciudad y el identificador de un producto
      * @post Si es posible modificaremos el producto que hay en la ciudad con dicho identificador
    */
    void modificar_prod(Cjt_Productos& Productos, string id_ciudad, int id_producto);

    /**
      * @brief Quita un producto del inventario de una ciudad si es posible
      * @param Productos Conjunto de productos
      * @param id_ciudad Nombre de la ciudad
      * @param id_producto Identificador del producto
      * @pre Tenemos un conjunto de productos, el nombre de una ciudad y el identificador de un producto
      * @post Si es posible eliminaremos el producto del inventario
    */
    void quitar_prod(Cjt_Productos& Productos, string id_ciudad, int id_producto);

    /**
      * @brief Realiza un viaje con un barco buscando la ruta más beneficiosa
      * @param Productos Conjunto de productos
      * @param Barco Objeto Barco
      * @pre Tenemos un río con ciudades y un barco
      * @post El barco busca la ruta con máximo beneficio y recorre dicha ruta vendiendo y comprando los productos ya indicados
    */
    void hacer_viaje(Cjt_Productos& Productos, Barco& Barco);

    // ESCRITURA

    /**
      * @brief Consulta la información de un producto en el inventario de una ciudad avisando de fallos
      * @param Productos Conjunto de productos
      * @param id_ciudad ID de la ciudad
      * @param id_producto ID del producto
      * @pre Tenemos un conjunto de productos, el ID de una ciudad y el ID de un producto
      * @post Imprimimos por el canal de salida la información de dicho producto en el inventario de la ciudad
    */
    void consultar_prod(const Cjt_Productos& Productos, string id_ciudad, int id_producto);

    /**
      * @brief Consulta la información de un producto en el inventario de una ciudad sin avisar de fallos
      * @param Productos Conjunto de productos
      * @param id_ciudad ID de la ciudad
      * @param id_producto ID del producto
      * @pre Tenemos un conjunto de productos, el ID de una ciudad y el ID de un producto
      * @post Imprimimos por el canal de salida la información de dicho producto en el inventario de la ciudad
    */
    void consultar_prod_c_sin_notificacion_de_errores(const Cjt_Productos& Productos, string id_ciudad, int id_producto);

    /**
      * @brief Escribe la información de una ciudad si existe
      * @param id_ciudad ID de la ciudad
      * @pre Tenemos un río con ciudades y el ID de una ciudad
      * @post Escribimos por el canal de salida la información de dicha ciudad si existe
    */
    void escribir_ciudad(string id_ciudad) const;
};
#endif