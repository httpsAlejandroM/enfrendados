#include <iostream>
#include <string>
#include "DeclaracionFunciones.h"
#include "rlutil.h"

using namespace std;

// Gestiona la actualizacion del ranking de jugadores al finalizar una partida.
// Identifica al ganador y al perdedor junto en base a sus puntajes,e intenta agregar ambos al ranking.
// Finalmente, ordena la tabla de ranking para reflejar los cambios correctamente.
// Parametros:
// string jugador1: Nombre del primer jugador de la partida.
// string jugador2: Nombre del segundo jugador de la partida.
// int puntosJ1: Puntaje alcanzado por el primer jugador.
// int puntosJ2: Puntaje alcanzado por el segundo jugador.
// string rankingNombres[]: Array de nombres de jugadores en el ranking.
// int rankingPuntajes[]: Array de puntajes de jugadores en el ranking.
// int &contadorRanking: Referencia al contador de elementos actuales en el ranking.
void manejadorResultadosRanking(string jugador1, string jugador2, int puntosJ1, int puntosJ2, string rankingNombres[], int rankingPuntajes[], int &contadorRanking){

    string jugadorGanador, jugadorPerdedor;
    int puntajeGanador, puntajePerdedor;

    // Identificacion del ganador y perdedor segun puntajes alcanzados
     if(puntosJ1 > puntosJ2){
        jugadorGanador = jugador1;
        puntajeGanador = puntosJ1;
        jugadorPerdedor = jugador2;
        puntajePerdedor = puntosJ2;

    } else {
        jugadorGanador = jugador2;
        puntajeGanador = puntosJ2;
        jugadorPerdedor = jugador1;
        puntajePerdedor = puntosJ1;
    }

    // Intenta agregar los resultados al ranking
    intentarAgregarResultados(jugadorGanador, puntajeGanador, rankingNombres, rankingPuntajes, contadorRanking);
    intentarAgregarResultados(jugadorPerdedor, puntajePerdedor, rankingNombres, rankingPuntajes, contadorRanking);

     // Ordena la tabla de ranking para reflejar correctamente los cambios
    ordenarRanking(rankingNombres, rankingPuntajes, contadorRanking);
}

// Intenta agregar un resultado al ranking de jugadores.
// Si el ranking tiene menos de 10 elementos, simplemente lo a¤ade.
// Si el ranking esta lleno (10 elementos), compara el puntaje con el de menor puntaje registrado:
// - Si el puntaje es mayor que el menor registrado, reemplaza ese registro con el nuevo puntaje y nombre.
// - Si no es mayor, no realiza cambios.
// Parametros:
// string nombre: Nombre del jugador cuyo puntaje se evalua para ingresar al ranking.
// int puntaje: Puntaje alcanzado por el jugador.
// string rankingNombres[]: Array de nombres de jugadores en el ranking.
// int rankingPuntajes[]: Array de puntajes registrados en el ranking.
// int &contadorRanking: Referencia al contador de elementos actuales en el ranking.
void intentarAgregarResultados(string nombre, int puntaje, string rankingNombres[], int rankingPuntajes[], int &contadorRanking){

    // Si hay menos de 10 elementos en el ranking, simplemente agregar
     if(contadorRanking < 10){
        rankingNombres[contadorRanking]  = nombre;
        rankingPuntajes[contadorRanking] = puntaje;
        contadorRanking++;
    } else {
        // Si el ranking esta lleno, buscar la posicion del menor puntaje registrado
        int menor = rankingPuntajes[0]; //Valor del menor puntaje
        int posMin = 0;                 // Posicion del menor puntaje

        for(int i = 1; i < 10; i++){
            if(rankingPuntajes[i] < menor){
                menor = rankingPuntajes[i]; // Se guarda el valor de puntaje menor
                posMin = i;                 // Se guarda la posicion del menor puntaje
            }
        }
        // Si el puntaje actual es mayor que el menor registrado, reemplazarlo
        if(puntaje > menor) {
            rankingNombres[posMin] = nombre;
            rankingPuntajes[posMin] = puntaje;
        }
    }

}

// Ordena el ranking de jugadores de mayor a menor puntaje.
// Reordena tanto los puntajes como los nombres, conservando la relacion nombre-puntaje correspondiente.
/// Parametros:
/// string rankingNombres[]: Array de nombres de jugadores en el ranking.
/// int rankingPuntajes[]: Array de puntajes en el ranking.
/// int &contadorRanking: Referencia al contador de elementos actuales en el ranking.
void ordenarRanking(string rankingNombres[], int rankingPuntajes[], int &contadorRanking){

    string auxNombre; // Variable temporal para guardar nombres durante el intercambio
    int auxPuntaje;   // Variable temporal para guardar puntajes durante el intercambio
    int i,j, posMax;

    // Recorre todas las posiciones del array, excepto la ultima,
    // para ir colocando el puntaje mayor en cada posicion correspondiente
    for(i = 0; i < contadorRanking - 1; i++){

        posMax = i;
        // Busca la posicion del puntaje maximo en la seccion restante del array (i+1)
        for(j = i + 1; j < contadorRanking; j++ ){
            if(rankingPuntajes[j] > rankingPuntajes[posMax]){
                posMax = j;
            }
        }

        // Intercambia tanto puntajes como nombres para mantener la relacion nombre-puntaje correspondiente
        auxPuntaje = rankingPuntajes[i];
        auxNombre = rankingNombres[i];
        rankingPuntajes[i] = rankingPuntajes[posMax];
        rankingNombres[i] = rankingNombres[posMax];
        rankingPuntajes[posMax] = auxPuntaje;
        rankingNombres[posMax] = auxNombre;

    }
}


void mostrarRanking(string rankingNombres[], int rankingPuntajes[], int contadorRanking){

    int ejeXPuesto = 17;
    int ejeXJugador = 51;
    int ejeXPuntos = 85;

    if(contadorRanking == 0){
        rlutil::locate(33, 13);
        cout << "El ranking esta vacio. Juga una partida para aparecer!";
    } else {

        rlutil::locate(ejeXPuesto, 10);
        cout << "PUESTO";

        rlutil::locate(ejeXJugador, 10);
        cout << "JUGADOR";

        rlutil::locate(ejeXPuntos, 10);
        cout << "PUNTOS";

        rlutil::locate(16, 11);
        cout << "-----------------------------------------------------------------------------";

        for(int i = 0 ; i < contadorRanking; i++ ){
        //cout << rankingNombres[i] << " \t \t" << rankingPuntajes[i] << " \t \t" << endl;
            rlutil::locate(ejeXPuesto, 12 + i);
            cout << i+1;

            rlutil::locate(ejeXJugador, 12 + i);
            cout << rankingNombres[i];

            rlutil::locate(ejeXPuntos, 12 + i);
            cout << rankingPuntajes[i];
    }
}
     rlutil::locate(33, 24);
    cout << "Presione una tecla para volver al menu principal..." << endl;
    rlutil::hidecursor();
    rlutil::anykey();
    rlutil::cls();
}
