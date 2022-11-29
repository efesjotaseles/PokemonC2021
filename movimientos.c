#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movimientos.h"

////////////////////////////////////////////////////////////////////////////////////
//***FUNCIONES***

infoMov inicInfoMov()
{

    infoMov aux;
    strcpy(aux.nombre , "");
    strcpy(aux.tipo , "");
    aux.potencia = -1;
    aux.ppMax = -1;

    return aux;
}

infoMov nuevaInfoMov(char nombreMov[] , char tipo[] , float potencia , int ppMax)
{
    infoMov aux;
    strcpy(aux.nombre , nombreMov);
    strcpy(aux.tipo , tipo);
    aux.potencia = potencia;
    aux.ppMax = ppMax;

    return aux;
}

movimiento inicMovimiento()
{
    movimiento aux;
    aux.datos = inicInfoMov();
    aux.ppDisponibles = aux.datos.ppMax;

    return aux;
}

movimiento nuevoMovimiento(infoMov datos)
{
    movimiento aux;
    aux.datos = datos;
    aux.ppDisponibles = datos.ppMax;

    return aux;
}

nodoInfoMov * inicListaInfoMov()
{
    return NULL;
}

nodoInfoMov * nuevoNodoInfoMov(infoMov dato)
{
    nodoInfoMov * aux = (nodoInfoMov*)malloc(sizeof(nodoInfoMov));
    aux->dato = dato;
    aux->sig = NULL;

    return aux;
}

nodoInfoMov * insertarNodoInfoMovAlFinal(nodoInfoMov * lista , nodoInfoMov * nodo)
{
    if(lista == NULL)
    {
        lista = nodo;
    }
    else
    {
        lista->sig = insertarNodoInfoMovAlFinal(lista->sig , nodo);
    }

    return lista;
}

nodoInfoMov * borrarNodoInfoMov(nodoInfoMov * lista , char nombreMov[])
{
    if(lista != NULL)
    {
        if(strcmp(lista->dato.nombre , nombreMov) == 0)
        {
            nodoInfoMov * aBorrar = lista;
            lista = lista->sig;
            free(aBorrar);
        }
        else
        {
            lista->sig = borrarNodoInfoMov(lista->sig , nombreMov);
        }
    }

    return lista;
}

infoMov movEnLista(nodoInfoMov * lista , char nombreMov[])
{
    infoMov aux = inicInfoMov();
    if(lista != NULL)
    {
        nodoInfoMov * seguidora = lista;
        while(seguidora != NULL && strcmp(seguidora->dato.nombre , nombreMov) != 0)
        {
            seguidora = seguidora->sig;
        }
        if(seguidora != NULL)
        {
            aux = seguidora->dato;
        }
    }

    return aux;
}

void inicSetMovimientos(movimiento setMovimientos[])
{
    for(int i=0 ; i<4 ; i++)
    {
        setMovimientos[i] = inicMovimiento();
    }
}

nodoInfoMov * leerArchivo_InfoMovimientos(nodoInfoMov * lista)
{
    if(lista == NULL)
    {
        FILE * archi = fopen(ARCHI_MOVIMIENTOS, "rb");
        if(archi != NULL)
        {
            int leido = 0;
            infoMov auxInfo;
            leido = fread(&auxInfo, sizeof(infoMov), 1, archi);
            while(!feof(archi))
            {
                nodoInfoMov * auxNodo = nuevoNodoInfoMov(auxInfo);
                lista = insertarNodoInfoMovAlFinal(lista, auxNodo);
                leido = fread(&auxInfo, sizeof(infoMov), 1, archi);
            }
        }
        fclose(archi);
    }

    return lista;
}

int escribirInfoMov_enArchivo(infoMov aGuardar)
{
    int cantEscrita = 0;
    FILE * archi = fopen(ARCHI_MOVIMIENTOS , "ab");
    if(archi != NULL)
    {
        cantEscrita = fwrite(&aGuardar , sizeof(infoMov) , 1 , archi);
    }
    fclose(archi);

    return cantEscrita;
}

int guardarListaInfoMov_enArchivo(nodoInfoMov * lista)
{
    int cantEscrita = 0;
    if(lista != NULL)
    {
        cantEscrita = escribirInfoMov_enArchivo(lista->dato);
        cantEscrita += guardarListaInfoMov_enArchivo(lista->sig);
    }

    return cantEscrita;
}

int reescribirArchivoMovimiento(nodoInfoMov * lista)
{
    int cantidadEscrita = 0;
    if(lista != NULL)
    {
        FILE * archi = fopen(ARCHI_MOVIMIENTOS , "wb");
        if(archi == NULL)
        {
            fclose(archi);
        }
        else
        {
            fclose(archi);
            cantidadEscrita = guardarListaInfoMov_enArchivo(lista);
        }
    }

    return cantidadEscrita;
}

int cantInfoMov_enArchivo()
{
    int rta = 0;
    FILE * archi = fopen(ARCHI_MOVIMIENTOS, "rb");
    if(archi != NULL)
    {
        fseek(archi, 0, SEEK_END);
        rta = ftell(archi) / sizeof(infoMov);
    }
    fclose(archi);

    return rta;
}

int setMovimientos_Validos(movimiento setMovimientos[])
{
   int rta = 0;
   int i = 0;
   while(i<4)
   {
       if(setMovimientos[i].datos.potencia != -1)
       {
           rta++;
       }
       else
       {
           i=4;
       }
       i++;
   }

   return rta;
}

movimiento quitarMov_deSetMovimientos(movimiento setMovimientos[] , int pos)
{
    movimiento removido = setMovimientos[pos];
    int posUltimoValido = setMovimientos_Validos(setMovimientos) -1; //Buscamos la posición del último válido.
    setMovimientos[pos] = setMovimientos[posUltimoValido]; //Lo copiamos en la posición del removido.
    setMovimientos[posUltimoValido] = inicMovimiento(); //Vaciamos el último válido.

    return removido;
}

void insertarMov_enSetMovimiento(infoMov aInsertar , movimiento setMovimientos[])
{
    int validos = setMovimientos_Validos(setMovimientos);
    if(validos <4)
    {
        movimiento aux = nuevoMovimiento(aInsertar);
        setMovimientos[validos] = aux;
    }
}
