#ifndef POKEMON_H_INCLUDED
#define POKEMON_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myConstants.h"
#include "movimientos.h"
#include "efectividades.h"

////////////////////////////////////////////////////////////////////////////////////
//***ESTRUCTURAS***
typedef struct infoPokedex
{
    int numPokedex;
    char nombre[30];
    char tipo_1[30];
    char tipo_2[30];
    int psMax;

}infoPokedex;

typedef struct nodoPokedex
{
    infoPokedex datoPokedex;
    struct nodoPokedex * sig;

}nodoPokedex;

typedef struct pokemon
{
    int uniqueID;
    infoPokedex datoPokedex;
    char apodo[30];
    int psActuales;
    movimiento setMovimientos[4];

}pokemon;

typedef struct nodoPokemon
{
    pokemon infoPokemon;
    struct nodoPokemon * sig;

}nodoPokemon;

////////////////////////////////////////////////////////////////////////////////////
//***PROTOTIPADOS***
int generarUniqueID();
nodoPokemon * recibirAtaque(nodoPokemon * oponente , movimiento ataque , celdaEfectividad arrEfect[]);
nodoPokemon * turnoJugador(pokemon delJugador , int ataque , nodoPokemon * delOponente , celdaEfectividad arrEfect[]);
nodoPokemon * turnoOponente(nodoPokemon * delOponente , nodoPokemon * delJugador , celdaEfectividad arrEfec[]);

//infoPokedex
infoPokedex inicInfoPokedex();
infoPokedex nuevaInfoPokedex(int num , char nombre[] , char tipo_1[] , char tipo_2[] , int psMax);
nodoPokedex * inicListaPokedex();
nodoPokedex * nuevoNodoPokedex(infoPokedex info);
nodoPokedex * insertarNodoPokedexAlFinal(nodoPokedex* lista , nodoPokedex * aInsertar);
nodoPokedex * borrarNodoPokedex(nodoPokedex * lista , char nombre[]);
infoPokedex infoPokedexEnLista(nodoPokedex * lista , char nombre[]);
nodoPokedex * leerArchivo_Pokedex(nodoPokedex * lista);
int escribirInfoPokedex_enArchivo(infoPokedex aGuardar);
int guardarListaPokedex_enArchivo(nodoPokedex * lista);
int reescribirArchivoPokedex(nodoPokedex * lista);
int cantInfoPokedex_enArchivo();

//Pokemon
pokemon nuevoPokemon(infoPokedex datoPokedex);
nodoPokemon * inicListaPokemon();
nodoPokemon * nuevoNodoPokemon(pokemon dato);
nodoPokemon * insertarNodoPokemon_alPpioDeLista(nodoPokemon * lista , nodoPokemon * aInsertar);
nodoPokemon * insertarNodoPokemon_alFinDeLista(nodoPokemon * lista , nodoPokemon * aInsertar);
nodoPokemon * borrarNodoPokemon(nodoPokemon * lista , int uniqueID);
nodoPokemon * vaciarEquipo(nodoPokemon * lista);
pokemon pokemonEnEquipo(nodoPokemon * lista , int uniqueID);
nodoPokemon * intercambiarDosNodosPokemon(nodoPokemon * lista , int uniqueID_A , int uniqueID_B);
int contarPokemonEnEquipo(nodoPokemon * lista);
nodoPokemon * leerArchivo_Equipo(nodoPokemon * equipo , char nombreArchivo[]);
int escribirPokemon_enArchivo(pokemon aGuardar , char nombreArchivo[]);
int guardarEquipoPokemon_enArchivo(nodoPokemon * equipo , char nombreArchivo[]);
int reescribirArchivoEquipo(nodoPokemon * equipo , char nombreArchivo[]);
nodoPokemon * primerPokeVivoEnEquipo(nodoPokemon * equipo);

int cantPokemon_enArchivo(char nombreArchivo[]);


//Defaults
nodoPokemon * defaultJugador_RED(nodoPokemon * equipo , nodoPokedex * pokedex , nodoInfoMov * listaMov);
nodoPokemon * defaultOponente_1(nodoPokemon * equipo , nodoPokedex * pokedex , nodoInfoMov * listaMov);
nodoPokemon * defaultOponente_2(nodoPokemon * equipo , nodoPokedex * pokedex , nodoInfoMov * listaMov);
nodoPokemon * defaultOponente_3(nodoPokemon * equipo , nodoPokedex * pokedex , nodoInfoMov * listaMov);
nodoPokemon * defaultOponente_4(nodoPokemon * equipo , nodoPokedex * pokedex , nodoInfoMov * listaMov);


#endif // POKEMON_H_INCLUDED
