#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
	int i; //nodo inicial

	int f; //nodo final
	//Costo
	float costo;
}enlace;

	
typedef struct{
	int numero_de_nodos;

	int numero_de_caminos;
	//areglo de vertices
	int* vertices;

	bool es_digrafo; 

	float** matriz;
}Grafo;

enlace CrearEnlace(int i, int f,float* costo);
Grafo* CrearGrafo(int n, int r[]);
void EliminarGrafo(Grafo* g);
int InsertarEnlace(Grafo* g, enlace e);
int RemoverEnlace(Grafo* g, int i, int f);
void Deshacer_digrafo(Grafo* g);
void Hacer_digrafo(Grafo* g);

