#pragma once
#include "Position.h"
#include <vector>
#include "PlayLogic.h"

#define IS_EMPTY(_cl) ((_cl) == ' ')
#define IS_CENTER(_nRow, _nCol) (_nRow == 1 && _nCol == 1)
#define IS_CORNER(_nRow, _nCol) ((((_nRow + _nCol) % 2) == 0) && !IS_CENTER(_nRow, _nCol))
#define IS_MIDDLE(_nRow, _nCol) ((((_nRow + _nCol) % 2) == 1))

void clear(char(&tablero)[3][3]);
void print(char(&tablero)[3][3]);
bool IsWon(char(&tablero)[3][3]);
GameResult GetTableValue(char tablero[3][3]);
bool IsFull(char(&tablero)[3][3]);
bool PlayPosition(char(&tablero)[3][3], int nFila, int nColumna, int nTurn);
void GetEmptyPositions(char tablero[3][3], std::vector<Position> *vtEmptyPositions);

void CopyTable(char(&dest)[3][3], char ori[3][3]);