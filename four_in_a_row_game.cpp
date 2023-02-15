// Created 15/02/2023 with help of @rubennmatey
#include <iostream>
#include <cstdlib>
using namespace std;

const int MAX_COLUMNAS = 7;
const int MAX_FILAS = 6;
const char VACIO = 196;
const char ROJO = 219;
const char BLANCO = 178;

typedef enum { rojo, blanco, vacio }tJugadores;
typedef tJugadores tMatriz[MAX_FILAS][MAX_COLUMNAS];

void inicializarJuego(tMatriz matriz);
int colocarFicha(tMatriz matriz, int columna, tJugadores jugador);
void presentarTablero(tMatriz matriz);
bool comprobarGanador(tMatriz matriz, int fila, int columna);

bool comprobarHorizontal(tMatriz matriz, int fila, int columna, tJugadores jugador);
bool comprobarVertical(tMatriz matriz, int fila, int columna, tJugadores jugador);
bool comprobarDiagonal(tMatriz matriz, int fila, int columna, tJugadores jugador);

string tJugadorAString(tJugadores jugador);

int main() {
	tMatriz tablero;
	inicializarJuego(tablero);

	bool gana = false;
	tJugadores jugadorActual = rojo;
	presentarTablero(tablero);
	while (!gana) {
		cout << "Le toca al jugador " << tJugadorAString(jugadorActual) << endl;

		int fila;
		int columna;
		do {
			cout << "Introduce una columna del 1 al 7: ";
			cin >> columna;
			columna--;
			fila = colocarFicha(tablero, columna, jugadorActual);
		} while (fila >= MAX_FILAS);

		system("cls");
		presentarTablero(tablero);
		gana = comprobarGanador(tablero, fila, columna);
		if (gana) {
			cout << "Gana el jugador " << tJugadorAString(jugadorActual) << endl;
		}
		if (jugadorActual == rojo) jugadorActual = blanco;
		else jugadorActual = rojo;
	}
	return 0;
}

void inicializarJuego(tMatriz matriz) {
	for (int i = 0; i < MAX_FILAS; i++) {
		for (int j = 0; j < MAX_COLUMNAS; j++) {
			matriz[i][j] = vacio;
		}
	}
}

int colocarFicha(tMatriz matriz, int columna, tJugadores jugador) {
	int i = 1;
	if (matriz[0][columna] != vacio) {
		cout << "Columna llena" << endl;
	}
	else {
		while (matriz[i][columna] == vacio && i < MAX_FILAS) {
			i++;
		}
		matriz[i-1][columna] = jugador;
	}
	return i-1;
}

void presentarTablero(tMatriz matriz) {
	for (int i = 0; i < MAX_FILAS; i++) {
		for (int j = 0; j < MAX_COLUMNAS; j++) {
			if (matriz[i][j] == rojo) {
				cout << ROJO; 
			}
			else if(matriz[i][j] == blanco){
				cout << BLANCO;

			}
			else {
				cout << VACIO;
			}
			cout << " ";
		}
		cout << endl;
	}
}

bool comprobarGanador(tMatriz matriz, int fila, int columna) {
	tJugadores jugador = matriz[fila][columna];
	bool gana = false;
	gana = comprobarHorizontal(matriz, fila, columna, jugador) || comprobarVertical(matriz, fila, columna, jugador) || comprobarDiagonal(matriz, fila, columna, jugador);
	return gana;
}

bool comprobarHorizontal(tMatriz matriz, int fila, int columna, tJugadores jugador) {
	bool gana = false;
	int contador = 1;
	int i = 1;
	while (contador != 4 && matriz[fila][columna - i] == jugador && columna - i >= 0) {
		i++;
		contador++;
	}
	while (contador != 4 && matriz[fila][columna + i] == jugador && columna + i <= MAX_COLUMNAS) {
		i++;
		contador++;
	}
	if (contador == 4) gana = true;
	return gana;
}

bool comprobarVertical(tMatriz matriz, int fila, int columna, tJugadores jugador) {
	bool gana = false;
	int contador = 1;
	int i = 1;
	while (contador != 4 && matriz[fila + i][columna] == jugador && fila + i <= MAX_FILAS) {
		i++;
		contador++;
	}
	if (contador == 4) gana = true;
	return gana;
}

bool comprobarDiagonalCreciente(tMatriz matriz, int fila, int columna, tJugadores jugador) {
	bool gana = false;
	int contador = 1;
	int i = 1;
	while (contador != 4 && matriz[fila + i][columna - i] == jugador && columna - i >= 0 && fila - i <= MAX_FILAS) {
		i++;
		contador++;
	}
	while (contador != 4 && matriz[fila - i][columna + i] == jugador && columna + i <= MAX_COLUMNAS && fila + i <= 0) {
		i++;
		contador++;
	}
	if (contador == 4) gana = true;
	return gana;
}

bool comprobarDiagonalDecreciente(tMatriz matriz, int fila, int columna, tJugadores jugador) {
	bool gana = false;
	int contador = 1;
	int i = 1;
	while (contador != 4 && matriz[fila - i][columna - i] == jugador && columna - i >= 0 && fila - i >= 0) {
		i++;
		contador++;
	}
	while (contador != 4 && matriz[fila + i][columna + i] == jugador && columna + i <= MAX_COLUMNAS && fila + i <= MAX_FILAS) {
		i++;
		contador++;
	}
	if (contador == 4) gana = true;
	return gana;
}

bool comprobarDiagonal(tMatriz matriz, int fila, int columna, tJugadores jugador) {
	return comprobarDiagonalCreciente(matriz, fila, columna, jugador) || comprobarDiagonalDecreciente(matriz, fila, columna, jugador);
}

string tJugadorAString(tJugadores jugador) {
	string resultado;
	if (jugador == rojo) resultado = "rojo";
	else resultado = "blanco";
	return resultado;
}
