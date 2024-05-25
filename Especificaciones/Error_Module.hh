/** @file Error_Module.hh
    @brief Especificación del módulo encargado de los errores.
*/

#ifndef HEADERFILE_ERROR_MODULE
#define HEADERFILE_ERROR_MODULE

#ifndef NO_DIAGRAM
#include <iostream>
#endif

using namespace std;

/**
 * @brief Notifica un error especificado por su número.
 * 
 * @param num Número del error a notificar.
 * 
 * @pre El número de error debe estar entre 1 y 9.
 * @post Se muestra por el canal de salida el mensaje de error correspondiente.
 * 
 * @b LISTA_DE_ERRORES:
 * 
 *   - (1) No existe el producto.
 *   - (2) No existe la ciudad.
 *   - (3) No se puede comprar y vender el mismo producto.
 *   - (4) La ciudad ya tiene el producto.
 *   - (5) La ciudad no tiene el producto.
 *   - (6) Unidades necesarias <= 0.
 *   - (7) Comando no disponible.
 *   - (8) No se puede comprar y vender el mismo producto.
 *   - (9) Ciudad repetida.
 * --------------------------------------------------------
 */
void error_notification(int num);

#endif // HEADERFILE_ERROR_MODULE
