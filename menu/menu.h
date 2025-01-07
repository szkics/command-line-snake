#include "../headers/error_codes.h"

class GameMenu
{
public:
    void render();
    void clearScreen();
    char getSelectedMode();
    void endOfTheGameMessage(const bool& playerHasWon, const int& gameState);
    void obstacleNumberMessage(const char& selectedGameMode);

private:
    void goodbyeMessage();
    void playerHasWonMessage();
    void userGuideMessage();
    void printEmptyLines();
};