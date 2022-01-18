#pragma once

// Logic for the human
void PlayHuman(char(&tablero)[3][3], int *fila, int *columna);

// Logic for the machine
void PlayMachine(char(&tablero)[3][3], int* fila, int* columna);
bool IsWinnerCorner(char(&tablero)[3][3], int fila, int columna);
bool IsWinnerMiddle(char(&tablero)[3][3], int fila, int columna);
bool Pmedio(char(&tablero)[3][3], int* fila, int* columna);
bool Pesquina(char(&tablero)[3][3], int* fila, int* columna);
bool TryWinnerMove(char(&tablero)[3][3], int* fila, int* columna);
bool TryBlockOpponent(char(&tablero)[3][3], int* fila, int* columna);
