void leerArchivo() {
	ifstream archivo("diccionario.txt");
	string palabra, traducci''on, funcionalidad;
	
	if (!archivo){
		cerr <<"Error al abrir el archivo." << endl;
		return;
	}
	
	while (getline(archivo, palabra, ',')){
		getline(archivo, traduccion, ',');
		getline(arvhivo, funcionalidad);
		
		cout << "palabra: " << palabra << endl;
		cout << "Traduccion: " <<traduccion << endl;
		cout << "Funcionalidad: " << funcionalidad << endl;
		cout << "-------------------------" << endl;
	}

	archivo.close();
}
