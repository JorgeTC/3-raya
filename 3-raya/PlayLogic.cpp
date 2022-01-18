#include "PlayLogic.h"
#include "iostream"

void PlayHuman(char(&tablero)[3][3], int* fila, int* columna) {

    int nFila;
    int nColumna;

    do {
        std::cout << "\nJugador. \nElige fila : ";
        std::cin >> nFila;
        nFila--;
        std::cout << "Elige columna: ";
        std::cin >> nColumna;
        nColumna--;
    } while (tablero[nFila][nColumna] != ' ');

    *fila = nFila;
    *columna = nColumna;
}

void PlayMachine(char(&tablero)[3][3], int* fila, int* columna) {

    std::cout << "\nJugada CPU: \n";

    // If the central place is empty, I always play there
    if (tablero[1][1] == ' ') {
        *fila = 1;
        *columna = 1;
        return;
    }

    // I try to win
    if ( TryWinnerMove(tablero, fila, columna) )
        return;
    
    // I try that the other player does not win
    if (TryBlockOpponent(tablero, fila, columna))
        return;
    //no puede hacer 3 en raya ni bloquear al jugador
    if (tablero[1][1] == 'X') {//coloca en los puntos medios
        if (Pmedio(tablero, fila, columna))
            return;
    }
    else {// coloca en las esquinas
        if (Pesquina(tablero, fila, columna) ||
            Pmedio(tablero, fila, columna))
            return;
    }

    Pesquina(tablero, fila, columna);
}

bool IsWinnerCorner(char(&tablero)[3][3], int fila, int columna)
{
    // Check if the current row is almost complete
    int nOtherInTheRow1 = (columna + 1) % 3;
    int nOtherInTheRow2 = (columna + 2) % 3;
    if (tablero[fila][nOtherInTheRow1] == 'X' &&
        tablero[fila][nOtherInTheRow2] == 'X')
        return true;

    // Check if the current column is almost complete
    int nOtherInTheColumn1 = (fila + 1) % 3;
    int nOtherInTheColumn2 = (fila + 2) % 3;
    if (tablero[nOtherInTheColumn1][columna] == 'X' &&
        tablero[nOtherInTheColumn2][columna] == 'X')
        return true;

    return false;
}

bool IsWinnerMiddle(char(&tablero)[3][3], int fila, int columna) {

    // Check if the current row is almost complete
    int nOtherInTheRow1 = (columna + 1) % 3;
    int nOtherInTheRow2 = (columna + 2) % 3;
    if (tablero[fila][nOtherInTheRow1] == 'X' &&
        tablero[fila][nOtherInTheRow2] == 'X')
        return true;

    // Check if the current column is almost complete
    int nOtherInTheColumn1 = (fila + 1) % 3;
    int nOtherInTheColumn2 = (fila + 2) % 3;
    if (tablero[nOtherInTheColumn1][columna] == 'X' &&
        tablero[nOtherInTheColumn2][columna] == 'X')
        return true;

    // Check if the current diagonal is almost complete
    int nOppositeCornerRow = 2 - fila;
    int nOppositeCornerColumn = 2 - columna;
    if (tablero[1][1] == 'X' &&
        tablero[nOppositeCornerRow][nOppositeCornerColumn] == 'X')
        return true;

    return false;
}

bool Pmedio(char(&tablero)[3][3], int* fila, int* columna)
{
    for ((*fila) = 0, (*columna) = 1; (*fila) < 3;) {
        if (tablero[*fila][*columna] == ' ' &&
            tablero[2 - *fila][2 - *columna] != 'O')
            return true;
        else {
            if (*columna)
                (*fila)++;
            *columna = ((*columna) + 2) % 3;
        }
    }

    return false;
}

bool Pesquina(char(&tablero)[3][3], int* fila, int* columna) {
    for ((*fila) = 0, (*columna) = 0; (*fila) < 3;) {
        if (tablero[*fila][*columna] == ' ')
            return true;
        else {
            (*fila) += (*columna);
            (*columna) = ((*columna) + 2) % 4;
        }
    }

    return false;
}

bool TryWinnerMove(char(&tablero)[3][3], int* fila, int* columna)
{
    for (int j = 0, i = 0; !(j == 3 && i == 0); i = (i + 1) % 3) {

        // Check if the current place is empty
        if (tablero[j][i] == ' ') {
            // It is a middle place
            if ((i + j) % 2) {
                if (IsWinnerMiddle(tablero, j, i)) {
                    *fila = j;
                    *columna = i;
                    return true;
                }
            }
            // It is a corner
            else {
                if (IsWinnerCorner(tablero, j, i)) {
                    *fila = j;
                    *columna = i;
                    return true;
                }
            }
        }

        // If I'm on the last column, i go to the next row
        if (i == 2)
            j++;
    }

    return false;
}

bool TryBlockOpponent(char(&tablero)[3][3], int* fila, int* columna)
{
    // Oppose position
    int fAUX = 2 - *fila;
    int cAUX = 2 - *columna;

    // Check if the opponent can make a diagonal
    if (tablero[*fila][*columna] == tablero[1][1] &&
        tablero[fAUX][cAUX] == ' ') {

        *fila = fAUX;
        *columna = cAUX;

        return true;
    }
    // Check if the opponent can make a row and its middle position it's empty
    else if (tablero[*fila][*columna] == tablero[*fila][cAUX] &&
        *columna != 1 && tablero[*fila][1] == ' ') {

        *columna = 1;

        return true;
    }
    // Check if the opponent can make a column and its middle position it's empty
    else if (tablero[*fila][*columna] == tablero[fAUX][*columna] &&
        *fila != 1 && tablero[1][*columna] == ' ') {

        *fila = 1;

        return true;
    }
    

    else if (*fila == 1 && *columna != 1) {
        
        if (tablero[1][*columna] == tablero[0][*columna] &&
            tablero[2][*columna] == ' ') {

            *fila = 2;

            return true;
        }
        
        else if (tablero[1][*columna] == tablero[2][*columna] &&
            tablero[0][*columna] == ' ') {

            *fila = 0;

            return true;
        }
    }
    else if (*columna == 1 && *fila != 1) {
        if (tablero[*fila][1] == tablero[*fila][0] &&
            tablero[*fila][2] == ' ') {

            *columna = 2;

            return true;
        }
        else if (tablero[*fila][1] == tablero[*fila][2] &&
            tablero[*fila][0] == ' ') {

            *columna = 0;

            return true;
        }
    }
    else if ((*columna + *fila) % 2 == 0 && *columna != 1) {
        if (tablero[*fila][cAUX] == ' ' &&
            tablero[*fila][1] == 'O') {

            *columna = cAUX;

            return true;
        }
        else if (tablero[cAUX][*columna] == ' ' &&
            tablero[1][*columna] == 'O') {

            *fila = fAUX;

            return true;
        }
    }

    //bloquea Angulos en las esquinas
    for (*fila = 0, *columna = 0; *fila < 3;) {
        if (tablero[*fila][*columna] == ' ' &&
            tablero[*fila][1] == 'O' &&
            tablero[1][*columna] == 'O')
            return true;
        else {
            *fila += *columna;
            *columna = (*columna + 2) % 4;
        }
    }

    return false;
}
