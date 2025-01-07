#include "gamemodes/gamemodes.h"
#include "menu/menu.h"

int main()
{
    GameMenu gameMenu;
    GameMode gameMode;

    char selectedGameMode = 'n';
    int  gameState        = 0;
    while (selectedGameMode != 'e' && !gameMode.playerHasWon)
    {
        gameMenu.clearScreen();
        gameMenu.render();
        selectedGameMode = gameMenu.getSelectedMode();
        gameMenu.clearScreen();
        gameMenu.obstacleNumberMessage(selectedGameMode);
        gameState = gameMode.playSelectedMode(selectedGameMode, std::cout);
        if (gameState == ERR_INVALID_INPUT)
        {
            break;
        }
    }
    gameMenu.endOfTheGameMessage(gameMode.playerHasWon, gameState);

    return 0;
}