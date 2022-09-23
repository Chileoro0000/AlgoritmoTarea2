//Estas colas fueron sacadas de github, fueron modificadas.
#include <stdlib.h>
#include <stdio.h>
#include "cola.h"

#define tam 1024
#define PI 3.14159265359

//Funciones cola
Cola* crearCola(){
  Cola* cola_a_retornar = (Cola*)malloc(sizeof(Cola));
  cola_a_retornar->inicio = NULL;
  cola_a_retornar->final = NULL;
  cola_a_retornar->largo = 0;
  return cola_a_retornar;
}

void encolar(Cola* C, Datacenter* Data_a_encolar ){
  NodoCola* NodoCola_a_encolar = (NodoCola*)malloc(sizeof(NodoCola));
  NodoCola_a_encolar->Data = Data_a_encolar;
  NodoCola_a_encolar->siguiente = NULL;
  if (C->inicio == NULL) { 
    C->inicio = NodoCola_a_encolar;
    C->final = NodoCola_a_encolar;
  }
  else {
    C->final->siguiente = NodoCola_a_encolar; 
    C->final = NodoCola_a_encolar; 
  }
  C->largo = C->largo + 1;
}

Datacenter desencolar(Cola* C){
  if(C->largo > 0) {
    NodoCola* primer_elemento = C->inicio;
    Datacenter variable_a_retornar = *primer_elemento->Data;
    C->inicio = C->inicio->siguiente; 
    if (C->largo == 1){
      C->final = NULL;
    }   
    free(primer_elemento);
    C->largo = C->largo-1;
    return variable_a_retornar;
  }
  else {
    printf("La cola esta vacia");
  }
  //return 0;
}

void mostrarCola(Cola *C){
  NodoCola* nos_paramos_en = C->inicio; 
  while(nos_paramos_en != NULL){
    printf("Datacenter --> ID: %i, latitud: %f, longitud: %f \n", nos_paramos_en->Data->id,
    	nos_paramos_en->Data->latitud, nos_paramos_en->Data->longitud);
    nos_paramos_en = nos_paramos_en->siguiente;
  }
  printf("La cola esta vacia.\n");
}


//Descripcion: Funcion que genera una cola a partir de los datos del archivo, en este caso id, lat, lon.
Cola* extraerDatos(FILE* entrada){
  Cola* ColaRaiz = crearCola();
  while(feof(entrada) == 0){
    //Variables a guardar
    int id;
    char *pais;
    char *ciudad;
    float longitud;
    float latitud;
    //Variables de trabajo
    char *token;
    char linea[tam];
    //Obtengo la linea
    fgets(linea, tam, entrada);
    //Obtengo los Datas
    token = strtok(linea, "\t");
    id = atoi(token);
    token = strtok(NULL, ",");
    ciudad = token;
    token = strtok(NULL, "\t");
    pais = token;
    token = strtok(NULL, "\t");
    latitud = atof(token);
    token = strtok(NULL, "\t");
    longitud = atof(token);
    Datacenter* nuevo = (Datacenter*)malloc(sizeof(Datacenter));    
      nuevo->id = id;
      nuevo->latitud = latitud;
      nuevo->longitud = longitud;
      encolar(ColaRaiz, nuevo);
  }
  return ColaRaiz;
}

//Descripcion: Funcion que va dato por dato calculando cual es el Datacenter que se encuentra mas al norte
int encontrarRaiz(Cola* cola){
  //printf("%i", cola->largo); //Imprime el largo de la cola
  int contador = cola->largo;
  int raizAretornar;
  for(int i = 0; i < contador-1; i++){
    if(i == 0){
      Datacenter nodoA = desencolar(cola);
      Datacenter nodoB = desencolar(cola);
      if(nodoA.latitud >= nodoB.latitud){
        raiz.latitud = (nodoA.latitud);
        raiz.id = nodoA.id;
        raiz.longitud  =nodoA.longitud;
      }else{
        raiz.latitud = (nodoB.latitud);
        raiz.id = nodoB.id;
        raiz.longitud  =nodoB.longitud;
      }
    }else{
      Datacenter nodoB = desencolar(cola);
      //printf("->%f\n",nodoB.latitud);
      if(nodoB.latitud >= raiz.latitud){
        raiz.latitud = (nodoB.latitud);
        raiz.id = nodoB.id;
        raiz.longitud  =nodoB.longitud;;
      }else{
        continue;
      }
    }
  }
  raizAretornar = raiz.id;
  return raizAretornar;
}
