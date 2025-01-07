#pragma once
#include "../entities/entities.h"
#include "../gamelogic/gamelogic.h"
#include "../headers/error_codes.h"
#include "../headers/headers.h"
#include "../snake/snake.h"
#include "../timer/timer.h"
#include "../userinteraction/userinteraction.h"

class GameModeInterface
{
public:
    virtual int  handleUserInputBasic(Game& game, Snake& snake, Point& generatedApple, std::ostream& outputStream,
                                      char input)                        = 0;
    virtual int  handleUserInput(Game& game, Snake& snake, Point& generatedApple, std::ostream& outputStream,
                                 char input)                             = 0;
    virtual void handleUserInput(Game& game, Anaconda& anaconda, Python& python, Point& generatedApple,
                                 std::ostream& outputStream, char input) = 0;
};

class GameMode : public GameModeInterface
{
public:
    int  playSelectedMode(const char& selectedGameMode, std::ostream& outputStream);
    int  handleUserInputBasic(Game& game, Snake& snake, Point& generatedApple, std::ostream& outputStream, char input);
    int  handleUserInput(Game& game, Snake& snake, Point& generatedApple, std::ostream& outputStream, char input);
    void handleUserInput(Game& game, Anaconda& anaconda, Python& python, Point& generatedApple,
                         std::ostream& outputStream, char input);

    bool playerHasWon = false;

    void initializeNormalMode(Snake& snake, Game& game);
    void initializeObstacleMode(Snake& snake, Game& game, coordinateVector& randomRocks);
    void initializeMultiplayerMode(Anaconda& anaconda, Python& python, Game& game);

private:
    int startObstacleMode(std::ostream& outputStream, char selectedGameMode);
    int startNormalMode(std::ostream& outputStream, char selectedGameMode);
    int startMultiplayerMode(std::ostream& outputStream, char selectedGameMode);

    GameBoard        gameBoard;
    Apple            apple;
    Rock             rock;
    UserInteraction  userInteraction;
    size_t           numberOfRocks;
    Point            generatedApple;
    coordinateVector snakeVector;
    coordinateVector anacondaVector;
    coordinateVector pythonVector;
    char             input;
};