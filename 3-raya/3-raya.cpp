#include "iostream"
#include "PlayLogic.h"
#include "TableMgr.h"
#define MAT 3

void imprimir(char tablero[3][3]);

int main(int argc, char** argv) {

    char tablero[MAT][MAT] = { {' ',' ',' ',},{' ',' ',' ',},{' ',' ',' ',} };
    int i = 0, j = 0, fila, columna, turno = 0, ganar = 0, fAUX, cAUX;
    while (i == 0) {
        j = 0; ganar = 0;
        do {
            printf("¿Quieres comenzar tú la partida?\n1.No\n0.Sí\n");
            std::cin >> turno;
        } while (turno != 0 && turno != 1);
        imprimir(tablero);
        while (turno < 9 && ganar == 0) {

            // It's human turn
            if ((turno % 2) == 0) {
                PlayHuman(tablero, &fila, &columna);
            }

            // It's machine turn
            else {
                PlayMachine(tablero, &fila, &columna);
            }
            if (tablero[fila][columna] != ' ')
                return (10);
            if ((turno++) % 2)  //cambias jugador   
                tablero[fila][columna] = 'X';
            else
                tablero[fila][columna] = 'O';
            imprimir(tablero);
            if (fila == columna || fila + columna == 2) {
                if ((tablero[0][0] != ' ' && tablero[1][1] == tablero[2][2] && tablero[2][2] == tablero[0][0]) || (tablero[0][2] != ' ' && tablero[1][1] == tablero[0][2] && tablero[1][1] == tablero[2][0]))
                    ganar++;
            }
            if (tablero[fila][0] == tablero[fila][2] && tablero[fila][0] == tablero[fila][1])
                ganar++;
            else if (tablero[1][columna] == tablero[0][columna] && tablero[2][columna] == tablero[0][columna])
                ganar++;
        }
        if (ganar) {
            if ((++turno) % 2 == 1)
                std::cout << "\n¡Ha ganado la CPU!";
            else
                std::cout << "\n¡Ha ganado el jugador 1!";
        }
        else
            std::cout << "\nEmpate.\n";

        // Set al the places to empty
        clear(tablero);

        do {
            std::cout << "¿Volver a jugar?\n0.Sí\n1.No\n";
            std::cin >> i;
        } while (i != 0 && i != 1);
    }
    return (EXIT_SUCCESS);
}

void imprimir(char tablero[3][3]) {
    int k, i = 0, j = 0;
    std::cout << "\n---------------\n";
    for (k = 0; k < 9; k++) {
        printf("| %c |", tablero[i][(j++) % 3]);
        if (!(j % 3)) {
            printf("\n|---++---++---|\n");
            i++;
        }
    }
}
