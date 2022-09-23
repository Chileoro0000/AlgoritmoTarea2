#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

//Funciones de archivo
Cola* extraerDatos(FILE* entrada);
//Funciones para contruir el grafo
int encontrarRaiz(Cola* cola);
float CalcularCosto(float latitudA, float longitudA, float latitudB, float longitudB);
Grafo* GrafoMain(Cola* cola, int largo);
void GenerarCostos(Grafo* g, Cola* cola);
void MostrarMatriz(Grafo* g);
//Funciones de generar arbol
void Prim(Grafo* g, int pos);
Arbol* GenerarArbol(int padres[], Grafo* g, int pos);
float EncontrarMinimo(float costos[], bool Verificador[], Grafo* g);
void GenerarRedPrincipal(int padres[], Grafo* g, int pos);
void GenerarRedRespaldo(int padres[], Grafo* , int pos);
void GenerarRedRespaldo2(int padres[], Grafo* g);
void prim(Grafo* g, int pos);
void ObtenerIP(int padres[], Grafo* g, int pos);