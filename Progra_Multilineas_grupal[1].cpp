#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

// Funcion para cargar las palabras y sus traduciones desde un archivo
void cargarDiccionario(map<string, string>& diccionario) {
	ifstream archivo ("diccionario.txt");
	if (!archivo){
		cerr << "Error al abrir el archivo." << endl;
		return;
	}
	
	
	string palabra, traduccion, funcion;
	while (getline(archivo, palabra, ',') && getline(archivo, traduccion, ',') && getline(archivo,funcion)) {
				diccionario[palabra] = traduccion;
		
	}
	
	archivo.close();
}

// Funcion para traducir una linea de codigo C++
string  traducirLinea(const string& linea, const map<string, string>& diccionario) {
	string lineaTraducida = linea;
	size_t pos = 0;
	
	// Buscar cada palabra en el diccionario y reemplazarla por su traduccion
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
	
	string linea;
	
	cout <<"Ingrese el codigo C++ a traducir (ingrese 'fin' para terminar):\n";
	while (getline(cin,linea) && linea != "fin") {
		
		
		// Verificar si la linea contiene llaves y determinar si es una estructura de control
		size_t posInicio = linea.find('{');
		size_t posFin = linea.find('}');
		bool esEstructuraControl = (posInicio != string::npos && posFin != string::npos && posInicio < posFin);
		
		/*// Verificar si la linea contiene llaves y determinar si es una estructura de control
		size_t posInicio = linea.find('{');
		size_t posFin = linea.find('}');
		bool esEstructuraControl = (posInicio != string::nposFin != string::npos && posInicio <posFin);*/
		
		// Traducir la linea
		string lineaTraducida = traducirLinea(linea, diccionario);
		
		// Concatenar inicio y fin si es una estructura de control
		if (esEstructuraControl){
			size_t posEspacio = lineaTraducida.find(' ');
			string estructuraControl = lineaTraducida.substr(0, posEspacio);
			lineaTraducida.insert(posEspacio, " " + estructuraControl + " {");
			lineaTraducida.append(" }");
			
		}
	
		cout << lineaTraducida << endl;
	}
	
	
	return 0;
	
}
 
