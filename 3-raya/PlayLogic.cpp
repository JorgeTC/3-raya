#include "PlayLogic.h"
#include "iostream"
#include "TableMgr.h"

GameResult PlayGame(int turno)
{
    // Create new table
    char tablero[3][3] = { {' ',' ',' ',},{' ',' ',' ',},{' ',' ',' ',} };

    print(tablero);

    int fila;
    int columna;
    bool bHasWon = false;
    bool bFullTable = false;

    while (!bFullTable && !bHasWon) {

        // It's human turn
        if (IS_HUMAN_TURN(turno))
            PlayHuman(tablero, &fila, &columna);

        // It's machine turn
        else
            PlayMachine(tablero, &fila, &columna);

        // Fill the corrent place with the sign
        PlayPosition(tablero, fila, columna, turno);

        // Advance to the next turn
        turno++;

        // Show the table after the last move
        print(tablero);

        // Check if someone has won
        bHasWon = IsWon(tablero);
        // Check if there is any empty cell
        bFullTable = IsFull(tablero);
    }

    if (!bHasWon)
        return GameResult::EVEN;
    if (turno % 2 == 0)
        return GameResult::CPU_WIN;
    else
        return GameResult::USER_WIN;
}

void PlayHuman(char(&tablero)[3][3], int* fila, int* columna) {

    int nFila;
    int nColumna;

    // Loop till the human picks an empty place
    do {
        // I let the human count the cells starting from 1
        std::cout << "\nJugador. \nElige fila : ";
        std::cin >> nFila;
        nFila--;

        std::cout << "Elige columna: ";
        std::cin >> nColumna;
        nColumna--;

    } while (!IS_EMPTY(tablero[nFila][nColumna]));

    *fila = nFila;
    *columna = nColumna;
}

void PlayMachine(char(&tablero)[3][3], int* fila, int* columna) {

    std::cout << "\nJugada CPU: \n";

    // If the central place is empty, I always play there
    if (IS_EMPTY(tablero[1][1])) {
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

    // I cannot win, I cannot block the opponent
    // If the middle place is mine, I play the middle positions
    if (tablero[1][1] == static_cast<char>(Sign::CPU)) {
        if (Pmedio(tablero, fila, columna) ||
            Pesquina(tablero, fila, columna) )
            return;
    }
    // Otherwise I play the corners
    else {
        if (Pesquina(tablero, fila, columna) ||
            Pmedio(tablero, fila, columna))
            return;
    }
}

bool IsWinnerCorner(char(&tablero)[3][3], int fila, int columna)
{
    // Check if the current row is almost complete
    int nOtherInTheRow1 = (columna + 1) % 3;
    int nOtherInTheRow2 = (columna + 2) % 3;
    if (tablero[fila][nOtherInTheRow1] == static_cast<char>(Sign::CPU) &&
        tablero[fila][nOtherInTheRow2] == static_cast<char>(Sign::CPU))
        return true;

    // Check if the current column is almost complete
    int nOtherInTheColumn1 = (fila + 1) % 3;
    int nOtherInTheColumn2 = (fila + 2) % 3;
    if (tablero[nOtherInTheColumn1][columna] == static_cast<char>(Sign::CPU) &&
        tablero[nOtherInTheColumn2][columna] == static_cast<char>(Sign::CPU))
        return true;

    return false;
}

bool IsWinnerMiddle(char(&tablero)[3][3], int fila, int columna) {

    // Check if the current row is almost complete
    int nOtherInTheRow1 = (columna + 1) % 3;
    int nOtherInTheRow2 = (columna + 2) % 3;
    if (tablero[fila][nOtherInTheRow1] == static_cast<char>(Sign::CPU) &&
        tablero[fila][nOtherInTheRow2] == static_cast<char>(Sign::CPU))
        return true;

    // Check if the current column is almost complete
    int nOtherInTheColumn1 = (fila + 1) % 3;
    int nOtherInTheColumn2 = (fila + 2) % 3;
    if (tablero[nOtherInTheColumn1][columna] == static_cast<char>(Sign::CPU) &&
        tablero[nOtherInTheColumn2][columna] == static_cast<char>(Sign::CPU))
        return true;

    // Check if the current diagonal is almost complete
    int nOppositeCornerRow = 2 - fila;
    int nOppositeCornerColumn = 2 - columna;
    if (tablero[1][1] == 'X' &&
        tablero[nOppositeCornerRow][nOppositeCornerColumn] == static_cast<char>(Sign::CPU))
        return true;

    return false;
}

bool Pmedio(char(&tablero)[3][3], int* fila, int* columna)
{
    // Loop through all the middle places
    for ((*fila) = 0, (*columna) = 1; (*fila) < 3;) {

        // I choose the middle position whose opposite place has been played by the opponent 
        if (IS_EMPTY(tablero[*fila][*columna]) &&
            tablero[2 - *fila][2 - *columna] != static_cast<char>(Sign::USER))
            return true;

        // Go to the next middle place
        if (*columna)
            (*fila)++;
        *columna = ((*columna) + 2) % 3;
    }

    // The opponent does not have a middle place that makes me choose a middle place
    return false;
}

bool Pesquina(char(&tablero)[3][3], int* fila, int* columna) {

    // Loop through all the corners
    for ((*fila) = 0, (*columna) = 0; (*fila) < 3;) {

        // If the corner is empty, I play that
        if (IS_EMPTY(tablero[*fila][*columna]))
            return true;

        // Go to the next corner
        (*fila) += (*columna);
        (*columna) = ((*columna) + 2) % 4;
    }

    // There are no empty corners
    return false;
}

bool TryWinnerMove(char(&tablero)[3][3], int* fila, int* columna)
{
    for (int nRow = 0; nRow < 3; nRow++) {
        for (int nColumn = 0; nColumn < 3; nColumn++){

            // Check if the current place is empty
            if (!IS_EMPTY(tablero[nRow][nColumn]))
                continue;

            // It is a middle place
            if (IS_MIDDLE(nRow, nColumn)) {
                // If playing that position I win the game, I choose it
                if (IsWinnerMiddle(tablero, nRow, nColumn)) {

                    *fila = nRow;
                    *columna = nColumn;

                    return true;
                }
            }
            // It is a corner
            else {
                // If playing that position I win the game, I choose it
                if (IsWinnerCorner(tablero, nRow, nColumn)) {

                    *fila = nRow;
                    *columna = nColumn;

                    return true;
                }
            }
        }
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
        IS_EMPTY(tablero[fAUX][cAUX])) {

        *fila = fAUX;
        *columna = cAUX;

        return true;
    }
    // Check if the opponent can make a row and its middle position it's empty
    else if (tablero[*fila][*columna] == tablero[*fila][cAUX] &&
        *columna != 1 && IS_EMPTY(tablero[*fila][1])) {

        *columna = 1;

        return true;
    }
    // Check if the opponent can make a column and its middle position it's empty
    else if (tablero[*fila][*columna] == tablero[fAUX][*columna] &&
        *fila != 1 && IS_EMPTY(tablero[1][*columna])) {

        *fila = 1;

        return true;
    }
    
    // The opponent has played the middle row
    // I try to block the column
    else if (*fila == 1 && *columna != 1) {
        
        // The oppponent has two consecutive places,
        // I play in the remaining empty place.
        if (tablero[1][*columna] == tablero[0][*columna] &&
            IS_EMPTY(tablero[2][*columna])) {

            // I choose the empty place to play
            *fila = 2;

            return true;
        }
        
        // The oppponent has two consecutive places,
        // I play in the remaining empty place.
        else if (tablero[1][*columna] == tablero[2][*columna] &&
            IS_EMPTY(tablero[0][*columna])) {

            // I choose the empty place to play
            *fila = 0;

            return true;
        }
    }
    // The opponen has played the middle column
    // I try to block the row the opponent has played
    else if (*columna == 1 && *fila != 1) {

        // The opponent has two consecutive places and I block the empty remaining
        if (tablero[*fila][1] == tablero[*fila][0] &&
            IS_EMPTY(tablero[*fila][2])) {

            // I play the empty space
            *columna = 2;

            return true;
        }
        // The opponent has two consecutive places and I block the empty remaining
        else if (tablero[*fila][1] == tablero[*fila][2] &&
            IS_EMPTY(tablero[*fila][0])) {

            // I play the empty space
            *columna = 0;

            return true;
        }
    }
    // It is a corner
    else if ((*columna + *fila) % 2 == 0 && *columna != 1) {

        // If the oponent has two places of the row
        // Try to block the remaining place of the row
        if (IS_EMPTY(tablero[*fila][cAUX]) &&
            tablero[*fila][1] == static_cast<char>(Sign::USER)) {

            // Play the empty place
            *columna = cAUX;

            return true;
        }
        // If the oponent has two places of the column
        // Try to block the remaining place of the column
        else if (IS_EMPTY(tablero[cAUX][*columna]) &&
            tablero[1][*columna] == static_cast<char>(Sign::USER)) {

            // Play the empty place
            *fila = fAUX;

            return true;
        }
    }

    // I play the corner that blocks at the same time an opponent's row and column
    // Loop through all the corners
    for (*fila = 0, *columna = 0; *fila < 3;) {

        // The current place is empty and it has two adjacent opponent's places
        if (IS_EMPTY(tablero[*fila][*columna]) &&
            tablero[*fila][1] == static_cast<char>(Sign::USER) &&
            tablero[1][*columna] == static_cast<char>(Sign::USER))

            return true;

        // Go to the next corner
        *fila += *columna;
        *columna = (*columna + 2) % 4;
    }

    return false;
}
