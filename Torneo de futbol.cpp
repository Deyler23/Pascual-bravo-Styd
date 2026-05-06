#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Equipo {
    string nombre;
    int partidosJugados;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;
    int puntos;
};

int totalEquipos = 16;
const int MAX_EQUIPOS = 20;

//Reconstruir empatados y perdidos
void reconstruirDatos(Equipo equipos[], int n) {
    for (int i = 0; i < n; i++) {
        
        //puntos = 3*G + 1*E  =>  E = puntos - 3*G
        int empatados = equipos[i].puntos - (3 * equipos[i].partidosGanados);
        
        //perdidos = jugados - ganados - empatados
        int perdidos = equipos[i].partidosJugados - equipos[i].partidosGanados - empatados;
        equipos[i].partidosEmpatados = empatados;
        equipos[i].partidosPerdidos  = perdidos;
    }
}

//Imprimir encabezado de tabla
void imprimirEncabezado() {
    cout << "\n"
         << left  << setw(25) << "Equipo"
         << right << setw(5)  << "PJ"
         << right << setw(5)  << "PG"
         << right << setw(5)  << "PE"
         << right << setw(5)  << "PP"
         << right << setw(7)  << "Puntos"
         << endl;
    cout << string(52, '-') << endl;
}

//Imprimir una fila de equipo
void imprimirEquipo(const Equipo& e, int pos) {
    cout << left  << setw(3)  << pos
         << left  << setw(22) << e.nombre
         << right << setw(5)  << e.partidosJugados
         << right << setw(5)  << e.partidosGanados
         << right << setw(5)  << e.partidosEmpatados
         << right << setw(5)  << e.partidosPerdidos
         << right << setw(7)  << e.puntos
         << endl;
}

//Opción 1: Tabla de mayor a menor
void tablaMayorAMenor(Equipo equipos[], int n) {
    
    //Copia para no alterar el arreglo original
    Equipo temp[MAX_EQUIPOS];
    for (int i = 0; i < n; i++) temp[i] = equipos[i];

    //Burbuja descendente
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (temp[j].puntos < temp[j+1].puntos)
                swap(temp[j], temp[j+1]);

    cout << "\n=== TABLA DE POSICIONES (Mayor a Menor) ===" << endl;
    imprimirEncabezado();
    for (int i = 0; i < n; i++)
        imprimirEquipo(temp[i], i + 1);
        cout << "\n" << endl;
}

//Opción 2: Tabla de menor a mayor
void tablaMenorAMayor(Equipo equipos[], int n) {
    Equipo temp[MAX_EQUIPOS];
    for (int i = 0; i < n; i++) temp[i] = equipos[i];

    //Burbuja ascendente
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (temp[j].puntos > temp[j+1].puntos)
                swap(temp[j], temp[j+1]);

    cout << "\n=== TABLA DE POSICIONES (Menor a Mayor) ===" << endl;
    imprimirEncabezado();
    for (int i = 0; i < n; i++)
        imprimirEquipo(temp[i], i + 1);
        cout << "\n" << endl;
}

//Opción 3: Equipo con más empates
void equipoMasEmpates(Equipo equipos[], int n) {
    int maxIdx = 0;
    for (int i = 1; i < n; i++)
        if (equipos[i].partidosEmpatados > equipos[maxIdx].partidosEmpatados)
            maxIdx = i;

    cout << "\n=== EQUIPO CON MAS EMPATES ===" << endl;
    imprimirEncabezado();
    imprimirEquipo(equipos[maxIdx], maxIdx + 1);
    cout << "\n" << endl;
}

//Opción 4: Buscar equipo por nombre
void buscarEquipo(Equipo equipos[], int n) {
    string nombre;
    cout << "\nIngrese el nombre del equipo a buscar: ";
    cin.ignore();
    getline(cin, nombre);

    bool encontrado = false;
    for (int i = 0; i < n; i++) {
        //Comparación case-insensitive
        string a = equipos[i].nombre, b = nombre;
        for (char& c : a) c = tolower(c);
        for (char& c : b) c = tolower(c);

        if (a == b) {
            cout << "\n=== INFORMACION DEL EQUIPO ===" << endl;
            imprimirEncabezado();
            imprimirEquipo(equipos[i], i + 1);
            encontrado = true;
            break;
            cout << "\n" << endl;
        }
    }
    if (!encontrado)
        cout << "\nEquipo no encontrado." << endl;
}

//Verificar consistencia de datos
bool verificarConsistencia(const Equipo& e) {
    int puntosEsperados = (3 * e.partidosGanados) + (1 * e.partidosEmpatados);
    int jugadosEsperados = e.partidosGanados + e.partidosEmpatados + e.partidosPerdidos;

    if (e.puntos != puntosEsperados) {
        cout << "\n  [ERROR] Los puntos no son consistentes." << endl;
        cout << "  Se esperaban: " << puntosEsperados
             << " pero se ingresaron: " << e.puntos << endl;
        return false;
    }
    if (e.partidosJugados != jugadosEsperados) {
        cout << "\n  [ERROR] Los partidos jugados no son consistentes." << endl;
        cout << "  Se esperaban: " << jugadosEsperados
             << " pero se ingresaron: " << e.partidosJugados << endl;
        return false;
    }
    return true;
}

//Opción 5: Agregar nuevo equipo
void agregarEquipo(Equipo equipos[], int& n) {
    if (n >= MAX_EQUIPOS) {
        cout << "\nNo se pueden agregar mas equipos (limite de 4 nuevos alcanzado)." << endl;
        return;
    }

    Equipo nuevo;
    cout << "\n=== AGREGAR NUEVO EQUIPO ===" << endl;
    cin.ignore();
    cout << "Nombre del equipo: ";
    getline(cin, nuevo.nombre);
    cout << "Partidos jugados:  "; cin >> nuevo.partidosJugados;
    cout << "Partidos ganados:  "; cin >> nuevo.partidosGanados;
    cout << "Partidos empatados:"; cin >> nuevo.partidosEmpatados;
    cout << "Partidos perdidos: "; cin >> nuevo.partidosPerdidos;
    cout << "Puntos:            "; cin >> nuevo.puntos;
    cout << "\n" << endl;

    if (verificarConsistencia(nuevo)) {
        equipos[n] = nuevo;
        n++;
        cout << "\n  Equipo agregado exitosamente!" << endl;
    } else {
        cout << "\n  Equipo NO guardado por datos inconsistentes." << endl;
    }
}

//Menú principal
void mostrarMenu() {
    cout << "   TORNEO DE FUTBOL INTERGALACTICO    " << endl;
    cout << "══════════════════════════════════════" << endl;
    cout << "  1. Tabla de posiciones (Mayor-Menor)" << endl;
    cout << "  2. Tabla de posiciones (Menor-Mayor)" << endl;
    cout << "  3. Equipo con mas empates           " << endl;
    cout << "  4. Buscar equipo por nombre         " << endl;
    cout << "  5. Agregar nuevo equipo             " << endl;
    cout << "  0. Salir                            " << endl;
    cout << "══════════════════════════════════════" << endl;
    cout << "Seleccione una opcion: ";
    cout << "\n" << endl;
}

//Principio
int main() {
    Equipo equipos[MAX_EQUIPOS] = {
        {"Andromeda FC",          12, 4, 0, 0, 13},
        {"Vulcano Academia",      11, 2, 0, 0, 10},
        {"Orion Confederacion",   11, 4, 0, 0, 14},
        {"Sirio Estrellas",       10, 6, 0, 0, 20},
        {"Caronte Titanes",       11, 1, 0, 0,  6},
        {"Quiron Cometas",        10, 5, 0, 0, 17},
        {"Pegaso Pulsares",       11, 7, 0, 0, 24},
        {"Osos Cosmicos",         11, 5, 0, 0, 18},
        {"Via Lactea Nomadas",    11, 6, 0, 0, 20},
        {"Leonidas FC",           11, 5, 0, 0, 16},
        {"Cangrejo Fortaleza",    11, 4, 0, 0, 16},
        {"Cefeo Cumulo",          11, 3, 0, 0, 14},
        {"Atletico Interestelar", 11, 4, 0, 0, 16},
        {"Deportivo Galactico",   11, 2, 0, 0,  8},
        {"Estrella Estelar",      11, 5, 0, 0, 17},
        {"Inter Galaxia",         10, 2, 0, 0, 10}
        cout << "\n" << endl;
    };

    reconstruirDatos(equipos, totalEquipos);

    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1: tablaMayorAMenor(equipos, totalEquipos); break;
            case 2: tablaMenorAMayor(equipos, totalEquipos); break;
            case 3: equipoMasEmpates(equipos, totalEquipos); break;
            case 4: buscarEquipo(equipos, totalEquipos);     break;
            case 5: agregarEquipo(equipos, totalEquipos);    break;
            case 0: cout << "\nHasta luego!" << endl;        break;
            default: cout << "\nOpcion invalida." << endl;   break;
        }
    } while (opcion != 0);

    return 0;
}
