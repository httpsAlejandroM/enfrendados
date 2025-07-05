#ifndef DECLARACIONFUNCIONES_H_INCLUDED
#define DECLARACIONFUNCIONES_H_INCLUDED
#include <string>
using namespace std;


/// Muestra el menu principal
int mostrarMenu();

/// Tira un dado de 6 caras
int tirarDado();

/// Tira un dado de 12 caras
int tirarDado12();

/// Tira dos dados de 6 caras y retorna la suma
int tirarDadoObjetivo();

/// Ingresa nombres de los jugadores
void ingresarNombres(string &jugador1, string &jugador2);

/// Logica principal del juego
void jugar(string rankingNombres[], int rankingPuntajes[], int &contadorRanking);

/// Determina quien comienza primero
void determinarJugadorInicial(string jugador1, string jugador2, string ordenJugadores[]);

//inicia la ronda (6 turnos si no hay victoria automatica)
void iniciarRonda(string ordenJugadores[], string rankingNombres[], int rankingPuntajes[], int &contadorRanking);

//Imprime por pantalla la ronda que va a comenzar
void anunciadorRondas(int nroRonda);

//iniciar turno
void iniciarTurno(string jugador, string jugador2, int dadosStock[], int &cantDados, int &cantDadosSeleccionados, int dadosSeleccionados[], int &sumaSeleccionada, int &puntaje, int &cantDadosJ2);

//Tira dados stock
void tirarDadosStock(int dadosStock[], int cantidad);

//Imprime por pantalla los dados stock que se pasan por parametro
void mostrarDadosStock(int dadosStock[], int cantDados);

//Imprime por pantalla el nro objetivo
void mostrarNroObjetivo(int nroObjetivo, string jugador);

//Permite al jugador seleccionar y sumar los dados
void seleccionarDados(int dadosStock[], int cantDados, int &cantDadosTransferidos, int dadosSeleccionados[], int &sumaSeleccionada);

//Imprime por pantalla la combinacion que eligio el usuario para intentar llegar al numero objetivo
void mostrarCombinacionElegida(int dadosSeleccionados[], int dadosStock[], int cantDadosTransferidos);

//Identifica si la suma seleccionada del jugador es igual al numero objetivo
bool identificarTiradaExitosa(string jugador, int sumaSeleccionada, int nroObjetivo);

//Muestra y suma los puntos de la ronda al puntaje total del jugador
void mostrarPuntosDelTurno(string jugador, bool tiradaExitosa, int cantDadosTransferidos, int &sumaSeleccionada, int &puntaje, int cantDados);

//Devuelve true o false si la opcion (numero de dado) que ingreso el jugador ya fue seleccionada
bool yaFueSeleccionado(int opcion, int dadosSeleccionados[], int cantDadosSeleccionados);

//Hace la transferencia de dados que corresponda segun si hubo tirada exitosa o no
void transferirDados(string jugador1, string jugador2, int &cantDadosJ1, int &cantDadosJ2, int &cantDadosSeleccionados, bool &tiradaExitosa);

//Muestra por pantalla los resultados finales y el ganador de la partida
void mostrarResultadosFinales(string jugador1, string jugador2, int puntosJ1, int puntosJ2, int cantDadosJ1, int cantDadosJ2);

//Agrega y ordena resultados de juegos al ranking
void manejadorResultadosRanking(string jugador1, string jugador2, int puntosJ1, int puntosJ2, string rankingNombres[], int rankingPuntajes[], int &contadorRanking);

//Intenta agregar un puntaje en el ranking lleno
void intentarAgregarResultados(string nombre, int puntaje, string rankingNombres[], int rankingPuntajes[], int &contadorRanking);

//Ordena el ranking
void ordenarRanking(string rankingNombres[], int rankingPuntajes[], int &contadorRanking);

//Muestra el ranking
void mostrarRanking(string rankingNombres[], int rankingPuntajes[], int contadorRanking);

void explicacionJuego();

int confirmarSalida();

void mostrarCreditos();



/*
https://tapiov.net/rlutil/docs/HTML/files/rlutil-h.html#rlutil.locate
rlutil::
cls() limpia la pantalla (llena de espacios la pantalla)
anykey() pone pausa
locate(5, 3); ingresar coordarnadas eje x, y (cant columnas, cantidad filas)
saveDefaultColor(); guarda el color que cambiemos
setColor(rlutil::LIGHTBLUE) le pone color al texto
resetColor() vuelve al color pro defecto
setBackgroundColor(); cambia el color de fondo (usandolo antes de cls cambiamos el fondo de toda la pantalla)
hidecursor() oculta el curso (linea titilando)
showcursor() muestra el cursor
*/

#endif // DECLARACIONFUNCIONES_H_INCLUDED
