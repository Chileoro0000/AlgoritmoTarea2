//Arbol.c fue extraido de el profe javier solamente cambie nombres.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arbol.h"

nodo* CrearNodo(int k){
  nodo* n = (nodo*)malloc(sizeof(nodo));

  n->id = k;
  
  n->padre = NULL;
  n->hijo_izq = NULL;
  n->hermano_der = NULL;

  return n;
}

nodo* InsertarIzq(nodo* x, int k){
    nodo* n = CrearNodo(k);
    
    n->padre = x;
    
    if(x->hijo_izq)
        n->hermano_der = x->hijo_izq;
    x->hijo_izq = n;
    
    return n;
}


nodo* InsertarDer(nodo* x, int k){
    nodo* n = CrearNodo(k);
    
    n->padre = x;
    
    if(!x->hijo_izq)
        x->hijo_izq = n;
    else{
        nodo* child = x->hijo_izq;
        while(child->hermano_der)
            child = child->hermano_der;
        child->hermano_der = n;
    }
}

void tree_empadrety(nodo* x){
    if(x){
        nodo* next = x->hijo_izq->hermano_der;
        tree_empadrety(x->hijo_izq);
        while(next){
            nodo* tempadre = next->hermano_der;
            tree_empadrety(next);
            next = tempadre;
        }
        free(x);
    }
}

void DestruirNodo(nodo* n){
    n->padre = NULL;
    n->hijo_izq = NULL;
    n->hermano_der = NULL;
    free(n);
}

void Inorden(nodo* n, FILE* e){
    if(n){
        Inorden(n->hijo_izq, e);
        fprintf(e ,"%i ", n->id);
        Inorden(n->hermano_der, e);
    }
}

void PreOrden(nodo* n, FILE* e){
    if(n){
        fprintf(e ,"%i ", n->id);
        PreOrden(n->hijo_izq, e);
        PreOrden(n->hermano_der, e);
    }
}

void PostOrden(nodo* n, FILE* e){
    if(n){
        PreOrden(n->hijo_izq, e);
        PreOrden(n->hermano_der, e);
        fprintf(e ,"%i ", n->id);
    }
}

void tree_empty(nodo* n){
    if(n){
        tree_empty(n->hijo_izq);
        tree_empty(n->hermano_der);
        tree_empty(n->padre);
        free(n);
    }
}