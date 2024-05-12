#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void leerArchivo() {
    ifstream archivo("diccionario.txt");
    string palabra, traduccion, funcionalidad;

    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    while (getline(archivo, palabra, ',')) {
        getline(archivo, traduccion, ',');
        getline(archivo, funcionalidad);

        cout << "Palabra: " << palabra << endl;
        cout << "Traduccion: " << traduccion << endl;
        cout << "Funcionalidad: " << funcionalidad << endl;
        cout << "-------------------------" << endl;
    }

    archivo.close();
}

void buscarPalabra(string palabra) {
    ifstream archivo("diccionario.txt");
    string linea, palabraArchivo, traduccion, funcionalidad;

    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    while (getline(archivo, linea)) {
        istringstream iss(linea);
        getline(iss, palabraArchivo, ',');
        getline(iss, traduccion, ',');
        getline(iss, funcionalidad);

        if (palabraArchivo == palabra) {
            cout << "Palabra encontrada: " << palabraArchivo << endl;
            cout << "Traduccion: " << traduccion << endl;
            cout << "Funcionalidad: " << funcionalidad << endl;
            return;
        }
    }

    cout << "Palabra no encontrada." << endl;
    archivo.close();
}

void actualizarPalabra(string palabra, string traduccion, string funcionalidad) {
    ifstream archivo("diccionario.txt");
    ofstream archivoTemporal("diccionarioTemporal.txt");
    string linea, palabraArchivo, traduccionArchivo, funcionalidadArchivo;

    if (!archivo ||!archivoTemporal) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    while (getline(archivo, linea)) {
        istringstream iss(linea);
        getline(iss, palabraArchivo, ',');
        getline(iss, traduccionArchivo, ',');
        getline(iss, funcionalidadArchivo);

        if (palabraArchivo == palabra) {
            archivoTemporal << palabra << "," << traduccion << "," << funcionalidad << endl;
        } else {
            archivoTemporal << linea << endl;
        }
    }

    archivo.close();
    archivoTemporal.close();

    remove("diccionario.txt");
    rename("diccionarioTemporal.txt", "diccionario.txt");
}

void borrarPalabra(string palabra) {
    ifstream archivo("diccionario.txt");
    ofstream archivoTemporal("diccionarioTemporal.txt");
    string linea, palabraArchivo, traduccion, funcionalidad;

    if (!archivo ||!archivoTemporal) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    while (getline(archivo, linea)) {
        istringstream iss(linea);
        getline(iss, palabraArchivo, ',');
        getline(iss, traduccion, ',');
        getline(iss, funcionalidad);

        if (palabraArchivo!= palabra) {
            archivoTemporal << linea << endl;
        }
    }

    archivo.close();
    archivoTemporal.close();

    remove("diccionario.txt");
    rename("diccionarioTemporal.txt", "diccionario.txt");
}

int main() {
	string palabra, traduccion, funcionalidad;
    char opcion;

    do {
        cout << "Seleccione una opcion:" << endl;
        cout << "1. Leer archivo" << endl;
        cout << "2. Buscar palabra" << endl;
        cout << "3. Actualizar palabra" << endl;
        cout << "4. Borrar palabra" << endl;
        cout << "5. Agregar palabra" << endl;
        cout << "6. Salir" << endl;
        cin >> opcion;

        switch (opcion) {
            case '1':
                leerArchivo();
                break;
            case '2':
                cout << "Ingrese la palabra a buscar: ";
                cin >> palabra;
                buscarPalabra(palabra);
                break;
            case '3':
                cout << "Ingrese la palabra a actualizar: ";
                cin >> palabra;
                cout << "Ingrese la nueva traduccion: ";
                cin >> traduccion;
                cout << "Ingrese la nueva funcionalidad: ";
                cin >> funcionalidad;
                actualizarPalabra(palabra, traduccion, funcionalidad);
                break;
            case '4':
                cout << "Ingrese la palabra a borrar: ";
                cin >> palabra;
                borrarPalabra(palabra);
                break;
            case '5':
                {
                    ofstream archivo("diccionario.txt", ios::app);

                    if (!archivo) {
                        cerr << "Error al abrir el archivo." << endl;
                        return 1;
                    }

                    string palabra, traduccion, funcionalidad;
                    char respuesta;

                    do {
                        cout << "Ingrese Palabra: ";
                        cin >> palabra;

                        cout << "Ingrese Traduccion: ";
                        cin >> traduccion;

                        cout << "Ingrese Funcionalidad: ";
                        cin.ignore();
                        getline(cin, funcionalidad);

                        archivo << palabra << "," << traduccion << "," << funcionalidad << endl;

                        cout << "¿Desea agregar otra palabra? (s/n): ";
                        cin >> respuesta;
                    } while (respuesta == 's' || respuesta == 'S');

                    archivo.close();
                }
                break;
            case '6':
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
        }

    } while (opcion != '6');

    cout << "Programa Finalizado!" << endl;

    return 0;
}
