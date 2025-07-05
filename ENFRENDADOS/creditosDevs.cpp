#include <iostream>
#include <string>
#include "DeclaracionFunciones.h"
#include "rlutil.h"

using namespace std;

void mostrarCreditos() {
    rlutil::cls();

    int ejeX = 40;
    int ejeY = 5;

    rlutil::locate(ejeX, ejeY);
    cout << "   =====================================" << endl;

    ejeY++; //va sumando 1 a la posicion de filas para abajo
    rlutil::locate(ejeX, ejeY);
    cout << "   |                                   |" << endl;

    ejeY++; //10
    rlutil::locate(ejeX, ejeY);
    cout << "   |           ENFRENDADOS             |" << endl;

    ejeY++;
    rlutil::locate(ejeX, ejeY);
    cout << "   |===================================|" << endl;

    ejeY++;
    rlutil::locate(ejeX, ejeY);
    cout << "   |     Juego desarrollado por:       |" << endl;

    ejeY++;
    rlutil::locate(ejeX, ejeY);
    cout << "   |            Equipo 7               |" << endl;

    ejeY++;
    rlutil::locate(ejeX, ejeY);
    cout << "   |                                   |" << endl;

    ejeY++;
    rlutil::locate(ejeX, ejeY);
    cout << "   |-Alejandro Medina   - Legajo 33220 |" << endl;

    ejeY++;
    rlutil::locate(ejeX, ejeY);
    cout << "   |-Zulema Cruz        - Legajo 28057 |" << endl;

    ejeY++;
    rlutil::locate(ejeX, ejeY);
    cout << "   |-Esteban Reyes      - Legajo 33402 |" << endl;

    ejeY++;
    rlutil::locate(ejeX, ejeY);
    cout << "   |-Rodrigo Martinez   - Legajo 28059 |" << endl;

    ejeY++;
    rlutil::locate(ejeX, ejeY);
    cout << "   |                                   |" << endl;

    ejeY++;
    rlutil::locate(ejeX, ejeY);
    cout << "   | Version 1.0                       |" << endl;

    ejeY++;
    rlutil::locate(ejeX, ejeY);
    cout << "   | UTN FRGP - Programacion 1         |" << endl;

    ejeY++;
    rlutil::locate(ejeX, ejeY);
    cout << "   |                                   |" << endl;

    ejeY++;
    rlutil::locate(ejeX, ejeY);
    cout << "   |                                   |" << endl;

    ejeY++;
    rlutil::locate(ejeX, ejeY);
    cout << "   | Libreria utilizada: RLUTIL        |" << endl;

    ejeY++;
    rlutil::locate(ejeX, ejeY);
    cout << "   |                                   |" << endl;

    ejeY++;
    rlutil::locate(ejeX, ejeY);
    cout << "   =====================================" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;

    ejeY+=4;
    rlutil::locate(ejeX, ejeY);
    rlutil::anykey("Presione una tecla para volver al menu principal...");
    rlutil::cls();

}

