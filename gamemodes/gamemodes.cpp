#include "gamemodes.h"

void GameMode::initializeNormalMode(Snake& snake, Game& game)
{
    snakeVector = snake.getPositionVector();
    gameBoard.initialize();
    generatedApple = apple.generateApple(snakeVector);
    game.start(gameBoard);
    input = RIGHT_D;
}

void GameMode::initializeObstacleMode(Snake& snake, Game& game, coordinateVector& randomRocks)
{
    snakeVector = snake.getPositionVector();
    gameBoard.initialize(randomRocks);
    game.start(gameBoard);
    generatedApple = apple.generateApple(snakeVector, randomRocks);
    input          = RIGHT_D;
}

void GameMode::initializeMultiplayerMode(Anaconda& anaconda, Python& python, Game& game)
{
    anacondaVector = anaconda.getPositionVector();
    pythonVector   = python.getPositionVector();
    gameBoard.initializeMultiplayer();
    game.start(gameBoard);
    generatedApple = apple.generateApple(anacondaVector);
    input          = RIGHT_D;
}

int GameMode::handleUserInputBasic(Game& game, Snake& snake, Point& generatedApple, std::ostream& outputStream,
                                   char input)
{
    snake.moves();
    try
    {
        snake.updateSnakeDirection(input);
    }
    catch (std::invalid_argument& e)
    {
        std::cerr << e.what() << std::endl;

        return ERR_INVALID_INPUT;
    }
    coordinateVector snakeVector = snake.getPositionVector();
    if (snake.eatsApple(generatedApple))
    {
        game.updateScoreBoard();
    }
    game.updateGameState(snakeVector, generatedApple, outputStream);

    return NO_ERROR;
}

int GameMode::handleUserInput(Game& game, Snake& snake, Point& generatedApple, std::ostream& outputStream, char input)
{
    snake.moves();
    try
    {
        snake.updateSnakeDirection(input);
    }
    catch (std::invalid_argument& e)
    {
        std::cerr << e.what() << std::endl;

        return ERR_INVALID_INPUT;
    }
    coordinateVector snakeVector = snake.getPositionVector();
    if (snake.eatsApple(generatedApple))
    {
        game.updateScoreBoard();
    }
    game.updateGameState(snakeVector, generatedApple, outputStream);

    return NO_ERROR;
}

void GameMode::handleUserInput(Game& game, Anaconda& anaconda, Python& python, Point& generatedApple,
                               std::ostream& outputStream, char input)
{
    anaconda.moves();
    anaconda.updateSnakeDirectionWASD(input);
    coordinateVector anacondaVector = anaconda.getPositionVector();
    if (anaconda.eatsApple(generatedApple))
    {
        game.updateScoreBoard(ANACONDA_SCORE);
    }

    python.moves();
    python.updateSnakeDirectionArrowKeys(input);
    coordinateVector pythonVector = python.getPositionVector();
    if (python.eatsApple(generatedApple))
    {
        game.updateScoreBoard(PYTHON_SCORE);
    }

    game.updateGameStateMultiplayer(pythonVector, anacondaVector, generatedApple, outputStream);
}

int GameMode::playSelectedMode(const char& selectedGameMode, std::ostream& outputStream)
{
    if (selectedGameMode == 'o' || selectedGameMode == 'w')
    {
        int gameState = startObstacleMode(outputStream, selectedGameMode);
        return gameState;
    }
    else if (selectedGameMode == 'n' || selectedGameMode == 't')
    {
        int gameState = startNormalMode(outputStream, selectedGameMode);
        return gameState;
    }
    else if (selectedGameMode == 'm')
    {
        int gameState = startMultiplayerMode(outputStream, selectedGameMode);
        return gameState;
    }
    else
    {
        return ERR_INVALID_GAME_MODE;
    }
};

int GameMode::startObstacleMode(std::ostream& outputStream, char selectedGameMode)
{
    Snake snake;
    Game  game;
    numberOfRocks                = userInteraction.getNumberOfRocks();
    coordinateVector randomRocks = rock.generateRocks(numberOfRocks);
    initializeObstacleMode(snake, game, randomRocks);

    Timer timer;
    timer.setSignal(1);

    while (snake.lives(selectedGameMode) && !snake.hitsRock(randomRocks) && !game.playerHasWon())
    {
        input = userInteraction.getInputOnKeyPressed(input);

        if (snake.eatsApple(generatedApple))
        {
            generatedApple = apple.generateApple(snakeVector, randomRocks);
        }

        if (timer.getSignal() == 1)
        {
            if (handleUserInput(game, snake, generatedApple, outputStream, input) == ERR_INVALID_INPUT)
            {
                return ERR_INVALID_INPUT;
            };
            timer.setSignal(0);
        }
    }

    playerHasWon = game.playerHasWon();
    return NO_ERROR;
}

int GameMode::startNormalMode(std::ostream& outputStream, char selectedGameMode)
{
    Snake snake;
    Game  game;
    initializeNormalMode(snake, game);

    Timer timer;
    timer.setSignal(1);

    while (snake.lives(selectedGameMode) && !game.playerHasWon())
    {
        input = userInteraction.getInputOnKeyPressed(input);

        if (timer.getSignal() == 1)
        {
            if (snake.eatsApple(generatedApple))
            {
                generatedApple = apple.generateApple(snakeVector);
            }
            if (handleUserInputBasic(game, snake, generatedApple, outputStream, input) == ERR_INVALID_INPUT)
            {
                return ERR_INVALID_INPUT;
            };
            timer.setSignal(0);
        }
    }

    playerHasWon = game.playerHasWon();
    return NO_ERROR;
}

int GameMode::startMultiplayerMode(std::ostream& outputStream, char selectedGameMode)
{
    Anaconda anaconda(ROW_NUMBER / 2, 2);
    Python   python(ROW_NUMBER / 2 + 1, 2);
    Game     game;
    initializeMultiplayerMode(anaconda, python, game);

    Timer timer;
    timer.setSignal(1);

    while (anaconda.lives(selectedGameMode) && python.lives(selectedGameMode)
           && !anaconda.bitesTheOtherSnake(pythonVector) && !python.bitesTheOtherSnake(anacondaVector))
    {
        input = userInteraction.getInputOnKeyPressed(input);

        if (anaconda.eatsApple(generatedApple) || python.eatsApple(generatedApple))
        {
            generatedApple = apple.generateApple(anacondaVector);
        }

        if (timer.getSignal() == 1)
        {
            handleUserInput(game, anaconda, python, generatedApple, outputStream, input);
            timer.setSignal(0);
        }
    }

    playerHasWon = game.playerHasWon();
    return NO_ERROR;
}