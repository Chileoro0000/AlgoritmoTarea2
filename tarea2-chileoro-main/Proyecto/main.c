//Proyecto realizado por Gabriel Rodriguez.
//V 1.3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include "cola.c"
#include "grafo.c"
#include "arbol.c"
#include "def.c"

int main(){
	//Leemos el archivo de entrada
	FILE *entrada;

	char entradaL[256];
    printf("Ingrese la ruta del archivo: ");
    scanf("%s", entradaL);
    entrada = fopen(entradaL, "r");

	//Verifico si el archivo esta.
  	if (!entrada) 
  	{
   		printf("No se puede leer archivo.");
    	return -1;
 	}

 	//Cola para encontrar raiz
 	Cola* ColaRaiz = extraerDatos(entrada);
 	//Cola para almacenar datos
 	rewind(entrada);
 	Cola* ColaDatos = extraerDatos(entrada);
 	rewind(entrada);
 	Cola* ColaCostos = extraerDatos(entrada);
 	//Encuentro raiz
 	int raiz = encontrarRaiz(ColaRaiz);

 	//Sacar tamaño de matriz
 	int LargoMatriz;
 	LargoMatriz = ColaDatos->largo;

 	//Creo el grafo principal
 	Grafo* GrafoPrincipal = GrafoMain(ColaDatos, LargoMatriz);
 	
 	//Genero costo para cada enlace
	GenerarCostos(GrafoPrincipal, ColaCostos);
 	
 	//Generamos el arbol de expasion minima con PRIM
 	int Nraiz = raiz;
 	//Este prim hace toda la magia para no tener tantas funciones en el main.
 	Prim(GrafoPrincipal, Nraiz);


 	EliminarGrafo(GrafoPrincipal);
 	fclose(entrada);
	return 0;
}


