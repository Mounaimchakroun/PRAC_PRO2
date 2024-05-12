/** @file Barco.hh
    @brief Especificación de Barco.
*/

#ifndef HEADERFILE_BARCO
#define HEADERFILE_BARCO

#include "Cjt_Productos.hh"

#ifndef NO_DIAGRAM
#include <list>
#endif

class Barco {
private:
    // ID del producto a vender
    int _id_producto_a_vender;
    // Cantidad del producto a vender
    int _cantidad_producto_a_vender;

    // ID del producto a comprar
    int _id_producto_a_comprar;
    // Cantidad del producto a comprar
    int _cantidad_producto_a_comprar;

    // Viajes realizados en orden cronológico
    list<string> _viajes_realizados;

public:
    // CONSTRUCTORES

    /**
     * @brief Constructor de Barco.
     * 
     * @pre Cierto.
     * @post Se crea un objeto Barco.
     */
    Barco();

    // MODIFICADORES

    /**
     * @brief Modifica los productos que el barco compra y vende, así como las cantidades.
     * 
     * @pre En el canal de salida hay el ID del producto que se quiere comprar y vender y la cantidad de cada uno.
     *      Las dos cantidades no son negativas y al menos una de ellas es estrictamente positiva.
     * @post Se modifican los IDs de los productos que el barco quiere comprar y vender y las cantidades asociadas.
     * 
     * @param Productos Conjunto de productos.
     */
    void modificar_barco(Cjt_Productos& Productos);

    /**
     * @brief Añade al registro de ciudades el nombre de la última ciudad donde el barco ha estado.
     * 
     * @pre Cierto.
     * @post Se añade el nombre de la última ciudad al registro de ciudades.
     * 
     * @param ciudad Nombre de la ciudad a añadir al registro.
     */
    void agregar_ultima_ciudad_consultada(string ciudad);

    /**
     * @brief Elimina el registro de ciudades.
     * 
     * @pre Cierto.
     * @post Se borra el registro de ciudades.
     */
    void borrar_registro_ciudades();
    
    // CONSULTORES
    
    /**
     * @brief Obtiene el ID del producto que el barco va a vender.
     * 
     * @pre El barco tiene productos a vender.
     * @post Se obtiene el ID del producto a vender.
     * 
     * @return ID del producto a vender.
     */
    int cons_id_producto_a_vender() const;

    /**
     * @brief Obtiene el ID del producto que el barco va a comprar.
     * 
     * @pre El barco tiene productos a comprar.
     * @post Se obtiene el ID del producto a comprar.
     * 
     * @return ID del producto a comprar.
     */
    int cons_id_producto_a_comprar() const;

    /**
     * @brief Obtiene la cantidad del producto que el barco va a vender.
     * 
     * @pre El barco tiene productos a vender.
     * @post Se obtiene la cantidad del producto a vender.
     * 
     * @return Cantidad del producto a vender.
     */
    int consultat_cantidad_a_vender() const;

    /**
     * @brief Obtiene la cantidad del producto que el barco va a comprar.
     * 
     * @pre El barco tiene productos a comprar.
     * @post Se obtiene la cantidad del producto a comprar.
     * 
     * @return Cantidad del producto a comprar.
     */
    int consultat_cantidad_a_comprar() const;

    
   // ESCRITURA

    /**
     * @brief Escribe por el canal de salida la información del barco.
     * 
     * @pre El barco tiene productos a comprar y vender, y las cantidades correspondientes.
     * @post Se imprime por el canal de salida el producto que se compra y se vende, así como las cantidades.
     *       Además, se imprime las últimas ciudades donde acabaron las rutas de comercio que el barco ha hecho.
     */
    void escribir_barco();
};

#endif
