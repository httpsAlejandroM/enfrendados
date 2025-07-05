#include <iostream>
#include "DeclaracionFunciones.h"
#include <string>
#include <ctime>    //para rand
#include <cstdlib>   //libreria de rand
#include "rlutil.h"

using namespace std;


int main()
{
    srand(time(nullptr));  // Inicializamos la semilla para la generacion de numeros aleatorios
    // Arrays para guardar nombres y puntajes de los jugadores para la tabla de estadisticas
    // rankingNombres: almacena nombres de jugadores
    // rankingPuntajes: almacena puntajes de jugadores
    // contadorRanking: cantidad de registros actuales en la tabla de ranking
    // opcion: almacena la opcion seleccionada por el usuario en el menu
    string rankingNombres[10] = {""};
    int rankingPuntajes[10] = {0}, contadorRanking = 0, opcion;


    // Bucle principal del programa. Se ejecuta hasta que el usuario seleccione salir (opcion == 0).
    do
    {
        //rlutil::showcursor(); //Muestra el cursor parpadeando
        opcion = mostrarMenu(); // Llama a la funcion mostrarMenu() para obtener la opcion seleccionada
        switch (opcion)  // Procesa la opcion ingresada por el usuario
        {
        case 1:

            rlutil::cls(); // limpia la pantalla
            // Inicia la logica principal del juego
            // Se reciben los arreglos de ranking para guardar los datos al finalizar el juego
            jugar(rankingNombres, rankingPuntajes, contadorRanking);
            break;
        case 2:
            rlutil::cls();
            // Muestra por pantalla la tabla de ranking actual
            mostrarRanking(rankingNombres, rankingPuntajes, contadorRanking);
            break;
        case 3:
            // Muestra los nombres de los desarrolladores
            mostrarCreditos();
            break;
        case 4:
            explicacionJuego();
            break;
        case 0:
            opcion = confirmarSalida();
            break;
        default:
            // Mensaje para opciones no validas
            cout << "Opcion invalida. Intente de nuevo." << endl;
        }

    }
    while (opcion != 0);

    return 0;
}


