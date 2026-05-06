#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Producto {
    string nombre;
    string codigo;
    int cantidad;
    double precio;
};

//ACTUALIZA CANTIDAD
void actualizarCantidad(Producto inventario[], int totalProductos) {
    string cod; int nuevaCant; bool encontrado = false;
    cout << "\nACTUALIZAR CANTIDAD\nCódigo del producto: ";
    cin >> cod;
    cout << "Nueva cantidad: ";
    cin >> nuevaCant;
    for (int i = 0; i < totalProductos; ++i) {
        if (inventario[i].codigo == cod) {
            inventario[i].cantidad = nuevaCant;
            cout << "Producto" << inventario[i].nombre << " actualizado a " << nuevaCant << " uds.\n";
            encontrado = true; break;
        }
    }
    if (!encontrado) cout << "código no encontrado.\n";
}

//REPORTE BAJO INVENTARIO
void generarReporte(const Producto inventario[], int totalProductos) {
    cout << "\nREPORTE: PRODUCTOS CON MENOS DE 5 UNIDADES\n";
    cout << string(65, '=') << "\n";
    cout << left << setw(12) << "Código" << setw(25) << "Nombre" 
         << setw(12) << "Cantidad" << setw(10) << "Precio\n";
    cout << string(65, '-') << "\n";
    bool hay = false;
    cout << fixed << setprecision(2);
    for (int i = 0; i < totalProductos; ++i) {
        if (inventario[i].cantidad < 5) {
            cout << left << setw(12) << inventario[i].codigo
                 << setw(25) << inventario[i].nombre
                 << setw(12) << inventario[i].cantidad
                 << "$" << setw(9) << inventario[i].precio << "\n";
            hay = true;
        }
    }
    if (!hay) cout << "Todos los productos tienen stock >= 5.\n";
    cout << string(65, '=') << "\n";
}

int main() {
    const int MAX = 10;
    Producto inventario[MAX];
    int numProductos = 4; // Cantidad inicial de datos de prueba

    //Datos precargados para prueba inmediata
    inventario[0] = {"Laptop Gamer", "LAP-001", 12, 3500.00};
    inventario[1] = {"Mouse USB", "MOU-002", 3, 45.50};
    inventario[2] = {"Teclado RGB", "TEC-003", 8, 120.00};
    inventario[3] = {"Monitor 24\"", "MON-004", 2, 850.00};

    int opcion;
    do {
        cout << "\nGADGETXPRESS - INVENTARIO\n";
        cout << "1. Actualizar cantidad\n";
        cout << "2. Generar reporte bajo inventario\n";
        cout << "3. Salir\n";
        cout << "Opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1: actualizarCantidad(inventario, numProductos); break;
            case 2: generarReporte(inventario, numProductos); break;
            case 3: cout << "Saliendo...\n"; break;
            default: cout << "Opción inválida.\n";
        }
    } while (opcion != 3);
    return 0;
}

