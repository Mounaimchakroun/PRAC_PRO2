#include "Error_Module.hh"

void error_notification(int num){
    string error;

    if (num == 1) error = "no existe el producto";
    else if (num == 2) error = "no existe la ciudad";
    else if (num == 3) error = "no se puede comprar y vender el mismo producto";
    else if (num == 4) error = "la ciudad ya tiene el producto";
    else if (num == 5) error = "la ciudad no tiene el producto";
    else if (num == 6) error = "unidades necesarias <= 0";
    else if (num == 7) error = "comando no disponible";
    else if (num == 8) error = "no se puede comprar y vender el mismo producto";
    
    cout << "error: " << error <<endl;
}