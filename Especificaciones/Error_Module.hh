#ifndef HEADERFILE_ERROR_MODULE
#define HEADERFILE_ERROR_MODULE

#include <iostream> 
using namespace std;

/**
 * @brief Notifica un error especificado por su número.
 * 
 * @pre Hay un número del 1 al 8 que equivale a un error.
 * @post Devuelve por el canal de salida el error correspondiente.
 * 
 * @param num Número del error a notificar.
 * 
 * @b Lista de Errores:
 *   - (1) No existe el producto.
 *   - (2) No existe la ciudad.
 *   - (3) No se puede comprar y vender el mismo producto.
 *   - (4) La ciudad ya tiene el producto.
 *   - (5) La ciudad no tiene el producto.
 *   - (6) Unidades necesarias <= 0.
 *   - (7) Comando no disponible.
 *   - (8) No se puede comprar y vender el mismo producto.
 */
void error_notification(int num);

#endif
