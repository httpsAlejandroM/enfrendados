#include <iostream>
#include <string>
#include "DeclaracionFunciones.h"
#include "rlutil.h"
using namespace std;


// Funcion principal para organizar una partida. Se encarga de:
// 1) Solicitar e ingresar los nombres de ambos jugadores.
// 2) Determinar cual jugador comienza primero lanzando un dado para cada uno.
// 3) Iniciar todas las rondas del juego utilizando el orden definido, junto con la tabla de ranking para guardar nombres y puntajes al finalizar.
// Parametros:
// string rankingNombres[]: Vector de nombres para guardar en la tabla de ranking.
// int rankingPuntajes[]: Vector de puntajes para guardar en la tabla de ranking.
// int &contadorRanking: Referencia al contador que almacena la cantidad de registros actuales en el ranking.
void jugar(string rankingNombres[], int rankingPuntajes[], int &contadorRanking)
{
    // Variables para guardar los nombres de los jugadores
    // 'ordenJugadores' almacena el turno de cada uno (el que comienza primero siempre en la posicion 0).
    string jugador1, jugador2, ordenJugadores[2];

    // Solicita al usuario que ingrese los nombres de ambos jugadores
    ingresarNombres(jugador1, jugador2);

    // Determina cual jugador comienza primero lanzando un dado para cada uno, guardando el orden en el array 'ordenJugadores'
    determinarJugadorInicial(jugador1, jugador2, ordenJugadores);

    // Da inicio a todas las rondas del juego, utilizando el orden definido y recibe los arreglos de ranking para guardar los puntajes al finalizar.
    iniciarRonda(ordenJugadores, rankingNombres, rankingPuntajes, contadorRanking);
}

// Ingresa los nombres de ambos jugadores para la partida.
// Parametros:
// string &jugador1: Referencia a la variable que almacena el nombre del Jugador 1.
// string &jugador2: Referencia a la variable que almacena el nombre del Jugador 2.
void ingresarNombres(string &jugador1, string &jugador2)
{
    // Solicita al usuario que ingrese el nombre de los jugadores
    rlutil::locate(40, 15);
    cout << "Ingresar nombre Jugador 1: ";
    cin >> jugador1; //Almacena el valor en la referencia recibida por parametro

    rlutil::cls();
    rlutil::locate(40, 15);
    cout << "Ingresar nombre Jugador 2: ";
    cin >> jugador2; //Almacena el valor en la referencia recibida por parametro
    cout << endl << endl;
    rlutil::cls();
}

// Determina cual jugador comienza primero lanzando un dado de 6 caras para cada uno.
// Si hay empate, la operacion se repite hasta obtener un ganador.
// Parametros:
// string jugador1: Nombre del Jugador 1.
// string jugador2: Nombre del Jugador 2.
// string ordenJugadores[]: Vector donde se almacena el orden de turno:
// ordenJugadores[0]         posicion 0 para el que comienza primero,
// ordenJugadores[1]         posicion 1 para el que juega en segundo lugar.
void determinarJugadorInicial(string jugador1, string jugador2, string ordenJugadores[])
{
    int dado1, dado2;
    rlutil::hidecursor(); // esconder el puntero
    // Se repite la operacion mientras ambos jugadores saquen el mismo valor en el dado
    do
    {
        rlutil::locate(28, 14);
        cout << jugador1 << " y " << jugador2 << " tiran un dado de 6 caras para ver quien comienza " << endl;
        dado1 = tirarDado();
        dado2 = tirarDado();

        rlutil::msleep(2000);

        rlutil::locate(30, 18);
        cout << jugador1 << " saca: " << dado1 << endl;

        rlutil::locate(70, 18);
        cout << jugador2 << " saca: " << dado2 << endl;

        rlutil::msleep(2500);
        rlutil::cls();
        if (dado1 > dado2) // Si dado1 es mayor que dado2, jugador1 comienza primero
        {
            rlutil::locate(44, 14);
            cout << jugador1 << " comienza la partida." << endl;
            ordenJugadores[0] = jugador1;
            ordenJugadores[1] = jugador2;
            rlutil::msleep(1500);
            rlutil::cls();
        } else if (dado2 > dado1) // Si dado2 es mayor que dado1, jugador2 comienza primero
         {
            rlutil::locate(44, 14);
            cout << jugador2 << " comienza la partida." << endl;
            ordenJugadores[0] = jugador2;
            ordenJugadores[1] = jugador1;
            rlutil::msleep(1500);
            rlutil::cls();
        } else {  // Si hay empate, se vuelve a tirar para decidir

            rlutil::locate(45, 14);
            cout << "Empate. Se vuelve a tirar." << endl;
            rlutil::msleep(1500);
            rlutil::cls();
        }
    } while (dado1 == dado2);
}


// Inicia todas las rondas del juego (hasta un maximo de 3), donde ambos jugadores participan por turno.
// El flujo de cada ronda es:
// 1) Se anuncia la ronda actual.
// 2) El primer jugador realiza su turno, lanzando dados para alcanzar el numero objetivo e intentar obtener puntos.
// 3) Si no hay victoria automatica, el segundo jugador realiza su turno.
// 4) Se verifica si quedan dados para continuar; si no, la partida finaliza antes de la tercera ronda.
// Al finalizar todas las rondas (o si un jugador se queda sin dados),
// se muestran los resultados finales y se actualiza el ranking correspondiente.
//
// Parametros:
// string ordenJugadores[]: Array de nombres de jugadores en el orden en que participan.
// string rankingNombres[]: Array donde almacena los nombres para la tabla de ranking.
// int rankingPuntajes[]: Array donde almacena los puntajes para la tabla de ranking.
// int &contadorRanking: Referencia al contador de registros actuales en la tabla de ranking.
void iniciarRonda(string ordenJugadores[], string rankingNombres[], int rankingPuntajes[], int &contadorRanking)
{
    int ronda = 1;
    int dadosStockJ1[11] = {0}, dadosStockJ2[11] = {0}; //Vector de 11 posiciones, representa el maximo de dados que un jugador puede tener
    int cantDadosJ1 = 6, cantDadosJ2 = 6; //Cantidad actual de dados de cada jugador
    int cantDadosSeleccionados = 0; //Contador de cantidad de dados que el jugador eligio sumar (cantDadosSeleccionados)
    int dadosSeleccionados[11] = {0}; //vector de posiciones de dados seleccionados
    int sumaSeleccionada = 0; //Suma de la combinacion de dados elegida por el jugador
    int puntajeJ1 = 0, puntajeJ2 = 0; //Puntajes de los jugadores

    //Se juega mientras no hayan alcanzado 3 rondas y ambos jugadores tengan al menos un dado
    while (ronda <= 3 && cantDadosJ1 > 0 && cantDadosJ2 > 0)
    {
        // Anunciar la ronda actual
        anunciadorRondas(ronda);

        // El primer jugador realiza su turno
        iniciarTurno(ordenJugadores[0], ordenJugadores[1], dadosStockJ1, cantDadosJ1, cantDadosSeleccionados, dadosSeleccionados, sumaSeleccionada, puntajeJ1, cantDadosJ2);

        // Si un jugador alcanza la victoria automatica (0 dados restantes), finaliza la partida
        if (cantDadosJ1 == 0 || cantDadosJ2 == 0){break;}

        anunciadorRondas(ronda);
        // El segundo jugador realiza su turno
        iniciarTurno(ordenJugadores[1], ordenJugadores[0], dadosStockJ2, cantDadosJ2, cantDadosSeleccionados, dadosSeleccionados, sumaSeleccionada, puntajeJ2, cantDadosJ1);
        ronda++;
    }
    // Al finalizar todas las rondas o alcanzarse una victoria automatica se muestran los resultados finales
    mostrarResultadosFinales(ordenJugadores[0], ordenJugadores[1], puntajeJ1, puntajeJ2, cantDadosJ1, cantDadosJ2);

    // Se guardan los resultados en la tabla de ranking correspondiente
    manejadorResultadosRanking(ordenJugadores[0], ordenJugadores[1], puntajeJ1, puntajeJ2, rankingNombres, rankingPuntajes, contadorRanking);
}


// Inicia un turno para un jugador especifico, donde:
// 1) Se obtiene un numero objetivo al lanzar dos dados de 12 caras.
// 2) Se lanzan los dados actuales del jugador para determinar que combinaciones usar para alcanzar el objetivo.
// 3) Se evalua si la tirada es exitosa, sumando puntaje correspondiente y transfiriendo dados al oponente si aplica.
// Parametros:
// string jugador1: Nombre del jugador que realiza el turno.
// string jugador2: Nombre del oponente.
// int dadosStock[]: Vector de 11 posiciones que almacena los dados actuales (nros aleatorios y 0) del jugador que realiza su turno
// int &cantDados: Referencia a la cantidad de dados actuales del jugador activo. (determina hasta donde iterar el vector de dados stock)
// int &cantDadosSeleccionados: Referencia a la cantidad de dados seleccionados para alcanzar el objetivo.
// int dadosSeleccionados[]: Vector donde se guardan los dados seleccionados para alcanzar el objetivo.
// int &sumaSeleccionada: Referencia a la sumatoria de los dados seleccionados para alcanzar el objetivo.
// int &puntaje: Referencia al puntaje acumulado del jugador activo.
// int &cantDadosJ2: Referencia a la cantidad de dados actuales del jugador oponente.
void iniciarTurno(string jugador1, string jugador2, int dadosStock[], int &cantDados, int &cantDadosSeleccionados, int dadosSeleccionados[], int &sumaSeleccionada, int &puntaje, int &cantDadosJ2)
{
    int nroObjetivo;
    bool tiradaExitosa;

    rlutil::showcursor(); //mostrar cursor
    rlutil::locate(53, 5);
    cout << "\t \t \t \t \t \t \t \t \t \t \t \t ";
    rlutil::locate(53, 5);
    cout << "Turno de " << jugador1 << endl << endl;

    // El jugador lanza dos dados de 12 caras para obtener el numero objetivo
    nroObjetivo = tirarDadoObjetivo();
    //Muestra el numero objetivo obtenido
    mostrarNroObjetivo(nroObjetivo, jugador1);

    // El jugador lanza sus dados actuales para intentar alcanzar el objetivo
    tirarDadosStock(dadosStock, cantDados);
    //Muestra los dados obtenidos
    mostrarDadosStock(dadosStock, cantDados);

    // El jugador selecciona los dados para intentar alcanzar el objetivo
    seleccionarDados(dadosStock, cantDados, cantDadosSeleccionados, dadosSeleccionados, sumaSeleccionada);

    // Se verifica si la seleccion alcanzo correctamente el numero objetivo
    tiradaExitosa = identificarTiradaExitosa(jugador1, sumaSeleccionada, nroObjetivo);

    // Se muestran los puntos alcanzados en este turno
    mostrarPuntosDelTurno(jugador1, tiradaExitosa, cantDadosSeleccionados, sumaSeleccionada, puntaje, cantDados );

    // Se transfieren dados al oponente o se reciben dados, segun corresponda
    transferirDados(jugador1, jugador2, cantDados, cantDadosJ2, cantDadosSeleccionados, tiradaExitosa);
}

// Lanza un dado de 6 caras y retorna un valor entero entre 1 y 6.
int tirarDado()
{
    return rand() % 6 + 1;
}

// Lanza un dado de 12 caras y retorna un valor entero entre 1 y 12.
int tirarDado12()
{
    return rand() % 12 + 1;
}

/// Tira dos dados de 12 caras y retorna la suma
int tirarDadoObjetivo()
{
    rlutil::locate(36, 7);
    cout << "Presione una tecla para tirar dados objetivo..." << endl;
    rlutil::anykey();
    rlutil::locate(36, 7);
    cout << "\t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t " << endl  << endl;
    int dado1 = tirarDado12();
    int dado2 = tirarDado12();

    return dado1 + dado2;
}

// Muestra por pantalla el nro objetivo
void mostrarNroObjetivo(int nroObjetivo, string jugador){
    rlutil::locate(42, 7);
    cout << "\t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t ";
    rlutil::locate(42, 7);
    cout << "   El numero objetivo de " << jugador << " es " << nroObjetivo;
}

// Parametros:
// int dadosStock[]: Vector de 11 posiciones que representa la cantidad maxima de dados que un jugador puede tener en su stock
// int cantidad: Representa la cantidad actual de dados del jugador
void tirarDadosStock(int dadosStock[], int cantidad)
{
    rlutil::locate(53, 9);
    //Mostramos por pantalla la cantidad actual de dados usando la variable cantidad
    cout << "Stock actual: " << cantidad << endl;
    rlutil::locate(36, 11);
    cout << "Presione una tecla para tirar sus dados stock..." << endl  << endl;
    //rlutil::anykey() pone en pause el programa hasta que se presione una tecla
    rlutil::anykey();
    rlutil::locate(36, 11);
    cout << "\t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t " << endl  << endl;

    // Recorremos el array de dadosStock hasta la posición definida por 'cantidad',
    for (int i = 0; i < cantidad; i++)
    {
    //En cada iteracion al vector dadosStock le asignamos el numero aleatorio del 1 al 6 que nos retorna la funcion tirarDado();
        dadosStock[i] = tirarDado();
    }
}


// Muestra por pantalla todos los dados actuales (stock) de un jugador, numerandolos para que el usuario pueda seleccionarlos posteriormente.
// Parametros:
// int dadosStock[]: Vector que almacena los valores actuales de los dados del jugador. Recibe los valores de la funcion iniciarTurno --
// int cantDados: Cantidad actual de dados en el stock del jugador.
void mostrarDadosStock(int dadosStock[], int cantDados)
{
    int columnas = rlutil::tcols(); //cuenta el ancho de la consola, las columnas
    int totalItems = cantDados + 1;
    int anchoItem = 6;

    int espaciosRestantes = columnas - (totalItems * anchoItem);
    int espaciado = espaciosRestantes / (totalItems + 1);

    int ejeX = 0;
    int ejeY = 17;

    for (int i = 0; i < cantDados; i++)
    {
        ejeX += anchoItem + espaciado;
        rlutil::locate(ejeX, ejeY);
        cout << i + 1 << ". [" << dadosStock[i] << "]";
    }
    cout << endl << endl;
}

// Permite al jugador seleccionar uno o varios dados de su stock para intentar alcanzar el numero objetivo.
// El usuario ingresa el indice del dado que quiere seleccionar (1 a cantDados), y `0` para finalizar la seleccion.
// Se valida que no pueda seleccionar el mismo dado dos veces ni un indice fuera de rango.
// Al finalizar, muestra la combinacion elegida junto con la sumatoria total alcanzada.
//
// Parametros:
// int dadosStock[]: Array con los valores actuales de los dados del jugador.
// int cantDados: Cantidad de dados actuales en el stock del jugador.
// int &cantDadosSeleccionados: Referencia al contador de dados seleccionados para esta jugada.
// int dadosSeleccionados[]: Array que almacena los indices de los dados seleccionados.
// int &sumaSeleccionada: Referencia a la variable donde se almacena la suma total de los dados seleccionados.
void seleccionarDados(int dadosStock[], int cantDados, int &cantDadosSeleccionados, int dadosSeleccionados[], int &sumaSeleccionada)
{
    int opcion;
    bool fueSeleccionado = false;

    rlutil::locate(34, 23);
    // Solicita al usuario que elija cuales dados quiere seleccionar para alcanzar el numero objetivo
    cout << "Elija que dados quiere sumar y 0 para terminar de elegir" << endl;
    rlutil::locate(34, 27);
    cout << "Seleccionar: ";
    cin >> opcion;
    rlutil::locate(34, 27);
    cout << "\t \t \t \t \t \t \t";

    while (opcion > 0)
    {
        fueSeleccionado = yaFueSeleccionado(opcion, dadosSeleccionados, cantDadosSeleccionados);
        // Verifica que el dado seleccionado no se haya utilizado anteriormente
        if(fueSeleccionado){
            rlutil::locate(34, 25);
            cout << "No puede seleccionar el mismo dado, intente nuevamente";
            rlutil::locate(34, 27);
            cout << "Seleccionar: ";
            cin >> opcion;
            rlutil::locate(34, 27);
            cout << "\t \t \t \t \t \t \t";
        }
        // Verifica que la posicion seleccionada no exceda la cantidad de dados disponibles
        else if (opcion > cantDados){
            rlutil::locate(34, 25);
            cout << "Opcion invalida, intente nuevamente  \t \t \t \t \t \t \t";
            rlutil::locate(34, 27);
            cout << "Seleccionar: ";
            cin >> opcion;
            rlutil::locate(34, 27);
            cout << "\t \t \t \t \t \t \t";
        } else {
        // Al seleccionar un dado valido (1 al 11), aumenta el contador de dados seleccionados,
        // almacena el indice en 'dadosSeleccionados' y aumenta la 'sumaSeleccionada' correspondiente
            switch (opcion)
        {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            cantDadosSeleccionados++; //Aumenta el contador de dados seleccionados
            dadosSeleccionados[cantDadosSeleccionados - 1] = opcion; //Almacena el indice en 'dadosSeleccionados'
            sumaSeleccionada += dadosStock[opcion - 1]; // Aumenta la 'sumaSeleccionada' correspondiente
            rlutil::locate(34, 25);
            cout << "\t \t \t \t \t \t \t";
            rlutil::locate(34, 25);
            cout << "Suma seleccionada: " << sumaSeleccionada << endl;
            break;
        // Por defecto, si la opcion no es valida
        default:
            rlutil::locate(34, 25);
            cout << "Opcion invalida, intente nuevamente \t \t \t \t \t \t \t \t " << endl;
            break;
        }
        // Solicita nuevamente la seleccion al usuario
        rlutil::locate(34, 27);
        cout << "Seleccionar: ";
        cin >> opcion;
        rlutil::locate(34, 27);
        cout << "\t \t \t \t \t \t \t";
        }

    }

    // Al finalizar la seleccion, muestra la combinacion elegida junto con la suma alcanzada
    rlutil::locate(34, 25);
    cout << "Combinacion elegida: ";
    mostrarCombinacionElegida(dadosSeleccionados, dadosStock, cantDadosSeleccionados);
    cout << sumaSeleccionada << "\t \t \t \t \t \t \t \t \t \t \t \t ";

     rlutil::locate(34, 27);
     cout << "Presione una tecla para continuar...";
     rlutil::anykey();
     rlutil::cls();

}

// Verifica si un dado especifico (identificado por su posicion) ya fue seleccionado previamente por el jugador.
// Parametros:
// int opcion: Numero de posicion del dado a verificar.
// int dadosSeleccionados[]: Array que almacena las posiciones de dados que fueron seleccionadas.
// int cantDadosSeleccionados: Cantidad de dados seleccionados hasta el momento.
// Retorna:`true` si el dado ya fue seleccionado, `false` si no lo fue.
bool yaFueSeleccionado(int opcion, int dadosSeleccionados[], int cantDadosSeleccionados){

    bool fueSeleccionado = false;
    // Recorre todas las opciones seleccionadas para verificar si alguna coincide con la posicion recibida
    for(int i = 0; i < cantDadosSeleccionados ;i++){
      if(opcion == dadosSeleccionados[i]){
        fueSeleccionado = true;
      }
    }

    return fueSeleccionado;
}

// Imprime por pantalla la combinacion de dados seleccionados por el jugador para intentar alcanzar el numero objetivo.
// Parametros:
// int dadosSeleccionados[]: Array con las posiciones de los dados seleccionados por el jugador.
// int dadosStock[]: Array que almacena los valores actuales de los dados del jugador.
// int cantDadosSeleccionados: Cantidad de dados seleccionados para esta jugada.
void mostrarCombinacionElegida(int dadosSeleccionados[], int dadosStock[], int cantDadosSeleccionados){

    // Recorre todas las posiciones de dados seleccionados para mostrar su valor correspondiente en dadosStock
    for (int i = 0; i < cantDadosSeleccionados; i++){

        if (i == cantDadosSeleccionados - 1){ // Si es el ultimo dado seleccionado, finaliza con " = "
            cout << dadosStock[dadosSeleccionados[i] - 1] << " = ";
        }
        else{ // Si no es el ultimo dado, a�ade " + " para indicar que la operacion sigue
            cout << dadosStock[dadosSeleccionados[i] - 1] << " + ";
        }
    }
}

// Verifica si la suma de dados seleccionados por el jugador es igual al numero objetivo.
// Parametros:
// string jugador: Nombre del jugador que realizo la tirada.
// int sumaSeleccionada: Resultado de la suma de los dados seleccionados por el jugador.
// int nroObjetivo: Numero objetivo a alcanzar para considerar la tirada como exitosa.
bool identificarTiradaExitosa(string jugador, int sumaSeleccionada, int nroObjetivo)
{
    bool tiradaExitosa;
    tiradaExitosa = sumaSeleccionada == nroObjetivo;

    if(tiradaExitosa){
        rlutil::locate(45, 5);
        cout << jugador << " logra una tirada exitosa" << endl;
    } else {
        rlutil::locate(42, 5);
        cout << jugador << " no logra una tirada exitosa" << endl;

    }

    return tiradaExitosa;
}

// Muestra e incrementa el puntaje total del jugador correspondiente al turno actual.
// Si la tirada es exitosa, el puntaje del turno es igual a la cantidad de dados seleccionados multiplicada por la suma alcanzada.
// Si el jugador usa todos los dados en la jugada, recibe un bonus adicional de 10,000 puntos.
// Si la tirada falla, no recibe puntos en esta ronda.
// Finalmente, reinicia la variable de `sumaSeleccionada` para la siguiente jugada.
// Parametros:
// string jugador: Nombre del jugador al que corresponden los puntos.
// bool tiradaExitosa: Resultado de la tirada actual (verdadero si alcanzo el numero objetivo).
// int cantDadosSeleccionados: Cantidad de dados usados para alcanzar el objetivo.
// int &sumaSeleccionada: Referencia al valor de la suma alcanzada por los dados seleccionados.
// int &puntaje: Referencia al puntaje total acumulado del jugador correspondiente.
// int cantDados: Cantidad total de dados actuales en el turno.
void mostrarPuntosDelTurno(string jugador, bool tiradaExitosa, int cantDadosSeleccionados, int &sumaSeleccionada, int &puntaje, int cantDados){

    int puntajeTurno = 0;
    // Si la tirada es exitosa
    if(tiradaExitosa){
        // El puntaje de turno es la suma alcanzada multiplicada por la cantidad de dados seleccionados
       puntajeTurno = sumaSeleccionada * cantDadosSeleccionados;

        // Se acumula al puntaje total
       puntaje += puntajeTurno;

        // Si uso todos los dados disponibles, recibe un bonus de 10,000 puntos
       if(cantDados == cantDadosSeleccionados){
        puntaje += 10000; // Se suma el bonus de 10000
            rlutil::locate(14, 7);
            cout << " usa todos los dados, obtiene " << puntajeTurno << " puntos + 10.000 de bonus, sumando un total de " << puntaje << " puntos." <<  endl << endl;
       }
       // Si no uso todos los dados disponibles suma solo los puntos del turno
       else {
        rlutil::locate(27, 7);
           cout << " consigue " << puntajeTurno << " puntos en esta ronda, sumando un total de " << puntaje << " puntos" <<  endl << endl;
       }

    }
     // Si falla la tirada, no recibe puntos
    else {
        rlutil::locate(29, 7);
        cout << " no suma puntos en esta ronda, mantiene un total de " << puntaje << " puntos" << endl << endl;
    }

    sumaSeleccionada = 0; //Se reinicia el valor de suma seleccionada para el siguiente turno
}

// Realiza la transferencia de dados entre jugadores segun el resultado de la tirada.
// Si la tirada es exitosa, el jugador activo transfiere la cantidad de dados seleccionados al oponente.
// Si esta accion hace que el jugador activo se quede sin dados, gana automaticamente la partida.
// Si la tirada falla, recibe un dado del oponente (si este ultimo tiene mas de 1 dado).
// Parametros:
// string jugador1: Nombre del jugador activo en el turno actual.
// string jugador2: Nombre del oponente.
// int &cantDadosJ1: Referencia a la cantidad de dados actuales del jugador activo.
// int &cantDadosJ2: Referencia a la cantidad de dados actuales del oponente.
// int &cantDadosSeleccionados: Referencia a la cantidad de dados seleccionados en esta jugada.
// bool &tiradaExitosa: Referencia al indicador de exito de la tirada actual.
void transferirDados(string jugador1, string jugador2, int &cantDadosJ1, int &cantDadosJ2, int &cantDadosSeleccionados, bool &tiradaExitosa){

    // Si la tirada es exitosa
    if(tiradaExitosa){
        // El jugador activo pierde los dados seleccionados
        cantDadosJ1 = cantDadosJ1 - cantDadosSeleccionados;

        // El oponente recibe esos dados
        cantDadosJ2 = cantDadosJ2 + cantDadosSeleccionados;

        // Si el jugador activo se queda sin dados, gana la partida automaticamente
        if(cantDadosJ1 == 0){
            rlutil::locate(28, 9);
            cout << "transfiere todos sus dados a " << jugador2 << " y logra una victoria automatica";

            rlutil::locate(42, 25);
            cout << "Presione una tecla para continuar...";
            rlutil::anykey();
            rlutil::cls();
        }
        // En caso de no obtener una victoria automatica se muestran los dados transferidos y stock de cada jugador
        else {
            rlutil::locate(45, 9);
            cout << "y transfiere " << cantDadosSeleccionados << " dados a " << jugador2 ;

            rlutil::locate(30, 12);
            cout << jugador1 << ": " << cantDadosJ1 << " dados stock";

            rlutil::locate(70, 12);
            cout << jugador2 << ": " << cantDadosJ2 << " dados stock";

            rlutil::locate(42, 25);
            cout << "Presione una tecla para continuar...";
            rlutil::anykey();
            rlutil::cls();
        }
    }
    // Si falla la tirada y el oponente tiene mas de 1 dado, este ultimo pierde un dado que recibe el jugador activo
    else if (cantDadosJ2 > 1) {
        cantDadosJ1 = cantDadosJ1 + 1;
        cantDadosJ2 = cantDadosJ2 - 1;
        rlutil::locate(48, 9);
        cout << "y recibe un dado de " << jugador2;

        rlutil::locate(25, 12);
        cout << jugador1 << ": " << cantDadosJ1 << " dados stock";

        rlutil::locate(75, 12);
        cout << jugador2 << ": " << cantDadosJ2 << " dados stock";

        rlutil::locate(42, 25);
        cout << "Presione una tecla para continuar...";
        rlutil::anykey();
        rlutil::cls();
    }
    // Reinicia los datos para la proxima jugada
    cantDadosSeleccionados = 0;
    tiradaExitosa = false;
}

//Muestra por pantalla los resultados finalesy el ganador de la partida
void mostrarResultadosFinales(string jugador1, string jugador2, int puntosJ1, int puntosJ2, int cantDadosJ1, int cantDadosJ2){
    string ganador;
    int puntajeGanador;

    int ejeXJugador = 16;
    int ejeXPuntos = 57;
    int ejeXDados = 94;

    rlutil::locate(ejeXJugador, 12);
    cout << "JUGADOR";

    rlutil::locate(ejeXPuntos, 12);
    cout << "PUNTOS";

    rlutil::locate(ejeXDados, 12);
    cout << "DADOS STOCK";

    rlutil::locate(ejeXJugador, 13);
    cout << "-----------------------------------------------------------------------------------------";
    // Determina cual jugador alcanza el puntaje mas alto, lo asigna como ganador y lo posiciona arriba en la tabla
    if (puntosJ1 > puntosJ2){
        ganador = jugador1;
        puntajeGanador = puntosJ1;
        rlutil::locate(ejeXJugador, 15);
        cout << jugador1 ;

        rlutil::locate(ejeXPuntos, 15);
        cout << puntosJ1;

        rlutil::locate(ejeXDados, 15);
        cout << cantDadosJ1 << " dados";

        rlutil::locate(ejeXJugador, 16);
        cout << jugador2;

        rlutil::locate(ejeXPuntos, 16);
        cout << puntosJ2;

        rlutil::locate(ejeXDados, 16);
        cout << cantDadosJ2 << " dados";

        // Anuncia al ganador de la partida junto con su puntaje
        rlutil::locate(30, 5);
        cout << "El ganador de la partida es " << ganador << " con un total de " << puntajeGanador << " puntos"  << endl << endl;
    } else {
        ganador = jugador2;
        puntajeGanador = puntosJ2;

        rlutil::locate(ejeXJugador, 14);
        cout << jugador2;

        rlutil::locate(ejeXPuntos, 14);
        cout << puntosJ2;

        rlutil::locate(ejeXDados, 14);
        cout << cantDadosJ2 << " dados";

        rlutil::locate(ejeXJugador, 15);
        cout << jugador1 ;

        rlutil::locate(ejeXPuntos, 15);
        cout << puntosJ1;

        rlutil::locate(ejeXDados, 15);
        cout << cantDadosJ1 << " dados";

        // Anuncia al ganador de la partida junto con su puntaje
        rlutil::locate(30, 5);
        cout << "El ganador de la partida es " << ganador << " con un total de " << puntajeGanador << " puntos"  << endl << endl;
    }

     rlutil::locate(30, 24);
    rlutil::anykey("Presione una tecla para volver al menu principal...");
    rlutil::cls();

}

int confirmarSalida() {
     rlutil::cls();
    char confirmaSalida;
    do {

        rlutil::locate(32, 15);
        cout << "Esta seguro que desea salir? Ingrese 's'(SI) o 'n'(NO): ";
        cin >> confirmaSalida;
        if (confirmaSalida == 's' || confirmaSalida == 'S') {
            rlutil::locate(53, 20);
            cout << "Vuelva pronto!" << endl <<endl;
            return 0;
            } else if (confirmaSalida == 'n'|| confirmaSalida == 'N') {
            rlutil::cls();
            return 1;
        } else {
           rlutil::locate(32, 15);
           cout << "Esta seguro que desea salir? Ingrese 's'(SI) o 'n'(NO):  "; //pisa la letra invalida que se ingreso dandole un espacio mas en la misma posicion 32 15
           rlutil::locate(43, 18);
           cout << "No es opcion, seleccione 's' o 'n'" << endl;
        }
    } while (confirmaSalida != 's' && confirmaSalida != 'S' && confirmaSalida != 'n' && confirmaSalida != 'N');
}






