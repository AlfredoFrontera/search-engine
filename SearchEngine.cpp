/*
 * SearchEngine.cpp
 * CCOM 4997 - Final Project: Simple Search Engine
 * Author: Alfredo Frontera
 * Date: December 2025
 */

#include "SearchEngine.h"

SearchEngine::SearchEngine(string dirPath) {
    directoryPath = dirPath;
    totalFilesIndexed = 0;
}

string SearchEngine::toLowercase(const string& word) {
    string result = word;
    for (uint i = 0; i < result.length(); i++) {
        result[i] = tolower(result[i]);
    }
    return result;
}

string SearchEngine::cleanWord(const string& word) {
    string result = "";
    for (uint i = 0; i < word.length(); i++) {
        char c = word[i];
        if (isalnum(c)) {
            result += tolower(c);
        }
    }
    return result;
}

bool SearchEngine::compareByFreq(const DocFrequency& a, const DocFrequency& b) {
    return a.frequency > b.frequency;
}

void SearchEngine::buildIndex() {
    cout << "Construyendo indice..." << endl;
    
    // Obtener lista de archivos usando funcion del profesor
    vector<string> files;
    int error = getdir(directoryPath, files);
    
    if (error != 0) {
        cout << "Error al abrir directorio: " << directoryPath << endl;
        return;
    }
    
    int fileCount = 0;
    int totalFiles = files.size();
    
    for (uint i = 0; i < files.size(); i++) {
        string filename = files[i];
        
        // Ignorar archivos ocultos (empiezan con .)
        if (filename[0] == '.') {
            continue;
        }
        
        // Construir ruta completa
        string filepath = directoryPath + "/" + filename;
        
        // Usar ParsedFile del profesor para leer y tokenizar
        ParsedFile pf(filepath);
        vector<string> words = pf.readAndTokenize();
        
        // Contar frecuencia de cada palabra en este archivo
        map<string, int> wordFreq;
        for (uint j = 0; j < words.size(); j++) {
            string cleaned = cleanWord(words[j]);
            if (cleaned.length() > 1) {
                wordFreq[cleaned]++;
            }
        }
        
        // Agregar al indice invertido
        for (map<string, int>::iterator it = wordFreq.begin(); it != wordFreq.end(); it++) {
            DocFrequency df(filename, it->second);
            invertedIndex[it->first].push_back(df);
        }
        
        fileCount++;
        
        // Mostrar progreso cada 5000 archivos
        if (fileCount % 5000 == 0) {
            cout << "Procesados " << fileCount << "/" << totalFiles << " archivos..." << endl;
        }
    }
    
    totalFilesIndexed = fileCount;
    cout << "Indice construido. " << fileCount << " archivos indexados." << endl;
}

vector<DocFrequency> SearchEngine::searchOne(const string& word) {
    vector<DocFrequency> results;
    string normalized = cleanWord(word);
    
    if (normalized.empty()) {
        return results;
    }
    
    // Buscar palabra en el indice
    map<string, vector<DocFrequency>>::iterator it = invertedIndex.find(normalized);
    
    if (it == invertedIndex.end()) {
        return results;  // Palabra no encontrada
    }
    
    // Copiar resultados y ordenar por frecuencia
    results = it->second;
    sort(results.begin(), results.end(), compareByFreq);
    
    // Retornar solo top 3
    if (results.size() > 3) {
        results.resize(3);
    }
    
    return results;
}

vector<DocFrequency> SearchEngine::searchTwo(const string& word1, const string& word2) {
    vector<DocFrequency> results;
    
    string norm1 = cleanWord(word1);
    string norm2 = cleanWord(word2);
    
    if (norm1.empty() || norm2.empty()) {
        return results;
    }
    
    // Obtener documentos para cada palabra
    map<string, vector<DocFrequency>>::iterator it1 = invertedIndex.find(norm1);
    map<string, vector<DocFrequency>>::iterator it2 = invertedIndex.find(norm2);
    
    if (it1 == invertedIndex.end() || it2 == invertedIndex.end()) {
        return results;  // Una o ambas palabras no encontradas
    }
    
    // Crear mapa para busqueda rapida de frecuencias de palabra1
    map<string, int> word1Freq;
    for (uint i = 0; i < it1->second.size(); i++) {
        word1Freq[it1->second[i].filename] = it1->second[i].frequency;
    }
    
    // Encontrar documentos que contienen ambas palabras
    for (uint i = 0; i < it2->second.size(); i++) {
        string docName = it2->second[i].filename;
        int freq2 = it2->second[i].frequency;
        
        // Verificar si este documento tambien tiene palabra1
        map<string, int>::iterator found = word1Freq.find(docName);
        if (found != word1Freq.end()) {
            int combinedFreq = found->second + freq2;
            DocFrequency df(docName, combinedFreq);
            results.push_back(df);
        }
    }
    
    // Ordenar por frecuencia combinada
    sort(results.begin(), results.end(), compareByFreq);
    
    // Retornar top 3
    if (results.size() > 3) {
        results.resize(3);
    }
    
    return results;
}

void SearchEngine::printStats() {
    cout << "\n=== Estadisticas del Indice ===" << endl;
    cout << "Archivos indexados: " << totalFilesIndexed << endl;
    cout << "Palabras unicas: " << invertedIndex.size() << endl;
    cout << "================================\n" << endl;
}
