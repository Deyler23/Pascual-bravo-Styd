#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

//Estructura de datos base
struct Producto {
    string nombre;
    string codigo;
    int cantidad;
    double precio;
};

//Función de ayuda, responsabilidad única: buscar por código
// Retorna el índice del producto o -1 si no existe.
int buscarProducto(const vector<Producto>& inventario, const string& codigo) {
    for (size_t i = 0; i < inventario.size(); ++i) {
        if (inventario[i].codigo == codigo) return i;
    }
    return -1;
}

//Mostrar menú - responsabilidad: interactuar con usuario
int mostrarMenu() {
    cout << "\n";
    cout << "============================================\n";
    cout << "\nGADGETXPRESS - SISTEMA DE INVENTARIO\n";
    cout << "============================================\n";
    cout << "1. Agregar nuevo producto\n";
    cout << "2. Listar todos los productos\n";
    cout << "3. Actualizar cantidad de producto\n";
    cout << "4. Generar reporte de bajo inventario\n";
    cout << "5. Salir\n";
    cout << "--------------------------------------------\n";
    cout << "Seleccione una opción: ";
    int opcion;
    cin >> opcion;
    cin.ignore(); // Limpia salto de línea residual
    return opcion;
}

//Agregar producto (responsabilidad: validar y insertar)
void agregarProducto(vector<Producto>& inventario) {
    string codigo, nombre;
    int cantidad;
    double precio;

    cout << "\nREGISTRO DE NUEVO PRODUCTO\n";
    cout << "Código: "; cin >> codigo;
    cin.ignore();

    //Reutiliza función auxiliar para evitar duplicados
    if (buscarProducto(inventario, codigo) != -1) {
        cout << "Error: Ya existe un producto con el código '" << codigo << "'.\n";
        return;
    }

    cout << "Nombre: "; getline(cin, nombre);
    cout << "Cantidad: "; cin >> cantidad;
    cout << "Precio: $"; cin >> precio;

    inventario.push_back({nombre, codigo, cantidad, precio});
    cout << "Producto agregado exitosamente.\n";
}

//Listar productos - responsabilidad: imprimir inventario completo
void listarProductos(const vector<Producto>& inventario) {
    if (inventario.empty()) {
        cout << "\nEl inventario está vacío.\n";
        return;
    }
    cout << "\nLISTA COMPLETA DE PRODUCTOS\n";
    cout << left 
         << setw(10) << "Código" 
         << setw(25) << "Nombre"
         << setw(10) << "Cantidad" 
         << setw(10) << "Precio\n";
    cout << string(55, '-') << "\n";
    cout << fixed << setprecision(2);

    for (const auto& p : inventario) {
        cout << left 
             << setw(10) << p.codigo
             << setw(25) << p.nombre
             << setw(10) << p.cantidad
             << "$" << setw(9) << p.precio << "\n";
    }
    cout << string(55, '-') << "\n";
}

//Actualizar cantidad - responsabilidad: modificar stock existente
void actualizarCantidad(vector<Producto>& inventario) {
    string codigo;
    int nuevaCantidad;

    cout << "\nACTUALIZAR CANTIDAD\n";
    cout << "Código del producto: "; cin >> codigo;

    //Reutiliza función auxiliar para localizar
    int idx = buscarProducto(inventario, codigo);
    if (idx == -1) {
        cout << "Producto no encontrado.\n";
        return;
    }

    cout << "Nueva cantidad para '" << inventario[idx].nombre << "': ";
    cin >> nuevaCantidad;
    inventario[idx].cantidad = nuevaCantidad;
    cout << "Cantidad actualizada correctamente.\n";
}

//Reporte bajo inventario - responsabilidad: filtrar y mostrar stock crítico
void generarReporteBajoInventario(const vector<Producto>& inventario) {
    cout << "\nREPORTE DE BAJO INVENTARIO (< 5 unidades)\n";
    cout << left 
         << setw(10) << "Código" 
         << setw(25) << "Nombre"
         << setw(10) << "Cantidad" 
         << setw(10) << "Precio\n";
    cout << string(55, '-') << "\n";

    bool hayStockBajo = false;
    cout << fixed << setprecision(2);

    for (const auto& p : inventario) {
        if (p.cantidad < 5) {
            cout << left 
                 << setw(10) << p.codigo
                 << setw(25) << p.nombre
                 << setw(10) << p.cantidad
                 << "$" << setw(9) << p.precio << "\n";
            hayStockBajo = true;
        }
    }
    if (!hayStockBajo) {
        cout << "Todos los productos tienen stock suficiente.\n";
    }
    cout << string(55, '-') << "\n";
}

//Programa principal - responsabilidad ÚNICA: orquestar flujo
int main() {
    //Inventario dinámico - mejor práctica profesional vs arreglos estáticos
    vector<Producto> inventario = {
        {"Mouse USB", "MOU-001", 3, 45.50},
        {"Teclado Mecánico", "TEC-002", 12, 120.00},
        {"Teclado RGB", "MON-003", 2, 850.00},
        {"Monitor 24",   "TEC-004",  2,  850.00}
    };

    int opcion;
    do {
        opcion = mostrarMenu(); //Solo muestra y captura
        switch (opcion) {
            case 1: agregarProducto(inventario); break;
            case 2: listarProductos(inventario); break;
            case 3: actualizarCantidad(inventario); break;
            case 4: generarReporteBajoInventario(inventario); break;
            case 5: cout << "Saliendo del sistema...\n"; break;
            default: cout << "Opción no válida.\n";
        }
    } while (opcion != 5);

    return 0;
}

