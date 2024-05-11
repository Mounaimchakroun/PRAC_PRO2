#include <vector>
#include "Cuenca.hh"
#include "Cjt_Productos.hh"

using namespace std;

int main(){
    string input;
    Cuenca Cuenca_Fluvial;
    Barco Barco;
    Cjt_Productos Productos;

    //INICIALIZAR / PRODUCTOS -----------------
    int max_productos;

    cin >> max_productos;

    Productos.agregar_productos(max_productos);
    //-----------------------------------------
    //INICIALIZAR / RIO -----------------------
    Cuenca_Fluvial.leer_rio(Productos,Barco);
    //-----------------------------------------
    //INICIALIZAR / BARCO ---------------------
    Barco.modificar_barco(Productos);
    //-----------------------------------------

    while (cin >> input and input != "fin")
    {
        if (input == "leer_rio" or input == "lr"){
            cout <<'#'<<input;
            cout <<endl;
            Cuenca_Fluvial.leer_rio(Productos,Barco);
        }
        else if (input == "leer_inventario" or input == "li"){
            string id_ciudad;
            cin >> id_ciudad;
            cout <<'#'<<input;
            cout <<" "<< id_ciudad <<endl;
            Cuenca_Fluvial.leer_inventario(Productos,id_ciudad);
        }
        else if (input == "leer_inventarios" or input == "ls"){
            cout <<'#'<<input;
            cout<<endl;
            Cuenca_Fluvial.leer_inventarios(Productos);
        }
        else if (input == "modificar_barco" or input == "mb"){
            cout <<'#'<<input;
            cout<<endl;
            Barco.modificar_barco(Productos);
        }
        else if (input == "escribir_barco" or input == "eb"){
            cout <<'#'<<input;
            cout<<endl;
            Barco.escribir_barco();
        }
        else if (input == "consultar_num" or input == "cn"){
            cout <<'#'<<input;
            cout<<endl;
            cout << Productos.consultar_num() <<endl;
        }   
        else if (input == "agregar_productos" or input == "ap"){
            int n;
            cin >> n;
            cout <<'#'<<input;
            cout<<" "<< n <<endl;
            Productos.agregar_productos(n);
        }
        else if (input == "escribir_producto" or input == "ep"){
            int id_producto;
            cin >> id_producto;
            cout <<'#'<<input;
            cout<<" "<< id_producto <<endl;
            Productos.escribir_producto(id_producto);
        }
        else if (input == "escribir_ciudad" or input == "ec"){
            string id_ciudad;
            cin >> id_ciudad;
            cout <<'#'<<input;
            cout<<" "<< id_ciudad <<endl;
            Cuenca_Fluvial.escribir_ciudad(id_ciudad);
        }
        else if (input == "poner_prod" or input == "pp"){
            string id_ciudad;
            int id_producto;
            cin >> id_ciudad >> id_producto;
            cout <<'#'<<input;
            cout<<" "<< id_ciudad <<" "<< id_producto <<endl;
            Cuenca_Fluvial.poner_prod(Productos, id_ciudad, id_producto);
        }
        else if (input == "modificar_prod" or input == "mp"){
            string id_ciudad;
            int id_producto;
            cin >> id_ciudad >> id_producto;
            cout <<'#'<<input;
            cout<<" "<< id_ciudad <<" "<< id_producto <<endl;
            Cuenca_Fluvial.modificar_prod(Productos,id_ciudad,id_producto);
        }
        else if (input == "quitar_prod" or input == "qp"){
            string id_ciudad;
            int id_producto;
            cin >> id_ciudad >> id_producto;
            cout <<'#'<<input;
            cout<<" "<< id_ciudad <<" "<< id_producto <<endl;
            Cuenca_Fluvial.quitar_prod(Productos,id_ciudad,id_producto);
        }
        else if (input == "consultar_prod" or input == "cp"){
            string id_ciudad;
            int id_producto;
            cin >> id_ciudad >> id_producto;
            cout <<'#'<<input;
            cout<<" "<< id_ciudad <<" "<< id_producto <<endl;
            Cuenca_Fluvial.consultar_prod(Productos, id_ciudad, id_producto);
        }
        else if (input == "comerciar" or input == "co"){
            string id_ciudad_1, id_ciudad_2;
            cin >> id_ciudad_1 >> id_ciudad_2;
            cout <<'#'<<input;
            cout <<" "<< id_ciudad_1 <<" "<< id_ciudad_2 <<endl;
            Cuenca_Fluvial.comerciar(Productos,id_ciudad_1,id_ciudad_2);
        }
        else if (input == "redistribuir" or input == "re"){
            cout <<'#'<<input;
            cout<<endl;
            Cuenca_Fluvial.redistribuir(Productos);
        }
        else if (input == "hacer_viaje" or input == "hv"){
            cout <<'#'<<input;
            cout<<endl;
            Cuenca_Fluvial.hacer_viaje(Productos,Barco);
        }
        else if (input == "//"){
            string residuo;
            cin >> residuo;
        }
    }
    
}
