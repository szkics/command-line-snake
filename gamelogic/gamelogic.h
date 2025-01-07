#pragma once
#include "../headers/headers.h"

struct ScoreBoard
{
    size_t score{10};
    size_t level{1};
    size_t speed{1};
};

struct ScoreBoardMultiplayer
{
    size_t scorePython{10};
    size_t scoreAnaconda{10};
    size_t level{1};
    size_t speed{1};
};

class GameBoard
{
public:
    void          initialize();
    void          initialize(const coordinateVector& rockVector);
    void          initializeMultiplayer();
    const matrix& getMatrix();

private:
    bool fieldIsOccupied(const coordinateVector& vector, const size_t& i, const size_t& j);

    matrix gameBoardMatrix;
};

class Game
{
public:
    void        start(GameBoard& gameBoard);
    void        updateGameState(const coordinateVector& snakeVector, const Point& apple, std::ostream& outputStream);
    void        updateGameStateMultiplayer(const coordinateVector& snakeVectorA, const coordinateVector& snakeVectorB,
                                           const Point& apple, std::ostream& outputStream);
    void        updateScoreBoard();
    void        updateScoreBoard(char pointWinner);
    bool        playerHasWon();
    std::string buildReply(const coordinateVector& snakeVector, const Point& apple);
    ScoreBoard  getScoreBoard();

private:
    void render(const coordinateVector& snakeVector, const Point& apple, std::ostream& outputStream);
    void renderMultiplayer(const coordinateVector& snakeVectorA, const coordinateVector& snakeVectorB,
                           const Point& apple, std::ostream& outputStream);
    void clearScreen(std::ostream& outputStream);

    matrix                gameBoardMatrix;
    ScoreBoard            scoreBoard;
    ScoreBoardMultiplayer scoreBoardMultiplayer;
};

class Sound
{
public:
    void playHittingNoise();
    void playAppleEatingNoise();
};