# Motor de Búsqueda Simple
## CCOM 4997 - Proyecto Final
**Autor:** Alfredo Frontera  
**Fecha:** Diciembre 2025

## Cómo correr el programa

### 1. Descargar el dataset
```bash
wget http://ccom.uprrp.edu/~rarce/ccom3034old/moviesdb.zip
unzip moviesdb.zip
```

### 2. Compilar
```bash
make
```

### 3. Ejecutar
```bash
./search_engine ./moviesdb
```

### 4. Usar
- Escribe 1 o 2 palabras para buscar
- Escribe `salir` para terminar
- Escribe `stats` para ver estadísticas

## Ejemplo de uso
```
Buscar> love
Resultados para: "love"
----------------------------------------
1. Love-Story.txt (frecuencia: 15)
2. Romeo-and-Juliet.txt (frecuencia: 12)
3. The-Notebook.txt (frecuencia: 10)
----------------------------------------

Buscar> love war
Resultados para: "love war"
----------------------------------------
1. Until-Next-Time.txt (frecuencia: 11)
2. Queen-Christina.txt (frecuencia: 11)
3. The-Princess-Bride.txt (frecuencia: 9)
----------------------------------------

Buscar> salir
Hasta luego!
```

## Archivos incluidos
- `ParsedFile.h` / `ParsedFile.cpp` - Funciones provistas por el profesor
- `SearchEngine.h` / `SearchEngine.cpp` - Clase del motor de búsqueda con índice invertido
- `main.cpp` - Programa principal
- `Makefile` - Para compilar
