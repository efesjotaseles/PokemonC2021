#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "pokemon.h"
#include "movimientos.h"
#include "drawings.h"

////////////////////////////////////////////////////////////////////////////////////
//***FUNCIONES***

//FORMATO
void limpiarPantalla()
{
    system("cls");
}

void saltarLinea()
{
    printf("\n");
}

void lineaAsteriscos100()
{
    for(int i=0; i<100; i++)
    {
        printf("*");
    }
}

void lineaUnderscore100()
{
    for(int i=0; i<100; i++)
    {
        printf("_");
    }
}

void draw_encabezado(char titulo[])
{
    //Color Format

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_INTENSITY);
    //printf("This is some nice COLORFUL text, isn't it?\n");
    ////////////////////////////////////////

    lineaAsteriscos100();
    saltarLinea();
    printf("\t\t\t\t\t%s", titulo);
    saltarLinea();
    lineaAsteriscos100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);
    //printf("Back to normal");
}

void escribirTipoFormateado(char aEscribir[])
{
    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;


    char opcion[TIPOS_VALIDOS][30] = {AGUA, BICHO, DRAGON, ELECTRICO, FANTASMA, FUEGO, HIELO, LUCHA, NORMAL, PLANTA, PSIQUICO, ROCA, TIERRA, VENENO, VOLADOR};
    int numOpcion = -1;
    int pos = 0;
    while(pos < TIPOS_VALIDOS && numOpcion == -1)
    {
        if(strcmp(aEscribir, opcion[pos]) == 0)
        {
            numOpcion = pos;
        }
        pos++;
    }
    switch (numOpcion)
    {
    case 0:
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        break;

    case 1:
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        break;

    case 2:
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_RED);
        break;

    case 3:
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        break;

    case 4:
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
        break;

    case 5:
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_INTENSITY);
        break;

    case 6:
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        break;

    case 7:
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_RED);
        break;

    case 8:
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
        break;

    case 9:
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_GREEN);
        break;

    case 10:
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        break;

    case 11:
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
        break;

    case 12:
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_RED);
        break;

    case 13:
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        break;

    case 14:
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        break;

    default:
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
        break;
    }

    printf("%s", aEscribir);

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);

}

void opcionesDeTipo()
{
    saltarLinea();
    printf("1)");
    escribirTipoFormateado(AGUA);
    printf(" | 2)");
    escribirTipoFormateado(BICHO);
    printf(" | 3)");
    escribirTipoFormateado(DRAGON);
    printf(" | 4)");
    escribirTipoFormateado(ELECTRICO);
    printf(" | 5)");
    escribirTipoFormateado(FANTASMA);
    printf(" | 6)");
    escribirTipoFormateado(FUEGO);
    printf(" | 7)");
    escribirTipoFormateado(HIELO);
    printf(" | 8)");
    escribirTipoFormateado(LUCHA);

    saltarLinea();
    printf("9)");
    escribirTipoFormateado(NORMAL);
    printf(" | 10)");
    escribirTipoFormateado(PLANTA);
    printf(" | 11)");
    escribirTipoFormateado(PSIQUICO);
    printf(" | 12)");
    escribirTipoFormateado(ROCA);
    printf(" | 13)");
    escribirTipoFormateado(TIERRA);
    printf(" | 14)");
    escribirTipoFormateado(VENENO);
    printf(" | 15)");
    escribirTipoFormateado(VOLADOR);
}

//MOSTRAR ESTRUCTURAS
void mostrarInfoMov(infoMov aMostrar)
{
    saltarLinea();
    lineaUnderscore100();
    printf("\nMovimiento: %s", aMostrar.nombre);
    printf("\nTipo      : ");
    escribirTipoFormateado(aMostrar.tipo);
    printf("\nPotencia  : %.0f", aMostrar.potencia);
    printf("\nPP Max    : %i", aMostrar.ppMax);
}

void mostrarInfoMov_Edicion(infoMov aMostrar)
{
    saltarLinea();
    lineaUnderscore100();
    printf("\nMovimiento:   ");
    if(strcmp(aMostrar.nombre, "") != 0)
    {
        printf("%s", aMostrar.nombre);
    }

    printf("\nTipo      :   ");
    if(strcmp(aMostrar.tipo, "") != 0)
    {
        escribirTipoFormateado(aMostrar.tipo);
    }
    printf("\nPotencia  :   ");
    if(aMostrar.potencia != -1)
    {
        printf("%.0f", aMostrar.potencia);
    }
    printf("\nPP Max    :   ");
    if(aMostrar.ppMax != -1)
    {
        printf("%i", aMostrar.ppMax);
    }
}

void mostrarListaInfoMov(nodoInfoMov * lista)
{
    if(lista != NULL)
    {
        mostrarInfoMov(lista->dato);
        mostrarListaInfoMov(lista->sig);
    }
}

void mostrarListaInfoMov_delTipoIndicado(nodoInfoMov * lista, char tipoIndicado[])
{
    if (lista != NULL)
    {
        if(strcmp(lista->dato.tipo, tipoIndicado) == 0)
        {
            mostrarInfoMov(lista->dato);
        }
        mostrarListaInfoMov_delTipoIndicado(lista->sig, tipoIndicado);
    }
}

void mostrarMovimiento(movimiento aMostrar)
{
    saltarLinea();
    lineaUnderscore100();
    printf("\nMovimiento: %s", aMostrar.datos.nombre);
    printf("\nTipo      : ");
    escribirTipoFormateado(aMostrar.datos.tipo);
    printf("\nPotencia  : %.0f", aMostrar.datos.potencia);
    printf("\nPP    : [%i / %i]", aMostrar.ppDisponibles, aMostrar.datos.ppMax);

}

void mostrarMovimiento_Edicion(movimiento aMostrar)
{
    saltarLinea();
    lineaUnderscore100();
    printf("\nMovimiento: ");
    if(strcmp(aMostrar.datos.nombre, "") != 0)
    {
        printf("%s", aMostrar.datos.nombre);
    }

    printf("\nTipo      : ");
    if(strcmp(aMostrar.datos.tipo , "") != 0)
    {
        escribirTipoFormateado(aMostrar.datos.tipo);
    }

    printf("\nPotencia  : ");
    if(aMostrar.datos.potencia != -1)
    {
       printf("%.0f", aMostrar.datos.potencia);
    }

    printf("\nPP    : ");
    if(aMostrar.datos.ppMax != -1)
    {
        printf("[%i / %i]" , aMostrar.ppDisponibles, aMostrar.datos.ppMax);
    }
}

void mostrarSetMovimientos(movimiento setMovimientos[])
{
    for (int i = 0 ; i<4 ; i++)
    {
        if(setMovimientos[i].datos.ppMax != -1)
        {
            saltarLinea();
            lineaUnderscore100();
            saltarLinea();
            printf("\nMOV %i)" , i+1);
            mostrarMovimiento(setMovimientos[i]);
        }
    }
}

void mostrarSetMovimientos_Edicion(movimiento setMovimientos[])
{
    for (int i = 0 ; i<4 ; i++)
    {
        saltarLinea();
        lineaUnderscore100();
        saltarLinea();
        printf("\nMOV %i)", i+1);
        mostrarMovimiento_Edicion(setMovimientos[i]);
    }
}


void mostrarInfoPokedex(infoPokedex aMostrar)
{
    saltarLinea();
    lineaUnderscore100();
    printf("\nNumero    : %i" , aMostrar.numPokedex);
    printf("\nNombre    : %s", aMostrar.nombre);
    printf("\nTipo 1    : ");
    escribirTipoFormateado(aMostrar.tipo_1);
    printf("\nTipo 2    : ");
    escribirTipoFormateado(aMostrar.tipo_2);
    printf("\nPS Max    : %i", aMostrar.psMax);

}

void mostrarInfoPokedex_Edicion(infoPokedex aMostrar)
{
    saltarLinea();
    lineaUnderscore100();
    printf("\nNum       :   ");
    if(aMostrar.numPokedex != -1)
    {
        printf("%i", aMostrar.numPokedex);
    }

    printf("\Nombre     :   ");
    if(strcmp(aMostrar.nombre, "") != 0)
    {
        printf("%s", aMostrar.nombre);
    }

    printf("\nTipo 1    :   ");
    if(strcmp(aMostrar.tipo_1, "") != 0)
    {
        printf("%s", aMostrar.tipo_1);
    }

    printf("\nTipo 2    :   ");
    if(strcmp(aMostrar.tipo_2, "") != 0)
    {
        printf("%s", aMostrar.tipo_2);
    }

    printf("\nPS Max    :   ");
    if(aMostrar.psMax != -1)
    {
        printf("%i", aMostrar.psMax);
    }
}

void mostrarListaPokedex(nodoPokedex * lista)
{
    if(lista != NULL)
    {
        mostrarInfoPokedex(lista->datoPokedex);
        mostrarListaPokedex(lista->sig);
    }
}

void mostrarListaPokedex_delTipoIndicado(nodoPokedex * lista , char tipoIndicado[])
{
    if(lista != NULL)
    {
        if((strcmp(tipoIndicado , lista->datoPokedex.tipo_1) == 0) || (strcmp(tipoIndicado , lista->datoPokedex.tipo_2) == 0))
        {
            mostrarInfoPokedex(lista->datoPokedex);
        }
        mostrarListaPokedex_delTipoIndicado(lista->sig , tipoIndicado);
    }
}

void mostrarUnPokemon(pokemon aMostrar)
{
    saltarLinea();
    lineaUnderscore100();
    printf("\nApodo     : %s" , aMostrar.apodo);
    printf("\nID        : %i" , aMostrar.uniqueID);
    printf("\nEspecie   : %s", aMostrar.datoPokedex.nombre);
    printf("\nTipo 1    : ");
    escribirTipoFormateado(aMostrar.datoPokedex.tipo_1);
    printf("\nTipo 2    : ");
    escribirTipoFormateado(aMostrar.datoPokedex.tipo_2);
    printf("\nPS        : [%i/%i]" , aMostrar.psActuales , aMostrar.datoPokedex.psMax);

}

void mostrarEquipo(nodoPokemon * equipo)
{
    if(equipo != NULL)
    {
        mostrarUnPokemon(equipo->infoPokemon);
        mostrarEquipo(equipo->sig);
    }
}

void mostrarEquipo_enBatalla_Cambiar(nodoPokemon * equipo)
{
    if(equipo != NULL)
    {
        int enEquipo = contarPokemonEnEquipo(equipo);
        nodoPokemon * aux = equipo;
        for(int i = 1 ; i <= enEquipo ; i++)
        {
            printf("%i) %s" , i , aux->infoPokemon.apodo);
            saltarLinea();
            printf("    ");
            escribirTipoFormateado(aux->infoPokemon.datoPokedex.tipo_1);
            if(strcmp(aux->infoPokemon.datoPokedex.tipo_2 , "") != 0)
            {
                printf(" / ");
                escribirTipoFormateado(aux->infoPokemon.datoPokedex.tipo_2);
            }
            saltarLinea();
            printf("    ");
            printf("PS: [%i/%i]" , aux->infoPokemon.psActuales , aux->infoPokemon.datoPokedex.psMax);
            saltarLinea();
            saltarLinea();

            aux = aux->sig;
        }
    }
}

void mostrarEquipo_delTipoIndicado(nodoPokemon * equipo , char tipoIndicado[])
{
    if(equipo != NULL)
    {
        if((strcmp(equipo->infoPokemon.datoPokedex.tipo_1 , tipoIndicado) == 0) || (strcmp(equipo->infoPokemon.datoPokedex.tipo_2 , tipoIndicado) == 0))
        {
            mostrarUnPokemon(equipo->infoPokemon);
        }
        mostrarEquipo_delTipoIndicado(equipo->sig , tipoIndicado);
    }
}

int mostrarEquipo_conNombreApodoIndicado(nodoPokemon * equipo , char nomApodoBuscado[]) //Devuelve uniqueID si uno solo, si no, -1
{
    int id_UnicoResultado = -1;
    int resultadoSiguiente = -1;
    if(equipo != NULL)
    {
        //Chequeamos si la palabra buscada es igual al nombre o el apodo del pokemon actual
        if(strcmp(nomApodoBuscado , equipo->infoPokemon.datoPokedex.nombre)== 0 || strcmp(nomApodoBuscado , equipo->infoPokemon.apodo)== 0)
        {
            mostrarUnPokemon(equipo->infoPokemon); //Lo mostramos por pantalla...
            id_UnicoResultado = equipo->infoPokemon.uniqueID; //Guardamos su uniqueID...
        }
        //Con recursión recorremos todo lo siguiente de la lista...
        resultadoSiguiente = mostrarEquipo_conNombreApodoIndicado(equipo->sig , nomApodoBuscado);

        //Si obtenemos otra cosa que -1(default por nulo o por no encontrar nada igual)....
        if(resultadoSiguiente != -1)
        {
            if(id_UnicoResultado == -1)//Si el actual no se mostró...
            {
                id_UnicoResultado = resultadoSiguiente;
            }
            else //Pero si también se mostró...
            {
                id_UnicoResultado = -2; // ...devolvemos -2, indicando que hay múltiples.
            }
        }
    }



    return id_UnicoResultado;
}

void mostrar_MovimientoEnBatalla(movimiento aMostrar)
{
    printf("%s\t\t||" , aMostrar.datos.nombre);
    escribirTipoFormateado(aMostrar.datos.tipo);
    printf("||PP:\t [%i/%i]" , aMostrar.ppDisponibles , aMostrar.datos.ppMax);
}

//BATALLA
void mostrar_PokeEnBatalla (pokemon aMostrar)
{
    saltarLinea();
    lineaUnderscore100();
    printf("\n%s" , aMostrar.apodo);
    saltarLinea();
    printf("(");
    escribirTipoFormateado(aMostrar.datoPokedex.tipo_1);
    printf("\ - ");
    escribirTipoFormateado(aMostrar.datoPokedex.tipo_2);
    printf(")");
    printf("\nPS: [%i/%i]" , aMostrar.psActuales , aMostrar.datoPokedex.psMax);
}

void draw_Batalla_Pokes(pokemon deJugador , pokemon deOponente)
{
    printf("\nOPONENTE");
    mostrar_PokeEnBatalla(deOponente);
    saltarLinea();
    lineaUnderscore100();
    saltarLinea();
    lineaUnderscore100();
    saltarLinea();
    printf("\JUGADOR");
    mostrar_PokeEnBatalla(deJugador);
}

void draw_Batalla_General(nodoPokemon * deJugador , nodoPokemon * deOponente)
{
    limpiarPantalla();
    draw_Batalla_Pokes(deJugador->infoPokemon , deOponente->infoPokemon);
    draw_menuBatalla_General();
}

void draw_menuBatalla_General()
{
    saltarLinea();
    lineaUnderscore100();
    saltarLinea();
    printf("1) Atacar \t 2)PkMn");
    saltarLinea();
    printf("          \t 0)Huir");
}

void draw_Batalla_Ataques(nodoPokemon * deJugador , nodoPokemon * deOponente)
{
    limpiarPantalla();
    draw_Batalla_Pokes(deJugador->infoPokemon , deOponente->infoPokemon);
    draw_menuBatalla_Ataques(deJugador->infoPokemon.setMovimientos);
}

void draw_menuBatalla_Ataques(movimiento setMovimientos[])
{
    saltarLinea();
    lineaUnderscore100();
    saltarLinea();
    for(int i = 0 ; i<4 ; i++)
    {
        if(setMovimientos[i].datos.potencia != -1)
        {
            saltarLinea();
            printf("%i) " , i+1);
            mostrar_MovimientoEnBatalla(setMovimientos[i]);
        }
    }
    saltarLinea();
    printf("0) Atras");
}

void draw_menuBatalla_CambiarPokemon(nodoPokemon * equipoJugador , int cambioForzado)//cambioForzado == 0 : Se permite salir sin cambiar / == 1 : No se permite salir sin cambiar
{
    limpiarPantalla();
    saltarLinea();
    printf("ELEGIR POKEMON");
    saltarLinea();
    lineaUnderscore100();
    saltarLinea();
    mostrarEquipo_enBatalla_Cambiar(equipoJugador);
    saltarLinea();
    if(cambioForzado == 0)
    {
        printf("0) Volver atras.");
        saltarLinea();
    }
    lineaUnderscore100();


}

//GRÁFICAS DE MENÚ
void draw_menuPrincipal()
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("POKEMON C - 2021");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    printf("1) Modo Juego");
    saltarLinea();
    printf("2) Modo Editor");
    saltarLinea();
    saltarLinea();
    printf("0: Salir");
    saltarLinea();
    lineaAsteriscos100();
    saltarLinea();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);

}

void draw_menuEditor()
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("MODO EDITOR");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    printf("1) Opciones de Pokedex.");
    saltarLinea();
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_INTENSITY);
    printf("2) Opciones de los Equipos (Jugador, Bill y Oponentes). [EN DESARROLLO]");
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    saltarLinea();
    printf("3) Opciones de los Movimientos.");
    saltarLinea();
    saltarLinea();
    printf("0: Volver al menu general.");
    saltarLinea();
    lineaAsteriscos100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);

}

//MENU EDITOR EQUIPOS/POKEMON
void draw_menuEditor_SeleccionarEquipo()
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("SELECCIONAR EQUIPO");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    printf("Elegir equipo.");
    saltarLinea();
    lineaUnderscore100();
    saltarLinea();
    printf("1) Jugador!");
    saltarLinea();
    printf("2) Bill!.");
    saltarLinea();
    printf("3) Oponente 1.");
    saltarLinea();
    printf("4) Oponente 2.");
    saltarLinea();
    printf("5) Oponente 3.");
    saltarLinea();
    printf("6) Oponente 4.");
    saltarLinea();
    saltarLinea();
    printf("0: Volver al menu del editor.");
    saltarLinea();
    lineaAsteriscos100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

void draw_AgregarMov_enSetMov_Inicio(char nombrePokemon[] , movimiento movNuevo)
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("AGREGAR MOVIMIENTO EN POKEMON");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    lineaUnderscore100();
    saltarLinea();
    printf("            *** %s ***" , nombrePokemon);
    saltarLinea();
    lineaUnderscore100();
    saltarLinea();
    printf("1) Buscar movimiento (por nombre).");
    saltarLinea();
    printf("2) Ver lista de movimientos entera.");
    saltarLinea();
    printf("3) Ver movimientos de un tipo especifico.");

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);

}

void draw_AgregarMovEnSet_MostrarExistente_Opciones(infoMov aMostrar)
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("AGREGAR MOVIMIENTO AL POKEMON");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    mostrarInfoMov(aMostrar);
    saltarLinea();
    lineaUnderscore100();
    printf("\nAgregar este movimiento al Pokemon?");
    saltarLinea();
    printf("\n1) Si! Agregarlo!");
    saltarLinea();
    saltarLinea();
    printf("\n0) Volver atras.");

    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
    lineaAsteriscos100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);

}

void draw_AgregarMovEnSet_MovNoExistente_Opciones(char nombreMov[])
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("AGREGAR MOVIMIENTO AL POKEMON");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    printf("\nNo existe [%s] en la lista de movimientos....." , nombreMov);
    saltarLinea();
    printf("\n1) Vamos a crearlo y agregarlo al Pokemon!");
    saltarLinea();
    printf("\n0) Ingresar un movimiento diferente.");

    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
    lineaAsteriscos100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

void draw_EditorNuevoSetMovimientos_OpcionesIniciales(char nombrePokemon[] , movimiento setMovimientos[])
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("AGREGAR POKEMON - MOVIMIENTOS");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    lineaUnderscore100();
    saltarLinea();
    printf("            *** %s ***" , nombrePokemon);
    saltarLinea();
    lineaUnderscore100();
    mostrarSetMovimientos_Edicion(setMovimientos);
    saltarLinea();
    lineaUnderscore100();
    saltarLinea();
    printf("1) Ingresar movimiento (por nombre).");
    saltarLinea();
    printf("2) Ver lista de movimientos entera.");
    saltarLinea();
    printf("3) Ver movimientos de un tipo especifico.");
    if(strcmp(setMovimientos[0].datos.nombre , "") != 0)
    {
        saltarLinea();
        printf("0) Listo! Movimientos ingresados!");
    }

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

void draw_menuEditorEquipo(int opcion) //EQUIPO NO BILL!!!!!!!!!!!!
{
    //ENCABEZADO
    limpiarPantalla();
    //1,3,4,5,6
    switch(opcion)
    {
    case 1:
        draw_encabezado("Equipo de Jugador");
        break;

    case 3:
        draw_encabezado("Equipo de Oponente 1");
        break;

    case 4:
        draw_encabezado("Equipo de Oponente 2");
        break;

    case 5:
        draw_encabezado("Equipo de Oponente 3");
        break;

    case 6:
        draw_encabezado("Equipo de Oponente 4");
        break;
    }

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    printf("1: Ver Pokemones en detalle.");
    saltarLinea();
    printf("2: Cambiar orden dentro del equipo.");
    saltarLinea();
    printf("3: Eliminar un Pokemon del equipo.");
    saltarLinea();
    printf("4: Agregar Pokemon al equipo (Límite de 6, a menos que sea equipo de Bill).");
    saltarLinea();
    lineaAsteriscos100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

void draw_menuEditor_Bill()
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("COMPUTADORA DE BILL");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    printf("            *** %i Pokemon almacenados en la Computadora de Bill ***" , cantPokemon_enArchivo(ARCHI_BILL));
    saltarLinea();
    lineaUnderscore100();
    printf("1) Agregar un Pokemon nuevo.");
    saltarLinea();
    printf("2) Buscar un Pokemon en la computadora.");
    saltarLinea();
    printf("3) Ver todos los Pokemon en la computadora.");
    saltarLinea();
    printf("4) Ver los Pokemon de un tipo en la computadora.");
    saltarLinea();
    saltarLinea();
    printf("0: Seleccionar otro equipo.");
    saltarLinea();
    lineaAsteriscos100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);

}

void draw_VerEquipo_IngresarTipo()
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("VER POKEMON POR TIPO");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    printf("\nIndicar el tipo:");
    opcionesDeTipo();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);

}

void draw_BuscarPokemon_enBill_Ingreso()
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("COMPUTADORA DE BILL - BUSCAR POKEMON");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    printf("\nIngrese nombre o apodo del pokemon que busca:");
    saltarLinea();

    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
    lineaAsteriscos100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);

}


//MENU EDITOR MOVIMIENTOS
void draw_menuEditorMovimientos()
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("EDITOR DE MOVIMIENTOS");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    printf("1) Agregar un movimiento.");
    saltarLinea();
    printf("2) Buscar un movimiento.");
    saltarLinea();
    printf("3) Ver todos los movimientos.");
    saltarLinea();
    printf("4) Ver los movimientos de un tipo.");
    saltarLinea();
    saltarLinea();
    printf("0) Volver al menu anterior.");
    saltarLinea();

    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
    lineaAsteriscos100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);

}

void draw_VerMovimientos_IngresarTipo()
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("VER MOVIMIENTOS POR TIPO");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    printf("\nIndicar el tipo:");
    opcionesDeTipo();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);

}

void draw_AgregarMovimiento (infoMov aMostrar)
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("AGREGAR MOVIMIENTO");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    mostrarInfoMov_Edicion(aMostrar);
    saltarLinea();
    lineaUnderscore100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

void draw_BuscarMovimiento_Ingreso()
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("BUSCAR MOVIMIENTO");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    printf("\nIngrese el movimiento que busca:");
    saltarLinea();

    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
    lineaAsteriscos100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);

}

void draw_BuscarMovimiento_Confirmacion(char nombreIngresado[])
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("BUSCAR MOVIMIENTO");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    printf("\nBuscar :  %s ?", nombreIngresado);
    saltarLinea();
    printf("\n1) Si, buscar ese movimiento!");
    printf("\n0) No, reingresar movimiento...");
    saltarLinea();

    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
    lineaAsteriscos100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);

}

void draw_BuscarMovimiento_Resultado(infoMov aMostrar)
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("BUSCAR MOVIMIENTO");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    mostrarInfoMov(aMostrar);
    saltarLinea();
    lineaUnderscore100();
    printf("\n1) Editar Movimiento...");
    printf("\n2) Eliminar Movimiento! (no se puede deshacer)");
    printf("\n0) Volver atras.");

    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
    lineaAsteriscos100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);


}

void draw_BuscarMovimiento_Resultado_paraSetMov(infoMov aMostrar)
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("BUSCAR MOVIMIENTO");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    mostrarInfoMov(aMostrar);
    saltarLinea();
    lineaUnderscore100();
    printf("\n1) Agregar al Pokemon!");
    printf("\n2) No...Buscar nuevamente...");
    printf("\n0) Volver atras.");

    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
    lineaAsteriscos100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);


}

void draw_MovNoEncontrado(char movNoEncontrado[])
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("MOVIMIENTO NO ENCONTRADO");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    printf("\nMovimiento [%s] no encontrado!!!" , movNoEncontrado);
    printf("\n1) Crear movimiento nuevo.");
    printf("\n2) Buscar otro.");

    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
    lineaAsteriscos100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);


}

void draw_BuscarMovimiento_Eliminar(infoMov aMostrar)
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("ELIMINAR MOVIMIENTO");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    mostrarInfoMov(aMostrar);
    saltarLinea();
    lineaUnderscore100();
    printf("\nSeguro que desea eliminar %s ?", aMostrar.nombre);
    printf("\n1) Si, eliminar!");
    printf("\n0) NO! Volver atras.");

    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
    lineaAsteriscos100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);


}

void draw_BuscarMovimiento_Eliminar_Eliminado(infoMov aMostrar)
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("ELIMINAR MOVIMIENTO");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    mostrarInfoMov(aMostrar);
    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    lineaUnderscore100();
    printf("\n%s eliminado exitosamente!", aMostrar.nombre);
    printf("\nPresione cualquier tecla para continuar...");

    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
    lineaAsteriscos100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

void draw_EditarMovBuscado(infoMov aEditar)
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("EDITAR MOVIMIENTO");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    mostrarInfoMov_Edicion(aEditar);
    saltarLinea();
    lineaUnderscore100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

void draw_EditarSetMovimientos(movimiento setMovimientos[])
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("EDITOR DE MOVIMIENTOS DE UN POKEMON");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    for(int i = 0 ; i<4 ; i++)
    {
        lineaUnderscore100();
        printf("\n%i)" , i);
        saltarLinea();
        if(setMovimientos[i].datos.potencia != -1)
        {
            mostrarInfoMov(setMovimientos[i].datos);
        }
    }

    saltarLinea();
    printf("1) Eliminar un movimiento.");
    if(setMovimientos[4].datos.potencia == -1)
    {
        saltarLinea();
        printf("2) Buscar una entrada en la Pokedex");
    }
    saltarLinea();
    saltarLinea();
    printf("0: Volver al menu anterior");
    saltarLinea();
    lineaAsteriscos100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

void draw_EditarSetMovimientos_ElegirPos(movimiento setMovimientos[])
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("EDITOR DE MOVIMIENTOS DE UN POKEMON");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    for(int i = 0 ; i<4 ; i++)
    {
        lineaUnderscore100();
        printf("\n%i)" , i);
        saltarLinea();
        if(setMovimientos[i].datos.potencia != -1)
        {
            mostrarInfoMov(setMovimientos[i].datos);
        }
    }

    printf("\nElija uno de los movimientos (1, 2, 3. 4):");

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

void draw_AgregarMovEnSet()
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("AGREGAR MOVIMIENTO AL POKEMON");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    printf("\n1) Ingresar nombre del movimiento deseado.");
    saltarLinea();
    printf("\n2) Ver movimientos disponibles.");
    saltarLinea();
    printf("\n3) Ver movimientos de un tipo.");
    saltarLinea();
    saltarLinea();
    printf("\n0) Volver atras.");

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);

}

//MENÚ EDITOR POKEDEX
void draw_menuEditorPokedex()
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("OPCIONES DE POKEDEX");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    printf("1) Crear nueva entrada en la Pokedex.");
    saltarLinea();
    printf("2) Buscar una entrada en la Pokedex");
    saltarLinea();
    printf("3) Ver Pokedex entera.");
    saltarLinea();
    printf("4) Ver las entradas de un tipo.");
    saltarLinea();
    saltarLinea();
    printf("0: Volver al menu del editor.");
    saltarLinea();
    lineaAsteriscos100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

void draw_VerListaPokedex_IngresarTipo()
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("EDITOR DE POKEDEX");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    printf("\nIndicar el tipo:");
    opcionesDeTipo();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);

}

void draw_AgregarInfoPokedex(infoPokedex aMostrar)
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("AGREGAR ENTRADA POKEDEX");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    mostrarInfoPokedex_Edicion(aMostrar);
    saltarLinea();
    lineaUnderscore100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

void draw_BuscarInfoPokedex_Ingreso()
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("BUSCAR ENTRADA POKEDEX");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    printf("\nIngrese el nombre del pokemon que busca:");
    saltarLinea();

    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
    lineaAsteriscos100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);

}

void draw_BuscarInfoPokedex_Confirmacion(char nombreIngresado[])
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("BUSCAR ENTRADA POKEDEX");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    printf("\nBuscar :  %s ?", nombreIngresado);
    saltarLinea();
    printf("\n1) Si, buscar ese Pokemon!");
    printf("\n0) No, reingresar nombre de Pokemon...");
    saltarLinea();

    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
    lineaAsteriscos100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);

}

void draw_BuscarInfoPokedex_Resultado(infoPokedex aMostrar)
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("BUSCAR ENTRADA POKEDEX");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    mostrarInfoPokedex(aMostrar);
    saltarLinea();
    lineaUnderscore100();
    printf("\n1) Editar entrada pokedex...");
    printf("\n2) Eliminar entrada pokedex! (no se puede deshacer)");
    printf("\n0) Volver atras.");

    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
    lineaAsteriscos100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);

}

void draw_EditarInfoPokedex(infoPokedex aEditar)
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("EDITAR ENTRADA POKEDEX");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    mostrarInfoPokedex_Edicion(aEditar);
    saltarLinea();
    lineaUnderscore100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

void draw_BuscarInfoPokedex_Eliminar(infoPokedex aMostrar)
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("ELIMINAR ENTRADA POKEDEX");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    mostrarInfoPokedex(aMostrar);
    saltarLinea();
    lineaUnderscore100();
    printf("\nSeguro que desea eliminar entrada de %s ?", aMostrar.nombre);
    printf("\n1) Si, eliminar!");
    printf("\n0) NO! Volver atras.");

    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
    lineaAsteriscos100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

void draw_BuscarInfoPokedex_Eliminar_Eliminada(infoPokedex aMostrar)
{
    //ENCABEZADO
    limpiarPantalla();
    draw_encabezado("ELIMINAR ENTRADA POKEDEX");

    //Color Format
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    mostrarInfoPokedex(aMostrar);
    //Set new color format
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    ////////////////////////////////////////

    saltarLinea();
    lineaUnderscore100();
    printf("\n%s eliminado exitosamente!", aMostrar.nombre);
    printf("\nPresione cualquier tecla para continuar...");

    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
    lineaAsteriscos100();

    //Restore original color format attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);
}
