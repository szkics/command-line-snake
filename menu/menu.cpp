#include "menu.h"
#include <iostream>

void GameMenu::render()
{
    std::cout << std::endl;
    std::cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << std::endl;
    std::cout << "|||||||||||||||||||	   sn@ke	  ||||||||||||||||" << std::endl;
    std::cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << std::endl;
    std::cout << std::endl;
    std::cout << "		choose mode" << std::endl;
    std::cout << "		type o for obstacle mode" << std::endl;
    std::cout << "		type n for normal mode" << std::endl;
    std::cout << "		type t for teleport mode" << std::endl;
    std::cout << "		type w for teleport mode with obstacles" << std::endl;
    std::cout << "		type m for multiplayer mode" << std::endl;

    for (size_t i = 0; i < 6; ++i)
    {
        std::cout << std::endl;
    }
    std::cout << "		type e to exit" << std::endl;
}

char GameMenu::getSelectedMode()
{
    char mode;
    std::cin >> mode;
    return mode;
}

void GameMenu::clearScreen()
{
    std::cout << "\033c";
}

void GameMenu::endOfTheGameMessage(const bool& playerHasWon, const int& gameState)
{
    if (gameState == ERR_INVALID_INPUT)
    {
        clearScreen();
        userGuideMessage();
    }
    else if (playerHasWon)
    {
        clearScreen();
        playerHasWonMessage();
    }
    else
    {
        clearScreen();
        goodbyeMessage();
    }
}

void GameMenu::goodbyeMessage()
{
    printEmptyLines();
    std::cout << "smooth slithering, goodbye! @" << std::endl;
    printEmptyLines();
}

void GameMenu::playerHasWonMessage()
{
    printEmptyLines();
    std::cout << "congratulations, You have won! the smoothest slitherings! @" << std::endl;
    printEmptyLines();
}

void GameMenu::userGuideMessage()
{
    printEmptyLines();
    std::cerr << "snake can be moved either by WASD or by arrow keys. any other attempt is forbidden." << std::endl;
    std::cout << "(sorry) @" << std::endl;
    printEmptyLines();
}

void GameMenu::obstacleNumberMessage(const char& selectedGameMode)
{
    if (selectedGameMode == 'o' || selectedGameMode == 'w')
    {
        std::cout << "number of obstacles: " << std::endl;
    }
}

void GameMenu::printEmptyLines()
{
    for (size_t i = 0; i < 10; ++i)
    {
        std::cout << std::endl;
    }
}
