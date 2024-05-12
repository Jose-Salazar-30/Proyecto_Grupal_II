#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// Función para cargar las palabras y sus traducciones desde un archivo
void cargarDiccionario(map<string, string>& diccionario) {
    ifstream archivo("diccionario.txt");
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    string palabra, traduccion, funcion;
    while (getline(archivo, palabra, ',') && getline(archivo, traduccion, ',') && getline(archivo, funcion)) {
        diccionario[palabra] = traduccion;
    }

    archivo.close();
}

// Función para traducir una línea de código C++
string traducirLinea(const string& linea, const map<string, string>& diccionario) {
    string lineaTraducida = linea;
    size_t pos = 0;

    // Buscar cada palabra en el diccionario y reemplazarla por su traducción
    for (const auto& par : diccionario) {
        while ((pos = lineaTraducida.find(par.first, pos)) != string::npos) {
            lineaTraducida.replace(pos, par.first.length(), par.second);
            pos += par.second.length();
        }
    }

    return lineaTraducida;
}

int main() {
    map<string, string> diccionario;
    cargarDiccionario(diccionario);

    vector<string> lineas_traducidas;

    string linea;

    cout << "Ingrese el código C++ a traducir (ingrese 'FIN' para terminar):\n";
    while (getline(cin, linea)) {
        // Convertir la línea a minúsculas para hacer la comparación sin importar el caso
        transform(linea.begin(), linea.end(), linea.begin(), ::tolower);

        // Si se ingresa "fin", comenzar a traducir
        if (linea == "fin") {
            break;
        }

        // Traducir la línea si se ingresó "fin"
        if (linea == "fin") {
            while (getline(cin, linea)) {
                string lineaTraducida = traducirLinea(linea, diccionario);
                lineas_traducidas.push_back(lineaTraducida);
            }
            break;
        }

        // Verificar si la línea contiene llaves y determinar si es una estructura de control
        size_t posInicio = linea.find('{');
        size_t posFin = linea.find('}');
        bool esEstructuraControl = (posInicio != string::npos && posFin != string::npos && posInicio < posFin);

        // Traducir la línea
        string lineaTraducida = traducirLinea(linea, diccionario);

        // Concatenar inicio y fin si es una estructura de control
        if (esEstructuraControl) {
            size_t posEspacio = lineaTraducida.find(' ');
            string estructuraControl = lineaTraducida.substr(0, posEspacio);
            lineaTraducida.insert(posEspacio, " " + estructuraControl + " {");
            lineaTraducida.append(" }");
        }

        lineas_traducidas.push_back(lineaTraducida);
    }

    // Imprimir las líneas de código traducidas
    for (const auto& linea : lineas_traducidas) {
        cout << linea << endl;
    }

    return 0;
}
