/*
 * main.cpp
 * CCOM 4997 - Final Project: Simple Search Engine
 * Author: Alfredo Frontera
 * Date: December 2025
 *
 * Programa principal - interfaz de usuario
 */

#include "SearchEngine.h"
#include <sstream>

void mostrarInstrucciones() {
    cout << "\n========================================" << endl;
    cout << "     Motor de Busqueda Simple v1.0     " << endl;
    cout << "========================================" << endl;
    cout << "Instrucciones:" << endl;
    cout << "  - Ingrese 1 o 2 palabras para buscar" << endl;
    cout << "  - Escriba 'salir' para terminar" << endl;
    cout << "  - Escriba 'stats' para ver estadisticas" << endl;
    cout << "========================================\n" << endl;
}

void mostrarResultados(vector<DocFrequency>& results, const string& query) {
    cout << "\nResultados para: \"" << query << "\"" << endl;
    cout << "----------------------------------------" << endl;
    
    if (results.empty()) {
        cout << "No se encontraron resultados." << endl;
    } else {
        for (uint i = 0; i < results.size(); i++) {
            cout << (i + 1) << ". " << results[i].filename 
                 << " (frecuencia: " << results[i].frequency << ")" << endl;
        }
    }
    cout << "----------------------------------------\n" << endl;
}

int main(int argc, char* argv[]) {
    // Verificar argumentos
    if (argc < 2) {
        cout << "Uso: " << argv[0] << " <directorio>" << endl;
        cout << "Ejemplo: " << argv[0] << " ./moviesdb" << endl;
        return 1;
    }
    
    string directorio = argv[1];
    
    cout << "Inicializando motor de busqueda..." << endl;
    cout << "Directorio: " << directorio << endl;
    
    // Crear motor y construir indice
    SearchEngine engine(directorio);
    engine.buildIndex();
    
    if (engine.getFileCount() == 0) {
        cout << "Error: No se indexaron archivos. Verifique el directorio." << endl;
        return 1;
    }
    
    mostrarInstrucciones();
    engine.printStats();
    
    // Loop principal de busqueda
    string input;
    while (true) {
        cout << "Buscar> ";
        getline(cin, input);
        
        // Entrada vacia
        if (input.empty()) {
            continue;
        }
        
        // Comando salir
        if (input == "salir" || input == "exit" || input == "quit") {
            cout << "Hasta luego!" << endl;
            break;
        }
        
        // Comando estadisticas
        if (input == "stats") {
            engine.printStats();
            continue;
        }
        
        // Parsear palabras de entrada
        vector<string> palabras = tokenize(input, " ");
        
        if (palabras.size() == 0) {
            continue;
        } else if (palabras.size() == 1) {
            // Busqueda de una palabra
            vector<DocFrequency> results = engine.searchOne(palabras[0]);
            mostrarResultados(results, palabras[0]);
        } else if (palabras.size() == 2) {
            // Busqueda de dos palabras
            vector<DocFrequency> results = engine.searchTwo(palabras[0], palabras[1]);
            string query = palabras[0] + " " + palabras[1];
            mostrarResultados(results, query);
        } else {
            cout << "Por favor ingrese solo 1 o 2 palabras." << endl;
        }
    }
    
    return 0;
}
