#include <iostream>
#include <string.h>
#include <cstdlib>
#include <time.h>

using namespace std;


int i = 0, j = 0;

//Variables Tablero
const int FILAS = 10, COLUMNAS = 10;
int tabVerificador[FILAS][COLUMNAS] = {0};
int tabMostrar[FILAS][COLUMNAS] = {0};

//Variablas Juego
int cantBombas = 0;

//Estadisticas
int totalJugadores = 0;
int idEst = 1;
int puntaje = 0;

//Casillas no jugadas (Verifica si ha ganado).
int casillasNoJug = 0;

//Estadisticas
struct datoEst {
    int id;
    string nombre;
    int puntos;
} estadisticas[100];


void menuPrincipal();
void crearTablero(int bombas);
void adyacenciaBombas();
void verificadorCeros(int fila, int columna);
void jugar(int fila, int columna);
int estado();
void mostrarTabJugador();
void mostrarTabSolucionado();
void llenarEst (int puntaje, int& idEst);
void getEst ( datoEst v[5], int maxEst);
void resetTab(int v[][10]);

main () {
    menuPrincipal();
}

void menuPrincipal() {
    //LLamada a limpiar tablero
	resetTab(tabVerificador);
	resetTab(tabMostrar);

    int opcUsuario;

    do{
        cout << "\n\n\t 1. Jugar" << endl;
        cout << "\t 2. Ver estadisticas" << endl;
        cout << "\t 3. Salir \n\n\n";
        cout << "Ingrese su opcion: ";
        cin >> opcUsuario;
        cout << "\n________________________\n";

        switch(opcUsuario){
            case 1: system("cls");
                    cantBombas = 0;
                    do{
                        cout << "Ingrese cantidad de bombas (10 Min): " << endl;
                        cin >> cantBombas;
                    } while (cantBombas < 10);

                    //Cantidad de nuevos juegos realizados.
                    totalJugadores++;

                    //Creacion de tablero.
                    crearTablero(cantBombas);
                    adyacenciaBombas();
                    tabVerificador[10][10] = 10, jugar(10, 10);

                break;
            case 2:
                    system("cls");
                    getEst(estadisticas, idEst);
                    do{
                        cout << "\n1) Volver.\n";
                        cin >> opcUsuario;

                    } while(opcUsuario != 1);
                    system("cls");
                    menuPrincipal();
                break;

            case 3: system("exit");
                break;
        }

    } while(opcUsuario <= 0 || opcUsuario > 3);


}

void crearTablero(int bombas) {
    srand(time(0));
    int asd = bombas;

    //Agrega bombas al tablero.
    for( i = 0; i < FILAS-2; i++) {
        for( j = 0; j < COLUMNAS-2; j++ ) {
            if( bombas != 0 && (rand() % 4) % 2 != 0) {
                tabVerificador[i][j] = -1;
                bombas--;
            } else {
                tabVerificador[i][j] = 0;
            }
        }
    }

    //Mezcla los 0 y -1 (bombas) en el tablero.
    for( i = 0; i < FILAS-2; i++ ){
        for( j = 0; j < COLUMNAS-2; j++ ){
            int rand1 = rand() % FILAS/2+4;
            int rand2 = rand() % COLUMNAS/2+3;

            if( tabVerificador[rand1][rand2] == 0 && tabVerificador[i][j] == -1 ) {
                tabVerificador[rand1][rand2] = -1;
                tabVerificador[i][j] = 0;
            }
        }
    }

    //Cargar array con numeros 10, para poder verificar y mostrar distintos tableros.
	for( i = 0; i < FILAS; i++ ) {
		for( j = 0; j < COLUMNAS; j++ ) {
			tabMostrar[i][j] = 10;
		}
	}

    //Bombas al rededor de cada casilla.
    adyacenciaBombas();
}

void adyacenciaBombas() {

    int totalBombasAdyacentes = 0;
    //Agrega la cantidad de bombas adyacentes al tablero.
	for( i = 0; i < FILAS-1; i++ ){
        for( j = 0; j < COLUMNAS-1; j++ ){
            //Si la posicion es una bomba, no se hace nada.
            if( tabVerificador[i][j] == -1 ){
                continue;
            } else {
                //Condiciones para obtener la cantidad de bombas adyacentes a la posicion.
                tabVerificador[i][j+1]    == -1 ? totalBombasAdyacentes++ : 0;
                tabVerificador[i+1][j]    == -1 ? totalBombasAdyacentes++ : 0;
                tabVerificador[i+1][j+1]  == -1 ? totalBombasAdyacentes++ : 0;
                tabVerificador[i-1][j]    == -1 ? totalBombasAdyacentes++ : 0;
                tabVerificador[i-1][j+1]  == -1 ? totalBombasAdyacentes++ : 0;
                tabVerificador[i-1][j-1]  == -1 ? totalBombasAdyacentes++ : 0;
                tabVerificador[i][j-1]    == -1 ? totalBombasAdyacentes++ : 0;
                tabVerificador[i+1][j-1]  == -1 ? totalBombasAdyacentes++ : 0;
            }
                //Ingresa la cantidad de bombas adyacentes a la posicion correspondiente.
                tabVerificador[i][j] = totalBombasAdyacentes;
                totalBombasAdyacentes = 0;
            }
        }
}

/*#############################################
###Apertura del tablero para comenzar a jugar.#
###############################################*/
void verificadorCeros(int fila, int columna) {

    if( tabVerificador[fila][columna] == 0 ) {
    	for( i = 0; i < FILAS; i++ ) {
    		for( j = 0; j < COLUMNAS; j++ ) {

                //Verifica los campos vacios (0, ceros) para agregarlos al tablero de juego(tabMostrar).
    			tabVerificador[i][j+1]    == 0 ? tabMostrar[i][j+1] 	= 0 : 0;
		        tabVerificador[i+1][j]    == 0 ? tabMostrar[i+1][j]		= 0 : 0;
		        tabVerificador[i+1][j+1]  == 0 ? tabMostrar[i+1][j+1] 	= 0 : 0;
		        tabVerificador[i-1][j]    == 0 ? tabMostrar[i-1][j] 	= 0 : 0;
		        tabVerificador[i-1][j+1]  == 0 ? tabMostrar[i-1][j+1] 	= 0 : 0;
		        tabVerificador[i-1][j-1]  == 0 ? tabMostrar[i-1][j-1] 	= 0 : 0;
		        tabVerificador[i][j-1]    == 0 ? tabMostrar[i][j-1] 	= 0 : 0;
		        tabVerificador[i+1][j-1]  == 0 ? tabMostrar[i+1][j-1] 	= 0 : 0;
			}
		}
	}

	for( i = 0; i < FILAS; i++ ) {
        for( j = 0; j < COLUMNAS; j++ ) {
            if( tabMostrar[i][j] == 0)  {

                //Numero de bombas adyacentes a los 0.
                tabVerificador[i][j+1]   > 0 && tabVerificador[i][j+1]   < 10  ? tabMostrar[i][j+1]   = tabVerificador[i][j+1]    : 0;
		        tabVerificador[i+1][j]   > 0 && tabVerificador[i+1][j]   < 10  ? tabMostrar[i+1][j]	  = tabVerificador[i+1][j]    : 0;
		        tabVerificador[i+1][j+1] > 0 && tabVerificador[i+1][j+1] < 10  ? tabMostrar[i+1][j+1] = tabVerificador[i+1][j+1]  : 0;
		        tabVerificador[i-1][j]   > 0 && tabVerificador[i-1][j]   < 10  ? tabMostrar[i-1][j]   = tabVerificador[i-1][j]    : 0;
		        tabVerificador[i-1][j+1] > 0 && tabVerificador[i-1][j+1] < 10  ? tabMostrar[i-1][j+1] = tabVerificador[i-1][j+1]  : 0;
		        tabVerificador[i-1][j-1] > 0 && tabVerificador[i-1][j-1] < 10  ? tabMostrar[i-1][j-1] = tabVerificador[i-1][j-1]  : 0;
		        tabVerificador[i][j-1]   > 0 && tabVerificador[i][j-1]   < 10  ? tabMostrar[i][j-1]   = tabVerificador[i][j-1]    : 0;
		        tabVerificador[i+1][j-1] > 0 && tabVerificador[i+1][j-1] < 10  ? tabMostrar[i+1][j-1] = tabVerificador[i+1][j-1]  : 0;
            }
        }
    }

    //Cuenta cantidad real de bombas en el tablero.
    cantBombas = 0;
    for( i = 0; i < FILAS; i++ ) {
        for( j = 0; j < COLUMNAS; j++ ) {
            if( tabVerificador[i][j] == -1 ) {
                cantBombas++;
            }
        }
    }

}

void mostrarTabSolucionado() {

    //Muestra tablero verificador.
    for( i = 0; i < COLUMNAS-1; i++ ) {
            cout << i << "  ";
        }

    cout << "\n\n";

    for( i = 0; i < FILAS-1; i++ ){
        cout << i << "|  ";
        for( j = 0; j < COLUMNAS-1; j++ ){

            if( tabVerificador[i][j] == -1 )
                cout << "B" << "  ";
            else
                cout << tabVerificador[i][j] << "  ";

        }
        cout << "\n";
    }
}

void mostrarTabJugador() {

    system("cls");
    //Dibujas filas
    cout << "     ";
    for( i = 0; i < FILAS-1; i++ ) {
        cout << i << "  ";
    }

    cout << "\n\n";

    //Dibuja eje Y y tablero.
    for( i = 0; i < FILAS-1; i++ ){
        cout << i << "|  ";
        for( j = 0; j < COLUMNAS-1; j++ ){

            if( tabMostrar[i][j] == 0 ) {
                cout << " 0 ";
            } else {
                if( tabMostrar[i][j] == 10 ) {
                    cout << " - ";
                } else {
                    if( tabMostrar[i][j] > 0 ) {
                        cout << " " << tabVerificador[i][j] << " ";
                    } else {
                        cout << " 0 ";
                    }
                }
            }
        }
        cout << "\n";
    }

    cout << endl << "Bombas en total: " << cantBombas << "\n\n";

}

/*Verifica las casillas no jugadas y las iguala a las cantidad de bombas.*/
int estado() {

    int ganador = 0;
    casillasNoJug = 0;

    for( i = 0; i < FILAS-1; i++ ) {
        for( j = 0; j < COLUMNAS-1; j++ ) {
            if( tabMostrar[i][j] == 10 ) {
                casillasNoJug++;
            }
        }
    }

    casillasNoJug == cantBombas ? ganador = 1 : 0;

    return ganador;
}

void jugar(int fila, int columna) {

    //Condicion para no agregar puntaje en caso de una jugada repetida.
    if( tabMostrar[fila][columna] == 10 ) {
        //Puntajes segun la cantidad de bombas y jugadas realizadas.
        switch( cantBombas ) {

            case 10: case 11: case 12: case 13: case 14: puntaje = puntaje + 50;
                break;
            case 15: case 16: case 17: case 18: case 19: puntaje = puntaje + 51;
                break;
            case 20: puntaje = puntaje + 52;
                break;
            default: puntaje = puntaje + 55;

        }
    }

    //Agrega el valor del tablero original al tablero del jugador.
    tabMostrar[fila][columna] = tabVerificador[fila][columna];

    verificadorCeros(fila, columna);


    if( tabVerificador[fila][columna] == -1 ) {
        system("cls");
        cout << "=========  PERDISTE ===========" << endl;
        cout << "===============================" << endl << "=========  SOLUCION  ==========" << endl << "===============================" << endl;
        cout << "    ";
        mostrarTabSolucionado();

        //Agrega las estadisticas.
        llenarEst(puntaje, idEst);

        //Reseteamos el puntaje por si hay un proximo jugador.
        puntaje = 0;

        menuPrincipal();

    } else {
        mostrarTabJugador();

        //Refresca las casillas no jugadas y verifica si se gano.
        estado();

        if( estado() ) {
            cout << "=================================" << endl << "=========    GANASTE     ========" << endl << "=================================" << endl;

            //Agrega las estadisticas.
            llenarEst(puntaje, idEst);

            //Resetea el puntaje.
            puntaje = 0;

            menuPrincipal();
        } else {

            int x2, y2;

            do{
                cout << "[NUM MAXIMO : " << FILAS - 2 << "]" << "\n__________________________________\n\n";
                cout << "Valor FILA: ";
                cin >> x2;
                cout << "Valor COLUMNA: ";
                cin >> y2;
            } while ( x2 > FILAS - 2 || y2 > COLUMNAS -2 );

            jugar(y2, x2);
        }
    }
}

//Ingresa las puntuaciones
void llenarEst (int puntaje, int& idEst) {

    int puntBaja;
    string nombreAnt;

    cout << "\n===============================\n";
    cout << "PUNTAJE [" << puntaje << "]" << endl;
    cout << "Tu nombre: " << endl;
    cin >> estadisticas[idEst].nombre;
    cout << "===============================\n";

    estadisticas[idEst].puntos = puntaje;

    //Ordena de menor a mayor los puntajes con sus respectivos nombres.
    if(estadisticas[idEst-1].puntos > estadisticas[idEst].puntos) {
        puntBaja = estadisticas[idEst-1].puntos;
        estadisticas[idEst-1].puntos = estadisticas[idEst].puntos;
        estadisticas[idEst].puntos = puntBaja;

        nombreAnt = estadisticas[idEst-1].nombre;
        estadisticas[idEst-1].nombre = estadisticas[idEst].nombre;
        estadisticas[idEst].nombre = nombreAnt;
    }

    idEst++;
}

//Muestra tabla de puntuaciones.
void getEst (datoEst v[5], int maxEst) {

    maxEst > 5 ? maxEst = 5 : 0;

    cout << "Nombre  |       Puntaje" << endl;
    for( i = maxEst-1; i > 0; i-- ) {
        cout << v[i].nombre << "\t  \t" << v[i].puntos << endl;
    }

}

//Resetea valores del tablero para las nuevas jugadas.
void resetTab(int v[][10]) {

	for(i = 0; i < FILAS; i++) {
		for(j = 0; j < COLUMNAS; j++) {
			v[i][j] = 0;
		}
	}

}

