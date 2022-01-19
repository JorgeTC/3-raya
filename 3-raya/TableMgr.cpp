#include "TableMgr.h"
#include "iostream"
#include "PlayLogic.h"

void clear(char(&tablero)[3][3]) {

    for (int j = 0, i = 0; !(j == 3 && i == 0); i = (i + 1) % 3) {

        // Set the place as empty
        tablero[j][i] = ' ';

        // Go to the next row
        if (i == 2)
            j++;
    }
}

void print(char(&tablero)[3][3]) {

    printf("\n|---++---++---|\n");

    // Scroll the all 9 elements of the grid
    for (int nRow = 0; nRow < 3; nRow++) {
        for (int nColumn = 0; nColumn < 3; nColumn++) {

            // Print current position
            printf("| %c |", tablero[nRow][nColumn]);
        }

        // Next row
        printf("\n|---++---++---|\n");
    }
}

bool IsWon(char(&tablero)[3][3])
{
    // I check the diagonals
    // Diagonal from left top to right bottom
    if (!IS_EMPTY(tablero[1][1]) &&
        tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2])
        return true;
    // Diagonal from left bottom to right top
    if (!IS_EMPTY(tablero[1][1]) &&
        tablero[2][0] == tablero[1][1] && tablero[1][1] == tablero[0][2])
        return true;

    // I check the rows
    for (int nRow = 0; nRow < 3; nRow++) {
        if (!IS_EMPTY(tablero[nRow][1]) &&
            tablero[nRow][0] == tablero[nRow][1] &&
            tablero[nRow][1] == tablero[nRow][2])
            return true;
    }

    // I check the columns
    for (int nColumn = 0; nColumn < 3; nColumn++) {
        if (!IS_EMPTY(tablero[1][nColumn]) &&
            tablero[0][nColumn] == tablero[1][nColumn] &&
            tablero[1][nColumn] == tablero[2][nColumn])
            return true;
    }

    return false;
}

#define GET_GAMERESULT_FROM_WINING_PLACE( _place ) _place == static_cast<char>(Sign::CPU) ? GameResult::CPU_WIN : GameResult::USER_WIN;
GameResult GetTableValue(char tablero[3][3])
{
    // I check the diagonals
    // Diagonal from left top to right bottom
    if (!IS_EMPTY(tablero[1][1]) &&
        tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2]) {

        return GET_GAMERESULT_FROM_WINING_PLACE(tablero[0][0]);
    }

    // Diagonal from left bottom to right top
    if (!IS_EMPTY(tablero[1][1]) &&
        tablero[2][0] == tablero[1][1] && tablero[1][1] == tablero[0][2]) {

        return GET_GAMERESULT_FROM_WINING_PLACE(tablero[2][0]);
    }

    // I check the rows
    for (int nRow = 0; nRow < 3; nRow++) {
        if (!IS_EMPTY(tablero[nRow][1]) &&
            tablero[nRow][0] == tablero[nRow][1] &&
            tablero[nRow][1] == tablero[nRow][2]) {

            return GET_GAMERESULT_FROM_WINING_PLACE(tablero[nRow][1]);
        }
            
    }

    // I check the columns
    for (int nColumn = 0; nColumn < 3; nColumn++) {
        if (!IS_EMPTY(tablero[1][nColumn]) &&
            tablero[0][nColumn] == tablero[1][nColumn] &&
            tablero[1][nColumn] == tablero[2][nColumn]) {
            return GET_GAMERESULT_FROM_WINING_PLACE(tablero[1][nColumn]);
        }
    }

    return GameResult::EVEN;
}

bool IsFull(char(&tablero)[3][3])
{
    // Scroll all the cells
    for (int nRow = 0; nRow < 3; nRow++) {
        for (int nColumn = 0; nColumn < 3; nColumn++) {

            // If one single cell is empty, the table is not full
            if (IS_EMPTY(tablero[nRow][nColumn]))
                return false;
        }
    }
    return true;
}

bool PlayPosition(char(&tablero)[3][3], int nFila, int nColumna, int nTurn)
{
    // Check if the selected place is empty
    if (!IS_EMPTY(tablero[nFila][nColumna]))
        return false;

    // Choose what sign I shall use
    Sign CurrentChar = IS_CPU_TURN(nTurn) ? Sign::CPU : Sign::USER;

    // Write the corrent sign in the selected position
    tablero[nFila][nColumna] = static_cast<char>(CurrentChar);

    return true;
}

void GetEmptyPositions(char tablero[3][3], std::vector<Position>* vtEmptyPositions)
{
    // Scroll the hole table
    for (Position i; i.Valid(); ++i) {
        // If the position is empty, add it to the vector
        if (IS_EMPTY(tablero[i.Row][i.Column])) {
            vtEmptyPositions->push_back(i);
        }
    }
}

void CopyTable(char(&dest)[3][3], char ori[3][3])
{
    for (int nRow = 0; nRow < 3; nRow++) {
        for (int nCol = 0; nCol < 3; nCol++) {
            dest[nRow][nCol] = ori[nRow][nCol];
        }
    }
}
