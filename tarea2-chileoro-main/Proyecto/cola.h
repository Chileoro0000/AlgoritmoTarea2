#include <stdlib.h>
#include <stdio.h>

struct raiz{
  int id;
  float latitud;
  float longitud;
}raiz;

//Estructuras de cola
struct Datacenter {
  int id;
  float latitud;
  float longitud;
} typedef Datacenter;

struct NodoCola{
  Datacenter* Data;
  struct NodoCola* siguiente;
} typedef NodoCola;

struct Cola {
  int largo;
  NodoCola* inicio;
  NodoCola* final;
} typedef Cola;
//Fin estructuras de cola

//Defino funciones cola
Cola* crearCola();
void encolar(Cola* C, Datacenter* Data_a_encolar );
void mostrarCola(Cola *C);
Datacenter desencolar(Cola* C);

