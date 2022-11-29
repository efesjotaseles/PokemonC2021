#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "myConstants.h"
#include "movimientos.h"
#include "pokemon.h"
#include "efectividades.h"

////////////////////////////////////////////////////////////////////////////////////
//***FUNCIONES***
int generarUniqueID()
{
    FILE * archi;
    //Se inicializa una variable int en 0;
    int uniqueID = 0;

    //Se intenta abrir el archivo en modo LECTURA
    archi = fopen(ARCHI_UNIQUE_ID, "rb");

    if (archi == NULL)
    {
        //Si da error, entonces se cierra el archivo.
        fclose(archi);
    }
    else
    {
        //Si no da error, entonces se almacena en la variable el dato del archivo.
        fread(&uniqueID, sizeof(int), 1, archi);
        //Luego se incrementa en 1 el dato almacenado en la variable.
        uniqueID++;
        //Y se cierra el archivo.
        fclose(archi);
    }
    //Se haya leído o no, se abre el archivo en modo ESCRITURA
    archi = fopen(ARCHI_UNIQUE_ID, "wb");
    //Se escribe en el archivo el dato almacenado en la variable (0 si no hubo archivo, un valor incrementado en 1 si hubo archivo)
    fwrite(&uniqueID, sizeof(int), 1, archi);

    //Y la función retorna la variable (0 si no hubo archivo, o lo que había originalmente en el achivo +1)
    return uniqueID;
}

nodoPokemon * recibirAtaque(nodoPokemon * defensor , movimiento ataque , celdaEfectividad arrEfect[])
{
    float danio = ataque.datos.potencia;
/*
    //Se calcula el daño
    float efecVS_tipo_1 = calcularEfectividad(arrEfect , ataque.datos.tipo , defensor->infoPokemon.datoPokedex.tipo_1);
    danio = danio * efecVS_tipo_1;
    if(strcmp(defensor->infoPokemon.datoPokedex.tipo_2 , "") != 0)
    {
        danio = danio * calcularEfectividad(arrEfect , ataque.datos.tipo , defensor->infoPokemon.datoPokedex.tipo_2);
    }
*/
    if(danio <= defensor->infoPokemon.psActuales)//Si el daño NO es mayor a los PS actuales...
    {
        //Se resta el daño obtenido a los PS del Pokemon
        defensor->infoPokemon.psActuales -= (int)danio;

    }
    else//Si el daño es mayor que los PS acutuales...
    {
        defensor->infoPokemon.psActuales = 0;
    }

    return defensor;
}

nodoPokemon * turnoJugador(pokemon delJugador , int ataque , nodoPokemon * delOponente , celdaEfectividad arrEfect[])
{
        delOponente = recibirAtaque(delOponente, delJugador.setMovimientos[ataque-1] , arrEfect);

    return delOponente;
}

nodoPokemon * turnoOponente(nodoPokemon * delOponente , nodoPokemon * delJugador , celdaEfectividad arrEfec[])
{
    int opcion = rand()%4;
    while(delOponente->infoPokemon.setMovimientos[opcion].ppDisponibles < 1)
    {
        opcion = rand()%4;
    }
    delJugador = recibirAtaque(delJugador, delOponente->infoPokemon.setMovimientos[opcion], arrEfec);
    delOponente->infoPokemon.setMovimientos[opcion].ppDisponibles--; //Disminuimos en 1 los PP del ataque usado

    return delJugador;
}

//infoPokedex
infoPokedex inicInfoPokedex()
{
    infoPokedex aux;
    aux.numPokedex = -1;
    aux.psMax = -1;
    strcpy(aux.nombre , "");
    strcpy(aux.tipo_1 , "");
    strcpy(aux.tipo_2 , "");

    return aux;
}

infoPokedex nuevaInfoPokedex(int num , char nombre[] , char tipo_1[] , char tipo_2[] , int psMax)
{
    infoPokedex aux;

    aux.numPokedex = num;
    aux.psMax = psMax;
    strcpy(aux.nombre , nombre);
    strcpy(aux.tipo_1 , tipo_1);
    strcpy(aux.tipo_2 , tipo_2);//Puede recibir "" como string.

    return aux;
}

nodoPokedex * inicListaPokedex()
{
    return NULL;
}

nodoPokedex * nuevoNodoPokedex(infoPokedex info)
{
    nodoPokedex * aux = (nodoPokedex*)malloc(sizeof(nodoPokedex));
    aux->datoPokedex = info;
    aux->sig = NULL;

    return aux;
}

nodoPokedex * insertarNodoPokedexAlFinal(nodoPokedex* lista , nodoPokedex * aInsertar)
{
    if(lista == NULL)
    {
        lista = aInsertar;
    }
    else
    {
        lista->sig = insertarNodoPokedexAlFinal(lista->sig , aInsertar);
    }

    return lista;
}

nodoPokedex * borrarNodoPokedex(nodoPokedex * lista , char nombre[])
{
    if(lista != NULL)
    {
        if(strcmp(lista->datoPokedex.nombre , nombre) == 0)
        {
            nodoPokedex * aBorrar = lista;
            lista = lista->sig;
            free(aBorrar);
        }
        else
        {
            lista->sig = borrarNodoPokedex(lista->sig , nombre);
        }
    }

    return lista;
}

infoPokedex infoPokedexEnLista(nodoPokedex * lista , char nombre[])
{
    infoPokedex aux = inicInfoPokedex();
    if(lista != NULL)
    {
        nodoPokedex * seguidora = lista;
        while(seguidora != NULL && strcmp(seguidora->datoPokedex.nombre , nombre) != 0)
        {
            seguidora = seguidora->sig;
        }
        if(seguidora != NULL)
        {
            aux = seguidora->datoPokedex;
        }
    }

    return aux;
}

nodoPokedex * leerArchivo_Pokedex(nodoPokedex * lista)
{
    if(lista == NULL)
    {
        FILE * archi = fopen(ARCHI_POKEDEX, "rb");
        if(archi != NULL)
        {
            int leido = 0;
            infoPokedex auxInfo;
            leido = fread(&auxInfo, sizeof(infoPokedex), 1, archi);
            while(!feof(archi))
            {
                nodoPokedex * auxNodo = nuevoNodoPokedex(auxInfo);
                lista = insertarNodoPokedexAlFinal(lista, auxNodo);
                leido = fread(&auxInfo, sizeof(infoPokedex), 1, archi);
            }
        }
        fclose(archi);
    }

    return lista;
}

int escribirInfoPokedex_enArchivo(infoPokedex aGuardar)
{
    int cantEscrita = 0;
    FILE * archi = fopen(ARCHI_POKEDEX , "ab");
    if(archi != NULL)
    {
        cantEscrita = fwrite(&aGuardar , sizeof(infoPokedex) , 1 , archi);
    }
    fclose(archi);

    return cantEscrita;
}

int guardarListaPokedex_enArchivo(nodoPokedex * lista)
{
    int cantEscrita = 0;
    if(lista != NULL)
    {
        cantEscrita = escribirInfoPokedex_enArchivo(lista->datoPokedex);
        cantEscrita += guardarListaPokedex_enArchivo(lista->sig);
    }

    return cantEscrita;
}

int reescribirArchivoPokedex(nodoPokedex * lista)
{
    int cantidadEscrita = 0;
    if(lista != NULL)
    {
        FILE * archi = fopen(ARCHI_POKEDEX , "wb");
        if(archi == NULL)
        {
            fclose(archi);
        }
        else
        {
            fclose(archi);
            cantidadEscrita = guardarListaPokedex_enArchivo(lista);
        }
    }

    return cantidadEscrita;
}

int cantInfoPokedex_enArchivo()
{
    int rta = 0;
    FILE * archi = fopen(ARCHI_POKEDEX, "rb");
    if(archi != NULL)
    {
        fseek(archi, 0, SEEK_END);
        rta = ftell(archi) / sizeof(infoPokedex);
    }
    fclose(archi);

    return rta;
}

//Pokemon
pokemon inicInfoPokemon()
{
    pokemon aux;
    aux.datoPokedex = inicInfoPokedex();
    strcpy(aux.apodo , aux.datoPokedex.nombre);
    aux.psActuales = aux.datoPokedex.psMax;
    inicSetMovimientos(aux.setMovimientos);
    aux.uniqueID = -1;

    return aux;
}
pokemon nuevoPokemon(infoPokedex datoPokedex)
{
    pokemon aux;
    aux.uniqueID = generarUniqueID();
    aux.datoPokedex = datoPokedex;
    strcpy(aux.apodo , aux.datoPokedex.nombre);
    aux.psActuales = aux.datoPokedex.psMax;
    inicSetMovimientos(aux.setMovimientos);

    return aux;
}

nodoPokemon * inicListaPokemon()
{
    return NULL;
}

nodoPokemon * nuevoNodoPokemon(pokemon dato)
{
    nodoPokemon * aux = (nodoPokemon*)malloc(sizeof(nodoPokemon));
    aux->infoPokemon = dato;
    aux->sig = NULL;

    return aux;
}

nodoPokemon * insertarNodoPokemon_alPpioDeLista(nodoPokemon * lista , nodoPokemon * aInsertar)
{
    if(lista == NULL)
    {
        lista = aInsertar;
    }
    else
    {
        aInsertar->sig = lista;
        lista = aInsertar;
    }

    return lista;
}

nodoPokemon * insertarNodoPokemon_alFinDeLista(nodoPokemon * lista , nodoPokemon * aInsertar)
{
    if(lista == NULL)
    {
        lista = aInsertar;
    }
    else
    {
        lista->sig = insertarNodoPokemon_alFinDeLista(lista->sig , aInsertar);
    }

    return lista;
}

nodoPokemon * borrarNodoPokemon(nodoPokemon * lista , int uniqueID)
{
    if(lista != NULL)
    {
        if(lista->infoPokemon.uniqueID == uniqueID)
        {
            nodoPokemon * aBorrar = lista;
            lista = lista->sig;
            free(aBorrar);
        }
        else
        {
            lista->sig = borrarNodoPokemon(lista->sig , uniqueID);
        }
    }

    return lista;
}

nodoPokemon * vaciarEquipo(nodoPokemon * lista)
{
    while(lista != NULL)
    {
        lista = borrarNodoPokemon(lista , lista->infoPokemon.uniqueID);
    }
    return lista;
}

pokemon pokemonEnEquipo(nodoPokemon * lista , int uniqueID)
{
    pokemon aux = inicInfoPokemon();
    nodoPokemon * seguidora = lista;
    while(seguidora != NULL && uniqueID != seguidora->infoPokemon.uniqueID)
    {
        seguidora = seguidora->sig;
    }
    if (seguidora != NULL)
    {
        aux = seguidora->infoPokemon;
    }

    return aux;
}

nodoPokemon * intercambiarDosNodosPokemon(nodoPokemon * lista , int uniqueID_A , int uniqueID_B)
{
    //Buscamos los nodos que contienen los uniqueID provistos
    if(lista != NULL)
    {
        nodoPokemon * nodoA;
        nodoPokemon * nodoB;
        nodoPokemon * seguidora = lista;
        //El nodoA
        while(seguidora != NULL && seguidora->infoPokemon.uniqueID != uniqueID_A)
        {
            seguidora = seguidora->sig;
        }
        if(seguidora != NULL)
        {
            nodoA = seguidora;
        }

        //el nodoB
        while(seguidora != NULL && seguidora->infoPokemon.uniqueID != uniqueID_B)
        {
            seguidora = seguidora->sig;
        }
        if(seguidora != NULL)
        {
            nodoB = seguidora;
        }

        pokemon aux = nodoA->infoPokemon;
        nodoA->infoPokemon = nodoB->infoPokemon;
        nodoB->infoPokemon = aux;
    }

    return lista;
}

int contarPokemonEnEquipo(nodoPokemon * lista)
{
    int rta = 0;
    if(lista != NULL)
    {
        rta = 1 + contarPokemonEnEquipo(lista->sig);
    }

    return rta;
}

nodoPokemon * leerArchivo_Equipo(nodoPokemon * equipo , char nombreArchivo[])
{
    if(equipo == NULL)
    {
        FILE * archi = fopen(nombreArchivo, "rb");
        if(archi != NULL)
        {
            int leido = 0;
            pokemon auxPokemon;
            leido = fread(&auxPokemon, sizeof(pokemon), 1, archi);
            while(!feof(archi))
            {
                nodoPokemon * auxNodo = nuevoNodoPokemon(auxPokemon);
                equipo = insertarNodoPokemon_alFinDeLista(equipo , auxNodo);
                leido = fread(&auxPokemon, sizeof(pokemon), 1, archi);
            }
        }
        fclose(archi);
    }

    return equipo;
}

int escribirPokemon_enArchivo(pokemon aGuardar , char nombreArchivo[])
{
    int cantEscrita = 0;
    FILE * archi = fopen(nombreArchivo , "ab");
    if(archi != NULL)
    {
        cantEscrita = fwrite(&aGuardar , sizeof(pokemon) , 1 , archi);
    }
    fclose(archi);

    return cantEscrita;
}

int guardarEquipoPokemon_enArchivo(nodoPokemon * equipo , char nombreArchivo[])
{
    int cantEscrita = 0;
    if(equipo != NULL)
    {
        cantEscrita = escribirPokemon_enArchivo(equipo->infoPokemon , nombreArchivo);
        cantEscrita += guardarEquipoPokemon_enArchivo(equipo->sig , nombreArchivo);
    }

    return cantEscrita;
}

int reescribirArchivoEquipo(nodoPokemon * equipo , char nombreArchivo[])
{
    int cantidadEscrita = 0;
    if(equipo != NULL)
    {
        FILE * archi = fopen(nombreArchivo , "wb");
        if(archi == NULL)
        {
            fclose(archi);
        }
        else
        {
            fclose(archi);
            cantidadEscrita = guardarEquipoPokemon_enArchivo(equipo , nombreArchivo);
        }
    }

    return cantidadEscrita;

}

nodoPokemon * primerPokeVivoEnEquipo(nodoPokemon * equipo)
{
    nodoPokemon * aux = equipo;
    if(aux != NULL)
    {
        if (aux->infoPokemon.psActuales <= 0)
        {
            aux = primerPokeVivoEnEquipo(aux->sig);
        }
    }

    return aux;
}


int cantPokemon_enArchivo(char nombreArchivo[])
{
    int rta = 0;
    FILE * archi = fopen(nombreArchivo , "rb");
    if(archi != NULL)
    {
        fseek(archi , 0 , SEEK_END);
        rta = ftell(archi)/sizeof(pokemon);
    }
    fclose(archi);

    return rta;
}


//EQUIPOS DEFAULT

//JUGADOR RED (default)
nodoPokemon * defaultJugador_RED(nodoPokemon * equipo , nodoPokedex * pokedex , nodoInfoMov * listaMov)
{
    equipo = vaciarEquipo(equipo);

    //Crear/insertar a Poli
    //Lo buscamos en la pokedex
    infoPokedex aux_pokedex = infoPokedexEnLista(pokedex , "Poliwrath");
    //Si no no encontramos, lo creamos...
    if(aux_pokedex.numPokedex == -1)
    {
        aux_pokedex = nuevaInfoPokedex(62 , "Poliwrath" , AGUA , LUCHA , 173);
        pokedex = insertarNodoPokedexAlFinal(pokedex , nuevoNodoPokedex(aux_pokedex));
    }
    //Generamos el nodo...
    pokemon aux_pokemon = nuevoPokemon(aux_pokedex);
    //Cambiamos el apodo
    strcpy(aux_pokemon.apodo , "Poli");
    nodoPokemon * aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos a Poli

    //
    //Buscamos DobleBofeton en la listaMov
    infoMov aux_InfoMov = movEnLista(listaMov , "DobleBofeton");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("DobleBofeton" , NORMAL , 15 , 10);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Poli
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos PunioCertero en la listaMov
    aux_InfoMov = movEnLista(listaMov , "PunioCertero");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("PunioCertero" , LUCHA , 150 , 20);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Poli
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos PistolaAgua en la listaMov
    aux_InfoMov = movEnLista(listaMov , "PistolaAgua");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("PistolaAgua" , AGUA , 40 , 25);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Poli
    aux_nodo->infoPokemon.setMovimientos[2] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos RayoHielo en la listaMov
    aux_InfoMov = movEnLista(listaMov , "RayoHielo");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("RayoHielo" , HIELO , 90 , 10);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Poli
    aux_nodo->infoPokemon.setMovimientos[3] = nuevoMovimiento(aux_InfoMov);

    //Insertamos a Poli en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);
    //////////////////////////////////////////////////////////////////

    //Crear/insertar a Saur
    //Lo buscamos en la pokedex
    aux_pokedex = infoPokedexEnLista(pokedex , "Venusaur");
    //Si no no encontramos, lo creamos...
    if(aux_pokedex.numPokedex == -1)
    {
        aux_pokedex = nuevaInfoPokedex(3 , "Venusaur" , PLANTA , VENENO , 163);
        pokedex = insertarNodoPokedexAlFinal(pokedex , nuevoNodoPokedex(aux_pokedex));
    }
    //Generamos el nodo...
    aux_pokemon = nuevoPokemon(aux_pokedex);
    //Cambiamos el apodo
    strcpy(aux_pokemon.apodo , "Saur");
    aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos a Saur

    //
    //Buscamos HojaAfilada en la listaMov
    aux_InfoMov = movEnLista(listaMov , "HojaAfilada");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("HojaAfilada" , PLANTA , 55 , 25);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Saur
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos RayoSolar en la listaMov
    aux_InfoMov = movEnLista(listaMov , "RayoSolar");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("RayoSolar" , PLANTA , 120 , 10);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Saur
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos PlantaFeroz en la listaMov
    aux_InfoMov = movEnLista(listaMov , "PlantaFeroz");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("PlantaFeroz" , PLANTA , 150 , 5);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Saur
    aux_nodo->infoPokemon.setMovimientos[2] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos LatigoCepa en la listaMov
    aux_InfoMov = movEnLista(listaMov , "LatigoCepa");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("LatigoCepa" , PLANTA , 45 , 25);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Saur
    aux_nodo->infoPokemon.setMovimientos[3] = nuevoMovimiento(aux_InfoMov);

    //Insertamos a Saur en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);
    //////////////////////////////////////////////////////////////////

    //Crear/insertar a Pika
    //Lo buscamos en la pokedex
    aux_pokedex = infoPokedexEnLista(pokedex , "Pikachu");
    //Si no no encontramos, lo creamos...
    if(aux_pokedex.numPokedex == -1)
    {
        aux_pokedex = nuevaInfoPokedex(25 , "Pikachu" , ELECTRICO , "" , 118);
        pokedex = insertarNodoPokedexAlFinal(pokedex , nuevoNodoPokedex(aux_pokedex));
    }
    //Generamos el nodo...
    aux_pokemon = nuevoPokemon(aux_pokedex);
    //Cambiamos el apodo
    strcpy(aux_pokemon.apodo , "Pika");
    aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos a Pika

    //
    //Buscamos Impactrueno en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Impactrueno");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Impactrueno" , ELECTRICO , 40 , 30);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Pika
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos AtaqueRapido en la listaMov
    aux_InfoMov = movEnLista(listaMov , "AtaqueRapido");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("AtaqueRapido" , NORMAL , 40 , 30);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Pika
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Trueno en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Trueno");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Trueno" , ELECTRICO , 110 , 10);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Pika
    aux_nodo->infoPokemon.setMovimientos[2] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Surf en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Surf");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Surf" , AGUA , 90 , 15);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Pika
    aux_nodo->infoPokemon.setMovimientos[3] = nuevoMovimiento(aux_InfoMov);

    //Insertamos a Pika en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);
    //////////////////////////////////////////////////////////////////

    //Crear/insertar a Lax
    //Lo buscamos en la pokedex
    aux_pokedex = infoPokedexEnLista(pokedex , "Snorlax");
    //Si no no encontramos, lo creamos...
    if(aux_pokedex.numPokedex == -1)
    {
        aux_pokedex = nuevaInfoPokedex(143 , "Snorlax" , NORMAL , "" , 243);
        pokedex = insertarNodoPokedexAlFinal(pokedex , nuevoNodoPokedex(aux_pokedex));
    }
    //Generamos el nodo...
    aux_pokemon = nuevoPokemon(aux_pokedex);
    //Cambiamos el apodo
    strcpy(aux_pokemon.apodo , "Lax");
    aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos a Lax

    //
    //Buscamos GolpeCuerpo en la listaMov
    aux_InfoMov = movEnLista(listaMov , "GolpeCuerpo");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("GolpeCuerpo" , NORMAL , 85 , 15);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Lax
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Terremoto en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Terremoto");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Terremoto" , TIERRA , 100 , 10);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Lax
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Cabezazo en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Cabezazo");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Cabezazo" , NORMAL , 130 , 10);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Lax
    aux_nodo->infoPokemon.setMovimientos[2] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Fuerza en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Fuerza");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Fuerza" , NORMAL , 80 , 15);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Lax
    aux_nodo->infoPokemon.setMovimientos[3] = nuevoMovimiento(aux_InfoMov);

    //Insertamos a Lax en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);
    //////////////////////////////////////////////////////////////////

    //Crear/insertar a Gyara
    //Lo buscamos en la pokedex
    aux_pokedex = infoPokedexEnLista(pokedex , "Gyarados");
    //Si no no encontramos, lo creamos...
    if(aux_pokedex.numPokedex == -1)
    {
        aux_pokedex = nuevaInfoPokedex(130 , "Gyarados" , AGUA , VOLADOR , 178);
        pokedex = insertarNodoPokedexAlFinal(pokedex , nuevoNodoPokedex(aux_pokedex));
    }
    //Generamos el nodo...
    aux_pokemon = nuevoPokemon(aux_pokedex);
    //Cambiamos el apodo
    strcpy(aux_pokemon.apodo , "Gyara");
    aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos a Gyara

    //
    //Buscamos Hidrobomba en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Hidrobomba");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Hidrobomba" , AGUA , 110 , 5);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Gyara
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Hiperrayo en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Hiperrayo");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Hiperrayo" , NORMAL , 150 , 5);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Gyara
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Mordisco en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Mordisco");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Mordisco" , NORMAL , 60 , 25);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Gyara
    aux_nodo->infoPokemon.setMovimientos[2] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Dragoaliento en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Dragoaliento");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Dragoaliento" , DRAGON , 60 , 20);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Gyara
    aux_nodo->infoPokemon.setMovimientos[3] = nuevoMovimiento(aux_InfoMov);

    //Insertamos a Gyara en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);
    //////////////////////////////////////////////////////////////////

    //Crear/insertar a Aero
    //Lo buscamos en la pokedex
    aux_pokedex = infoPokedexEnLista(pokedex , "Aerodactyl");
    //Si no no encontramos, lo creamos...
    if(aux_pokedex.numPokedex == -1)
    {
        aux_pokedex = nuevaInfoPokedex(142 , "Aerodactyl" , ROCA , VOLADOR , 163);
        pokedex = insertarNodoPokedexAlFinal(pokedex , nuevoNodoPokedex(aux_pokedex));
    }
    //Generamos el nodo...
    aux_pokemon = nuevoPokemon(aux_pokedex);
    //Cambiamos el apodo
    strcpy(aux_pokemon.apodo , "Aero");
    aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos a Aero

    //
    //Buscamos Vuelo en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Vuelo");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Vuelo" , VOLADOR , 90 , 15);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Aero
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Derribo en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Derribo");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Derribo" , NORMAL , 90 , 20);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Aero
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos GarraDragon en la listaMov
    aux_InfoMov = movEnLista(listaMov , "GarraDragon");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("GarraDragon" , DRAGON , 80 , 15);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Aero
    aux_nodo->infoPokemon.setMovimientos[2] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Hiperrayo en la listaMov
    aux_InfoMov = movEnLista(listaMov , "GarraDragon");
    //Sabemos que existe porque lo creamos previamente...
    //Lo insertamos en Aero
    aux_nodo->infoPokemon.setMovimientos[3] = nuevoMovimiento(aux_InfoMov);

    //Insertamos a Aero en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);
    //////////////////////////////////////////////////////////////////

    return equipo;
}

//LORELEI (default)
nodoPokemon * defaultOponente_1(nodoPokemon * equipo , nodoPokedex * pokedex , nodoInfoMov * listaMov)
{

    equipo = vaciarEquipo(equipo);

    //Crear/insertar a Dewgong
    //Lo buscamos en la pokedex
    infoPokedex aux_pokedex = infoPokedexEnLista(pokedex , "Dewgong");
    //Si no no encontramos, lo creamos...
    if(aux_pokedex.numPokedex == -1)
    {
        aux_pokedex = nuevaInfoPokedex(87 , "Dewgong" , AGUA , HIELO , 173);
        pokedex = insertarNodoPokedexAlFinal(pokedex , nuevoNodoPokedex(aux_pokedex));
    }
    //Generamos el nodo...
    pokemon aux_pokemon = nuevoPokemon(aux_pokedex);
    nodoPokemon * aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos a Dewgong

    //
    //Buscamos RayoAurora en la listaMov
    infoMov aux_InfoMov = movEnLista(listaMov , "RayoAurora");

    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("RayoAurora" , HIELO , 65 , 20);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Dewgong
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Derribo en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Derribo");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Derribo" , NORMAL , 90 , 20);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Dewgong
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //Insertamos a Dewgong en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);
    //////////////////////////////////////////////////////////////////

    //Crear/insertar a Cloyster
    //Lo buscamos en la pokedex
    aux_pokedex = infoPokedexEnLista(pokedex , "Cloyster");
    //Si no no encontramos, lo creamos...
    if(aux_pokedex.numPokedex == -1)
    {
        aux_pokedex = nuevaInfoPokedex(91 , "Cloyster" , AGUA , HIELO , 133);
        pokedex = insertarNodoPokedexAlFinal(pokedex , nuevoNodoPokedex(aux_pokedex));
    }
    //Generamos el nodo...
    aux_pokemon = nuevoPokemon(aux_pokedex);
    aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos a Cloyster

    //
    //Buscamos Tenaza en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Tenaza");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Tenaza" , AGUA , 35 , 15);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Cloyster
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos RayoAurora en la listaMov
    aux_InfoMov = movEnLista(listaMov , "RayoAurora");
    //Sabemos que lo vamos a encontrar porque lo hubiéramos creado al generar a Dewgong
    //Lo insertamos en Cloyster
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos ClavoCanion en la listaMov
    aux_InfoMov = movEnLista(listaMov , "ClavoCanion");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("ClavoCanion" , NORMAL , 20 , 15);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Cloyster
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //Insertamos a Cloyster en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);
    //////////////////////////////////////////////////////////////////

    //Crear/insertar a Slowbro
    //Lo buscamos en la pokedex
    aux_pokedex = infoPokedexEnLista(pokedex , "Slowbro");
    //Si no no encontramos, lo creamos...
    if(aux_pokedex.numPokedex == -1)
    {
        aux_pokedex = nuevaInfoPokedex(80 , "Slowbro" , AGUA , PSIQUICO , 178);
        pokedex = insertarNodoPokedexAlFinal(pokedex , nuevoNodoPokedex(aux_pokedex));
    }
    //Generamos el nodo...
    aux_pokemon = nuevoPokemon(aux_pokedex);
    aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos a Slowbro

    //Buscamos PistolaAgua en la listaMov
    aux_InfoMov = movEnLista(listaMov , "PistolaAgua");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("PistolaAgua" , AGUA , 40 , 25);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Slowbro
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //Insertamos a Slowbro en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);

    //////////////////////////////////////////////////////////////////

    //Crear/insertar a Jynx
    //Lo buscamos en la pokedex
    aux_pokedex = infoPokedexEnLista(pokedex , "Jynx");
    //Si no no encontramos, lo creamos...
    if(aux_pokedex.numPokedex == -1)
    {
        aux_pokedex = nuevaInfoPokedex(124 , "Jynx" , HIELO , PSIQUICO , 148);
        pokedex = insertarNodoPokedexAlFinal(pokedex , nuevoNodoPokedex(aux_pokedex));
    }
    //Generamos el nodo...
    aux_pokemon = nuevoPokemon(aux_pokedex);
    aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos a Jynx

    //Buscamos DobleBofeton en la listaMov
    aux_InfoMov = movEnLista(listaMov , "DobleBofeton");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("DobleBofeton" , NORMAL , 15 , 10);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Jynx
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //Buscamos PunioHielo en la listaMov
    aux_InfoMov = movEnLista(listaMov , "PunioHielo");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("PunioHielo" , HIELO , 75 , 15);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Jynx
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //Buscamos GolpeCuerpo en la listaMov
    aux_InfoMov = movEnLista(listaMov , "GolpeCuerpo");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("GolpeCuerpo" , NORMAL , 85 , 15);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Jynx
    aux_nodo->infoPokemon.setMovimientos[2] = nuevoMovimiento(aux_InfoMov);

    //Buscamos Golpe en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Golpe");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Golpe" , NORMAL , 120 , 10);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Jynx
    aux_nodo->infoPokemon.setMovimientos[3] = nuevoMovimiento(aux_InfoMov);

    //Insertamos a Jynx en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);

    //////////////////////////////////////////////////////////////////

    //Crear/insertar a Lapras
    //Lo buscamos en la pokedex
    aux_pokedex = infoPokedexEnLista(pokedex , "Lapras");
    //Si no no encontramos, lo creamos...
    if(aux_pokedex.numPokedex == -1)
    {
        aux_pokedex = nuevaInfoPokedex(131 , "Lapras" , AGUA , HIELO , 213);
        pokedex = insertarNodoPokedexAlFinal(pokedex , nuevoNodoPokedex(aux_pokedex));
    }
    //Generamos el nodo...
    aux_pokemon = nuevoPokemon(aux_pokedex);
    aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos a Lapras

    //Buscamos GolpeCuerpo en la listaMov
    aux_InfoMov = movEnLista(listaMov , "GolpeCuerpo");
    //Sabemos que lo vamos a encontrar porque lo hubiéramos creado al generar a Jynx
    //Lo insertamos en Lapras
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //Buscamos Ventisca en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Ventisca");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Ventisca" , HIELO , 110 , 5);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Lapras
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //Buscamos Hidrobomba en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Hidrobomba");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Hidrobomba" , AGUA , 110 , 5);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Lapras
    aux_nodo->infoPokemon.setMovimientos[2] = nuevoMovimiento(aux_InfoMov);

    //Insertamos a Lapras en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);

    //////////////////////////////////////////////////////////////////

    return equipo;
}

//BRUNO (default)
nodoPokemon * defaultOponente_2(nodoPokemon * equipo , nodoPokedex * pokedex , nodoInfoMov * listaMov)
{
    equipo = vaciarEquipo(equipo);

    //Crear/insertar a Onix
    //Lo buscamos en la pokedex
    infoPokedex aux_pokedex = infoPokedexEnLista(pokedex , "Onix");
    //Si no no encontramos, lo creamos...
    if(aux_pokedex.numPokedex == -1)
    {
        aux_pokedex = nuevaInfoPokedex(95 , "Onix" , ROCA , TIERRA , 118);
        pokedex = insertarNodoPokedexAlFinal(pokedex , nuevoNodoPokedex(aux_pokedex));
    }
    //Generamos el nodo...
    pokemon aux_pokemon = nuevoPokemon(aux_pokedex);
    nodoPokemon * aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos a Onix

    //
    //Buscamos Lanzarrocas en la listaMov
    infoMov aux_InfoMov = movEnLista(listaMov , "Lanzarrocas");

    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Lanzarrocas" , ROCA , 50 , 15);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Onix
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Furia en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Furia");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Furia" , NORMAL , 20 , 20);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Onix
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Atizar en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Atizar");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Atizar" , NORMAL , 80 , 20);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Onix
    aux_nodo->infoPokemon.setMovimientos[2] = nuevoMovimiento(aux_InfoMov);


    //Insertamos a Onix en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);
    //////////////////////////////////////////////////////////////////

    //Crear/insertar a Hitmonchan
    //Lo buscamos en la pokedex
    aux_pokedex = infoPokedexEnLista(pokedex , "Hitmonchan");
    //Si no no encontramos, lo creamos...
    if(aux_pokedex.numPokedex == -1)
    {
        aux_pokedex = nuevaInfoPokedex(107 , "Hitmonchan" , LUCHA , "" , 133);
        pokedex = insertarNodoPokedexAlFinal(pokedex , nuevoNodoPokedex(aux_pokedex));
    }
    //Generamos el nodo...
    aux_pokemon = nuevoPokemon(aux_pokedex);
    aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos a Hitmonchan

    //
    //Buscamos PunioHielo en la listaMov
    aux_InfoMov = movEnLista(listaMov , "PunioHielo");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("PunioHielo" , HIELO , 75 , 15);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Hitmonchan
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos PunioTrueno en la listaMov
    aux_InfoMov = movEnLista(listaMov , "PunioTrueno");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("PunioTrueno" , ELECTRICO , 75 , 15);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Hitmonchan
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Megapunio en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Megapunio");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Megapunio" , NORMAL , 80 , 20);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Hitmonchan
    aux_nodo->infoPokemon.setMovimientos[2] = nuevoMovimiento(aux_InfoMov);

    //Insertamos a Hitmonchan en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);
    //////////////////////////////////////////////////////////////////

    //Crear/insertar a Hitmonlee
    //Lo buscamos en la pokedex
    aux_pokedex = infoPokedexEnLista(pokedex , "Hitmonlee");
    //Si no no encontramos, lo creamos...
    if(aux_pokedex.numPokedex == -1)
    {
        aux_pokedex = nuevaInfoPokedex(108 , "Hitmonlee" , LUCHA , "" , 133);
        pokedex = insertarNodoPokedexAlFinal(pokedex , nuevoNodoPokedex(aux_pokedex));
    }
    //Generamos el nodo...
    aux_pokemon = nuevoPokemon(aux_pokedex);
    aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos a Hitmonlee

    //
    //Buscamos PatadaSalto en la listaMov
    aux_InfoMov = movEnLista(listaMov , "PatadaSalto");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("PatadaSalto" , LUCHA , 100 , 10);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Hitmonlee
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos PatadaSaltoAlta en la listaMov
    aux_InfoMov = movEnLista(listaMov , "PatadaSaltoAlta");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("PatadaSaltoAlta" , LUCHA , 130 , 10);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Hitmonlee
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Megapatada en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Megapatada");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Megapatada" , NORMAL , 120 , 5);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Hitmonlee
    aux_nodo->infoPokemon.setMovimientos[2] = nuevoMovimiento(aux_InfoMov);


    //Insertamos a Hitmonlee en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);
    //////////////////////////////////////////////////////////////////

    //Insertar al segundo Onix
    //Lo buscamos en la pokedex
    aux_pokedex = infoPokedexEnLista(pokedex , "Onix");
    //Lo deberíamos encontrar, ya que lo creamos previamente en esta función
    //Generamos el nodo...
    aux_pokemon = nuevoPokemon(aux_pokedex);
    aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos al segundo Onix

    //
    //Buscamos Lanzarrocas en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Lanzarrocas");
    //La deberíamos encontrar, ya que la creamos previamente en esta función
    //Lo insertamos en Onix
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Furia en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Furia");
    //La deberíamos encontrar, ya que la creamos previamente en esta función
    //Lo insertamos en Onix
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Atizar en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Atizar");
    //La deberíamos encontrar, ya que la creamos previamente en esta función
    //Lo insertamos en Onix
    aux_nodo->infoPokemon.setMovimientos[2] = nuevoMovimiento(aux_InfoMov);


    //Insertamos al segundo Onix en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);
    //////////////////////////////////////////////////////////////////

    //Crear/insertar a Machamp
    //Lo buscamos en la pokedex
    aux_pokedex = infoPokedexEnLista(pokedex , "Machamp");
    //Si no no encontramos, lo creamos...
    if(aux_pokedex.numPokedex == -1)
    {
        aux_pokedex = nuevaInfoPokedex(68 , "Machamp" , LUCHA , "" , 173);
        pokedex = insertarNodoPokedexAlFinal(pokedex , nuevoNodoPokedex(aux_pokedex));
    }
    //Generamos el nodo...
    aux_pokemon = nuevoPokemon(aux_pokedex);
    aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos a Machamp

    //
    //Buscamos Sumision en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Sumision");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Sumision" , LUCHA , 80 , 20);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Machamp
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos GolpeKarate en la listaMov
    aux_InfoMov = movEnLista(listaMov , "GolpeKarate");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("GolpeKarate" , LUCHA , 50 , 25);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Machamp
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Fuerza en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Fuerza");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Fuerza" , NORMAL , 80 , 15);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Machamp
    aux_nodo->infoPokemon.setMovimientos[2] = nuevoMovimiento(aux_InfoMov);

    //Insertamos a Machamp en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);
    //////////////////////////////////////////////////////////////////


    return equipo;
}

//AGATHA (default)
nodoPokemon * defaultOponente_3(nodoPokemon * equipo , nodoPokedex * pokedex , nodoInfoMov * listaMov)
{
    equipo = vaciarEquipo(equipo);

    //Crear/insertar a Gengar
    //Lo buscamos en la pokedex
    infoPokedex aux_pokedex = infoPokedexEnLista(pokedex , "Gengar");
    //Si no no encontramos, lo creamos...
    if(aux_pokedex.numPokedex == -1)
    {
        aux_pokedex = nuevaInfoPokedex(94 , "Gengar" , FANTASMA , VENENO , 143);
        pokedex = insertarNodoPokedexAlFinal(pokedex , nuevoNodoPokedex(aux_pokedex));
    }
    //Generamos el nodo...
    pokemon aux_pokemon = nuevoPokemon(aux_pokedex);
    nodoPokemon * aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos a Gengar

    //
    //Buscamos Comesuenios en la listaMov
    infoMov aux_InfoMov = movEnLista(listaMov , "Comesuenios");

    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Comesuenios" , PSIQUICO , 100 , 15);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Gengar
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Lenguetazo en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Lenguetazo");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Lenguetazo" , FANTASMA , 30 , 30);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Gengar
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Megaagotar en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Megaagotar");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Megaagotar" , PLANTA , 40 , 15);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Gengar
    aux_nodo->infoPokemon.setMovimientos[2] = nuevoMovimiento(aux_InfoMov);

    //Insertamos a Gengar en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);
    //////////////////////////////////////////////////////////////////

    //Crear/insertar a Golbat
    //Lo buscamos en la pokedex
    aux_pokedex = infoPokedexEnLista(pokedex , "Golbat");
    //Si no no encontramos, lo creamos...
    if(aux_pokedex.numPokedex == -1)
    {
        aux_pokedex = nuevaInfoPokedex(42 , "Golbat" , VENENO , VOLADOR , 158);
        pokedex = insertarNodoPokedexAlFinal(pokedex , nuevoNodoPokedex(aux_pokedex));
    }
    //Generamos el nodo...
    aux_pokemon = nuevoPokemon(aux_pokedex);
    aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos a Golbat

    //
    //Buscamos AtaqueAla en la listaMov
    aux_InfoMov = movEnLista(listaMov , "AtaqueAla");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("AtaqueAla" , VOLADOR , 60 , 35);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Golbat
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Chupavidas en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Chupavidas");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Chupavidas" , BICHO , 80 , 10);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Golbat
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //Insertamos a Golbat en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);
    //////////////////////////////////////////////////////////////////

    //Crear/insertar a Haunter
    //Lo buscamos en la pokedex
    aux_pokedex = infoPokedexEnLista(pokedex , "Haunter");
    //Si no no encontramos, lo creamos...
    if(aux_pokedex.numPokedex == -1)
    {
        aux_pokedex = nuevaInfoPokedex(93 , "Haunter" , FANTASMA , VENENO , 128);
        pokedex = insertarNodoPokedexAlFinal(pokedex , nuevoNodoPokedex(aux_pokedex));
    }
    //Generamos el nodo...
    aux_pokemon = nuevoPokemon(aux_pokedex);
    aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos a Haunter

    //
    //Buscamos Comesuenios en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Comesuenios");
    //La deberíamos encontrar, ya que la creamos previamente en esta función
    //Lo insertamos en Haunter
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Lenguetazo en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Lenguetazo");
    //La deberíamos encontrar, ya que la creamos previamente en esta función
    //Lo insertamos en Haunter
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //Insertamos a Haunter en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);

    //////////////////////////////////////////////////////////////////

    //Crear/insertar a Arbok
    //Lo buscamos en la pokedex
    aux_pokedex = infoPokedexEnLista(pokedex , "Arbok");
    //Si no no encontramos, lo creamos...
    if(aux_pokedex.numPokedex == -1)
    {
        aux_pokedex = nuevaInfoPokedex(24 , "Arbok" , VENENO , "" , 143);
        pokedex = insertarNodoPokedexAlFinal(pokedex , nuevoNodoPokedex(aux_pokedex));
    }
    //Generamos el nodo...
    aux_pokemon = nuevoPokemon(aux_pokedex);
    aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos a Arbok

    //
    //Buscamos Mordisco en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Mordisco");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Mordisco" , NORMAL , 60 , 25);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Arbok
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Acido en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Acido");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Acido" , VENENO , 40 , 30);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Arbok
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Constriccion en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Constriccion");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Constriccion" , NORMAL , 15 , 20);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Arbok
    aux_nodo->infoPokemon.setMovimientos[2] = nuevoMovimiento(aux_InfoMov);

    //Insertamos a Arbok en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);

    //////////////////////////////////////////////////////////////////

    //Insertamos al segundo Gengar
    //Lo buscamos en la pokedex
    aux_pokedex = infoPokedexEnLista(pokedex , "Gengar");
    //Lo deberíamos encontrar, ya que lo creamos previamente en esta función
    //Generamos el nodo...
    aux_pokemon = nuevoPokemon(aux_pokedex);
    aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos al segundo Gengar

    //
    //Buscamos Comesuenios en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Comesuenios");
    //La deberíamos encontra, ya que la creamos previamente en esta función
    //Lo insertamos en Gengar
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Lenguetazo en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Lenguetazo");
    //La deberíamos encontrar, ya que la creamos previamente en esta función
    //Lo insertamos en Gengar
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Megaagotar en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Megaagotar");
    //La deberíamos encontra, ya que la creamos previamente en esta función
    //Lo insertamos en Gengar
    aux_nodo->infoPokemon.setMovimientos[2] = nuevoMovimiento(aux_InfoMov);

    //Insertamos al segundo Gengar en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);

    return equipo;
}

//LANCE (default)
nodoPokemon * defaultOponente_4(nodoPokemon * equipo , nodoPokedex * pokedex , nodoInfoMov * listaMov)
{
    equipo = vaciarEquipo(equipo);

    //Crear/insertar a Gyarados
    //Lo buscamos en la pokedex
    infoPokedex aux_pokedex = infoPokedexEnLista(pokedex , "Gyarados");
    //Si no no encontramos, lo creamos...
    if(aux_pokedex.numPokedex == -1)
    {
        aux_pokedex = nuevaInfoPokedex(130 , "Gyarados" , AGUA , VOLADOR , 178);
        pokedex = insertarNodoPokedexAlFinal(pokedex , nuevoNodoPokedex(aux_pokedex));
    }
    //Generamos el nodo...
    pokemon aux_pokemon = nuevoPokemon(aux_pokedex);
    nodoPokemon * aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos a Gyarados

    //
    //Buscamos Hidrobomba en la listaMov
    infoMov aux_InfoMov = movEnLista(listaMov , "Hidrobomba");

    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Hidrobomba" , AGUA , 110 , 5);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Gyarados
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Hiperrayo en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Hiperrayo");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Hiperrayo" , NORMAL , 150 , 5);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Gyarados
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Mordisco en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Mordisco");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Mordisco" , NORMAL , 60 , 25);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Gyarados
    aux_nodo->infoPokemon.setMovimientos[2] = nuevoMovimiento(aux_InfoMov);

    //Insertamos a Gyarados en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);

    //////////////////////////////////////////////////////////////////

    //Crear/insertar a Dragonair
    //Lo buscamos en la pokedex
    aux_pokedex = infoPokedexEnLista(pokedex , "Dragonair");
    //Si no no encontramos, lo creamos...
    if(aux_pokedex.numPokedex == -1)
    {
        aux_pokedex = nuevaInfoPokedex(148 , "Dragonair" , DRAGON , "" , 144);
        pokedex = insertarNodoPokedexAlFinal(pokedex , nuevoNodoPokedex(aux_pokedex));
    }
    //Generamos el nodo...
    aux_pokemon = nuevoPokemon(aux_pokedex);
    aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos a Dragonair

    //
    //Buscamos Atizar en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Atizar");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Atizar" , NORMAL , 80 , 20);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Dragonair
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Rayo en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Rayo");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Rayo" , ELECTRICO , 90 , 15);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Dragonair
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Hiperrayo en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Hiperrayo");
    //Si no lo encontramos, lo creamos...
    //La deberíamos encontra, ya que la creamos previamente en esta función
    //Lo insertamos en Gyarados
    aux_nodo->infoPokemon.setMovimientos[2] = nuevoMovimiento(aux_InfoMov);

    //Insertamos a Dragonair en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);

    //////////////////////////////////////////////////////////////////

    //Insertamos al segundo Dragonair
    //Lo buscamos en la pokedex
    aux_pokedex = infoPokedexEnLista(pokedex , "Dragonair");
    //Lo deberíamos encontrar, ya que la creamos previamente en esta función
    //Generamos el nodo...
    aux_pokemon = nuevoPokemon(aux_pokedex);
    aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos al segundo Dragonair

    //
    //Buscamos RayoBurbuja en la listaMov
    aux_InfoMov = movEnLista(listaMov , "RayoBurbuja");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("RayoBurbuja" , AGUA , 65 , 20);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en el segundo Dragonair
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Constriccion en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Constriccion");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Constriccion" , NORMAL , 15 , 20);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en el segundo Dragonair
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos RayoHielo en la listaMov
    aux_InfoMov = movEnLista(listaMov , "RayoHielo");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("RayoHielo" , HIELO , 90 , 10);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en el segundo Dragonair
    aux_nodo->infoPokemon.setMovimientos[2] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Hiperrayo en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Hiperrayo");
    //Si no lo encontramos, lo creamos...
    //La deberíamos encontra, ya que la creamos previamente en esta función
    //Lo insertamos en Gyarados
    aux_nodo->infoPokemon.setMovimientos[3] = nuevoMovimiento(aux_InfoMov);

    //Insertamos al segundo Dragonair en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);

    //////////////////////////////////////////////////////////////////

    //Crear/insertar a Aerodactyl
    //Lo buscamos en la pokedex
    aux_pokedex = infoPokedexEnLista(pokedex , "Aerodactyl");
    //Si no no encontramos, lo creamos...
    if(aux_pokedex.numPokedex == -1)
    {
        aux_pokedex = nuevaInfoPokedex(142 , "Aerodactyl" , ROCA , VOLADOR , 163);
        pokedex = insertarNodoPokedexAlFinal(pokedex , nuevoNodoPokedex(aux_pokedex));
    }
    //Generamos el nodo...
    aux_pokemon = nuevoPokemon(aux_pokedex);
    aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos a Aerodactyl

    //
    //Buscamos AtaqueAla en la listaMov
    aux_InfoMov = movEnLista(listaMov , "AtaqueAla");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("AtaqueAla" , VOLADOR , 60 , 35);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Aerodactyl
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Rapidez en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Rapidez");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Rapidez" , NORMAL , 60 , 20);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Aerodactyl
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Vuelo en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Vuelo");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Vuelo" , VOLADOR , 90 , 15);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Aerodactyl
    aux_nodo->infoPokemon.setMovimientos[2] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Hiperrayo en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Hiperrayo");
    //Si no lo encontramos, lo creamos...
    //La deberíamos encontra, ya que la creamos previamente en esta función
    //Lo insertamos en Aerodactyl
    aux_nodo->infoPokemon.setMovimientos[3] = nuevoMovimiento(aux_InfoMov);

    //Insertamos a Aerodactyl en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);

    //////////////////////////////////////////////////////////////////

    //Crear/insertar a Dragonite
    //Lo buscamos en la pokedex
    aux_pokedex = infoPokedexEnLista(pokedex , "Dragonite");
    //Si no no encontramos, lo creamos...
    if(aux_pokedex.numPokedex == -1)
    {
        aux_pokedex = nuevaInfoPokedex(149 , "Dragonite" , DRAGON , VOLADOR , 174);
        pokedex = insertarNodoPokedexAlFinal(pokedex , nuevoNodoPokedex(aux_pokedex));
    }
    //Generamos el nodo...
    aux_pokemon = nuevoPokemon(aux_pokedex);
    aux_nodo = nuevoNodoPokemon(aux_pokemon);

    //Crear/Insertar movimientos a Dragonite

    //
    //Buscamos Ventisca en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Ventisca");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Ventisca" , HIELO , 110 , 5);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Dragonite
    aux_nodo->infoPokemon.setMovimientos[0] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Llamarada en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Llamarada");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Llamarada" , FUEGO , 110 , 5);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Dragonite
    aux_nodo->infoPokemon.setMovimientos[1] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Trueno en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Trueno");
    //Si no lo encontramos, lo creamos...
    if (aux_InfoMov.ppMax == -1)
    {
        aux_InfoMov = nuevaInfoMov("Trueno" , ELECTRICO , 110 , 10);
        listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(aux_InfoMov));
    }
    //Lo insertamos en Dragonite
    aux_nodo->infoPokemon.setMovimientos[2] = nuevoMovimiento(aux_InfoMov);

    //
    //Buscamos Hiperrayo en la listaMov
    aux_InfoMov = movEnLista(listaMov , "Hiperrayo");
    //Si no lo encontramos, lo creamos...
    //La deberíamos encontra, ya que la creamos previamente en esta función
    //Lo insertamos en Dragonite
    aux_nodo->infoPokemon.setMovimientos[3] = nuevoMovimiento(aux_InfoMov);

    //Insertamos a Dragonite en el equipo
    equipo = insertarNodoPokemon_alFinDeLista(equipo , aux_nodo);

    return equipo;
}
