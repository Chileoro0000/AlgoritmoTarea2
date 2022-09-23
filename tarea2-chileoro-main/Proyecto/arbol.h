#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

typedef struct nodo_template* link;
typedef struct nodo_template {
    int id;

    link padre;
    link hijo_izq;
    link hermano_der;
} nodo;

typedef struct nodo Arbol;

nodo* InsertarIzq(nodo*, int);
nodo* InsertarDer(nodo*, int);
nodo* CrearNodo(int k);
void Inorden(nodo* n, FILE* e);
void PreOrden(nodo* n, FILE* e);
void PostOrden(nodo* n, FILE* e);
void tree_empty(nodo* n);
