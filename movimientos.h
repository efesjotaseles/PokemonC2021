#ifndef MOVIMIENTOS_H_INCLUDED
#define MOVIMIENTOS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myConstants.h"

////////////////////////////////////////////////////////////////////////////////////
//***ESTRUCTURAS***
typedef struct infoMov
{
    char nombre[30];
    char tipo[30];
    float potencia;
    int ppMax;

}infoMov;

typedef struct nodoInfoMov
{
    infoMov dato;
    struct nodoInfoMov * sig;

}nodoInfoMov;

//Usado en un Pokemon.
typedef struct movimiento
{
    infoMov datos;
    int ppDisponibles;

}movimiento;

////////////////////////////////////////////////////////////////////////////////////
//***PROTOTIPADOS***
infoMov inicInfoMov();
infoMov nuevaInfoMov(char nombreMov[] , char tipo[] , float potencia , int ppMax);
movimiento inicMovimiento();
movimiento nuevoMovimiento(infoMov datos);
nodoInfoMov * inicListaInfoMov();
nodoInfoMov * nuevoNodoInfoMov(infoMov dato);
nodoInfoMov * insertarNodoInfoMovAlFinal(nodoInfoMov * lista , nodoInfoMov * nodo);
nodoInfoMov * borrarNodoInfoMov(nodoInfoMov * lista , char nombreMov[]);
infoMov movEnLista(nodoInfoMov * lista , char nombreMov[]);
void inicSetMovimientos(movimiento setMovimientos[]);
nodoInfoMov * leerArchivo_InfoMovimientos(nodoInfoMov * lista);
int escribirInfoMov_enArchivo(infoMov aGuardar);
int reescribirArchivoMovimiento(nodoInfoMov * lista);
int cantInfoMov_enArchivo();
int setMovimientos_Validos(movimiento setMovimientos[]);
movimiento quitarMov_deSetMovimientos(movimiento setMovimientos[] , int pos);
void insertarMov_enSetMovimiento(infoMov aInsertar , movimiento setMovimientos[]);


#endif // MOVIMIENTOS_H_INCLUDED
