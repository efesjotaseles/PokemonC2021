#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movimientos.h"
#include "pokemon.h"
#include "userInterface.h"
#include "efectividades.h"

////////////////////////////////////////////////////////////////////////////////////
//***FUNCIONES***

void tipoEstandarizado(char variableTipo[] , int eleccion)
{
    switch (eleccion)
    {
    case 1:
        strcpy(variableTipo, AGUA);
        break;

    case 2:
        strcpy(variableTipo, BICHO);
        break;

    case 3:
        strcpy(variableTipo, DRAGON);
        break;

    case 4:
        strcpy(variableTipo, ELECTRICO);
        break;

    case 5:
        strcpy(variableTipo, FANTASMA);
        break;

    case 6:
        strcpy(variableTipo, FUEGO);
        break;

    case 7:
        strcpy(variableTipo, HIELO);
        break;

    case 8:
        strcpy(variableTipo, LUCHA);
        break;

    case 9:
        strcpy(variableTipo, NORMAL);
        break;

    case 10:
        strcpy(variableTipo, PLANTA);
        break;

    case 11:
        strcpy(variableTipo, PSIQUICO);
        break;

    case 12:
        strcpy(variableTipo, ROCA);
        break;

    case 13:
        strcpy(variableTipo, TIERRA);
        break;

    case 14:
        strcpy(variableTipo, VENENO);
        break;

    case 15:
        strcpy(variableTipo, VOLADOR);
        break;
    }
}

int convertirOpcionChar(char opcionChar)
{
    int opcionConvertida = -1;
    switch(opcionChar)
    {
    case '1':
        opcionConvertida = 1;
        break;

    case '2':
        opcionConvertida = 2;
        break;

    case '3':
        opcionConvertida = 3;
        break;

    case '4':
        opcionConvertida = 4;
        break;

    case '5':
        opcionConvertida = 5;
        break;

    case '6':
        opcionConvertida = 6;
        break;
    }

    return opcionConvertida;
}

////////////////////////////////////////////////////////////////////////////////////
//MENÚ PRINCIPAL
void user_Main()
{
    //Variables iniciales
    char opcion = 'x';

    while (opcion != '0')
    {
        draw_menuPrincipal();
        fflush(stdin);
        opcion = getch();

        switch (opcion)
        {
        case '1':
            //MODO JUEGO
            user_ModoJuego();
            opcion = 'x';
            break;

        case '2':
            //MODO EDITOR
            user_ModoEditor();
            opcion = 'x';
            break;
        }
    }

}


////////////////////////////////////////////////////////////////////////////////////
//MODO JUEGO
void user_ModoJuego()
{
    char opcion = 'x';

    while (opcion != '0')
    {
        limpiarPantalla();
        draw_encabezado("MODO JUEGO");
        printf("\n1) Comenzar batalla!");
        printf("\n0) Salir del Modo Juego.");
        saltarLinea();
        lineaUnderscore100();
        saltarLinea();

        fflush(stdin);
        opcion = getch();

        switch (opcion)
        {
        case '1':
            user_Batalla();
            opcion = 'x';
            break;

            //Casos 2 Muestra Equipo, cambiar el orden, etc.
            //Caso 3 Ver computadora de Bill, intercambiar Pokemon, etc.

        }
    }

}

void user_Batalla()
{
    //Variables iniciales
    char salir = 'n';
    char opcion = 'x';
    char continuar = 'x';

    //Cargar equipos
    //Jugador
    nodoPokemon * jugador = inicListaPokemon();
    jugador = leerArchivo_Equipo(jugador, ARCHI_JUGADOR);
    int pokesJugador = contarPokemonEnEquipo(jugador);

    //Oponente 1 (se usará para el resto de oponentes)
    nodoPokemon * oponente = inicListaPokemon();
    oponente = leerArchivo_Equipo(oponente, ARCHI_OPP_1);
    int pokesOponente = contarPokemonEnEquipo(oponente);

    //Inicializar efectividades.
    celdaEfectividad arrEfectividades[TIPOS_VALIDOS];
    inicEfectividades(arrEfectividades);

    while(opcion != '0')
    {
        while (opcion != '1' && opcion != '2' && opcion != '0')
        {
            draw_Batalla_General(jugador, oponente);
            fflush(stdin);
            opcion = getch();
        }

        switch (opcion)
        {
            //ATAQUE!
        case '1':
            opcion = 'x';
            while (opcion != '0')//Mantiene en menú de elegir ataque
            {
                //Inhabilita elección por fuera de las opciones en el menú de ataques
                while (opcion != '0' && opcion != '1' && opcion != '2' && opcion != '3' && opcion != '4')
                {
                    draw_Batalla_Ataques(jugador, oponente);
                    fflush(stdin);
                    opcion = getch();
                }
                if(opcion != '0')//Si se eligió un ataque
                {
                    //Primero convertimos el char ataque a un int
                    int opcionConvertida = convertirOpcionChar(opcion);

                    ////////////////
                    //RESOLVER TURNO
                    //1º Chequeamos que haya PP en el ataque
                    if(jugador->infoPokemon.setMovimientos[opcionConvertida-1].ppDisponibles > 0)//Si el ataque elegido tiene PP disponibles
                    {
                        //Ataque del jugador
                        oponente = turnoJugador(jugador->infoPokemon, opcionConvertida, oponente, arrEfectividades);    //Oponente recibe el daño del ataque.
                        jugador->infoPokemon.setMovimientos[opcionConvertida-1].ppDisponibles--; //Disminuimos en 1 los PP del ataque usado.
                        //Si oponente sobrevivió, ataca
                        if(oponente->infoPokemon.psActuales > 0)
                        {
                            //Ataque de oponente
                            jugador = turnoOponente(oponente, jugador, arrEfectividades);
                            //CERTIFICAR SI EL POKEMON DEL JUGADOR TIENE PS
                            if(jugador->infoPokemon.psActuales < 1)//Si no tiene PS
                            {
                                pokesJugador--;
                                if(pokesJugador < 1)//Si no le quedan Pokes vivos, perdió la batalla!
                                {
                                    //FIN DE LA BATALLA - PERDIÓ JUGADOR
                                    saltarLinea();
                                    printf("No te quedan Pokemon!!!");
                                    saltarLinea();
                                    printf("Pierdes la batalla, algo de dinero, y te quedas sin conocimiento!!!");
                                    fflush(stdin);
                                    continuar = getch();
                                    opcion = '0';
                                }
                                else//Si le queda algún Poke vivo...
                                {
                                    saltarLinea();
                                    printf("%s ha quedado fuera de combate!", jugador->infoPokemon.apodo);
                                    saltarLinea();
                                    printf("Elige otro Pokemon...");
                                    fflush(stdin);
                                    continuar = getch();
                                    user_Batalla_CambiarPoke(jugador , 1);
                                    //Volver al menú general de la batalla luego de haber cambiado Pokemon
                                    saltarLinea();
                                    printf("Has enviado a %s!!!", jugador->infoPokemon.apodo);
                                    fflush(stdin);
                                    continuar = getch();
                                    opcion = 'x';
                                }
                            }
                            opcion = 'x';
                        }
                        else//Si el Pokemon de oponente se quedó sin PS
                        {
                            printf("\n%s ha quedado fuera de combate!!!", oponente->infoPokemon.apodo);
                            fflush(stdin);
                            continuar = getch();
                            pokesOponente--;

                            if(pokesOponente > 0)//Si le quedan pokes vivos a oponente
                            {
                            //Buscamos el primero vivo en el equipo.
                            nodoPokemon * siguienteVivo = primerPokeVivoEnEquipo(oponente);
                            //Intercambiamos las infoPokemon
                            pokemon aux = oponente->infoPokemon;
                            oponente->infoPokemon = siguienteVivo->infoPokemon;
                            siguienteVivo->infoPokemon = aux;
                            saltarLinea();
                            printf("Oponente ha enviado a %s!!!", oponente->infoPokemon.apodo);
                            fflush(stdin);
                            continuar = getch();
                            opcion = 'x';
                            }
                            else//Si no le queda ningún poke vivo...
                            {
                            //FIN DE LA BATALLA - GANÓ JUGADOR
                            saltarLinea();
                            printf("Oponente se ha quedado sin Pokemon!!");
                            saltarLinea();
                            printf("Felicitaciones!!! Has ganado la batalla!!!!");
                            fflush(stdin);
                            continuar = getch();
                            opcion = '0';
                            }
                        }
                    }
                    else//Si Jugador eligió ataque sin PP disponibles, se le avisa y se vuelve al menú de elegir ataque.
                    {
                        saltarLinea();
                        printf("NO HAY PP DISPONIBLES!!!");
                        opcion = getch();
                        opcion = 'x'; //Seteamos para regresar al menú de elegir ataque.
                    }
                    }

                    break;

            case '2': //CAMBIAR POKEMON
                //Menú de cambio de Pokemon, con posibilidad de volver sin realizar el cambio.
                user_Batalla_CambiarPoke(jugador, 0);
                saltarLinea();
                printf("Has enviado a %s!!!", jugador->infoPokemon.apodo);
                fflush(stdin);
                continuar = getch();
                opcion = 'x';

                    //Oponente ataca!
                    jugador = turnoOponente(oponente, jugador, arrEfectividades);
                            //CERTIFICAR SI EL POKEMON DEL JUGADOR TIENE PS
                            if(jugador->infoPokemon.psActuales < 1)//Si no tiene PS
                            {
                                pokesJugador--;
                                if(pokesJugador < 1)//Si no le quedan Pokes vivos, perdió la batalla!
                                {
                                    //FIN DE LA BATALLA - PERDIÓ JUGADOR
                                    saltarLinea();
                                    printf("No te quedan Pokemon!!!");
                                    saltarLinea();
                                    printf("Pierdes la batalla, algo de dinero, y te quedas sin conocimiento!!!");
                                    fflush(stdin);
                                    continuar = getch();
                                    opcion = '0';
                                }
                                else//Si le queda algún Poke vivo...
                                {
                                    saltarLinea();
                                    printf("%s ha quedado fuera de combate!", jugador->infoPokemon.apodo);
                                    saltarLinea();
                                    printf("Elige otro Pokemon...");
                                    fflush(stdin);
                                    continuar = getch();
                                    user_Batalla_CambiarPoke(jugador , 1);
                                    //Volver al menú general de la batalla luego de haber cambiado Pokemon
                                    saltarLinea();
                                    printf("Has enviado a %s!!!", jugador->infoPokemon.apodo);
                                    fflush(stdin);
                                    continuar = getch();
                                    opcion = 'x';
                                }
                            }
                    opcion = 'x';
                    break;

                case '0'://HUIR
                    //HUIDA (???)
                    break;
                }
            }
        }
    }


void user_Batalla_CambiarPoke(nodoPokemon * equipo , int cambioForzado)//cambioForzado == 0 : Se permite salir sin cambiar / == 1 : No se permite salir sin cambiar
{
    //Variables iniciales
    char opcion = 'x';
    int opcionConvertida = -1;
    int seleccion_PS = -1;
    int pokesEnEquipo = contarPokemonEnEquipo(equipo);
    nodoPokemon * aux = equipo;


    while(opcion != '0')
    {
        draw_menuBatalla_CambiarPokemon(equipo , cambioForzado);
        fflush(stdin);
        opcion = getch();

        if(opcion != '0')
        {
        //Convertimos el char opcion a un int
        //Elijo este método para que el pedido sea mediante getch()
        opcionConvertida = convertirOpcionChar(opcion);

            if(opcionConvertida > pokesEnEquipo)
            {
                opcion = 'x';
            }
            else
            {
                //Ubicar el nodo correspondiente a la elección
                int i = 1;
                while(i != opcionConvertida)
                {
                    aux = aux->sig;
                    i++;
                }
                if(aux->infoPokemon.psActuales < 1)
                {
                    opcion = 'x';
                    aux = equipo;
                }
                else
                {
                    pokemon auxInfo = equipo->infoPokemon;
                    equipo->infoPokemon = aux->infoPokemon;
                    aux->infoPokemon = auxInfo;
                    opcion = '0';
                }
            }
        }
        else
        {
            if(cambioForzado == 1)
            {
                opcion = 'x';
            }
        }
    }
}



////////////////////////////////////////////////////////////////////////////////////
//MODO EDITOR
void user_ModoEditor()//LVL-1
{
    //Variables iniciales
    char opcion = 'x';

    while (opcion != '0')
    {
        draw_menuEditor();
        opcion = getch();

        switch (opcion)
        {
        case '1':
            user_EditorPokedex();
            opcion = 'x';
            break;

        case '2':
            //EDITOR DE EQUIPOS!!!!!!!!!!!!
            opcion = 'x';
            break;

        case '3':
            user_EditorMovimientos();
            opcion = 'x';
            break;
        }
    }

}

//EDITOR DE EQUIPOS
void user_SeleccionarEquipo_aEditar()//LVL-2
{
    //Variables iniciales
    char opcion = 'x';

    while (opcion != '0')
    {
        draw_menuEditor_SeleccionarEquipo();
        opcion = getch();

        switch (opcion)
        {
        case '1':
            //user_  editar equipo jugador
            opcion = 'x';
            break;

        case '2':
            //user_ editar BILL
            opcion = 'x';
            break;

        case '3':
            //user_ editar oponente 1
            opcion = 'x';
            break;

        case '4':
            //user_ editar oponente 2
            opcion = 'x';
            break;

        case '5':
            //user_ editar oponente 3
            opcion = 'x';
            break;

        case '6':
            //user_ editar oponente 4
            opcion = 'x';
            break;
        }
    }

}

//Por cada movimiento agregado en un set
void user_AgregarMov_enSetMov_Inicio(char nombrePokemon[] , movimiento setMovimientos[] , int pos)
{
    //Variables iniciales
    nodoInfoMov * listaMov = inicListaInfoMov();
    listaMov = leerArchivo_InfoMovimientos(listaMov);
    infoMov movBuscado;
    char nombreBuscado[30];
    int tipoElegido = 0;
    char opcion = 'x';

    while (opcion != '1')
    {
        draw_AgregarMov_enSetMov_Inicio(nombrePokemon, setMovimientos[pos]);
        fflush(stdin);
        opcion = getch();

        switch (opcion)
        {
        case '1': //USUARIO INGRESA NOMBRE, SE LO BUSCA, ETC....
            //user_AgregarMov_enSetMov_Buscar
            //Mantenemos opcion = '1', para salir del while y terminar la

            break;

        case '2': //MOSTRAR LISTAMOV ENTERA
            mostrarListaInfoMov(listaMov);
            printf("\nPresiones cualquier tecla para volver al menu.");
            opcion = getch();
            opcion = 'x';
            break;

        case '3': //USUARIO INGRESA UN TIPO, SE MUESTRAN LISTAMOV DE ESE TIPO
            while(tipoElegido<=0 || tipoElegido>TIPOS_VALIDOS)
            {
                draw_VerMovimientos_IngresarTipo();
                scanf("\n%i", &tipoElegido);
            }
            char tipoAMostrar[30];
            tipoEstandarizado(tipoAMostrar , tipoElegido);
            mostrarListaInfoMov_delTipoIndicado(listaMov , tipoAMostrar);
            printf("\nPresiones cualquier tecla para volver al menu.");
            opcion = getch();
            tipoElegido = 0;//Seteamos en 0 por si se reingresa en este case
            opcion = 'x';
            break;
        }
    }



}

void user_EditorNuevoSetMovimientos(char nombrePokemon[] , movimiento setMovimientos[])
{
    //Variables iniciales
    nodoInfoMov * listaMov = inicListaInfoMov();
    listaMov = leerArchivo_InfoMovimientos(listaMov);
    infoMov movBuscado;
    char nombreBuscado[30];
    int tipoElegido = 0;
    char opcion = 'x';
    int pos = 0;

    while (opcion != '0')
    {
        draw_EditorNuevoSetMovimientos_OpcionesIniciales(nombrePokemon , setMovimientos);
        opcion = getch();

        switch (opcion)
        {
        case '1':
            //INGRESAR NOMBRE DE MOVIMIENTO A AGREGAR - USER_INGRESAR NOMBRE DE MOVIMIENTO (VALIDAR QUE NO EXISTE ESE NOMBRE EN EL SET)
            //SI NO EXISTE MOVIMIENTO CON ESE NOMBRE EN LA LISTA, PEDIR RESTO DE DATOS, AGREGAR A LA LISTA DE MOVIMIENTOS... (SE REINGRESA EN EL CHEQUEO DE SI EXISTE)
            //SI EXISTE , MOSTRAR INFOMOVIMIENTO Y CONFIRMAR (SI NO SE CONFIRMA, SE VUELVE A USER_INGRESAR NOMBRE DE MOVIMIENTO
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!SEGUIR POR ACÁ!!!
            //validar si quedan slots libres en el set de movimientos!
            //SI SE LLENÓ EL SET, MOSTRAR RESULTADO, Y SETEAR OPCION = '0'
            //SI QUEDAN SLOTS LIBRES EN EL SET, SETEAR OPCION = 'x' PARA CONTINUAR EN EL MISMO MENÚ
            opcion = 'x';
            break;

        case '2'://Mostrar todos los movimientos de la lista.
            mostrarListaInfoMov(listaMov);
            printf("\nPresiones cualquier tecla para volver al menu.");
            opcion = getch();
            opcion = 'x';
            break;

        case '3'://Mostrar los movimientos del tipo indicado.
            while(tipoElegido<=0 || tipoElegido>TIPOS_VALIDOS)
            {
                draw_VerMovimientos_IngresarTipo();
                scanf("\n%i", &tipoElegido);
            }
            char tipoAMostrar[30];
            tipoEstandarizado(tipoAMostrar , tipoElegido);
            mostrarListaInfoMov_delTipoIndicado(listaMov , tipoAMostrar);
            printf("\nPresiones cualquier tecla para volver al menu.");
            opcion = getch();
            tipoElegido = 0;//Seteamos en 0 por si se reingresa en este case
            opcion = 'x';
            break;
        }




    }


}

void user_EditorBill()//LVL-3
{
    //Variables iniciales
    nodoPokemon * computadora = inicListaPokemon();
    computadora = leerArchivo_Equipo(computadora , ARCHI_BILL);
    int tipoElegido = -1;
    char opcion = 'x';

    while (opcion != '0')
    {
        draw_menuEditor_Bill();
        opcion = getch();

        switch (opcion)
        {
        case '1':
            //AGREGAR UN POKEMON
            opcion = 'x';
            break;

        case '2':
            //BUSCAR UN POKEMON
            opcion = 'x';
            break;

        case '3'://VER TODOS LOS POKEMON DE LA COMPUTADORA
            mostrarEquipo(computadora);
            printf("\nPresiones cualquier tecla para volver al menu.");
            opcion = getch();
            opcion = 'x';
            break;

        case '4'://VER LOS POKEMON DEL TIPO INDICADO
            while(tipoElegido<=0 || tipoElegido>TIPOS_VALIDOS)
            {
                draw_VerEquipo_IngresarTipo();
                scanf("\n%i", &tipoElegido);
            }
            char tipoAMostrar[30];
            tipoEstandarizado(tipoAMostrar , tipoElegido);
            mostrarEquipo_delTipoIndicado(computadora , tipoAMostrar);
            printf("\nPresiones cualquier tecla para volver al menu.");
            opcion = getch();
            tipoElegido = 0;//Seteamos en 0 por si se reingresa en este case
            opcion = 'x';
            break;

        }
    }
}

void user_AgregarPokemon_enBill()//LVL-4
{

}

void user_EditarSetMovimientos(movimiento setMovimientos[])//LVL-5
{
    //Variables iniciales
    char opcion = 'x';
    int pos = -1;
    int validos = setMovimientos_Validos(setMovimientos);

    while(opcion != '0')
    {
        draw_EditarSetMovimientos(setMovimientos);
        fflush(stdin);
        opcion = getch();

        switch (opcion)
        {
        case '1'://Eliminar uno de los movimientos
            while (pos == -1 || pos > validos)
            {
                draw_EditarSetMovimientos_ElegirPos(setMovimientos);
                fflush(stdin);
                scanf("%i" , &pos);
            }
            pos--;//Corregimos la posición(usuario ve 1-4, las posiciones son 0-3)
            quitarMov_deSetMovimientos(setMovimientos , pos);
            opcion = 'x';
            break;

        case '2'://Agregar un movimiento.... solo entra efectivamente en esta opcion si hay espacio libre en el set
            if(validos < 4)//Hay espacio!
            {
                user_AgregarMov_alSet(setMovimientos);
            }
            opcion = 'x';//Para continuar en el menú de edición del set
            break;
        }


    }

}

void user_AgregarMov_alSet(movimiento setMovimientos[])//LVL-6
{
    //Variables iniciales
    nodoInfoMov * listaMov = inicListaInfoMov();
    infoMov aAgregar = inicInfoMov();
    char movBuscado[30] = "";
    int tipoElegido = 0;
    char opcion = 'x';

    while (opcion != '0')
    {
        listaMov = leerArchivo_InfoMovimientos(listaMov);
        draw_AgregarMovEnSet();

        switch(opcion)
        {
        case '1':
            //1) Ingresar nombre movimiento....
            draw_BuscarMovimiento_Ingreso();
            fflush(stdin);
            scanf("%s" , &movBuscado);
            //Existe en listaMov?
            if(strcmp(movBuscado , movEnLista(listaMov , movBuscado).nombre) == 0)
                {
                    //Si! Confirmar si se agrega...
                    opcion = 'x';
                    while (opcion != '1' && opcion != '0')
                    {
                        draw_AgregarMovEnSet_MostrarExistente_Opciones();
                        fflush(stdin);
                        opcion = getch();
                    }
                    if(opcion == '1')//Si? Agregar en el set y salir del todo END
                    {
                        aAgregar = movEnLista(listaMov , movBuscado);
                        insertarMov_enSetMovimiento(aAgregar , setMovimientos);
                        opcion = '0';
                    }
                    else//No? Volver a mostrar draw_AgregarMovEnSet
                    {
                        opcion = 'x';
                    }
                }
                else //No existe.... Generarlo?
                {
                    opcion = 'x';
                    while (opcion != '1' && opcion != '0')
                    {
                        draw_AgregarMovEnSet_MovNoExistente_Opciones(movBuscado);
                        fflush(stdin);
                        opcion = getch();
                    }
                    if(opcion == '1')//Generar movimiento nuevo y agregarlo al pokemon
                    {
                        user_AgregarMovimiento();//Se envía a esta función... Tiene libertad de agregar cualquier movimiento.
                        opcion = 'x';
                    }
                    else
                    {
                        opcion = 'x';
                    }
                }
            break;

        case '2'://Mostrar toda la lista de movimientos

            mostrarListaInfoMov(listaMov);
            printf("\nPresione cualquier tecla para continuar.");
            fflush(stdin);
            opcion = getch();
            opcion = 'x';
            break;

        case '3'://3) Ver movimientos de un tipo

            while(tipoElegido<=0 || tipoElegido>TIPOS_VALIDOS)
            {
                draw_VerMovimientos_IngresarTipo();
                scanf("\n%i", &tipoElegido);
            }
            char tipoAMostrar[30];
            tipoEstandarizado(tipoAMostrar, tipoElegido);
            mostrarListaInfoMov_delTipoIndicado(listaMov, tipoAMostrar);
            printf("\nPresiones cualquier tecla para volver al menu.");
            fflush(stdin);
            opcion = getch();
            tipoElegido = 0;//Seteamos en 0 por si se reingresa en este case
            opcion = 'x';
            break;
        }
    }
}

void user_BuscarPokemon_enBill()
{
    //Variables iniciales
    nodoPokemon * computadora = inicListaPokemon();
    computadora = leerArchivo_Equipo(computadora , ARCHI_BILL);
    nodoPokemon * listaResultados = inicListaPokemon();
    char buscado[30];
    int idBuscado;
    char confirmar = 'x';

    //Pedido de datos al usuario.
    while(confirmar != '1')
    {
        //Inicializamos las variables a utilizar.
        listaResultados = inicListaPokemon();
        idBuscado = -1;
        strcpy(buscado , "");

        //Ingreso del nombre/apodo
        draw_BuscarPokemon_enBill_Ingreso();
        fflush(stdin);
        scanf("%s", &buscado);

        idBuscado = mostrarEquipo_conNombreApodoIndicado(computadora , buscado);
        if(idBuscado == -1) //Caso de no haber encontrado ninguno...
        {
            printf("\nNo hay Pokemon con nombre o apodo [%s]." , buscado);
            printf("\nPresione cualquie tecla para buscar nuevamente.");
            fflush(stdin);
            confirmar = getch();
            confirmar = 'x';
        }
        else if(idBuscado > -1) //Caso de haber encontrado uno solo.
        {
            printf("\nEste es el Pokemon buscado?");
            printf("\n1) Si.");
            printf("\n0) No.");
            fflush(stdin);
            confirmar = getch();
        }
        else //Caso de haber mostrado múltiples
        {
            printf("\n1)El Pokemon esta entre los mostrados!");
            printf("\nNo esta entre los mostrados, quiero reingresar el nombre...");
            fflush(stdin);
            confirmar = getch();
            if(confirmar == '1')
            {
                printf("\nIndique el ID del Pokemon que busca.");
                fflush(stdin);
                scanf("%i" , &idBuscado);
            }
        }

        //////////////////////////////FALTA COMPLETAR!!!

    }

     //Buscamos la entrada pokedex en la lista.

    confirmar = 'x';//Seteamos para reutilizar.

    //Mostramos resultado, y damos las opciones.

}


//EDITOR DE MOVIMIENTOS
void user_EditorMovimientos()//LVL-2
{
    //Variables iniciales
    nodoInfoMov * listaMov = inicListaInfoMov();
    listaMov = leerArchivo_InfoMovimientos(listaMov);
    int tipoElegido = 0;
    char opcion = 'x';

    while (opcion != '0')
    {
        draw_menuEditorMovimientos();
        opcion = getch();
        switch (opcion)
        {
        case '1'://Agregar un movimiento a la lista.
            user_AgregarMovimiento();
            listaMov = inicListaInfoMov();//Reseteamos la lista de movimientos;
            listaMov = leerArchivo_InfoMovimientos(listaMov);//Releemos el archivo para dar cuenta de los cambios.
            opcion = 'x';//Seteamos para reingresar en el while y permanecer en el Menú Editor de Movimientos.
            break;
        case '2'://Buscar un movimiento en la lista.
            user_BuscarMovimiento();
            listaMov = inicListaInfoMov();//Reseteamos la lista de movimientos;
            listaMov = leerArchivo_InfoMovimientos(listaMov);//Releemos el archivo para dar cuenta de los cambios.
            opcion = 'x';//Seteamos para reingresar en el while y permanecer en el Menú Editor de Movimientos.
            break;
        case '3'://Mostrar todos los movimientos de la lista.
            mostrarListaInfoMov(listaMov);
            printf("\nPresiones cualquier tecla para volver al menu.");
            fflush(stdin);
            opcion = getch();
            opcion = 'x';
            break;
        case '4'://Mostrar los movimientos del tipo indicado.
            while(tipoElegido<=0 || tipoElegido>TIPOS_VALIDOS)
            {
                draw_VerMovimientos_IngresarTipo();
                scanf("\n%i", &tipoElegido);
            }
            char tipoAMostrar[30];
            tipoEstandarizado(tipoAMostrar , tipoElegido);
            mostrarListaInfoMov_delTipoIndicado(listaMov , tipoAMostrar);
            printf("\nPresiones cualquier tecla para volver al menu.");
            fflush(stdin);
            opcion = getch();
            tipoElegido = 0;//Seteamos en 0 por si se reingresa en este case
            opcion = 'x';
            break;
        }
    }
}

void user_AgregarMovimiento()//LVL-3
{
    //Variables iniciales
    nodoInfoMov * listaMov = inicListaInfoMov();
    listaMov = leerArchivo_InfoMovimientos(listaMov);
    infoMov aAgregar = inicInfoMov();
    char confirmar = '0';
    int tipoElegido = 0;

    //Pedido de datos al usuario.
    while(confirmar != '1')
    {
        //Nombre
        draw_AgregarMovimiento(aAgregar);
        printf("\nIngrese el nombre (sin espacios): ");
        fflush(stdin);
        scanf("%s", &aAgregar.nombre);

        //Tipo
        while(tipoElegido<=0 || tipoElegido>TIPOS_VALIDOS)
        {
            draw_AgregarMovimiento(aAgregar);
            printf("\nIngrese el tipo: ");
            opcionesDeTipo();
            saltarLinea();
            fflush(stdin);
            scanf("%i", &tipoElegido);
        }
        tipoEstandarizado(aAgregar.tipo , tipoElegido);


        //Potencia
        draw_AgregarMovimiento(aAgregar);
        printf("\nIngrese la potencia: ");
        fflush(stdin);
        scanf("%f" , &aAgregar.potencia);

        //PP Max
        draw_AgregarMovimiento(aAgregar);
        printf("\nIngrese los PP: ");
        fflush(stdin);
        scanf("%i" , &aAgregar.ppMax);

        //Mostrar ingresado y pedir confirmación
        draw_AgregarMovimiento(aAgregar);
        printf("\n1)Los datos son correctos. Guardar movimiento!");
        printf("\n0)Algo anduvo mal... Reingresar datos.");
        fflush(stdin);
        confirmar = getch();
    }
    //Chequeamos que el movimiento NO exista en la lista cargada del archivo.
    if(strcmp(aAgregar.nombre, movEnLista(listaMov, aAgregar.nombre).nombre) != 0)
    {
        //Guardamos en el archivo la infoMov ingresada por usuario
        escribirInfoMov_enArchivo(aAgregar);
    }
}

void user_BuscarMovimiento()//LVL-3
{
    //Variables iniciales
    nodoInfoMov * listaMov = inicListaInfoMov();
    listaMov = leerArchivo_InfoMovimientos(listaMov);
    infoMov movBuscado;
    char nombreBuscado[30];
    char confirmar = 'x';

    //Pedido de datos al usuario.
    while(confirmar != '1')
    {
        //Inicializamos las variables a utilizar.
        movBuscado = inicInfoMov();
        strcpy(nombreBuscado , "");

        //Ingreso del nombre
        draw_BuscarMovimiento_Ingreso();
        fflush(stdin);
        scanf("%s", &nombreBuscado);

        //Mostrar nombre ingresado y pedir confirmación
        draw_BuscarMovimiento_Confirmacion(nombreBuscado);
        fflush(stdin);
        confirmar = getch();
    }
    //Buscamos el movimiento en la lista.
    movBuscado = movEnLista(listaMov , nombreBuscado);
    confirmar = 'x';//Seteamos para reutilizar.

    //Mostramos resultado, y damos las opciones.
    while(confirmar != '0')
    {
        draw_BuscarMovimiento_Resultado(movBuscado);
        fflush(stdin);
        confirmar = getch();
        switch (confirmar)
        {
        case '1'://Editar movimiento
            user_EditarMovBuscado(movBuscado);
            confirmar = '0';//Seteamos en 0 para salir del menú de Buscar Movimiento.
            break;

        case '2'://Eliminar movimiento
            draw_BuscarMovimiento_Eliminar(movBuscado);
            fflush(stdin);
            confirmar = getch();
            if (confirmar == '1')//Confirma eliminación
            {
                draw_BuscarMovimiento_Eliminar_Eliminado(movBuscado);//Mostramos mensaje confirmando la eliminación
                listaMov = borrarNodoInfoMov(listaMov, movBuscado.nombre); //Borramos el nodo correspondiente de la lista
                reescribirArchivoMovimiento(listaMov);//Reescribimos el archivo de movimientos con la nueva lista
                confirmar = '0';//Seteamos en 0 para salir del menú de Buscar Movimiento.
            }
            else//No se quiere eliminar el movimiento
            {
                confirmar = 'x';//Seteamos en x para permanecer en el menú del movimiento encontrado.
            }
            break;
        }
    }
}

void user_EditarMovBuscado(infoMov movBuscado)//LVL-4
{
    //Variables iniciales
    nodoInfoMov * listaMov = inicListaInfoMov();
    listaMov = leerArchivo_InfoMovimientos(listaMov);
    infoMov movEditado;
    char confirmar = '0';
    int tipoElegido = 0;

    //Pedido de datos al usuario.
    while(confirmar != '1')
    {
        movEditado = movBuscado;

        //Nombre
        draw_EditarMovBuscado(movEditado);
        printf("\nIngrese el nombre nuevo (sin espacios): ");
        fflush(stdin);
        scanf("%s", &movEditado.nombre);

        //Tipo
        while(tipoElegido<=0 || tipoElegido>TIPOS_VALIDOS)
        {
            draw_EditarMovBuscado(movEditado);
            printf("\nIngrese el tipo nuevo: ");
            opcionesDeTipo();
            saltarLinea();
            fflush(stdin);
            scanf("%i", &tipoElegido);
        }
        tipoEstandarizado(movEditado.tipo , tipoElegido);


        //Potencia
        draw_EditarMovBuscado(movEditado);
        printf("\nIngrese la potencia nueva: ");
        fflush(stdin);
        scanf("%f" , &movEditado.potencia);

        //PP Max
        draw_EditarMovBuscado(movEditado);
        printf("\nIngrese los PP nuevos: ");
        fflush(stdin);
        scanf("%i" , &movEditado.ppMax);

        //Mostrar edición y pedir confirmación
        draw_EditarMovBuscado(movEditado);
        printf("\n1)Los datos son correctos. Guardar cambios!");
        printf("\n0)Algo anduvo mal... Reingresar datos.");
        fflush(stdin);
        confirmar = getch();

    }

    //Eliminamos de la lista el movimiento anterior
    listaMov = borrarNodoInfoMov(listaMov , movBuscado.nombre);

    //Si ya hay un movimiento con el mismo nombre, también lo eliminamos
    if(strcmp(movEditado.nombre , movEnLista(listaMov , movEditado.nombre).nombre) == 0)
    {
        //Eliminamos el movimiento con el mismo nombre ya existente.
        listaMov = borrarNodoInfoMov(listaMov , movEditado.nombre);
    }

    //Insertamos el movimiento editado en la lista
    listaMov = insertarNodoInfoMovAlFinal(listaMov , nuevoNodoInfoMov(movEditado));

     //Reescribimos el archivo con la lista editada
        reescribirArchivoMovimiento(listaMov);

}

//EDITOR DE POKEDEX
void user_EditorPokedex()//LVL-2
{
    //Variables iniciales
    nodoPokedex * listaPokedex = inicListaPokedex();
    listaPokedex = leerArchivo_Pokedex(listaPokedex);
    int tipoElegido = 0;
    char opcion = 'x';

    while (opcion != '0')
    {
        draw_menuEditorPokedex();
        opcion = getch();
        switch (opcion)
        {
        case '1'://Agregar nueva infoPokedex a la lista
            user_AgregarInfoPokedex();
            listaPokedex = inicListaPokedex();//Reseteamos la lista pokedex.
            listaPokedex = leerArchivo_Pokedex(listaPokedex);//Releemos el archivo para dar cuenta de los cambios.
            opcion = 'x';//Seteamos para reingresar en el while y permanecer en el Menú Editor de Pokedex.
            break;
        case '2'://Buscar una entrada
            user_BuscarInfoPokedex();
            listaPokedex = inicListaPokedex();//Reseteamos la lista pokedex.
            listaPokedex = leerArchivo_Pokedex(listaPokedex);//Releemos el archivo para dar cuenta de los cambios.
            opcion = 'x';//Seteamos para reingresar en el while y permanecer en el Menú Editor de Pokedex.
            break;
        case '3'://Mostrar toda la pokedex
            mostrarListaPokedex(listaPokedex);
            printf("\nPresiones cualquier tecla para volver al menu.");
            opcion = getch();
            opcion = 'x';
            break;
        case '4'://Mostrar entradas del tipo indicado
            while(tipoElegido<=0 || tipoElegido>TIPOS_VALIDOS)
            {
                draw_VerListaPokedex_IngresarTipo();
                scanf("\n%i", &tipoElegido);
            }
            char tipoAMostrar[30];
            tipoEstandarizado(tipoAMostrar , tipoElegido);
            mostrarListaPokedex_delTipoIndicado(listaPokedex , tipoAMostrar);
            printf("\nPresiones cualquier tecla para volver al menu.");
            opcion = getch();
            tipoElegido = 0;//Seteamos en 0 por si se reingresa en este case
            opcion = 'x';
            break;
        }
    }

}

void user_AgregarInfoPokedex()//LVL-3
{
    //Variables iniciales
    nodoPokedex * listaPokedex = inicListaPokedex();
    listaPokedex = leerArchivo_Pokedex(listaPokedex);
    infoPokedex aAgregar = inicInfoPokedex();
    char confirmar = '0';
    int tipoElegido = 0;

    //Pedido de datos al usuario.
    while(confirmar != '1')
    {
        //Numero
        draw_AgregarInfoPokedex(aAgregar);
        printf("\nIngrese numero de pokemon:    ");
        fflush(stdin);
        scanf("%i" , &aAgregar.numPokedex);

        //Nombre
        draw_AgregarInfoPokedex(aAgregar);
        printf("\nIngrese el nombre (sin espacios): ");
        fflush(stdin);
        scanf("%s", &aAgregar.nombre);

        //Tipo 1
        while(tipoElegido<=0 || tipoElegido>TIPOS_VALIDOS)
        {
            draw_AgregarInfoPokedex(aAgregar);
            printf("\nIngrese el tipo 1: ");
            opcionesDeTipo();
            saltarLinea();
            fflush(stdin);
            scanf("%i", &tipoElegido);
        }
        tipoEstandarizado(aAgregar.tipo_1 , tipoElegido);
        tipoElegido = 0;//Seteamos en 0 para reutilizar la variable en el tipo 2

        //Tipo 2
        confirmar = 'x';
        while(confirmar != '1' && confirmar != '0')
        {
        draw_AgregarInfoPokedex(aAgregar);
        printf("\nTiene un segundo tipo?");
        printf("\n1) Si, tiene un segundo tipo.");
        printf("\n0) No. Tiene un solo tipo.");
        confirmar = getch();
        }

        if(confirmar == '1')//Se confirmó que tiene un segundo tipo
        {
            while(tipoElegido<=0 || tipoElegido>TIPOS_VALIDOS)
            {
                draw_AgregarInfoPokedex(aAgregar);
                printf("\nIngrese el tipo 2: ");
                opcionesDeTipo();
                saltarLinea();
                fflush(stdin);
                scanf("%i", &tipoElegido);
            }
            tipoEstandarizado(aAgregar.tipo_2, tipoElegido);
            confirmar = 'x';

        }

        //PS Max
        draw_AgregarInfoPokedex(aAgregar);
        printf("\nIngrese los PS: ");
        fflush(stdin);
        scanf("%i" , &aAgregar.psMax);

        //Mostrar ingresado y pedir confirmación
        draw_AgregarInfoPokedex(aAgregar);
        printf("\n1)Los datos son correctos. Guardar entrada pokedex!");
        printf("\n0)Algo anduvo mal... Reingresar datos.");
        fflush(stdin);
        confirmar = getch();
    }

}

void user_BuscarInfoPokedex()//LVL-3
{
    //Variables iniciales
    nodoPokedex * listaPokedex = inicListaPokedex();
    listaPokedex = leerArchivo_Pokedex(listaPokedex);
    infoPokedex infoPokedexBuscada;
    char nombreBuscado[30];
    char confirmar = 'x';

    //Pedido de datos al usuario.
    while(confirmar != '1')
    {
        //Inicializamos las variables a utilizar.
        infoPokedexBuscada = inicInfoPokedex();
        strcpy(nombreBuscado , "");

        //Ingreso del nombre
        draw_BuscarInfoPokedex_Ingreso();
        fflush(stdin);
        scanf("%s", &nombreBuscado);

        //Mostrar nombre ingresado y pedir confirmación
        draw_BuscarInfoPokedex_Confirmacion(nombreBuscado);
        fflush(stdin);
        confirmar = getch();
    }

     //Buscamos la entrada pokedex en la lista.
    infoPokedexBuscada = infoPokedexEnLista(listaPokedex , nombreBuscado);
    confirmar = 'x';//Seteamos para reutilizar.

    //Mostramos resultado, y damos las opciones.
    while(confirmar != '0')
    {
        draw_BuscarInfoPokedex_Resultado(infoPokedexBuscada);
        fflush(stdin);
        confirmar = getch();
        switch (confirmar)
        {
        case '1'://Editar entrada pokedex
            user_EditarInfoPokedexBuscada(infoPokedexBuscada);
            confirmar = '0';//Seteamos en 0 para salir del menú de Buscar Entrada Pokedex
            break;

        case '2'://Eliminar entrada pokedex
            draw_BuscarInfoPokedex_Eliminar(infoPokedexBuscada);
            fflush(stdin);
            confirmar = getch();
            if (confirmar == '1')//Confirma eliminación
            {
                draw_BuscarInfoPokedex_Eliminar_Eliminada(infoPokedexBuscada);//Mostramos mensaje confirmando la eliminación
                listaPokedex = borrarNodoPokedex(listaPokedex , infoPokedexBuscada.nombre); //Borramos el nodo correspondiente de la lista
                reescribirArchivoPokedex(listaPokedex);//Reescribimos el archivo de movimientos con la nueva lista
                confirmar = '0';//Seteamos en 0 para salir del menú de Buscar Entrada Pokedex.
            }
            else//No se quiere eliminar el movimiento
            {
                confirmar = 'x';//Seteamos en x para permanecer en el menú de la entrada pokedex encontrada.
            }
            break;
        }

    }

}

void user_EditarInfoPokedexBuscada(infoPokedex infoPokedexBuscada)//LVL-4
{
    //Variables iniciales
    nodoPokedex * listaPokedex = inicListaPokedex();
    listaPokedex = leerArchivo_Pokedex(listaPokedex);
    infoPokedex infoEditada;
    char confirmar = '0';
    int tipoElegido = 0;

    //Pedido de datos al usuario.
    while(confirmar != '1')
    {
        infoEditada = infoPokedexBuscada;

        //Numero
        draw_EditarInfoPokedex(infoEditada);
        printf("\nIngrese el numero pokedex nuevo:");
        fflush(stdin);
        scanf("%i" , &infoEditada.numPokedex);

        //Nombre
        draw_EditarInfoPokedex(infoEditada);
        printf("\nIngrese el nombre nuevo (sin espacios): ");
        fflush(stdin);
        scanf("%s", &infoEditada.nombre);

        //Tipo 1
        while(tipoElegido<=0 || tipoElegido>TIPOS_VALIDOS)
        {
            draw_EditarInfoPokedex(infoEditada);
            printf("\nIngrese el nuevo tipo 1: ");
            opcionesDeTipo();
            saltarLinea();
            fflush(stdin);
            scanf("%i", &tipoElegido);
        }
        tipoEstandarizado(infoEditada.tipo_1 , tipoElegido);
        tipoElegido = 0;//Seteamos en 0 para reutilizar la variable en el tipo 2

        //Tipo 2
        confirmar = 'x';
        while(confirmar != '1' && confirmar != '0')
        {
        draw_EditarInfoPokedex(infoEditada);
        printf("\nTiene un segundo tipo?");
        printf("\n1) Si, tiene un segundo tipo.");
        printf("\n0) No. Tiene un solo tipo.");
        confirmar = getch();
        }

        if(confirmar == '1')//Se confirmó que tiene un segundo tipo
        {
            while(tipoElegido<=0 || tipoElegido>TIPOS_VALIDOS)
            {
                draw_EditarInfoPokedex(infoEditada);
                printf("\nIngrese el nuevo tipo 2: ");
                opcionesDeTipo();
                saltarLinea();
                fflush(stdin);
                scanf("%i", &tipoElegido);
            }
            tipoEstandarizado(infoEditada.tipo_2, tipoElegido);
            confirmar = 'x';
        }
        else//Se confirmó que NO tiene segundo tipo, así que hay que vaciar el tipo_2
        {
            strcpy(infoEditada.tipo_2 , "");
            confirmar = 'x';
        }

        //PS Max
        draw_EditarInfoPokedex(infoEditada);
        printf("\nIngrese los PS nuevos: ");
        fflush(stdin);
        scanf("%i" , &infoEditada.psMax);

        //Mostrar edición y pedir confirmación
        draw_EditarInfoPokedex(infoEditada);
        printf("\n1)Los datos son correctos. Guardar cambios!");
        printf("\n0)Algo anduvo mal... Reingresar datos.");
        fflush(stdin);
        confirmar = getch();
    }

    //Eliminamos de la lista la infoPokedex anterior
    listaPokedex = borrarNodoPokedex(listaPokedex , infoPokedexBuscada.nombre);

    //Si ya hay una infoPokedex con el mismo nombre, también la eliminamos
    if(strcmp(infoEditada.nombre , infoPokedexEnLista(listaPokedex , infoEditada.nombre).nombre) == 0)
    {
        //Eliminamos la infoPokedex con el mismo nombre ya existente.
        listaPokedex = borrarNodoInfoMov(listaPokedex , infoEditada.nombre);
    }

    //Insertamos el movimiento editado en la lista
    listaPokedex = insertarNodoPokedexAlFinal(listaPokedex , nuevoNodoPokedex(infoEditada));

     //Reescribimos el archivo con la lista editada
        reescribirArchivoPokedex(listaPokedex);
}
