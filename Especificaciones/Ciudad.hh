/** @file Ciudad.hh
    @brief Especificación de la clase Ciudad.
*/

#ifndef HEADERFILE_CIUDAD
#define HEADERFILE_CIUDAD

#ifndef NO_DIAGRAM
#include <map>
#endif

#include "Cjt_Productos.hh"

/**
 * @class Ciudad
 * @brief Representa una ciudad con un inventario de productos.
 *
 * La clase Ciudad mantiene un inventario de productos, junto con el peso y volumen total de los productos en la ciudad.
 */
class Ciudad
{
private:
    int _peso_total = 0;  ///< Peso total de la ciudad.
    int _volumen_total = 0;  ///< Volumen total de la ciudad.
    
    /**
     * @brief Inventario de productos.
     *
     * El inventario es un mapa donde:
     * - La clave es el ID del producto.
     * - El valor es un par donde:
     *   - first: número de unidades disponibles.
     *   - second: número de unidades necesarias.
     */
    map<int,pair<int, int>> _Inventario;

    map<int,pair<int, int>>::iterator _it_Inventario;  ///< Iterador para el mapa del inventario.
    int _num_de_productos = 0;  ///< Número total de productos en el inventario.

public:
    // CONSTRUCTORES / DESTRUCTORES:

    /**
     * @brief Constructor por defecto de la clase Ciudad.
     *
     * @pre Cierto.
     * @post Se crea una ciudad con peso y volumen total igual a cero y sin productos en el inventario.
     */
    Ciudad();

    // MODIFICADORES:

    /**
     * @brief Añade un producto al inventario de la ciudad.
     *
     * @param Productos Conjunto de productos disponibles.
     * @param id_producto Identificador del producto.
     * @param unidades_poseidas Unidades disponibles del producto.
     * @param unidades_necesarias Unidades necesarias del producto.
     * @return true si el producto se añadió con éxito, false en caso contrario.
     *
     * @pre El inventario puede estar vacío o no.
     * @post Se añade el producto especificado al inventario con las cantidades poseídas y necesarias.
     */
    bool poner_prod_c(Cjt_Productos& Productos, int id_producto, int unidades_poseidas, int unidades_necesarias);

    /**
     * @brief Modifica un producto existente en el inventario de la ciudad.
     *
     * @param Productos Conjunto de productos disponibles.
     * @param id_producto Identificador del producto.
     * @param unidades_poseidas Nuevas unidades disponibles del producto.
     * @param unidades_necesarias Nuevas unidades necesarias del producto.
     * @param notificacion_de_errores Indica si se deben notificar errores.
     * @return true si el producto se modificó con éxito, false en caso contrario.
     *
     * @pre El inventario debe contener el producto especificado.
     * @post Las unidades poseídas y necesarias del producto son modificadas.
     */
    bool modificar_prod_c(Cjt_Productos& Productos, int id_producto, int unidades_poseidas, int unidades_necesarias, bool notificacion_de_errores);

    /**
     * @brief Elimina un producto del inventario de la ciudad.
     *
     * @param Productos Conjunto de productos disponibles.
     * @param id_producto Identificador del producto.
     * @return true si el producto se eliminó con éxito, false en caso contrario.
     *
     * @pre El inventario puede estar vacío o no.
     * @post El producto especificado se elimina del inventario si existe.
     */
    bool quitar_prod_c(Cjt_Productos& Productos, int id_producto);

    /**
     * @brief Realiza comercio con otra ciudad.
     *
     * @param Productos Conjunto de productos disponibles.
     * @param ciudad_con_la_que_comerciaremos Referencia a la ciudad con la que se comerciará.
     *
     * @pre El inventario de la ciudad puede estar vacío o no y debe haber otra ciudad con la que comerciar.
     * @post Se realiza el comercio entre las dos ciudades.
     */
    void comerciar_c(Cjt_Productos& Productos, Ciudad& ciudad_con_la_que_comerciaremos);

    // CONSULTORES

    /**
     * @brief Consulta la información de un producto en el inventario de la ciudad.
     *
     * @param id_producto Identificador del producto.
     * @param info_producto Par que recibirá la información del producto (unidades poseídas y necesarias).
     * @param notificacion_de_errores Indica si se deben notificar errores.
     * @return true si el producto está en el inventario, false en caso contrario.
     *
     * @pre El inventario puede estar vacío o no.
     * @post Se consulta la información del producto especificado. Si el producto no está en el inventario, se devuelve false.
     */
    bool consultar_prod_c(int id_producto, std::pair<int, int>& info_producto, bool notificacion_de_errores) const;

    /**
     * @brief Consulta el peso total del inventario de la ciudad.
     * 
     * @return Peso total del inventario de la ciudad.
     *
     * @pre El inventario puede estar vacío o no.
     * @post Devuelve el peso total de todos los productos en la ciudad.
     */
    int consultar_peso_total() const;

    /**
     * @brief Consulta el volumen total del inventario de la ciudad.
     * 
     * @return Volumen total del inventario de la ciudad.
     *
     * @pre El inventario puede estar vacío o no.
     * @post Devuelve el volumen total de todos los productos en la ciudad.
     */
    int consultar_volumen_total() const;
    
    /**
     * @brief Limpia el inventario de la ciudad.
     *
     * @pre La ciudad puede tener un inventario vacío o lleno.
     * @post El inventario de la ciudad queda vacío.
     */
    void limpiar_inventario();
   
   // ESCRITURA

    /**
     * @brief Imprime el inventario de la ciudad.
     *
     * Imprime por el canal de salida el inventario de la ciudad junto con el peso y volumen total del inventario.
     *
     * @pre El inventario puede estar vacío o no.
     * @post El inventario de la ciudad se imprime en el canal de salida, incluyendo el peso y volumen total.
     */
    void escribir_ciudad_c() const;
};

#endif // HEADERFILE_CIUDAD
