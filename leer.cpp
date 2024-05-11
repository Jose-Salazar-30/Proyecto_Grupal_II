void buscarpalabra(string palabra){
	ifstream archivo("diccionario.txt");
	string linea, palabraArchivo, traduccion, funcionalidad;
	
	if (!archivo) {
		cerr<<"Error al abrir el archivo."<<endl;
		return;
	}
	
	
	while (getline(archivo, linea)) {
		istringstream iss(linea);
		getline(iss, palabraArchivo,',');
		getline(iss, traduccion, ',');
		getline(iss, funcionalidad);
		
		if (palabraArchivo==palabra){
			cout<<"palabra encontrada:"<<palabraArchivo<<endl;
			cout << "traduccion:" <<traduccion <<endl;
			cout << "funcionalidad:" << funcionalidad <<endl;
			return;
		}
	}
	
	cout << "palabra no encontrada." << endl;
	archivo.close();
	
}