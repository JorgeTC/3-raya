#pragma once
#include "Position.h"

// Class to keep the result of a finished game
enum class GameResult {
	USER_WIN = -1,
	EVEN = 0,
	CPU_WIN = 1
};

// Sign for every player
enum class Sign {
	USER = 'O',
	CPU = 'X'
};

// Macro to tell the turn
#define IS_HUMAN_TURN(_tr) ((_tr % 2) == 0)
#define IS_CPU_TURN(_tr)   ((_tr % 2) == 1)

// Main function
GameResult PlayGame(int turno);

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
void AlgorithmicMachinePlay(char(&tablero)[3][3], int* fila, int* columna);
void MinimaxAlgorithm(char(&tablero)[3][3], int* fila, int* columna);
int MiniMax(char tablero[3][3], bool bMax, Position* BestMove = nullptr);
