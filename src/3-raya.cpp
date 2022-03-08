#include "iostream"
#include "PlayLogic.h"
#include "TableMgr.h"
#include "GUI.h"

int main(int argc, char** argv) {

    bool bOtherGame = true;

    while (bOtherGame) {

        // Ask the user who will make the first movement
        int turno = PickInitialPlayer();

        GameResult result = PlayGame(turno);

        // Print the result of the game
        PrintGameResult(result);

        // Ask the user if he wants to play another round
        bOtherGame = OtherGame();
    }

    return (EXIT_SUCCESS);
}
