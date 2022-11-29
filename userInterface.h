#ifndef USERINTERFACE_H_INCLUDED
#define USERINTERFACE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movimientos.h"

////////////////////////////////////////////////////////////////////////////////////
//***PROTOTIPADOS***

void tipoEstandarizado(char variableTipo[] , int eleccion);
int convertirOpcionChar(char opcionChar);

//MENÚ PRINCIPAL
void user_Main();

//MODO JUEGO
void user_ModoJuego();//LVL-1
void user_Batalla();//LVL-2
void user_Batalla_CambiarPoke(nodoPokemon * equipo , int cambioForzado);

//MODO EDITOR
void user_ModoEditor();//LVL-1

//EDITOR DE EQUIPOS
void user_SeleccionarEquipo_aEditar();//LVL-2

void user_EditorNuevoSetMovimientos(char nombrePokemon[] , movimiento setMovimientos[]);

void user_EditorBill();//LVL-3
void user_AgregarPokemon_enBill();//LVL-4
void user_EditarSetMovimientos(movimiento setMovimientos[]);//LVL-5
void user_AgregarMov_alSet(movimiento setMovimientos[]);//LVL-6

//EDITOR DE MOVIMIENTOS
void user_EditorMovimientos();//LVL-2
void user_AgregarMovimiento();//LVL-3
void user_BuscarMovimiento();//LVL-3
void user_EditarMovBuscado(infoMov movBuscado);//LVL-4

//EDITOR DE POKEDEX
void user_EditorPokedex();//LVL-2
void user_AgregarInfoPokedex();//LVL-3
void user_BuscarInfoPokedex();//LVL-3
void user_EditarInfoPokedexBuscada(infoPokedex infoPokedexBuscada);//LVL-4


#endif // USERINTERFACE_H_INCLUDED
