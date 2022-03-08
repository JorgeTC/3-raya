#pragma once
#include "GUI.h"
#include "iostream"

int PickInitialPlayer()
{
    int nTurn = -1;

    // Check that the introduced number is a valid turn
    while (nTurn != 0 && nTurn != 1) {
        printf("¿Quieres comenzar tú la partida?\n1.No\n0.Sí\n");
        std::cin >> nTurn;
    }

    return nTurn;
}

bool OtherGame()
{
    int nAns = -1;

    // Check that the introduced number is a valid answer
    while (nAns != 0 && nAns != 1) {
        std::cout << "¿Volver a jugar?\n0.Sí\n1.No\n";
        std::cin >> nAns;
    }

    // Convert the option into a bool
    return nAns == 0;
}

void PrintGameResult(GameResult result)
{
    if (result == GameResult::CPU_WIN)
        std::cout << "\n¡Ha ganado la CPU!";
    else if (result == GameResult::USER_WIN)
        std::cout << "\n¡Ha ganado el jugador 1!";
    else if (result == GameResult::EVEN)
        std::cout << "\nEmpate.\n";
}
