#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "main.h"

#define tam 1024
#define PI 3.14159265359

//Descripcion: Funcion que genera el costo que se enlazaran en los data centers. XXXXXX arreglar XXXXXXX
float CalcularCosto(float latitudA, float longitudA, float latitudB, float longitudB){
	float costo;
	float r = 6371.0088;
	latitudA = (latitudA*PI)/180;
	longitudA = (longitudA*PI)/180;
	latitudB = (latitudB*PI)/180;
	longitudB = (longitudB*PI)/180;
	costo = (2*r)*(asin(sqrt((pow(sin((latitudB-latitudA)/2), 2))+(cos(latitudA))*(cos(latitudB))*(pow(sin((longitudB-longitudA)/2),2)))));
	return costo;
}

//Descripcion: Genera el grafo principal el cual tiene el tamaño de el total de datacenters.
Grafo* GrafoMain(Cola* cola, int largo){
	int arreglo[largo];
	for(int i = 0; i < largo; i++){
		Datacenter nodoA = desencolar(cola);
		arreglo[i] = nodoA.id;
	}
	Grafo* g = CrearGrafo(largo, arreglo);
	return g;
}

//Descripcion: Genera los costos para cada conexion de los datacenters.
void GenerarCostos(Grafo* g, Cola* cola){
	int contador = cola->largo;
	Datacenter lista[contador];
	for(int a = 0; a < contador; a++){
		Datacenter d = desencolar(cola);
		lista[a] = d;
	}
	for(int i = 0; i < contador; i++){
		//printf("%f\n", lista[i].latitud);
		float latA = lista[i].latitud;
		float lonA = lista[i].longitud;
		for(int o = 0; o < g->numero_de_nodos; o++){
			float latB = lista[o].latitud;
			float lonB = lista[o].longitud;
			//printf("latA->%f, lonA->%f, latB->%f, lonB->%f", latA, lonA, latB, lonB);
			float costo = CalcularCosto(latA, lonA, latB, lonB);
 			enlace e = CrearEnlace(i, o, &costo);
 			InsertarEnlace(g, e);
		}
	}
}

//Descripcion: lee el nombre de la funcion.
void MostrarMatriz(Grafo* GrafoPrincipal){
	for(int i=0; i < GrafoPrincipal->numero_de_nodos; i++)
        printf("\t %i", GrafoPrincipal->vertices[i]);
    putchar('\n');
    for(int i=0; i < GrafoPrincipal->numero_de_nodos; i++){
        printf("%i\t", GrafoPrincipal->vertices[i]);
        for(int j=0; j < GrafoPrincipal->numero_de_nodos; j++)
            printf("%.2f\t", GrafoPrincipal->matriz[i][j]);
        putchar('\n');
    }
}


float EncontrarMinimo(float costos[], bool Verificador[], Grafo* g)
{
    int min = INT_MAX, min_index;
    int V = g->numero_de_nodos;
    for (int v = 0; v < V; v++)
        if (Verificador[v] == false && costos[v] < min)
            min = costos[v], min_index = v;
    return min_index;
}

Arbol* GenerarArbol(int padres[], Grafo* g, int pos)
{
	int V = g->numero_de_nodos;
	//Genero arbol con raiz
	nodo* Arbol = CrearNodo(pos);
	for(int i = 1; i < V; i++){
		if(i % 2 == 0){
			InsertarDer(Arbol, g->vertices[padres[i]]);
		}else{
			InsertarIzq(Arbol, g->vertices[padres[i]]);
		}
	}
	//Creo los archivos
	FILE* preorden = fopen("preorden.txt", "w");
	FILE* inorden = fopen("inorden.txt", "w");
	FILE* postorden = fopen("postorden.txt", "w");

	PreOrden(Arbol, preorden);
	fprintf(preorden, "\n");
	Inorden(Arbol, inorden);
	fprintf(inorden, "\n");
	PostOrden(Arbol, postorden);
	fprintf(postorden, "\n");
}

void Prim(Grafo* g, int pos)
{
	int V = g->numero_de_nodos;
	float MatrizDuplicada[g->numero_de_nodos][g->numero_de_nodos];
	for(int i = 0; i < g->numero_de_nodos; i++){
		for(int j = 0; j < g->numero_de_nodos; j++){
			MatrizDuplicada[i][j] = g->matriz[i][j];
		}
	}
    int padres[V];
    float costos[V];
    bool Verificador[V];
    for (int i = 0; i < V; i++)
        costos[i] = INT_MAX, Verificador[i] = false;
 
    costos[0] = 0;
    padres[0] = -1;
 
    for (int contador = 0; contador < V - 1; contador++) {
        int u = EncontrarMinimo(costos, Verificador, g);
 
        Verificador[u] = true;
        for (int v = 0; v < V; v++)

            if (MatrizDuplicada[u][v] && Verificador[v] == false && MatrizDuplicada[u][v] < costos[v])
                padres[v] = u, costos[v] = MatrizDuplicada[u][v];
    }

    GenerarRedPrincipal(padres, g, pos);
    GenerarArbol(padres, g, pos);
    GenerarRedRespaldo(padres, g, pos);
}

void GenerarRedPrincipal(int padres[], Grafo* g, int pos){
	//Generar archivo
	FILE* RedPrincipal = fopen("red_principal.tsv", "w");
	float MatrizDuplicada[g->numero_de_nodos][g->numero_de_nodos];
	for(int i = 0; i < g->numero_de_nodos; i++){
		for(int j = 0; j < g->numero_de_nodos; j++){
			MatrizDuplicada[i][j] = g->matriz[i][j];
		}
	}
	//Agrego los conexiones
	int V = g->numero_de_nodos;
    for (int i = 1; i < V; i++){
    	fprintf(RedPrincipal, "%i\t", g->vertices[padres[i]]);
    	fprintf(RedPrincipal, "%i\t", g->vertices[i]);
    	fprintf(RedPrincipal, "%.2f\n", MatrizDuplicada[i][padres[i]]);
    }
          
	//Sumatoria de pesos final de archivo
    float sumaPesos = 0;
    for(int i = 1; i < V; i++){
    	sumaPesos = sumaPesos + MatrizDuplicada[i][padres[i]];
    }
    //Agregar suma de peso
    fprintf(RedPrincipal, "%.2f\n", sumaPesos);
    fclose(RedPrincipal);
}


void GenerarRedRespaldo(int padres[], Grafo* g, int pos){
	int V = g->numero_de_nodos;
	for(int i = 1; i < V; i++){
		g->matriz[padres[i]][i] = 0;
		g->matriz[i][padres[i]] = 0;
	}
	prim(g, pos);
}

void prim(Grafo* g, int pos)
{
	int V = g->numero_de_nodos;
	float MatrizDuplicada[g->numero_de_nodos][g->numero_de_nodos];
	for(int i = 0; i < g->numero_de_nodos; i++){
		for(int j = 0; j < g->numero_de_nodos; j++){
			MatrizDuplicada[i][j] = g->matriz[i][j];
		}
	}
    int padres[V];
    float costos[V];
    bool Verificador[V];
    for (int i = 0; i < V; i++)
        costos[i] = INT_MAX, Verificador[i] = false;

    int posR = 0;
    for(int i = 0; i < g->numero_de_nodos; i++){
    	if(g->vertices[i] == pos){
    		posR = i;
    	}
    }

    costos[0] = 0;
    padres[0] = -1+posR;
 
    for (int contador = 0; contador < V - 1; contador++) {
        int u = EncontrarMinimo(costos, Verificador, g);
 
        Verificador[u] = true;
        for (int v = 0; v < V; v++)

            if (MatrizDuplicada[u][v] && Verificador[v] == false && MatrizDuplicada[u][v] < costos[v])
                padres[v] = u, costos[v] = MatrizDuplicada[u][v];
    }
    GenerarRedRespaldo2(padres, g);
    ObtenerIP(padres, g, pos);
}

void GenerarRedRespaldo2(int padres[], Grafo* g){
	//Generar archivo
	FILE* RedRespaldo = fopen("red_respaldo.tsv", "w");
	//Agrego los conexiones
	int V = g->numero_de_nodos;
    for (int i = 1; i < V; i++){
    	fprintf(RedRespaldo, "%i\t", g->vertices[padres[i]]);
    	fprintf(RedRespaldo, "%i\t", g->vertices[i]);
    	fprintf(RedRespaldo, "%.2f\n", g->matriz[i][padres[i]]);
    }
          
	//Sumatoria de pesos final de archivo
    float sumaPesos = 0;
    for(int i = 1; i < V; i++){
    	sumaPesos = sumaPesos + g->matriz[i][padres[i]];
    }
    //Agregar suma de peso
    fprintf(RedRespaldo, "%.2f\n", sumaPesos);
    fclose(RedRespaldo);
}

void ObtenerIP(int padres[], Grafo* g, int pos){
	int V = g->numero_de_nodos;
	//Genero arbol con raiz
	nodo* Arbol = CrearNodo(pos);
	for(int i = 1; i < V; i++){
		if(i % 2 == 0){
			InsertarDer(Arbol, g->vertices[padres[i]]);
		}else{
			InsertarIzq(Arbol, g->vertices[padres[i]]);
		}
	}

	//Creo los archivos
	FILE* preorden = fopen("preorden.txt", "a");
	FILE* inorden = fopen("inorden.txt", "a");
	FILE* postorden = fopen("postorden.txt", "a");

	PreOrden(Arbol, preorden);
	Inorden(Arbol, inorden);
	PostOrden(Arbol, postorden);
	//Eliminar arbol
	//tree_empty(Arbol);
}

//Intento te crear arbol
/*nodo* insertarHijo(Arbol* T, int padres[], int i){
	nodo* padre = tree_search(T->raiz, padres[i]);
	if(padre != NULL){
		nodo* hijo = CrearNodo(i);
		InsertarIzq(padre, hijo->id);
		return hijo;
	}else{
		nodo* padre = insertarHijo(T, padres, padres[i]);
		nodo* hijo = CrearNodo(i);
		InsertarIzq(padre, hijo->id);
		return hijo;
	}
}

Arbol* GenerarArbol2(int padres[], int raiz, Grafo* g){
	Arbol* T;
	nodo* r = CrearNodo(raiz);
	T->raiz = r;
	int largo = g->numero_de_nodos;

	for(int i = 0; i < largo; i++){
		if(tree_search(T->raiz, i) != NULL){
			insertarHijo(T, padres, i);
		}
	}
	return T;
}*/
