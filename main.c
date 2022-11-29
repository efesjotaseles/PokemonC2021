#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "myConstants.h"
#include "movimientos.h"
#include "pokemon.h"
#include "userInterface.h"
#include "drawings.h"
#include "efectividades.h"

int main()
{
    //AL INICIAR EL PROGRAMA TENGO QUE ESTABLECER SYSTEM("COLOR XX")
    system("COLOR F0");
    srand(time(NULL));

    /*
    //Reescribir Archivo Oponente 1 con otro default, para luchar contra los otros equipos.
    nodoPokedex * listaPokedex = inicListaPokedex();
    listaPokedex = leerArchivo_Pokedex(listaPokedex);

    nodoInfoMov * listaMov = inicListaInfoMov();
    listaMov = leerArchivo_InfoMovimientos(listaMov);

    nodoPokemon * equipoOponente = inicListaPokemon();

    //1
    //equipoOponente = defaultOponente_1(equipoOponente , listaPokedex , listaMov);
    //2
    //equipoOponente = defaultOponente_2(equipoOponente , listaPokedex , listaMov);
    //3
    //equipoOponente = defaultOponente_3(equipoOponente , listaPokedex , listaMov);
    //4
    //equipoOponente = defaultOponente_4(equipoOponente , listaPokedex , listaMov);

    reescribirArchivoEquipo(equipoOponente , ARCHI_OPP_1);
    */

    user_Main();



    return 0;
}
