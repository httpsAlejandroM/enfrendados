#include <iostream>
#include <string>
#include "DeclaracionFunciones.h"
#include "rlutil.h"

using namespace std;

/// Muestra el menu principal
int mostrarMenu()
{
    int opcion;
    string tituloVector[7];

    tituloVector[0] = " _______  __    _  _______  ______    _______  __    _  ______   _______  ______   _______  _______ ";
    tituloVector[1] = "|       ||  |  | ||       ||    _ |  |       ||  |  | ||      | |   _   ||      | |       ||       |";
    tituloVector[2] = "|    ___||   |_| ||    ___||   | ||  |    ___||   |_| ||  _    ||  |_|  ||  _    ||   _   ||  _____|";
    tituloVector[3] = "|   |___ |       ||   |___ |   |_||_ |   |___ |       || | |   ||       || | |   ||  | |  || |_____ ";
    tituloVector[4] = "|    ___||  _    ||    ___||    __  ||    ___||  _    || |_|   ||   _   || |_|   ||  |_|  ||_____  |";
    tituloVector[5] = "|   |___ | | |   ||   |    |   |  | ||   |___ | | |   ||       ||  | |  ||       ||       | _____| |";
    tituloVector[6] = "|_______||_|  |__||___|    |___|  |_||_______||_|  |__||______| |__| |__||______| |_______||_______|";

    for (int i = 0; i < 7; i++){
        rlutil::locate(10, 5+i);
        cout << tituloVector[i] << endl; //muestra por pantalla los valores asignados a cada elemento del vector tituloVector
    }

    int posicionXMenu = 50; ///posicion X de las opciones al ver consola
    rlutil::locate(posicionXMenu, 16);
    cout << "1. JUGAR" << endl;
    rlutil::locate(posicionXMenu, 18);
    cout << "2. ESTADISTICAS" << endl;
    rlutil::locate(posicionXMenu, 20);
    cout << "3. CREDITOS" << endl;
    rlutil::locate(posicionXMenu, 22);
    cout << "4. REGLAS" << endl;
    rlutil::locate(posicionXMenu, 24);
    cout << "0. SALIR" << endl << endl;
    rlutil::locate(posicionXMenu, 26);
    cout << "Elija una opcion: ";

    cin >> opcion;
    cout << endl;

    return opcion;
}


// Anuncia en consola cual ronda esta por jugarse.
/// Parametros:
/// int nroRonda: Numero de ronda actual (1, 2 o 3).
void anunciadorRondas(int nroRonda)
{
    rlutil::locate(56, 3);
    switch (nroRonda)
    {
    case 1:
        cout << "Ronda " << nroRonda << endl << endl;
        break;
    case 2:
        cout << "Ronda " << nroRonda << endl << endl;
        break;
    case 3:
        cout << "Ronda " << nroRonda << endl << endl;
        break;
    default:
        cout << "Esta ronda no deberia existir" << nroRonda << endl << endl;
        break;
    }
}



void explicacionJuego(){

    rlutil::cls();
    int posicitionX = 5;
    int positionY = 8;

    rlutil::locate(posicitionX, 8);
    cout << "Reglas del juego: " << endl << endl;

    positionY++;
    positionY++;
    rlutil::locate(posicitionX, positionY);
    cout << "Ambos jugadores lanzan un dado de 6 caras. Quien obtenga el valor ms alto inicia la partida." << endl;

    positionY++;
    rlutil::locate(posicitionX, positionY);
    cout << "Cada jugador comienza con 6 dados de 6 caras (dados stock) y durante cada ronda se lanzan 2 dados " << endl;

    positionY++;
    rlutil::locate(posicitionX, positionY);
    cout << "de 12 caras (dados objetivo), cuyo resultado determina un numero objetivo a alcanzar. " << endl;

    positionY++;
    rlutil::locate(posicitionX, positionY);
    cout << "En cada turno, el jugador debe intentar seleccionar dados de su stock cuya suma sea " << endl;

    positionY++;
    rlutil::locate(posicitionX, positionY);
    cout << "igual al numero objetivo. Si lo logra, su tirada es exitosa. Los dados utilizados son transferidos al rival, " << endl;

    positionY++;
    rlutil::locate(posicitionX, positionY);
    cout << "disminuyendo el stock del jugador actual y aumentando el del oponente. Si un jugador logra una tirada exitosa " << endl;

    positionY++;
    rlutil::locate(posicitionX, positionY);
    cout << "y se queda sin dados, gana automaticamente la partida y se le suman 10.000 puntos." << endl;

    positionY++;
    rlutil::locate(posicitionX, positionY);
    cout << "El juego finaliza cuando se completan las 3 rondas o bien un jugador se queda sin dados." << endl;

    positionY++;
    rlutil::locate(posicitionX, positionY);
    cout << "Gana quien tenga mayor puntaje al final de las 3 rondas o quien logre la victoria automtica. " << endl;

    positionY++;
    rlutil::locate(posicitionX, positionY);
    cout << "Si ambos jugadores empatan en puntos, el juego finaliza en empate." << endl << endl;

    positionY++;
    rlutil::locate(posicitionX, positionY);
    cout << "AHORA SI, COMENCEMOS!" << endl << endl;

    positionY++;
    positionY++;
    rlutil::locate(posicitionX, positionY);
    rlutil::anykey("Presione una tecla para volver al menu principal...");
    rlutil::cls();
}



