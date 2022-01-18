#include "TableMgr.h"

void clear(char(&tablero)[3][3]) {

    for (int j = 0, i = 0; !(j == 3 && i == 0); i = (i + 1) % 3) {

        // Set the place as empty
        tablero[j][i] = ' ';

        // Go to the next row
        if (i == 2)
            j++;
    }
}

bool IsFinish(char(&tablero)[3][3])
{
    if ((tablero[0][0] != ' ' &&
         tablero[1][1] == tablero[2][2] &&
         tablero[2][2] == tablero[0][0]) ||
        (tablero[0][2] != ' ' &&
         tablero[1][1] == tablero[0][2] &&
         tablero[1][1] == tablero[2][0]))
        return true;

    if (tablero[fila][0] == tablero[fila][2] && tablero[fila][0] == tablero[fila][1])
        return true;

    else if (tablero[1][columna] == tablero[0][columna] && tablero[2][columna] == tablero[0][columna])
        return true;

    return false;
}
