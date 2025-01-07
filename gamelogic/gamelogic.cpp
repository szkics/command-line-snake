#include "gamelogic.h"

const matrix& GameBoard::getMatrix()
{
    return gameBoardMatrix;
}

void GameBoard::initialize()
{
    for (size_t i = 0; i < ROW_NUMBER; ++i)
    {
        for (size_t j = 0; j < COLUMN_NUMBER; ++j)
        {
            gameBoardMatrix[i][j] = " ";
        }
    }
}

void GameBoard::initializeMultiplayer()
{
    for (size_t i = 0; i < ROW_NUMBER; ++i)
    {
        for (size_t j = 0; j < COLUMN_NUMBER; ++j)
        {
            gameBoardMatrix[i][j] = " ";
        }
    }
}

bool GameBoard::fieldIsOccupied(const coordinateVector& vector, const size_t& i, const size_t& j)
{
    coordinateVector::const_iterator it = vector.begin();

    while (it != vector.end())
    {
        if ((*it).X == i && (*it).Y == j)
        {
            return true;
        }
        ++it;
    }
    return false;
}

void GameBoard::initialize(const coordinateVector& rockVector)
{
    for (size_t i = 0; i < ROW_NUMBER; ++i)
    {
        for (size_t j = 0; j < COLUMN_NUMBER; ++j)
        {
            if (!fieldIsOccupied(rockVector, i, j))
            {
                gameBoardMatrix[i][j] = " ";
            }
            else
            {
                gameBoardMatrix[i][j] = "#";
            }
        }
    }
}

ScoreBoard Game::getScoreBoard()
{
    return scoreBoard;
}

void Game::start(GameBoard& gameBoard)
{
    gameBoardMatrix = gameBoard.getMatrix();
}

void Game::render(const coordinateVector& snakeVector, const Point& apple, std::ostream& outputStream)
{
    for (size_t i = 0; i < ROW_NUMBER; ++i)
    {
        for (size_t j = 0; j < COLUMN_NUMBER; ++j)
        {
            Point snakeHead = snakeVector[0];
            if (i == 0 || j == 0 || i == ROW_NUMBER - 1 || j == COLUMN_NUMBER - 1)
            {
                outputStream << ".";
            }
            else if ((snakeHead).X == i && (snakeHead).Y == j)
            {
                outputStream << "@";
            }
            else if ((apple).X == i && (apple).Y == j)
            {
                outputStream << "a";
            }
            else
            {
                coordinateVector::const_iterator it = snakeVector.begin();
                ++it;
                bool fieldIsOccupied = false;
                while (it != snakeVector.end())
                {
                    if ((*it).X == i && (*it).Y == j)
                    {
                        outputStream << "o";
                        fieldIsOccupied = true;
                    }
                    ++it;
                }
                if (!fieldIsOccupied)
                {
                    outputStream << gameBoardMatrix[i][j];
                }
            }
        }
        outputStream << std::endl;
    }

    outputStream << "Score: " << scoreBoard.score << " | Level: " << scoreBoard.level
                 << " | Speed: " << 100 + scoreBoard.speed * 5 << std::endl;
}

std::string Game::buildReply(const coordinateVector& snakeVector, const Point& apple)
{
    std::string response = "\n";

    for (size_t i = 0; i < ROW_NUMBER; ++i)
    {
        for (size_t j = 0; j < COLUMN_NUMBER; ++j)
        {
            Point snakeHead = snakeVector[0];
            if (i == 0 || j == 0 || i == ROW_NUMBER - 1 || j == COLUMN_NUMBER - 1)
            {
                response.append(".");
            }
            else if ((snakeHead).X == i && (snakeHead).Y == j)
            {
                response.append("@");
            }
            else if ((apple).X == i && (apple).Y == j)
            {
                response.append("a");
            }
            else
            {
                coordinateVector::const_iterator it = snakeVector.begin();
                ++it;
                bool fieldIsOccupied = false;
                while (it != snakeVector.end())
                {
                    if ((*it).X == i && (*it).Y == j)
                    {
                        response.append("o");
                        fieldIsOccupied = true;
                    }
                    ++it;
                }
                if (!fieldIsOccupied)
                {
                    response.append(gameBoardMatrix[i][j]);
                }
            }
        }
        response.append("\n");
    }

    response.append("Score: ");
    std::string scoreString = std::to_string(scoreBoard.score);
    response.append(scoreString);
    response.append(" | Level: ");
    std::string levelString = std::to_string(scoreBoard.level);
    response.append(levelString);
    response.append(" | Speed: ");
    std::string speedString = std::to_string(100 + scoreBoard.speed * 5);
    response.append(speedString);

    return response;
}

void Game::renderMultiplayer(const coordinateVector& snakeVectorA, const coordinateVector& snakeVectorB,
                             const Point& apple, std::ostream& outputStream)
{
    if ((snakeVectorA.size() > 0) && (snakeVectorB.size() > 0))
    {
        for (size_t i = 0; i < ROW_NUMBER; ++i)
        {
            for (size_t j = 0; j < COLUMN_NUMBER; ++j)
            {
                Point snakeHeadA = snakeVectorA[0];
                Point snakeHeadB = snakeVectorB[0];

                if ((snakeHeadA).X == i && (snakeHeadA).Y == j)
                {
                    outputStream << "@";
                }
                else if ((snakeHeadB).X == i && (snakeHeadB).Y == j)
                {
                    outputStream << "&";
                }
                else if ((apple).X == i && (apple).Y == j)
                {
                    outputStream << "a";
                }
                else
                {
                    coordinateVector::const_iterator itA = snakeVectorA.begin();
                    coordinateVector::const_iterator itB = snakeVectorB.begin();

                    ++itA;
                    bool fieldIsOccupied = false;
                    while (itA != snakeVectorA.end() || itB != snakeVectorB.end())
                    {
                        if (itA != snakeVectorA.end())
                        {
                            if ((*itA).X == i && (*itA).Y == j)
                            {
                                outputStream << "o";
                                fieldIsOccupied = true;
                            }
                            ++itA;
                        }

                        if (itB != snakeVectorB.end())
                        {
                            if ((*itB).X == i && (*itB).Y == j)
                            {
                                outputStream << "o";
                                fieldIsOccupied = true;
                            }
                            ++itB;
                        }
                    }
                    if (!fieldIsOccupied)
                    {
                        outputStream << gameBoardMatrix[i][j];
                    }
                }
            }
            outputStream << std::endl;
        }
    }

    outputStream << "Python score: " << scoreBoardMultiplayer.scorePython
                 << " | Anaconda score: " << scoreBoardMultiplayer.scoreAnaconda
                 << " | Level: " << scoreBoardMultiplayer.level << " | Speed: " << 100 + scoreBoardMultiplayer.speed * 5
                 << std::endl;
}

bool Game::playerHasWon()
{
    if (scoreBoard.level == 17)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Game::clearScreen(std::ostream& outputStream)
{
    outputStream << "\033c";
}

void Game::updateGameState(const coordinateVector& snakeVector, const Point& apple, std::ostream& outputStream)
{
    clearScreen(outputStream);
    render(snakeVector, apple, outputStream);
}

void Game::updateGameStateMultiplayer(const coordinateVector& snakeVectorA, const coordinateVector& snakeVectorB,
                                      const Point& apple, std::ostream& outputStream)
{
    clearScreen(outputStream);
    renderMultiplayer(snakeVectorA, snakeVectorB, apple, outputStream);
}

void Game::updateScoreBoard()
{
    scoreBoard.score += 10;
    ++scoreBoard.level;
    ++scoreBoard.speed;
}

void Game::updateScoreBoard(char pointWinner)
{
    if (pointWinner == ANACONDA_SCORE)
    {
        scoreBoardMultiplayer.scoreAnaconda += 10;
        ++scoreBoardMultiplayer.level;
        ++scoreBoardMultiplayer.speed;
    }
    else if (pointWinner == PYTHON_SCORE)
    {
        scoreBoardMultiplayer.scorePython += 10;
        ++scoreBoardMultiplayer.level;
        ++scoreBoardMultiplayer.speed;
    }
}

void Sound::playHittingNoise()
{
    system("aplay -q ~/project/calib-ansic-internal/snake/sound/hit_sound.wav &");
}

void Sound::playAppleEatingNoise()
{
    system("aplay -q ~/project/calib-ansic-internal/snake/sound/apple_bite_sound.wav &");
}