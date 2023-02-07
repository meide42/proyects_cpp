#include <iostream>
#include <windows.h>
#include <cstdlib>
using namespace std;

const int FILAS = 20;
const int COLUMNAS = 20;
const int CENTINELA = -1;
const int MAX_GENERACIONES = 50;
const unsigned int DELAY = 100;
const char ON = 219;
const char OFF = 240;

typedef bool tMatriz[FILAS][COLUMNAS];
typedef enum { nace, sobrevive, muere } tEstado;

void cargar(tMatriz matriz);
void actualizar(tMatriz matriz);
tEstado comprobarEstado(tMatriz matriz, int x, int y);
void copiar(tMatriz matrizDestino, tMatriz matrizOrigen);
void mostrar(tMatriz matriz);

int main() {
    system("chcp 850");
    tMatriz matriz = { false };
    cargar(matriz);
    mostrar(matriz);
    Sleep(DELAY);
    system("CLS");
    for (int generacion = 0; generacion < MAX_GENERACIONES; generacion++) {
        actualizar(matriz);
        mostrar(matriz);
        Sleep(DELAY);
        system("CLS");
    }
}
void cargar(tMatriz matriz) {
    int x, y;
    cin >> x >> y;
    while (x != CENTINELA && y != CENTINELA) {
        matriz[x][y] = true;
        cin >> x >> y;
    }
}

void actualizar(tMatriz matriz) {
    tMatriz siguienteEstado;
    copiar(siguienteEstado, matriz);

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            tEstado estado = comprobarEstado(matriz, i, j);
            if (estado == nace) {
                siguienteEstado[i][j] = true;
            }
            else if (estado == muere) {
                siguienteEstado[i][j] = false;
            }
        }
    }
    copiar(matriz, siguienteEstado);
}

tEstado comprobarEstado(tMatriz matriz, int x, int y) {
    int vecinos = 0;
    tEstado estado;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (i != 0 || j != 0) {
                int vecino_x = (FILAS + ((x + i) % FILAS)) % FILAS;
                int vecino_y = (COLUMNAS + ((y + j) % COLUMNAS)) % COLUMNAS;
                if (matriz[vecino_x][vecino_y]) {
                    vecinos++;
                }
            }
        }
    }
    if (vecinos == 3 && !matriz[x][y]) {
        estado = nace;
    }
    else if ((vecinos == 2 || vecinos == 3) && matriz[x][y]) {
        estado = sobrevive;
    }
    else {
        estado = muere;
    }
    return estado;
}

void copiar(tMatriz matrizDestino, tMatriz matrizOrigen) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            matrizDestino[i][j] = matrizOrigen[i][j];
        }
    }
}

void mostrar(tMatriz matriz) {
    string linea;
    for (int i = 0; i < FILAS; i++) {
        linea = "";
        for (int j = 0; j < COLUMNAS; j++) {
            if (matriz[i][j]) linea += ON;
            else linea += OFF;
            linea += " ";
        }
        cout << linea << endl;
    }
    cout << endl;
    
}
