#ifndef EFECTIVIDADES_H_INCLUDED
#define EFECTIVIDADES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myConstants.h"

////////////////////////////////////////////////////////////////////////////////////
//***ESTRUCTURAS***
typedef struct efectividad
{
    char tipo[30];
    float multiplicador;

}efectividad;

typedef struct nodoEfectividad
{
    efectividad dato;
    struct nodoEfectividad * izq;
    struct nodoEfectividad * der;

}nodoEfectividad;

typedef struct celdaEfectividad
{
    char tipoAtaque[30];
    nodoEfectividad * arbol;

}celdaEfectividad;

////////////////////////////////////////////////////////////////////////////////////
//***PROTOTIPADOS***
efectividad nuevaEfectividad(char tipo[] , float multiplicador);
nodoEfectividad * nuevoNodoEfec(efectividad dato);
nodoEfectividad * inicArbol();
nodoEfectividad * insertarNodoEfec(nodoEfectividad * arbol , nodoEfectividad * aInsertar);
celdaEfectividad nuevaCeldaEfec(char tipo[]);
nodoEfectividad * llenarArbol(nodoEfectividad * arbol , float arrMult[]);
void inicEfectividades(celdaEfectividad arrCeldas[]);
int posTipoAtaque(celdaEfectividad arrEfect[] , char tipoAtaque[]);
float buscarMultiplicador(nodoEfectividad * arbol , char tipoDefensor[]);




#endif // EFECTIVIDADES_H_INCLUDED
