#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myConstants.h"
#include "efectividades.h"

////////////////////////////////////////////////////////////////////////////////////
//***FUNCIONES***
efectividad nuevaEfectividad(char tipo[] , float multiplicador)
{
    efectividad aux;
    strcpy(aux.tipo , tipo);
    aux.multiplicador = multiplicador;

    return aux;
}

nodoEfectividad * nuevoNodoEfec(efectividad dato)
{
    nodoEfectividad * aux = (nodoEfectividad*)malloc(sizeof(nodoEfectividad));
    aux->dato = dato;
    aux->izq = NULL;
    aux->der = NULL;

    return aux;
}

nodoEfectividad * inicArbol()
{
    return NULL;
}

nodoEfectividad * insertarNodoEfec(nodoEfectividad * arbol , nodoEfectividad * aInsertar)
{
    if(arbol == NULL)
    {
        arbol = aInsertar;
    }
    else
    {
        if(strcmp(aInsertar->dato.tipo , arbol->dato.tipo) > 0)
        {
            arbol->der = insertarNodoEfec(arbol->der , aInsertar);
        }
        else
        {
            arbol->izq = insertarNodoEfec(arbol->izq , aInsertar);
        }
    }

    return arbol;
}

celdaEfectividad nuevaCeldaEfec(char tipo[])
{
    celdaEfectividad aux;
    strcpy(aux.tipoAtaque , tipo);
    aux.arbol = inicArbol();

    return aux;
}

nodoEfectividad * llenarArbol(nodoEfectividad * arbol , float arrMult[])
{
    //[cantidad de strings][dimensión máxima de cada string]
    char ordenTipos[TIPOS_VALIDOS][30] = {LUCHA , ELECTRICO , ROCA , BICHO , FUEGO , DRAGON , AGUA , FANTASMA , HIELO , VENENO , PLANTA , TIERRA , VOLADOR , NORMAL , PSIQUICO};
    for(int i=0 ; i<TIPOS_VALIDOS ; i++)
    {
        efectividad aux = nuevaEfectividad(ordenTipos[i] , arrMult[i]);

        arbol = insertarNodoEfec(arbol , nuevoNodoEfec(aux));
    }


    return arbol;
}

void inicEfectividades(celdaEfectividad arrCeldas[])
{
    //Agua
    arrCeldas[0] = nuevaCeldaEfec(AGUA);
    float multAgua[TIPOS_VALIDOS] = {1.0,2.0,1.0,1.0,2.0,0.5,1.0,1.0,1.0,1.0,0.5,2.0,1.0,1.0,1.0};
    arrCeldas[0].arbol = llenarArbol(arrCeldas[0].arbol , multAgua);

    //Bicho
    arrCeldas[1] = nuevaCeldaEfec(BICHO);
    float multBicho[TIPOS_VALIDOS] = {0.5,1,1,1,0.5,1,1,1,1,2,2,1,0.5,1,2};
    arrCeldas[1].arbol = llenarArbol(arrCeldas[1].arbol , multBicho);

    //Dragon
    arrCeldas[2] = nuevaCeldaEfec(DRAGON);
    float multDragon[TIPOS_VALIDOS] = {1,1,1,1,1,2,1,1,1,1,1,1,1,1,1};
    arrCeldas[2].arbol = llenarArbol(arrCeldas[2].arbol , multDragon);

    //Electrico
    arrCeldas[3] = nuevaCeldaEfec(ELECTRICO);
    float multElectric[TIPOS_VALIDOS] = {1,0.5,1,1,1,0.5,2,1,1,1,0.5,0,2,1,1};
    arrCeldas[3].arbol = llenarArbol(arrCeldas[3].arbol , multElectric);

    //Fantasma
    arrCeldas[4] = nuevaCeldaEfec(FANTASMA);
    float multFantasma[TIPOS_VALIDOS] = {1,1,1,1,1,1,1,2,1,1,1,1,1,0,0};
    arrCeldas[4].arbol = llenarArbol(arrCeldas[4].arbol , multFantasma);

    //Fuego
    arrCeldas[5] = nuevaCeldaEfec(FUEGO);
    float multFuego[TIPOS_VALIDOS] = {1,1,0.5,2,0.5,0.5,0.5,1,2,1,2,1,1,1,1};
    arrCeldas[5].arbol = llenarArbol(arrCeldas[5].arbol , multFuego);

    //Hielo
    arrCeldas[6] = nuevaCeldaEfec(HIELO);
    float multHielo[TIPOS_VALIDOS] = {1,1,1,1,1,2,0.5,1,0.5,1,2,2,2,1,1};
    arrCeldas[6].arbol = llenarArbol(arrCeldas[6].arbol , multHielo);

    //Lucha
    arrCeldas[7] = nuevaCeldaEfec(LUCHA);
    float multLucha[TIPOS_VALIDOS] = {1,1,2,0.5,1,1,1,0,2,0.5,1,1,0.5,2,0.5};
    arrCeldas[7].arbol = llenarArbol(arrCeldas[7].arbol , multLucha);

    //Normal
    arrCeldas[8] = nuevaCeldaEfec(NORMAL);
    float multNormal[TIPOS_VALIDOS] = {1,1,0.5,1,1,1,1,0,1,1,1,1,1,1,1};
    arrCeldas[8].arbol = llenarArbol(arrCeldas[8].arbol , multNormal);

    //Planta
    arrCeldas[9] = nuevaCeldaEfec(PLANTA);
    float multPlanta[TIPOS_VALIDOS] = {1,1,2,0.5,0.5,0.5,2,1,1,0.5,0.5,2,0.5,1,1};
    arrCeldas[9].arbol = llenarArbol(arrCeldas[9].arbol , multPlanta);

    //Psiquico
    arrCeldas[10] = nuevaCeldaEfec(PSIQUICO);
    float multPsiquico[TIPOS_VALIDOS] = {2,1,1,1,1,1,1,1,1,2,1,1,1,1,0.5};
    arrCeldas[10].arbol = llenarArbol(arrCeldas[10].arbol , multPsiquico);

    //Roca
    arrCeldas[11] = nuevaCeldaEfec(ROCA);
    float multRoca[TIPOS_VALIDOS] = {0.5,1,1,2,2,1,1,1,2,1,1,0.5,2,1,1};
    arrCeldas[11].arbol = llenarArbol(arrCeldas[11].arbol , multRoca);

    //Tierra
    arrCeldas[12] = nuevaCeldaEfec(TIERRA);
    float multTierra[TIPOS_VALIDOS] = {1,2,2,0.5,2,1,1,1,1,2,0.5,1,0,1,1};
    arrCeldas[12].arbol = llenarArbol(arrCeldas[12].arbol , multTierra);

    //Veneno
    arrCeldas[13] = nuevaCeldaEfec(VENENO);
    float multVeneno[TIPOS_VALIDOS] = {1,1,0.5,2,1,1,1,0.5,1,0.5,2,0.5,1,1,1};
    arrCeldas[13].arbol = llenarArbol(arrCeldas[13].arbol , multVeneno);

    //Volador
    arrCeldas[14] = nuevaCeldaEfec(VOLADOR);
    float multVolador[TIPOS_VALIDOS] = {2,0.5,0.5,2,1,1,1,1,1,1,2,1,1,1,1};
    arrCeldas[14].arbol = llenarArbol(arrCeldas[14].arbol , multVolador);
}

int posTipoAtaque(celdaEfectividad arrEfect[] , char tipoAtaque[])
{
    int i = 0;
    int pos = -1;
    while(pos == -1 && i < TIPOS_VALIDOS)
    {
        if(strcmp(tipoAtaque , arrEfect[i].tipoAtaque) == 0)
        {
            pos = i;
        }
        i++;
    }
    return pos;
}

float buscarMultiplicador(nodoEfectividad * arbol , char tipoDefensor[])
{
    float rta = 1;
    if(arbol != NULL)
    {
        if(strcmp(arbol->dato.tipo , tipoDefensor) == 0)
        {
            rta = (float)arbol->dato.multiplicador;
        }
        else
        {
            if(strcmp(tipoDefensor , arbol->dato.tipo) > 0)
            {
                rta = buscarMultiplicador(arbol->der , tipoDefensor);
            }
            else
            {
                rta = buscarMultiplicador(arbol->izq , tipoDefensor);
            }
        }
    }
    return rta;
}

float calcularEfectividad(celdaEfectividad arrEfect[] , char tipoAtaque[] , char tipoDefensor[])
{
    float rta = 1;
    int pos = posTipoAtaque(arrEfect , tipoAtaque);
    rta = buscarMultiplicador(arrEfect[pos].arbol , tipoDefensor);

    return rta;
}
