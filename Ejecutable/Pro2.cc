/** @mainpage 
    Esta es la práctica de Programación 2 de la primavera de 2024 con el siguiente enunciado:

    Tenemos una cuenca fluvial formada por un río principal y varios afluentes. Hay
    ciudades en sus fuentes/nacimientos y en los puntos en que dos afluentes se unen, in-
    cluida la desembocadura, donde casualmente se unen dos afluentes. No hay ciudades
    en tramos del río que no sean nacimientos o uniones de afluentes.
    De cara a una posible representación gráfica, vamos a suponer que la desembocadura
    está al norte y las fuentes al sur, es decir, que las aguas van de sur a norte y cuando se
    va río arriba, se va de norte a sur. Las ciudades a partir de la desembocadura tienen dos
    ciudades “siguientes” mirando río arriba, una a mano izquierda y otra a mano derecha,
    y así sucesivamente hasta llegar a las de los nacimientos.
    El río y sus afluentes son unas importantes arterias comerciales entre las ciudades
    situadas en ellos. Las ciudades comercian entre ellas a través del río con unos productos
    que tienen un identificador numérico que va desde 1 a un cierto valor máximo. Los
    atributos de un producto son su peso y volumen.
    Cada ciudad tiene un identificador string que comienza por una letra y solo tiene
    letras y dígitos. Cada ciudad dispone de un inventario de productos, que no son nece-
    sariamente todos los posibles. Cada producto en el inventario de una ciudad tiene como
    atributos cuantas unidades de dicho producto tiene la ciudad y cuantas necesita. Puede
    pasar que tenga más unidades de las necesarias, exactamente las que necesita o menos
    (incluso 0). Todos los productos de un inventario de una ciudad se necesitan, es decir, el
    número de unidades necesitadas es mayor que 0.
    La cuenca dispone de un barquito dedicado a realizar viajes comerciales. En cada via-
    je, este barco intenta vender una cierta cantidad de un determinado producto e intenta
    comprar una cantidad (posiblemente diferente) de otro producto. Ambas cantidades se-
    rán no negativas y al menos una de ellas será estrictamente positiva. El barco no puede
    intentar vender y comprar el mismo producto, tienen que ser necesariamente diferentes.
    Solo se emplea el barco para una de las acciones de comercio entre las ciudades (ver la
    acción “Viajar” en la descripción posterior).
    Se comienza leyendo cuantos productos diferentes hay. Luego, se leen correlativa-
    mente sus pesos y volúmenes respectivos. Posteriormente se lee la estructura de la cuen-
    ca. Luego se leen los datos del barco, es decir, qué producto quiere comprar y cuantas
    unidades, y qué producto quiere vender y cuantas unidades. Estos datos iniciales no
    contienen situaciones erróneas.

    A partir de este momento las acciones que se pueden realizar son las siguientes:

    ------------------------------------------------------------------------------------------
    1)  leer_rio o lr: Se leerán los identificadores de las ciudades indicando la estructura
        de la cuenca. No se escribe nada. Los inventarios de las ciudades quedan vacíos. El
        barco conserva sus atributos de productos pero no ha realizado viajes en la nueva
        cuenca.
    ------------------------------------------------------------------------------------------
    2)  leer_inventario o li: Se leerá el identificador de una ciudad. Si la ciudad no existe
        se escribirá un mensaje de error. Si la ciudad existe, se leerá un número que in-
        dica la cantidad de elementos del inventario y para cada uno de ellos se leerá el
        identificador del producto, cuantas unidades tiene la ciudad y cuantas necesita. El
        número de unidades necesitadas siempre ha de ser mayor que 0. Aunque la ciu-
        dad no exista, habrá datos de su inventario que igualmente se han de leer aunque
        no se usen, para pasar a la siguiente operación.
    ------------------------------------------------------------------------------------------
    3)  leer_inventarios o ls: Se leerán los inventarios de ciudades del río. Todas las ciu-
        dades existirán. Los datos del inventario son como en la funcionalidad anterior.
        No necesariamente todas las ciudades del río tendrán inventario.
    ------------------------------------------------------------------------------------------
    4)  modificar_barco o mb: Se leerá el identificador del producto que se quiere comprar
        y la cantidad, y el identificador del producto que se quiere vender y la cantidad.
        Si algún producto no existe, se escribirá un mensaje de error. Si los dos productos
        son el mismo, se escribirá un mensaje de error. Se garantiza que ambas cantidades
        serán no negativas y al menos una de ellas será estrictamente positiva.
    ------------------------------------------------------------------------------------------
    5)  escribir_barco o eb: Se escriben los cuatro valores mencionados en la anterior ope-
        ración y los viajes realizados en la cuenca actual, en orden cronológico. Para cada
        viaje solo se ha de escribir la última ciudad visitada de la ruta escogida.
    ------------------------------------------------------------------------------------------
    6)  consultar_num o cn: Escribe cuantos productos diferentes hay.
    ------------------------------------------------------------------------------------------
    7)  agregar_productos o ap: Se lee el número de productos nuevos, mayor que 0. Sus
        identificadores serán correlativos a partir del último producto existente. Se leerán
        sus pesos y volúmenes respectivos.
    ------------------------------------------------------------------------------------------
    8)  escribir_producto o ep: Se lee el identificador de un producto. Si no existe el pro-
        ducto se escribe un mensaje de error. En caso contrario se escribe el peso y volumen
        del producto.
    ------------------------------------------------------------------------------------------
    9)  escribir_ciudad o ec: Se leerá el identificador de una ciudad. Si la ciudad no existe
        se escribirá un mensaje de error. Si la ciudad existe, se escribirá su inventario, y el
        peso y el volumen total de los productos almacenados.
    ------------------------------------------------------------------------------------------
    10) poner_prod o pp: Se leerá el identificador de una ciudad, de un producto y las
        unidades que tiene y que quiere. Si el producto no existe escribe un mensaje de
        error. Si la ciudad no existe, escribe un mensaje de error. Si el producto ya está en
        el inventario de la ciudad, escribe un mensaje de error. Si no hay errores, los datos
        de ese producto se añaden a la ciudad, modificándose el peso y el volumen total si
        hace falta. Se escribe el peso y el volumen total. El número de unidades necesitadas
        siempre ha de ser mayor que 0.
    ------------------------------------------------------------------------------------------
    11) modificar_prod o mp: Se leerá el identificador de una ciudad, de un producto y las
        unidades que tienen y que quiere. Si el producto no existe escribe un mensaje de
        error. Si la ciudad no existe, escribe un mensaje de error. Si el producto no está en
        el inventario de la ciudad, escribe un mensaje de error. Si no hay errores, los datos
        de ese producto sustituyen a los que había en la ciudad, modificándose el peso y
        el volumen total si hace falta. Se escribe el peso y el volumen total. El número de
        unidades necesitadas se puede modificar, pero siempre ha de ser mayor que 0.
    ------------------------------------------------------------------------------------------
    12) quitar_prod o qp: Se leerá el identificador de una ciudad y de un producto. Si
        el producto no existe escribe un mensaje de error. Si la ciudad no existe, escribe
        un mensaje de error. Si el producto no está en el inventario de la ciudad, escribe
        un mensaje de error. Si no hay errores, se quitan los datos de este producto en la
        ciudad, modificándose el peso y el volumen total si hace falta. Se escribe el peso y
        el volumen total.
    ------------------------------------------------------------------------------------------
    13) consultar_prod o cp: Se leerá el identificador de una ciudad y de un producto. Si
        el producto no existe escribe un mensaje de error. Si la ciudad no existe, escribe un
        mensaje de error. Si el producto no está en el inventario de la ciudad, escribe un
        mensaje de error. Si no hay errores, se escribe cuantas unidades de ese producto
        tiene y quiere la ciudad.
    ------------------------------------------------------------------------------------------
    14) comerciar o co: Se leerán los identificadores de dos ciudades. Si no existe alguna
        de las dos (o las dos), se escribe un mensaje de error. Si las ciudades existen y son
        la misma, se escribe un mensaje de error. Si las ciudades existen y son diferentes, 
        comercian entre ellas.
    ------------------------------------------------------------------------------------------
    15) redistribuir o re: No se leen datos. La ciudad de la desembocadura comercia con su
        ciudad río arriba a mano derecha y luego con la ciudad río arriba a mano izquierda,
        y así sucesivamente.
    ------------------------------------------------------------------------------------------
    16) hacer_viaje o hv: No se leen datos. El barco busca la ruta a partir de la desembo-
        cadura que le permita comprar y vender el mayor número posible de productos.
        En caso que haya más de una ruta que lo cumpla, se queda con la más corta, y en
        caso de que tengan la misma longitud, se queda con la que viene río arriba a mano
        derecha. Una vez encontrada la ruta, se hace el viaje y se compran y venden los
        productos a lo largo de la ruta, modificándose los inventarios de las ciudades. Se
        escribe el total de unidades de productos compradas y vendidas por el barco.
    ------------------------------------------------------------------------------------------
    17) fin: Acaba la ejecución.
    ------------------------------------------------------------------------------------------
*/

/** @file Pro2.cc
    @brief Programa principal
*/

#include "Cuenca.hh"
#include "Cjt_Productos.hh"

#ifndef NO_DIAGRAM
#include <vector>
using namespace std;
#endif

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
