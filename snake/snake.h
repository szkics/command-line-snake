#pragma once
#include "../headers/headers.h"

class Snake
{
public:
    Snake();
    void updateSnakeDirection(const char& input);
    bool lives(char selectedMode);
    void moves();
    bool eatsApple(const Point& apple);
    bool hitsRock(const coordinateVector& rocks);
    bool bitesTheOtherSnake(const coordinateVector& anotherSnake);
    bool bitesItself();

    const coordinateVector&           getPositionVector() const;
    std::shared_ptr<coordinateVector> snakeVector;

private:
    bool lives();
    bool livesAndTeleports();

    bool bitesItselfTeleport();
    bool hitsWall();
    bool dies();
    void teleports();

    size_t direction;
};

class Anaconda : public Snake
{
public:
    Anaconda(const size_t& x, const size_t& y);
    void updateSnakeDirectionWASD(const char& input);

private:
    char previousDirectionWASD;
};

class Python : public Snake
{
public:
    Python(const size_t& x, const size_t& y);
    void updateSnakeDirectionArrowKeys(const char& input);

private:
    char previousDirection;
};