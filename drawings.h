#ifndef DRAWINGS_H_INCLUDED
#define DRAWINGS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "movimientos.h"

////////////////////////////////////////////////////////////////////////////////////
//***PROTOTIPADOS***
//FORMATO
void limpiarPantalla();
void saltarLinea();
void lineaAsteriscos100();
void lineaUnderscore100();
void draw_encabezado(char titulo[]);;
void escribirTipoFormateado(char aEscribir[]);
void opcionesDeTipo();

//MOSTRAR ESTRUCTURAS
void mostrarInfoMov(infoMov aMostrar);
void mostrarInfoMov_Edicion(infoMov aMostrar);
void mostrarListaInfoMov(nodoInfoMov * lista);
void mostrarListaInfoMov_delTipoIndicado(nodoInfoMov * lista , char tipoIndicado[]);
void mostrarMovimiento(movimiento aMostrar);
void mostrarMovimiento_Edicion(movimiento aMostrar);
void mostrarSetMovimientos(movimiento setMovimientos[]);
void mostrarSetMovimientos_Edicion(movimiento setMovimientos[]);

void mostrarInfoPokedex(infoPokedex aMostrar);
void mostrarInfoPokedex_Edicion(infoPokedex aMostrar);
void mostrarListaPokedex(nodoPokedex * lista);
void mostrarListaPokedex_delTipoIndicado(nodoPokedex * lista , char tipoIndicado[]);

void mostrarUnPokemon(pokemon aMostrar);
void mostrarEquipo(nodoPokemon * equipo);
void mostrarEquipo_enBatalla_Cambiar(nodoPokemon * equipo);
void mostrarEquipo_delTipoIndicado(nodoPokemon * equipo , char tipoIndicado[]);
int mostrarEquipo_conNombreApodoIndicado(nodoPokemon * equipo , char nomApodoBuscado[]);
void mostrar_MovimientoEnBatalla(movimiento aMostrar);

//BATALLA
void mostrar_PokeEnBatalla (pokemon aMostrar);
void draw_Batalla_Pokes(pokemon deJugador , pokemon deOponente);
void draw_Batalla_General(nodoPokemon * deJugador , nodoPokemon * deOponente);
void draw_menuBatalla_General();
void draw_Batalla_Ataques(nodoPokemon * deJugador , nodoPokemon * deOponente);
void draw_menuBatalla_Ataques(movimiento setMovimientos[]);
void draw_menuBatalla_CambiarPokemon(nodoPokemon * equipoJugador , int cambioForzado);

//GRÁFICAS DE MENÚ
void draw_menuPrincipal();
void draw_menuEditor();

//MENÚ EDITOR DE EQUIPOS/POKEMON
void draw_menuEditor_SeleccionarEquipo();
void draw_EditorNuevoSetMovimientos_OpcionesIniciales(char nombrePokemon[] , movimiento setMovimientos[]);
void draw_menuEditorEquipo();
void draw_menuEditor_Bill();
void draw_VerEquipo_IngresarTipo();
void draw_BuscarPokemon_enBill_Ingreso();

void draw_AgregarMovEnSet_MostrarExistente_Opciones(infoMov aMostrar);



//MENÚ EDITOR DE MOVIMIENTOS
void draw_menuEditorMovimientos();
void draw_VerMovimientos_IngresarTipo();
void draw_AgregarMovimiento (infoMov aMostrar);
void draw_BuscarMovimiento_Ingreso();
void draw_BuscarMovimiento_Confirmacion(char nombreIngresado[]);
void draw_BuscarMovimiento_Resultado(infoMov aMostrar);
void draw_BuscarMovimiento_Resultado_paraSetMov(infoMov aMostrar);
void draw_BuscarMovimiento_Eliminar(infoMov aMostrar);
void draw_BuscarMovimiento_Eliminar_Eliminado(infoMov aMostrar);
void draw_EditarMovBuscado(infoMov aEditar);
void draw_EditarSetMovimientos(movimiento setMovimientos[]);
void draw_EditarSetMovimientos_ElegirPos(movimiento setMovimientos[]);

void draw_AgregarMovEnSet();


//MENÚ EDITOR DE POKEDEX
void draw_menuEditorPokedex();
void draw_VerListaPokedex_IngresarTipo();
void draw_AgregarInfoPokedex(infoPokedex aMostrar);
void draw_BuscarInfoPokedex_Ingreso();
void draw_BuscarInfoPokedex_Confirmacion(char nombreIngresado[]);
void draw_BuscarInfoPokedex_Resultado(infoPokedex aMostrar);
void draw_EditarInfoPokedex(infoPokedex aEditar);
void draw_BuscarInfoPokedex_Eliminar(infoPokedex aMostrar);
void draw_BuscarInfoPokedex_Eliminar_Eliminada(infoPokedex aMostrar);


#endif // DRAWINGS_H_INCLUDED
