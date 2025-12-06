/*
 * SearchEngine.h
 * CCOM 4997 - Final Project: Simple Search Engine
 * Author: Alfredo Frontera
 * Date: December 2025
 *
 * Clase principal del motor de busqueda con indice invertido
 */

#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include "ParsedFile.h"
#include <map>
#include <algorithm>

using namespace std;

// Estructura para almacenar archivo y su frecuencia
struct DocFrequency {
    string filename;
    int frequency;
    
    DocFrequency() : filename(""), frequency(0) {}
    DocFrequency(string f, int freq) : filename(f), frequency(freq) {}
};

class SearchEngine {
private:
    // Indice invertido: palabra -> vector de (archivo, frecuencia)
    map<string, vector<DocFrequency>> invertedIndex;
    
    string directoryPath;
    int totalFilesIndexed;
    
    // Convierte palabra a minusculas
    string toLowercase(const string& word);
    
    // Limpia palabra de caracteres especiales
    string cleanWord(const string& word);
    
    // Comparador para ordenar por frecuencia descendente
    static bool compareByFreq(const DocFrequency& a, const DocFrequency& b);

public:
    SearchEngine(string dirPath);
    
    // Construye el indice invertido leyendo todos los archivos
    void buildIndex();
    
    // Busqueda de una palabra, retorna top 3
    vector<DocFrequency> searchOne(const string& word);
    
    // Busqueda de dos palabras, retorna top 3 con frecuencia combinada
    vector<DocFrequency> searchTwo(const string& word1, const string& word2);
    
    // Getters para estadisticas
    int getFileCount() const { return totalFilesIndexed; }
    int getWordCount() const { return invertedIndex.size(); }
    
    // Imprime estadisticas del indice
    void printStats();
};

#endif
