#include "userinteraction.h"

size_t UserInteraction::getNumberOfRocks()
{
    size_t numberOfRocks;
    std::cin >> numberOfRocks;
    if (!std::cin)
    {
        numberOfRocks = DEFAULT_NUMBER_OF_ROCKS;
        /*TODO: understand why this is important + proper exception maybe if not a number is given as input.*/
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return numberOfRocks;
}

void UserInteraction::cleanInputBuffer()
{
    while ((getchar()) != '\n')
        ;
}

char UserInteraction::getInput()
{
    char input = getchar();
    if (input == 27)
    {
        input = getchar();
        if (input == 91)
        {
            input = getchar();
        }
    }
    return input;
}

char UserInteraction::getInputOnKeyPressed(char& input)
{
    if (_kbhit())
    {
        input = getInput();
    }
    return input;
}