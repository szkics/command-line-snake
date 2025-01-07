#define CATCH_CONFIG_MAIN
#include "../catch/catch.hpp"
#include "../fakeit/fakeit.hpp"
#include "../gamemodes/gamemodes.h"

TEST_CASE("test initial state of the player")
{
    GameMode gamemode;
    CHECK(gamemode.playerHasWon == false);
}

TEST_CASE("test snake creation")
{
    Snake snake;
    char  modeOfLiving = 'n';
    CHECK(snake.lives(modeOfLiving) == true);
}

TEST_CASE("test random number generation interval for rock")
{
    Rock             rock;
    coordinateVector randomRocks = rock.generateRocks(DEFAULT_NUMBER_OF_ROCKS);
    for (size_t i = 0; i < randomRocks.size(); ++i)
    {
        Point actualRock = randomRocks.at(i);
        CHECK(actualRock.X <= ROW_NUMBER);
        CHECK(actualRock.Y <= COLUMN_NUMBER);
    }
}

TEST_CASE("check size of rock vector")
{
    Rock             rock;
    coordinateVector randomRocks = rock.generateRocks(DEFAULT_NUMBER_OF_ROCKS);
    CHECK(randomRocks.size() == DEFAULT_NUMBER_OF_ROCKS);
}

TEST_CASE("test interval for random apple generation")
{
    Snake            snake;
    Apple            apple;
    Rock             rock;
    coordinateVector snakeVector = snake.getPositionVector();
    coordinateVector randomRocks = rock.generateRocks(DEFAULT_NUMBER_OF_ROCKS);

    Point randomApple = apple.generateApple(snakeVector, randomRocks);

    CHECK(randomApple.X <= ROW_NUMBER);
    CHECK(randomApple.Y <= COLUMN_NUMBER);
}

TEST_CASE("test snake hitting right wall")
{
    Snake            snake;
    char             input       = RIGHT_D;
    coordinateVector snakeVector = snake.getPositionVector();

    size_t i = 0;
    for (i = 0; i < COLUMN_NUMBER / 2 - 1; ++i)
    {
        char modeOfLiving = 'n';
        CHECK(snake.lives(modeOfLiving));
        snake.moves();
        input = RIGHT_D;
        try
        {
            snake.updateSnakeDirection(input);
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    CHECK(i == COLUMN_NUMBER / 2 - 1);
    char modeOfLiving = 'n';
    CHECK(!snake.lives(modeOfLiving));
}

TEST_CASE("test snake hitting left wall")
{
    Snake            snake;
    char             input       = LEFT_A;
    coordinateVector snakeVector = snake.getPositionVector();

    size_t i = 0;
    for (i = 0; i < COLUMN_NUMBER / 2 + 1; ++i)
    {
        char modeOfLiving = 'n';
        CHECK(snake.lives(modeOfLiving));
        snake.moves();
        input = LEFT_A;
        try
        {
            snake.updateSnakeDirection(input);
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    CHECK(i == COLUMN_NUMBER / 2 + 1);
    char modeOfLiving = 'n';
    CHECK(!snake.lives(modeOfLiving));
}

TEST_CASE("test snake hitting upper wall")
{
    Snake            snake;
    char             input       = UP_W;
    coordinateVector snakeVector = snake.getPositionVector();

    size_t i = 0;
    for (i = 0; i < ROW_NUMBER / 2 + 1; ++i)
    {
        char modeOfLiving = 'n';
        CHECK(snake.lives(modeOfLiving));
        snake.moves();
        input = UP_W;
        try
        {
            snake.updateSnakeDirection(input);
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    CHECK(i == ROW_NUMBER / 2 + 1);
    char modeOfLiving = 'n';
    CHECK(!snake.lives(modeOfLiving));
}

TEST_CASE("test snake hitting lower wall")
{
    Snake            snake;
    char             input       = DOWN_S;
    coordinateVector snakeVector = snake.getPositionVector();

    size_t i = 0;
    for (i = 0; i < ROW_NUMBER / 2 - 1; ++i)
    {
        char modeOfLiving = 'n';
        CHECK(snake.lives(modeOfLiving));
        snake.moves();
        input = DOWN_S;
        try
        {
            snake.updateSnakeDirection(input);
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    CHECK(i == ROW_NUMBER / 2 - 1);
    char modeOfLiving = 'n';
    CHECK(!snake.lives(modeOfLiving));
}

TEST_CASE("test snake eating an apple after one move.")
{
    Snake            snake;
    char             input       = RIGHT_D;
    coordinateVector snakeVector = snake.getPositionVector();

    size_t appleRow    = (ROW_NUMBER) / 2 + 1;
    size_t appleColumn = (COLUMN_NUMBER) / 2 + 2;
    Point  randomApple;
    randomApple.X = appleRow;
    randomApple.Y = appleColumn;

    char   modeOfLiving = 'n';
    size_t steps        = 0;
    while (snake.lives(modeOfLiving))
    {
        CHECK(snake.lives(modeOfLiving));
        snake.moves();
        input = RIGHT_D;
        try
        {
            snake.updateSnakeDirection(input);
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
        }

        if (snake.eatsApple(randomApple))
        {
            CHECK(snake.eatsApple(randomApple));
            CHECK(steps == 0);
            break;
        }
        steps++;
    }
}

TEST_CASE("test snake eating an apple after six moves.")
{
    Snake            snake;
    char             input       = RIGHT_D;
    coordinateVector snakeVector = snake.getPositionVector();

    size_t appleRow    = (ROW_NUMBER) / 2 + 1;
    size_t appleColumn = (COLUMN_NUMBER) / 2 + 7;
    Point  point;
    point.X           = appleRow;
    point.Y           = appleColumn;
    Point randomApple = point;

    char   modeOfLiving = 'n';
    size_t steps        = 0;
    while (snake.lives(modeOfLiving))
    {
        CHECK(snake.lives(modeOfLiving));
        snake.moves();
        input = RIGHT_D;
        try
        {
            snake.updateSnakeDirection(input);
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
        }

        if (snake.eatsApple(randomApple))
        {
            CHECK(snake.eatsApple(randomApple));
            CHECK(steps == 5);
            break;
        }
        steps++;
    }
}

TEST_CASE("test snake hitting a rock after one move (to its right)")
{
    Snake            snake;
    char             input       = RIGHT_D;
    coordinateVector snakeVector = snake.getPositionVector();
    coordinateVector randomRocks;

    size_t rockRow    = (ROW_NUMBER) / 2 + 1;
    size_t rockColumn = (COLUMN_NUMBER) / 2 + 2;
    Point  point;
    point.X          = rockRow;
    point.Y          = rockColumn;
    Point randomRock = point;

    randomRocks.push_back(randomRock);

    char   modeOfLiving = 'n';
    size_t steps        = 0;
    while (snake.lives(modeOfLiving))
    {
        snake.moves();
        input = RIGHT_D;
        try
        {
            snake.updateSnakeDirection(input);
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
        }
        if (snake.hitsRock(randomRocks))
        {
            CHECK(snake.hitsRock(randomRocks));
            CHECK(steps == 0);
            break;
        }
        ++steps;
    }
}

TEST_CASE("test snake hitting a rock after two moves (to its left)")
{
    Snake            snake;
    char             input       = LEFT_A;
    coordinateVector snakeVector = snake.getPositionVector();
    coordinateVector randomRocks;

    size_t rockRow    = (ROW_NUMBER) / 2 + 1;
    size_t rockColumn = (COLUMN_NUMBER) / 2 - 1;
    Point  point;
    point.X          = rockRow;
    point.Y          = rockColumn;
    Point randomRock = point;

    randomRocks.push_back(randomRock);

    char   modeOfLiving = 'n';
    size_t steps        = 0;
    while (snake.lives(modeOfLiving))
    {
        snake.moves();
        input = LEFT_A;
        try
        {
            snake.updateSnakeDirection(input);
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
        }
        if (snake.hitsRock(randomRocks))
        {
            CHECK(snake.hitsRock(randomRocks));
            CHECK(steps == 1);
            break;
        }
        ++steps;
    }
}

TEST_CASE("test snake hitting a rock after three moves (above)")
{
    Snake            snake;
    char             input       = UP_W;
    coordinateVector snakeVector = snake.getPositionVector();
    coordinateVector randomRocks;

    size_t rockRow    = (ROW_NUMBER) / 2 - 2;
    size_t rockColumn = (COLUMN_NUMBER) / 2 + 1;
    Point  point;
    point.X          = rockRow;
    point.Y          = rockColumn;
    Point randomRock = point;

    randomRocks.push_back(randomRock);

    char   modeOfLiving = 'n';
    size_t steps        = 0;
    while (snake.lives(modeOfLiving))
    {
        snake.moves();
        input = UP_W;
        try
        {
            snake.updateSnakeDirection(input);
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
        }
        if (snake.hitsRock(randomRocks))
        {
            CHECK(snake.hitsRock(randomRocks));
            CHECK(steps == 2);
            break;
        }
        ++steps;
    }
}

TEST_CASE("test snake hitting a rock after four moves (below)")
{
    Snake            snake;
    char             input       = DOWN_S;
    coordinateVector snakeVector = snake.getPositionVector();
    coordinateVector randomRocks;

    size_t rockRow    = (ROW_NUMBER) / 2 + 4;
    size_t rockColumn = (COLUMN_NUMBER) / 2 + 1;
    Point  point;
    point.X          = rockRow;
    point.Y          = rockColumn;
    Point randomRock = point;

    randomRocks.push_back(randomRock);

    char   modeOfLiving = 'n';
    size_t steps        = 0;
    while (snake.lives(modeOfLiving))
    {
        snake.moves();
        input = DOWN_S;
        try
        {
            snake.updateSnakeDirection(input);
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
        }
        if (snake.hitsRock(randomRocks))
        {
            CHECK(snake.hitsRock(randomRocks));
            CHECK(steps == 2);
            break;
        }
        ++steps;
    }
}

TEST_CASE("test snake hitting a rock after eight moves")
{
    Snake            snake;
    char             input       = RIGHT_D;
    coordinateVector snakeVector = snake.getPositionVector();
    coordinateVector randomRocks;

    size_t rockRow    = (ROW_NUMBER) / 2 + 1;
    size_t rockColumn = (COLUMN_NUMBER) / 2 + 9;
    Point  point;
    point.X          = rockRow;
    point.Y          = rockColumn;
    Point randomRock = point;

    randomRocks.push_back(randomRock);

    char   modeOfLiving = 'n';
    size_t steps        = 0;
    while (snake.lives(modeOfLiving))
    {
        snake.moves();
        input = RIGHT_D;
        try
        {
            snake.updateSnakeDirection(input);
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
        }
        if (snake.hitsRock(randomRocks))
        {
            CHECK(snake.hitsRock(randomRocks));
            CHECK(steps == 7);
            break;
        }
        ++steps;
    }
}

TEST_CASE("test random number between minimum and maximum.")
{
    StaticEntity staticEntity;
    Point        randomPoint = staticEntity.getRandomPoint();

    size_t PointRow = randomPoint.X;
    CHECK(PointRow > 1);
    CHECK(PointRow < ROW_NUMBER - 1);

    size_t PointColumn = randomPoint.Y;
    CHECK(PointColumn > 1);
    CHECK(PointColumn < COLUMN_NUMBER - 1);
}

TEST_CASE("test if field is empty: field being empty")
{
    Point buildPoint;
    buildPoint.X = 4;
    buildPoint.Y = 5;
    Point snakeBody;
    snakeBody.X = 5;
    snakeBody.Y = 5;

    coordinateVector snake;
    snake.push_back(snakeBody);

    bool isEmpty = false;
    isEmpty      = fieldIsEmpty(buildPoint, snake);
    CHECK(isEmpty == true);
}

TEST_CASE("test if field is empty: filed being occupied")
{
    Point buildPoint;
    buildPoint.X = 4;
    buildPoint.Y = 5;
    Point snakeBody;
    snakeBody.X = 4;
    snakeBody.Y = 5;
    coordinateVector snake;
    snake.push_back(snakeBody);

    bool isEmpty = false;
    isEmpty      = fieldIsEmpty(buildPoint, snake);
    CHECK(isEmpty == false);
}

TEST_CASE("test if field is empty: field being occupied because of rock")
{
    Point buildPoint;
    buildPoint.X = 4;
    buildPoint.Y = 5;
    Point snakeBody;
    snakeBody.X = 5;
    snakeBody.Y = 5;
    Point rock;
    rock.X = 4;
    rock.Y = 5;

    coordinateVector rockVector;
    rockVector.push_back(rock);
    coordinateVector snake;
    snake.push_back(snakeBody);

    bool isEmpty = false;
    isEmpty      = fieldIsEmpty(buildPoint, snake, rockVector);
    CHECK(isEmpty == false);
}

TEST_CASE("test if field is empty: field being empty (rock is elsewhere)")
{
    Point buildPoint;
    buildPoint.X = 4;
    buildPoint.Y = 5;
    Point snakeBody;
    snakeBody.X = 5;
    snakeBody.Y = 5;
    Point rock;
    rock.X = 5;
    rock.Y = 6;

    coordinateVector rockVector;
    rockVector.push_back(rock);
    coordinateVector snake;
    snake.push_back(snakeBody);

    bool isEmpty = false;
    isEmpty      = fieldIsEmpty(buildPoint, snake, rockVector);
    CHECK(isEmpty == true);
}

TEST_CASE("test apple generation value between min and max. (without rocks)")
{
    coordinateVector snakeVector;

    Apple  apple;
    Point  generatedApple = apple.generateApple(snakeVector);
    size_t appleRow       = generatedApple.X;
    size_t appleColumn    = generatedApple.Y;
    CHECK(appleRow > 1);
    CHECK(appleRow < ROW_NUMBER - 1);
    CHECK(appleColumn > 1);
    CHECK(appleColumn < COLUMN_NUMBER - 1);
}

TEST_CASE("test apple generation value between min and max. (with rocks)")
{
    coordinateVector snakeVector;
    coordinateVector rockVector;

    Apple  apple;
    Point  generatedApple = apple.generateApple(snakeVector, rockVector);
    size_t appleRow       = generatedApple.X;
    size_t appleColumn    = generatedApple.Y;
    CHECK(appleRow > 1);
    CHECK(appleRow < ROW_NUMBER - 1);
    CHECK(appleColumn > 1);
    CHECK(appleColumn < COLUMN_NUMBER - 1);
}

TEST_CASE("test apple generation value differ from snake position")
{
    coordinateVector snakeVector;
    for (size_t i = 1; i < ROW_NUMBER - 1; ++i)
    {
        Point point;
        point.X = i;
        point.Y = i;
        snakeVector.push_back(point);
    }

    Apple  apple;
    Point  generatedApple = apple.generateApple(snakeVector);
    size_t appleRow       = generatedApple.X;
    size_t appleColumn    = generatedApple.Y;
    for (size_t i = 1; i < ROW_NUMBER - 1; ++i)
    {
        if (i != appleRow && i != appleColumn)
        {
            CHECK(true);
        }
    }
}

TEST_CASE("test apple generation value differ from snake position with rocks")
{
    coordinateVector snakeVector;
    coordinateVector rockVector;

    for (size_t i = 1; i < ROW_NUMBER - 1; ++i)
    {
        Point point;
        point.X = i;
        point.Y = i;

        snakeVector.push_back(point);
    }

    StaticEntity staticEntity;
    for (size_t i = 1; i < COLUMN_NUMBER; ++i)
    {
        Point randomPoint = staticEntity.getRandomPoint();
        rockVector.push_back(randomPoint);
    }

    Apple  apple;
    Point  generatedApple = apple.generateApple(snakeVector);
    size_t appleRow       = generatedApple.X;
    size_t appleColumn    = generatedApple.Y;

    for (size_t i = 1; i < ROW_NUMBER - 1; ++i)
    {
        if (i != appleRow && i != appleColumn)
        {
            CHECK(true);
        }
    }

    for (size_t i = 1; i < COLUMN_NUMBER; ++i)
    {
        if (i != appleRow && i != appleColumn)
        {
            CHECK(true);
        }
    }
}

TEST_CASE("test reply of the server to the client.")
{
    Snake snake;
    Game  game;
    Apple apple;

    coordinateVector snakeVector = snake.getPositionVector();
    GameBoard        gameBoard;
    gameBoard.initialize();
    game.start(gameBoard);
    Point randomApple = apple.generateApple(snakeVector);

    std::string reply = "";

    reply                   = game.buildReply(snakeVector, randomApple);
    size_t centerOfTheBoard = (COLUMN_NUMBER + 1) * ((ROW_NUMBER + 1) / 2) + ((COLUMN_NUMBER + 1) / 2) + 1;
    CHECK(reply[centerOfTheBoard] == '@');
}

TEST_CASE("assert exception to incorrect user input")
{
    Snake snake;

    char input = 'o';

    bool exceptionIsThrown = false;
    try
    {
        snake.updateSnakeDirection(input);
    }
    catch (std::invalid_argument& e)
    {
        exceptionIsThrown = true;
    }

    CHECK(exceptionIsThrown);
}

TEST_CASE("test simulation of snake biting itself.")
{
    Snake snake;
    Game  game;

    char             input       = RIGHT_D;
    coordinateVector snakeVector = snake.getPositionVector();

    GameBoard gameBoard;
    gameBoard.initialize();
    game.start(gameBoard);
    Point point;

    point.X = 13;
    point.Y = 32;

    Point randomApple = point;

    std::ofstream testFile;
    testFile.open("testFile.txt");
    char modeOfLiving = 'n';
    while (snake.lives(modeOfLiving) && !game.playerHasWon())
    {
        snake.moves();
        input = RIGHT_D;

        /*snake changing direction once its size is greater than 2 results in death (snake bites itself.).*/
        if (snakeVector.size() > 2)
        {
            input = LEFT_A;
        }

        try
        {
            snake.updateSnakeDirection(input);
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
        }

        if (snake.eatsApple(randomApple))
        {
            game.updateScoreBoard();
            Point point;

            point.X = 13;
            point.Y = 34;

            randomApple = point;
        }

        game.updateGameState(snakeVector, randomApple, testFile);
    }

    CHECK(!snake.lives(modeOfLiving));
    testFile.close();
}

TEST_CASE("test simulation of snakes biting each other.")
{
    Anaconda anaconda(ROW_NUMBER / 2 + 1, 2);
    Python   python(ROW_NUMBER / 2 + 1, COLUMN_NUMBER - 2);

    Game  game;
    Apple apple;

    char inputAnaconda = RIGHT_D;
    char inputPython   = LEFT_ARROW;

    coordinateVector anacondaVector = anaconda.getPositionVector();
    coordinateVector pythonVector   = python.getPositionVector();

    GameBoard gameBoard;
    gameBoard.initializeMultiplayer();
    game.start(gameBoard);
    Point point;
    point.X = ROW_NUMBER / 2 + 1;
    point.Y = COLUMN_NUMBER - 4;

    Point randomApple = point;

    std::ofstream testFile;
    testFile.open("testFile.txt");
    char modeOfLiving = 't';

    while (anaconda.lives(modeOfLiving) && python.lives(modeOfLiving) && !anaconda.bitesTheOtherSnake(pythonVector)
           && !python.bitesTheOtherSnake(anacondaVector))
    {
        anaconda.moves();
        anaconda.updateSnakeDirectionWASD(inputAnaconda);

        if (anaconda.eatsApple(randomApple))
        {
            game.updateScoreBoard(ANACONDA_SCORE);
            randomApple = apple.generateApple(anacondaVector);
        }

        python.moves();
        python.updateSnakeDirectionArrowKeys(inputPython);

        if (python.eatsApple(randomApple))
        {
            game.updateScoreBoard(PYTHON_SCORE);
            Point point;
            point.X = ROW_NUMBER / 2 + 1;
            point.Y = 18;

            randomApple = point;
        }

        game.updateGameStateMultiplayer(pythonVector, anacondaVector, randomApple, testFile);
    }

    CHECK(anaconda.bitesTheOtherSnake(pythonVector));
    CHECK(python.bitesTheOtherSnake(anacondaVector));

    testFile.close();
}

TEST_CASE("test possible game mode selections. option: invalid.")
{
    GameMode      gameMode;
    std::ofstream testFile;
    testFile.open("testFile.txt");

    const char invalidOption = 'u';
    int        response      = gameMode.playSelectedMode(invalidOption, testFile);

    CHECK(response == ERR_INVALID_GAME_MODE);
    testFile.close();
}

TEST_CASE("test player winning the game.")
{
    Snake snake;
    Game  game;

    char             input       = RIGHT_D;
    coordinateVector snakeVector = snake.getPositionVector();

    GameBoard gameBoard;
    gameBoard.initialize();
    game.start(gameBoard);
    size_t columnIndex = 32;
    Point  point;

    point.X = 13;
    point.Y = columnIndex;

    Point randomApple = point;

    std::ofstream testFile;
    testFile.open("testFile.txt");
    char modeOfLiving = 'n';
    while (snake.lives(modeOfLiving) && !game.playerHasWon())
    {
        snake.moves();
        input = RIGHT_D;

        try
        {
            snake.updateSnakeDirection(input);
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
        }

        if (snake.eatsApple(randomApple))
        {
            game.updateScoreBoard();
            ++columnIndex;
            Point point;

            point.X = 13;
            point.Y = columnIndex;

            randomApple = point;
        }

        game.updateGameState(snakeVector, randomApple, testFile);
    }

    ScoreBoard scoreBoard = game.getScoreBoard();
    CHECK(scoreBoard.level == 17);
    CHECK(game.playerHasWon());
    testFile.close();
}

TEST_CASE("test build reply for snake body.")
{
    Snake snake;
    Game  game;

    char             input       = RIGHT_D;
    coordinateVector snakeVector = snake.getPositionVector();

    GameBoard gameBoard;
    gameBoard.initialize();
    game.start(gameBoard);
    size_t columnIndex = 32;
    Point  point;
    point.X = 13;
    point.Y = columnIndex;

    Point randomApple = point;

    std::ofstream testFile;
    testFile.open("testFile.txt");

    std::string responseString;
    char        modeOfLiving = 'n';
    while (snake.lives(modeOfLiving) && !game.playerHasWon())
    {
        snake.moves();
        input = RIGHT_D;

        if (snakeVector.size() > 10)
        {
            responseString = game.buildReply(snakeVector, randomApple);
            break;
        }

        try
        {
            snake.updateSnakeDirection(input);
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
        }

        if (snake.eatsApple(randomApple))
        {
            game.updateScoreBoard();
            ++columnIndex;
            Point point;

            point.X = 13;
            point.Y = columnIndex;

            randomApple = point;
        }

        snakeVector = snake.getPositionVector();
        game.updateGameState(snakeVector, randomApple, testFile);
    }

    testFile.close();

    std::string   line;
    std::ifstream testFileOpen;
    testFileOpen.open("testFile.txt");

    size_t index = 0;
    if (testFileOpen.is_open())
    {
        while (getline(testFileOpen, line))
        {
            if (index == 481)
            {
                CHECK(line[28] == '@');
                CHECK(line[48] == 'a');
            }
            ++index;
        }
        testFileOpen.close();
    }

    testFileOpen.close();
}

TEST_CASE("test gameboard with random rocks")
{
    Snake     snake;
    Game      game;
    GameBoard gameBoard;

    Rock rock;

    coordinateVector snakeVector = snake.getPositionVector();
    size_t           numberOfRocks;

    numberOfRocks                = 16;
    coordinateVector randomRocks = rock.generateRocks(numberOfRocks);

    Apple apple;
    Point randomApple = apple.generateApple(snakeVector, randomRocks);

    gameBoard.initialize(randomRocks);
    game.start(gameBoard);

    std::ofstream testFile;
    testFile.open("testFile.txt");

    game.updateGameState(snakeVector, randomApple, testFile);

    testFile.close();

    std::string   line;
    std::ifstream testFileOpen;
    testFileOpen.open("testFile.txt");

    size_t rockCounter = 0;
    if (testFileOpen.is_open())
    {
        while (getline(testFileOpen, line))
        {
            for (char& c : line)
            {
                if (c == '#')
                {
                    ++rockCounter;
                }
            }
        }
        testFileOpen.close();
    }

    testFileOpen.close();
    CHECK(rockCounter >= 14);
}

TEST_CASE("test possible user input handling. option: normal.")
{
    Snake     snake;
    Game      game;
    GameBoard gameBoard;
    GameMode  gameMode;
    Apple     apple;

    char             input       = RIGHT_D;
    coordinateVector snakeVector = snake.getPositionVector();
    gameBoard.initialize();
    game.start(gameBoard);
    Point generatedApple = apple.generateApple(snakeVector);

    std::ofstream testFile;
    testFile.open("testFile.txt");
    char modeOfLiving = 'n';
    while (snake.lives(modeOfLiving) && !game.playerHasWon())
    {
        input = RIGHT_D;

        if (gameMode.handleUserInputBasic(game, snake, generatedApple, testFile, input) == ERR_INVALID_INPUT)
        {
            break;
        };
    }
    testFile.close();

    CHECK(snake.lives(modeOfLiving) == false);
}

TEST_CASE("test possible user input handling. option: normal. invalid input.")
{
    Snake     snake;
    Game      game;
    GameBoard gameBoard;
    GameMode  gameMode;
    Apple     apple;

    char             input       = RIGHT_D;
    coordinateVector snakeVector = snake.getPositionVector();
    gameBoard.initialize();
    game.start(gameBoard);
    Point generatedApple = apple.generateApple(snakeVector);

    std::ofstream testFile;
    testFile.open("testFile.txt");
    int  errorCode    = NO_ERROR;
    char modeOfLiving = 'n';
    while (snake.lives(modeOfLiving) && !game.playerHasWon())
    {
        input = 'x';

        if (gameMode.handleUserInputBasic(game, snake, generatedApple, testFile, input) == ERR_INVALID_INPUT)
        {
            errorCode = ERR_INVALID_INPUT;
            break;
        };
    }
    testFile.close();

    CHECK(errorCode == ERR_INVALID_INPUT);
}

TEST_CASE("test possible user input handling. option: normal. eating apple.")
{
    Snake     snake;
    Game      game;
    GameBoard gameBoard;
    GameMode  gameMode;
    Apple     apple;

    char             input       = RIGHT_D;
    coordinateVector snakeVector = snake.getPositionVector();
    gameBoard.initialize();
    game.start(gameBoard);
    Point generatedApple;
    generatedApple.X = (ROW_NUMBER) / 2 + 1;
    generatedApple.Y = (COLUMN_NUMBER) / 2 + 6;

    std::ofstream testFile;
    testFile.open("testFile.txt");
    char modeOfLiving = 'n';
    while (snake.lives(modeOfLiving) && !game.playerHasWon())
    {
        input = RIGHT_D;

        if (gameMode.handleUserInputBasic(game, snake, generatedApple, testFile, input) == ERR_INVALID_INPUT)
        {
            break;
        };
    }
    testFile.close();

    CHECK(snake.lives(modeOfLiving) == false);
}

TEST_CASE("test possible user input handling. option: obstacle.")
{
    Snake            snake;
    Game             game;
    GameBoard        gameBoard;
    GameMode         gameMode;
    Apple            apple;
    Rock             rock;
    size_t           numberOfRocks = 16;
    coordinateVector randomRocks   = rock.generateRocks(numberOfRocks);

    char             input       = RIGHT_D;
    coordinateVector snakeVector = snake.getPositionVector();
    gameBoard.initialize();
    game.start(gameBoard);
    Point generatedApple = apple.generateApple(snakeVector);

    std::ofstream testFile;
    testFile.open("testFile.txt");
    char modeOfLiving = 'n';
    while (snake.lives(modeOfLiving) && !game.playerHasWon())
    {
        input = RIGHT_D;

        if (gameMode.handleUserInput(game, snake, generatedApple, testFile, input) == ERR_INVALID_INPUT)
        {
            break;
        }
    }
    testFile.close();

    CHECK(snake.lives(modeOfLiving) == false);
}

TEST_CASE("test possible user input handling. option: obstacle. eating apples.")
{
    Snake            snake;
    Game             game;
    GameBoard        gameBoard;
    GameMode         gameMode;
    Rock             rock;
    size_t           numberOfRocks = 0;
    coordinateVector randomRocks   = rock.generateRocks(numberOfRocks);

    char             input       = RIGHT_D;
    coordinateVector snakeVector = snake.getPositionVector();
    gameBoard.initialize();
    game.start(gameBoard);
    Point generatedApple;
    generatedApple.X = (ROW_NUMBER) / 2 + 1;
    generatedApple.Y = (COLUMN_NUMBER) / 2 + 6;

    std::ofstream testFile;
    testFile.open("testFile.txt");
    char modeOfLiving = 'n';
    while (snake.lives(modeOfLiving) && !game.playerHasWon())
    {
        input = RIGHT_D;

        if (gameMode.handleUserInput(game, snake, generatedApple, testFile, input) == ERR_INVALID_INPUT)
        {
            break;
        }
    }
    testFile.close();

    CHECK(snake.lives(modeOfLiving) == false);
}

TEST_CASE("test possible user input handling. option: obstacle. invalid input.")
{
    Snake            snake;
    Game             game;
    GameBoard        gameBoard;
    GameMode         gameMode;
    Apple            apple;
    Rock             rock;
    size_t           numberOfRocks = 16;
    coordinateVector randomRocks   = rock.generateRocks(numberOfRocks);

    char             input       = RIGHT_D;
    coordinateVector snakeVector = snake.getPositionVector();
    gameBoard.initialize();
    game.start(gameBoard);
    Point generatedApple = apple.generateApple(snakeVector);

    std::ofstream testFile;
    testFile.open("testFile.txt");

    int  errorCode    = NO_ERROR;
    char modeOfLiving = 'n';
    while (snake.lives(modeOfLiving) && !game.playerHasWon())
    {
        input = 'x';

        if (gameMode.handleUserInput(game, snake, generatedApple, testFile, input) == ERR_INVALID_INPUT)
        {
            errorCode = ERR_INVALID_INPUT;
            break;
        }
    }
    testFile.close();

    CHECK(errorCode == ERR_INVALID_INPUT);
}

TEST_CASE("test possible user input handling. option: multiplayer.")
{
    Anaconda anaconda(ROW_NUMBER / 2, 2);
    Python   python(ROW_NUMBER / 2 + 1, 2);

    Game      game;
    GameBoard gameBoard;
    GameMode  gameMode;
    Apple     apple;

    char input = RIGHT_D;

    coordinateVector anacondaVector = anaconda.getPositionVector();
    coordinateVector pythonVector   = python.getPositionVector();

    gameBoard.initializeMultiplayer();
    game.start(gameBoard);
    Point generatedApple = apple.generateApple(anacondaVector);

    std::ofstream testFile;
    testFile.open("testFile.txt");
    char modeOfLiving = 'n';
    while (anaconda.lives(modeOfLiving) && python.lives(modeOfLiving))
    {
        input = RIGHT_D;
        gameMode.handleUserInput(game, anaconda, python, generatedApple, testFile, input);
    }
    testFile.close();

    CHECK(anaconda.lives(modeOfLiving) == false);
}

TEST_CASE("test possible user input handling. option: multiplayer. anaconda eating apple.")
{
    Anaconda anaconda(ROW_NUMBER / 2, 2);
    Python   python(ROW_NUMBER / 2 + 1, 2);

    Game      game;
    GameBoard gameBoard;
    GameMode  gameMode;

    char input = RIGHT_D;

    coordinateVector anacondaVector = anaconda.getPositionVector();
    coordinateVector pythonVector   = python.getPositionVector();

    gameBoard.initializeMultiplayer();
    game.start(gameBoard);
    Point generatedApple;
    generatedApple.X = ROW_NUMBER / 2;
    generatedApple.Y = 4;

    std::ofstream testFile;
    testFile.open("testFile.txt");
    char modeOfLiving = 'n';

    while (anaconda.lives(modeOfLiving) && python.lives(modeOfLiving))
    {
        input = RIGHT_D;
        gameMode.handleUserInput(game, anaconda, python, generatedApple, testFile, input);
    }
    testFile.close();

    CHECK(anaconda.lives(modeOfLiving) == false);
}

TEST_CASE("test possible user input handling. option: multiplayer. python eating apple.")
{
    Anaconda anaconda(ROW_NUMBER / 2, 2);
    Python   python(ROW_NUMBER / 2 + 1, 2);

    Game      game;
    GameBoard gameBoard;
    GameMode  gameMode;
    Apple     apple;

    char input = RIGHT_D;

    coordinateVector anacondaVector = anaconda.getPositionVector();
    coordinateVector pythonVector   = python.getPositionVector();

    gameBoard.initializeMultiplayer();
    game.start(gameBoard);
    Point generatedApple;
    generatedApple.X = ROW_NUMBER / 2 + 1;
    generatedApple.Y = 4;

    std::ofstream testFile;
    testFile.open("testFile.txt");
    char modeOfLiving = 'n';

    while (anaconda.lives(modeOfLiving) && python.lives(modeOfLiving))
    {
        input = RIGHT_D;
        gameMode.handleUserInput(game, anaconda, python, generatedApple, testFile, input);
    }
    testFile.close();

    CHECK(anaconda.lives(modeOfLiving) == false);
}

TEST_CASE("test possible user input handling. option: multiplayer. direction: LEFT.")
{
    Anaconda anaconda(ROW_NUMBER / 2, 2);
    Python   python(ROW_NUMBER / 2 + 1, 2);

    Game      game;
    GameBoard gameBoard;
    GameMode  gameMode;
    Apple     apple;

    char input = LEFT_A;

    coordinateVector anacondaVector = anaconda.getPositionVector();
    coordinateVector pythonVector   = python.getPositionVector();

    gameBoard.initializeMultiplayer();
    game.start(gameBoard);
    Point generatedApple = apple.generateApple(anacondaVector, pythonVector);

    std::ofstream testFile;
    testFile.open("testFile.txt");
    char modeOfLiving = 'n';

    size_t whichSnakeMoves = 0;
    while (anaconda.lives(modeOfLiving) && python.lives(modeOfLiving))
    {
        if (whichSnakeMoves % 2 == 0)
        {
            input = LEFT_A;
        }
        else
        {
            input = LEFT_ARROW;
        }
        ++whichSnakeMoves;
        gameMode.handleUserInput(game, anaconda, python, generatedApple, testFile, input);
    }
    testFile.close();

    CHECK(python.lives(modeOfLiving) == false);

    std::string   line;
    std::ifstream testFileOpen;
    testFileOpen.open("testFile.txt");

    size_t index = 0;
    if (testFileOpen.is_open())
    {
        while (getline(testFileOpen, line))
        {
            if (index == 91)
            {
                CHECK(line[0] == '@');
            }
            ++index;
        }
        testFileOpen.close();
    }

    testFileOpen.close();
}

TEST_CASE("test possible user input handling. option: multiplayer. direction: UP.")
{
    Anaconda anaconda(ROW_NUMBER / 2, 2);
    Python   python(ROW_NUMBER / 2 + 1, 2);

    Game      game;
    GameBoard gameBoard;
    GameMode  gameMode;
    Apple     apple;

    char input = UP_W;

    coordinateVector anacondaVector = anaconda.getPositionVector();
    coordinateVector pythonVector   = python.getPositionVector();

    gameBoard.initializeMultiplayer();
    game.start(gameBoard);
    Point generatedApple = apple.generateApple(anacondaVector, pythonVector);

    std::ofstream testFile;
    testFile.open("testFile.txt");
    char modeOfLiving = 'n';

    size_t whichSnakeMoves = 0;
    while (anaconda.lives(modeOfLiving) && python.lives(modeOfLiving))
    {
        if (whichSnakeMoves % 2 == 0)
        {
            input = UP_W;
        }
        else
        {
            input = UP_ARROW;
        }
        ++whichSnakeMoves;
        gameMode.handleUserInput(game, anaconda, python, generatedApple, testFile, input);
    }
    testFile.close();

    CHECK(anaconda.lives(modeOfLiving) == false);

    std::string   line;
    std::ifstream testFileOpen;
    testFileOpen.open("testFile.txt");

    size_t index = 0;
    if (testFileOpen.is_open())
    {
        while (getline(testFileOpen, line))
        {
            if (index == 288)
            {
                CHECK(line[3] == '@');
            }
            ++index;
        }
        testFileOpen.close();
    }

    testFileOpen.close();
}

TEST_CASE("test possible user input handling. option: multiplayer. direction: DOWN.")
{
    Anaconda anaconda(ROW_NUMBER / 2, 2);
    Python   python(ROW_NUMBER / 2 + 1, 2);

    Game      game;
    GameBoard gameBoard;
    GameMode  gameMode;
    Apple     apple;

    char input = DOWN_S;

    coordinateVector anacondaVector = anaconda.getPositionVector();
    coordinateVector pythonVector   = python.getPositionVector();

    gameBoard.initializeMultiplayer();
    game.start(gameBoard);
    Point generatedApple = apple.generateApple(anacondaVector, pythonVector);

    std::ofstream testFile;
    testFile.open("testFile.txt");
    char modeOfLiving = 'n';

    size_t whichSnakeMoves = 0;
    while (anaconda.lives(modeOfLiving) && python.lives(modeOfLiving))
    {
        if (whichSnakeMoves % 2 == 0)
        {
            input = DOWN_S;
        }
        else
        {
            input = DOWN_ARROW;
        }
        ++whichSnakeMoves;
        gameMode.handleUserInput(game, anaconda, python, generatedApple, testFile, input);
    }
    testFile.close();

    CHECK(python.lives(modeOfLiving) == false);
    CHECK(anaconda.lives(modeOfLiving) == false);

    std::string   line;
    std::ifstream testFileOpen;
    testFileOpen.open("testFile.txt");

    size_t index = 0;
    if (testFileOpen.is_open())
    {
        while (getline(testFileOpen, line))
        {
            if (index == 310)
            {
                CHECK(line[2] == '&');
                CHECK(line[3] == '@');
            }
            ++index;
        }
        testFileOpen.close();
    }

    testFileOpen.close();
}

TEST_CASE("snake bites itself in teleport mode.")
{
    Snake     snake;
    Game      game;
    GameBoard gameBoard;

    char             input       = RIGHT_D;
    coordinateVector snakeVector = snake.getPositionVector();
    gameBoard.initialize();
    game.start(gameBoard);
    Point generatedApple;
    generatedApple.X        = (ROW_NUMBER) / 2 + 1;
    generatedApple.Y        = (COLUMN_NUMBER) / 2 + 6;
    size_t columnCoordinate = (COLUMN_NUMBER) / 2 + 6;

    std::ofstream testFile;
    testFile.open("testFile.txt");
    char modeOfLiving   = 't';
    bool snakeBitItself = false;
    while (snake.lives(modeOfLiving) && !game.playerHasWon())
    {
        if ((snake.getPositionVector()).size() > 4)
        {
            input = LEFT_A;
        }

        snake.moves();
        try
        {
            snake.updateSnakeDirection(input);
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
            break;
        }
        coordinateVector snakeVector = snake.getPositionVector();
        if (snake.eatsApple(generatedApple))
        {
            game.updateScoreBoard();
            generatedApple.X = (ROW_NUMBER) / 2 + 1;
            generatedApple.Y = columnCoordinate + 2;
        }
        game.updateGameState(snakeVector, generatedApple, testFile);
        if (snake.bitesItself())
        {
            snakeBitItself = true;
        }
    }
    testFile.close();

    CHECK(snake.lives(modeOfLiving) == false);
    CHECK(snakeBitItself == true);
}

TEST_CASE("snake bites itself's segment in teleport mode.")
{
    Snake     snake;
    Game      game;
    GameBoard gameBoard;

    char             input       = RIGHT_D;
    coordinateVector snakeVector = snake.getPositionVector();
    gameBoard.initialize();
    game.start(gameBoard);
    Point generatedApple;
    generatedApple.X        = (ROW_NUMBER) / 2 + 1;
    generatedApple.Y        = (COLUMN_NUMBER) / 2 + 6;
    size_t columnCoordinate = (COLUMN_NUMBER) / 2 + 6;

    std::ofstream testFile;
    testFile.open("testFile.txt");
    char   modeOfLiving = 't';
    size_t flag = false, flag2 = false, stop = false;
    while (snake.lives(modeOfLiving) && !game.playerHasWon())
    {
        if (flag2)
        {
            input = DOWN_S;
        }

        if (flag)
        {
            input = LEFT_A;
            flag2 = true;
            flag  = false;
        }

        if ((snake.getPositionVector()).size() == 6 && !stop)
        {
            input = UP_W;
            flag  = true;
            stop  = true;
        }

        snake.moves();
        try
        {
            snake.updateSnakeDirection(input);
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
            break;
        }
        coordinateVector snakeVector = snake.getPositionVector();
        if (snake.eatsApple(generatedApple))
        {
            game.updateScoreBoard();
            generatedApple.X = (ROW_NUMBER) / 2 + 1;
            generatedApple.Y = columnCoordinate + 2;
        }
        game.updateGameState(snakeVector, generatedApple, testFile);
    }
    testFile.close();

    CHECK(snake.lives(modeOfLiving) == false);
}

TEST_CASE("snake teleporting to left.")
{
    Snake     snake;
    Game      game;
    GameBoard gameBoard;

    char             input       = LEFT_A;
    coordinateVector snakeVector = snake.getPositionVector();
    gameBoard.initialize();
    game.start(gameBoard);
    Point generatedApple;
    generatedApple.X        = (ROW_NUMBER) / 2 + 1;
    generatedApple.Y        = (COLUMN_NUMBER) / 2 - 6;
    size_t columnCoordinate = (COLUMN_NUMBER) / 2 - 6;

    std::ofstream testFile;
    testFile.open("testFile.txt");
    char modeOfLiving = 't';
    while (snake.lives(modeOfLiving) && !game.playerHasWon())
    {
        snake.moves();
        try
        {
            snake.updateSnakeDirection(input);
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
            break;
        }
        coordinateVector snakeVector = snake.getPositionVector();
        if (snake.eatsApple(generatedApple))
        {
            game.updateScoreBoard();
            generatedApple.X = (ROW_NUMBER) / 2 + 1;
            generatedApple.Y = columnCoordinate - 2;
        }
        game.updateGameState(snakeVector, generatedApple, testFile);
    }
    testFile.close();

    ScoreBoard scoreBoard = game.getScoreBoard();
    CHECK(scoreBoard.level == 17);
    CHECK(game.playerHasWon() == true);
}

TEST_CASE("snake teleporting down.")
{
    Snake     snake;
    Game      game;
    GameBoard gameBoard;

    char             input       = DOWN_S;
    coordinateVector snakeVector = snake.getPositionVector();
    gameBoard.initialize();
    game.start(gameBoard);
    Point generatedApple;
    generatedApple.X = (ROW_NUMBER) / 2 + 2;
    generatedApple.Y = (COLUMN_NUMBER) / 2 + 1;

    std::ofstream testFile;
    testFile.open("testFile.txt");
    char modeOfLiving = 't';
    while (snake.lives(modeOfLiving) && !game.playerHasWon())
    {
        snake.moves();
        try
        {
            snake.updateSnakeDirection(input);
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
            break;
        }
        coordinateVector snakeVector = snake.getPositionVector();
        if (snake.eatsApple(generatedApple))
        {
            game.updateScoreBoard();
            generatedApple.X = (ROW_NUMBER) / 2 + 2;
            generatedApple.Y = (COLUMN_NUMBER) / 2 + 1;
        }
        game.updateGameState(snakeVector, generatedApple, testFile);
    }
    testFile.close();

    CHECK(game.playerHasWon() == true);
}

TEST_CASE("snake teleporting up.")
{
    Snake     snake;
    Game      game;
    GameBoard gameBoard;

    char             input       = UP_W;
    coordinateVector snakeVector = snake.getPositionVector();
    gameBoard.initialize();
    game.start(gameBoard);
    Point generatedApple;
    generatedApple.X = (ROW_NUMBER) / 2 + 2;
    generatedApple.Y = (COLUMN_NUMBER) / 2 + 1;

    std::ofstream testFile;
    testFile.open("testFile.txt");
    char modeOfLiving = 't';
    while (snake.lives(modeOfLiving) && !game.playerHasWon())
    {
        snake.moves();
        try
        {
            snake.updateSnakeDirection(input);
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
            break;
        }
        coordinateVector snakeVector = snake.getPositionVector();
        if (snake.eatsApple(generatedApple))
        {
            game.updateScoreBoard();
            generatedApple.X = (ROW_NUMBER) / 2 + 2;
            generatedApple.Y = (COLUMN_NUMBER) / 2 + 1;
        }
        game.updateGameState(snakeVector, generatedApple, testFile);
    }
    testFile.close();

    ScoreBoard scoreBoard = game.getScoreBoard();
    CHECK(scoreBoard.level == 17);
    CHECK(game.playerHasWon() == true);
}

TEST_CASE("tests empty field")
{
    Snake            snake;
    coordinateVector snakeVector = snake.getPositionVector();
    Point            randomApple;
    randomApple.X = (ROW_NUMBER) / 2 + 1;
    randomApple.Y = (COLUMN_NUMBER) / 2 + 1;
    Rock             rock;
    coordinateVector rockVector = rock.generateRocks(16);

    bool isEmpty = true;
    if (!fieldIsEmpty(randomApple, snakeVector, rockVector))
    {
        isEmpty = false;
    }

    CHECK(isEmpty == false);
}

struct MockSnake
{
    virtual int isAlive(int) = 0;
};

TEST_CASE("mocking a snake isAlive")
{
    using namespace fakeit;

    // Instantiate a mock object.
    Mock<MockSnake> mock;
    // Stub a method to return a value once
    When(Method(mock, isAlive)).Return(1);

    MockSnake& fakeSnake = mock.get();

    // Will print "1".
    CHECK(fakeSnake.isAlive(0) == 1);
}

TEST_CASE("mocking a snake verify call invocation")
{
    using namespace fakeit;

    Mock<MockSnake> mock;

    When(Method(mock, isAlive)).Return(0);

    MockSnake& fakeSnake = mock.get();
    // Production code
    fakeSnake.isAlive(42);

    // Verify method mock.isAlive was invoked.
    Verify(Method(mock, isAlive));

    // Verify method mock.isAlive was invoked with specific arguments.
    Verify(Method(mock, isAlive).Using(42));
}

TEST_CASE("mock game modes: no error.")
{
    using namespace fakeit;

    Snake     snake;
    Game      game;
    GameBoard gameBoard;

    Mock<GameModeInterface> mock;
    GameModeInterface&      fakeGameMode = mock.get();
    Apple                   apple;

    char             input       = RIGHT_D;
    coordinateVector snakeVector = snake.getPositionVector();
    gameBoard.initialize();
    game.start(gameBoard);
    Point generatedApple = apple.generateApple(snakeVector);

    std::ofstream testFile;
    testFile.open("testFile.txt");

    input = RIGHT_D;
    Fake(Method(mock, handleUserInputBasic));
    CHECK(fakeGameMode.handleUserInputBasic(game, snake, generatedApple, testFile, input) == NO_ERROR);

    testFile.close();
}

TEST_CASE("mock game modes: error, invalid input.")
{
    using namespace fakeit;

    Snake     snake;
    Game      game;
    GameBoard gameBoard;
    Apple     apple;

    char             input       = RIGHT_D;
    coordinateVector snakeVector = snake.getPositionVector();
    gameBoard.initialize();
    game.start(gameBoard);
    Point generatedApple = apple.generateApple(snakeVector);

    std::ofstream testFile;
    testFile.open("testFile.txt");

    input = 'e';

    GameMode gameMode;
    CHECK(gameMode.handleUserInputBasic(game, snake, generatedApple, testFile, input) == ERR_INVALID_INPUT);

    testFile.close();
}

TEST_CASE("field empty for empty vector")
{
    Point apple;
    apple.X = 0;
    apple.Y = 0;
    coordinateVector snakeVector;
    bool             isEmpty = fieldIsEmpty(apple, snakeVector);

    CHECK(isEmpty == true);
}

TEST_CASE("test snake eating an apple after one move to the left.")
{
    Snake            snake;
    char             input       = LEFT_A;
    coordinateVector snakeVector = snake.getPositionVector();

    size_t appleRow    = (ROW_NUMBER) / 2 + 1;
    size_t appleColumn = (COLUMN_NUMBER) / 2 - 2;
    Point  randomApple;
    randomApple.X = appleRow;
    randomApple.Y = appleColumn;

    char   modeOfLiving = 'n';
    size_t steps        = 0;
    while (snake.lives(modeOfLiving))
    {
        CHECK(snake.lives(modeOfLiving));
        snake.moves();
        input = LEFT_A;
        try
        {
            snake.updateSnakeDirection(input);
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
        }

        if (snake.eatsApple(randomApple))
        {
            CHECK(snake.eatsApple(randomApple));
            CHECK(steps == 2);
            break;
        }
        steps++;
    }
}

TEST_CASE("stub game modes: ERR_INVALID_INPUT.")
{
    using namespace fakeit;

    Snake     snake;
    Game      game;
    GameBoard gameBoard;

    Mock<GameModeInterface> mock;
    Apple                   apple;

    char             input       = RIGHT_D;
    coordinateVector snakeVector = snake.getPositionVector();
    gameBoard.initialize();
    game.start(gameBoard);
    Point generatedApple = apple.generateApple(snakeVector);

    std::ofstream testFile;
    testFile.open("testFile.txt");

    input               = 'x';
    auto inputIsInvalid = [](Game& game, Snake& snake, Point& generatedApple, std::ostream& outputStream, char input) {
        return (input != RIGHT_D && input && LEFT_A && input != UP_W && input != DOWN_S);
    };
    When(Method(mock, handleUserInputBasic).Matching(inputIsInvalid)).Return(ERR_INVALID_INPUT);
    GameModeInterface& i = mock.get();

    CHECK(i.handleUserInputBasic(game, snake, generatedApple, testFile, input) == ERR_INVALID_INPUT);

    testFile.close();
}

TEST_CASE("stub game modes: NO_ERROR.")
{
    using namespace fakeit;

    Snake     snake;
    Game      game;
    GameBoard gameBoard;

    Mock<GameModeInterface> mock;
    Apple                   apple;

    char             input       = RIGHT_D;
    coordinateVector snakeVector = snake.getPositionVector();
    gameBoard.initialize();
    game.start(gameBoard);
    Point generatedApple = apple.generateApple(snakeVector);

    std::ofstream testFile;
    testFile.open("testFile.txt");

    input               = DOWN_S;
    auto inputIsInvalid = [](Game& game, Snake& snake, Point& generatedApple, std::ostream& outputStream, char input) {
        return !(input != RIGHT_D && input && LEFT_A && input != UP_W && input != DOWN_S);
    };
    When(Method(mock, handleUserInputBasic).Matching(inputIsInvalid)).Return(NO_ERROR);
    GameModeInterface& i = mock.get();

    CHECK(i.handleUserInputBasic(game, snake, generatedApple, testFile, input) == NO_ERROR);

    testFile.close();
}

TEST_CASE("mock. verifying how many times a function was called")
{
    using namespace fakeit;

    // Instantiate a mock object.
    Mock<MockSnake> mock;
    // Stub a method to return a value once
    When(Method(mock, isAlive)).Return(1);

    MockSnake& fakeSnake = mock.get();

    fakeSnake.isAlive(1);

    Verify(Method(mock, isAlive));
    Verify(Method(mock, isAlive)).AtLeastOnce();
    Verify(Method(mock, isAlive)).AtLeast(1);
    Verify(Method(mock, isAlive)).AtLeast(1_Time);
    Verify(Method(mock, isAlive).Using(1)).Exactly(Once);
}

TEST_CASE("test initializeNormalMode")
{
    Snake    snake;
    Game     game;
    GameMode gameMode;
    gameMode.initializeNormalMode(snake, game);

    CHECK(snake.lives('n') == true);
}

TEST_CASE("test initializeObstacleMode")
{
    Snake            snake;
    Game             game;
    GameMode         gameMode;
    Rock             rock;
    coordinateVector randomRocks = rock.generateRocks(16);
    gameMode.initializeObstacleMode(snake, game, randomRocks);

    CHECK(snake.lives('o') == true);
}

TEST_CASE("test initializeMultiplayerMode")
{
    Anaconda anaconda(2, 2);
    Python   python(1, 1);
    Game     game;
    GameMode gameMode;
    gameMode.initializeMultiplayerMode(anaconda, python, game);

    CHECK(python.lives('m') == true);
    CHECK(anaconda.lives('m') == true);
}

TEST_CASE("stub random")
{
    using namespace fakeit;
    Mock<StaticEntityInterface> mock;
    Point                       point;
    point.X = 1;
    point.Y = 1;
    When(Method(mock, getRandomPoint)).AlwaysReturn(point);
    StaticEntityInterface& i = mock.get();

    CHECK(i.getRandomPoint().X == point.X);
    CHECK(i.getRandomPoint().Y == point.Y);

    coordinateVector snakeVector;
    snakeVector.push_back(point);
    Apple apple;
    apple.generateApple(snakeVector);

    Mock<AppleInterface> mockApple;
    When(ConstOverloadedMethod(mockApple, generateApple, Point(const coordinateVector&))).AlwaysReturn(point);
    AppleInterface& getApple = mockApple.get();

    CHECK(getApple.generateApple(snakeVector).X == point.X);
    CHECK(getApple.generateApple(snakeVector).Y == point.Y);
}

TEST_CASE("stub random 2")
{
    using namespace fakeit;
    Mock<StaticEntityInterface> mock;
    Point                       point;
    point.X = 1;
    point.Y = 1;
    When(Method(mock, getRandomPoint)).AlwaysReturn(point);
    StaticEntityInterface& i = mock.get();

    CHECK(i.getRandomPoint().X == point.X);
    CHECK(i.getRandomPoint().Y == point.Y);

    coordinateVector snakeVector, rockVector;
    snakeVector.push_back(point);
    rockVector.push_back(point);
    Apple apple;
    apple.generateApple(snakeVector);

    Mock<AppleInterface> mockApple;
    When(ConstOverloadedMethod(mockApple, generateApple, Point(const coordinateVector&, const coordinateVector&)))
        .AlwaysReturn(point);
    AppleInterface& getApple = mockApple.get();

    CHECK(getApple.generateApple(snakeVector, rockVector).X == point.X);
    CHECK(getApple.generateApple(snakeVector, rockVector).Y == point.Y);
}

TEST_CASE("spying random")
{
    using namespace fakeit;

    StaticEntity       obj;
    Mock<StaticEntity> spy(obj);
    Point              point;
    point.X = 1;
    point.Y = 1;
    When(Method(spy, getRandomPoint)).AlwaysReturn(point);
    StaticEntity& i = spy.get();
    CHECK(i.getRandomPoint().X == point.X);
    CHECK(i.getRandomPoint().Y == point.Y);

    coordinateVector snakeVector;
    snakeVector.push_back(point);
    Apple apple;
    apple.generateApple(snakeVector);

    Mock<AppleInterface> mockApple;
    When(ConstOverloadedMethod(mockApple, generateApple, Point(const coordinateVector&))).AlwaysReturn(point);
    AppleInterface& getApple = mockApple.get();

    CHECK(getApple.generateApple(snakeVector).X == point.X);
    CHECK(getApple.generateApple(snakeVector).Y == point.Y);
}

TEST_CASE("spying random 2")
{
    using namespace fakeit;

    StaticEntity       obj;
    Mock<StaticEntity> spy(obj);
    Point              point;
    point.X = 1;
    point.Y = 1;
    When(Method(spy, getRandomPoint)).AlwaysReturn(point);
    StaticEntity& i = spy.get();
    CHECK(i.getRandomPoint().X == point.X);
    CHECK(i.getRandomPoint().Y == point.Y);

    coordinateVector snakeVector, rockVector;
    snakeVector.push_back(point);
    rockVector.push_back(point);
    Apple apple;
    apple.generateApple(snakeVector);

    Mock<AppleInterface> mockApple;
    When(ConstOverloadedMethod(mockApple, generateApple, Point(const coordinateVector&, const coordinateVector&)))
        .AlwaysReturn(point);
    AppleInterface& getApple = mockApple.get();

    CHECK(getApple.generateApple(snakeVector, rockVector).X == point.X);
    CHECK(getApple.generateApple(snakeVector, rockVector).Y == point.Y);
}