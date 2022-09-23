#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enlace CrearEnlace(int i, int f, float* costo){
	enlace t;
	if(costo){
		t.costo = *costo;
	}else{
		t.costo = 1;
	}
	t.i = i;
	t.f = f;
	return(t);
}

Grafo* CrearGrafo(int n, int r[]){
	Grafo* g = (Grafo*)malloc(sizeof(Grafo)); //asigno memoria a mi grafito
	//le doi los datos a mi grafo
	g->numero_de_nodos = n;
	g->numero_de_caminos = 0;
	g->es_digrafo = false;

	g->vertices = (int*)malloc(sizeof(int)*g->numero_de_nodos); //reservo memoria a mi arreglo de enteros

	for(int i = 0; i < g->numero_de_nodos; i++){
		g->vertices[i] = r[i];
	} 

	g->matriz = (float**)malloc(g->numero_de_nodos * sizeof(float*));
	if(!g->matriz){
		printf("Error en memoria");
		free(g->vertices);
		free(g);
		return NULL;
	}

	//Rellenar matriz con 0 por cuidado.
	for(int i = 0; i < g->numero_de_nodos; i++){
		g->matriz[i] = (float*)malloc(g->numero_de_nodos * sizeof(float));

		if(!g->matriz[i]){
			printf("Error en memoria");
			for(i = i-1; i >= 0; i--){
				free(g->matriz[i]);
			}
			free(g->vertices);
			free(g);
			return NULL;
		}
		for(int a = 0; a < g->numero_de_nodos; a++) g->matriz[i][a] = 0;
	}
	return g;
}

void EliminarGrafo(Grafo* g){
    for(int i= 0; i < g->numero_de_nodos; i++) free(g->matriz[i]);
    free(g->matriz);
    free(g->vertices);
    free(g);
}

int InsertarEnlace(Grafo* g, enlace e){
	g->matriz[e.i][e.f] = e.costo;
	if(!g->es_digrafo) g->matriz[e.f][e.i] = e.costo;
	g->numero_de_caminos++;
	return g->numero_de_caminos;
}

int RemoverEnlace(Grafo* g, int i, int f){
	g->matriz[i][f] = 0;
	if(!g->es_digrafo){
		g->matriz[f][i] = 0;
		g->numero_de_caminos--;
	}
	return g->numero_de_caminos;
}

// Convierte el grafo en digrafo
// Ninguna de estas funciones modifica las aristas, solo cambian cómo se insertan
void Hacer_digrafo(Grafo* g){
    g->es_digrafo = true;
}


// Convierte el grafo en no dirigido
void Deshacer_digrafo(Grafo* g){
    g->es_digrafo = false;
}

