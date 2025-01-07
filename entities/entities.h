#pragma once
#include "../headers/headers.h"

class StaticEntityInterface
{
public:
    virtual Point getRandomPoint() const = 0;
};

class StaticEntity : public StaticEntityInterface
{
public:
    Point getRandomPoint() const;
};

class AppleInterface
{
public:
    virtual Point generateApple(const coordinateVector& snakeVector) const                                     = 0;
    virtual Point generateApple(const coordinateVector& snakeVector, const coordinateVector& rockVector) const = 0;
};

class Apple : public StaticEntity, public AppleInterface
{
public:
    Point generateApple(const coordinateVector& snakeVector) const;
    Point generateApple(const coordinateVector& snakeVector, const coordinateVector& rockVector) const;
};

class Rock : public StaticEntity
{
public:
    const coordinateVector& generateRocks(const size_t& numberOfRocks);
    size_t                  getNumberOfRocks();

private:
    std::vector<Point> rockVector;
};

bool fieldIsEmpty(const Point& randomApple, const coordinateVector& snakeVector, const coordinateVector& rockVector);
bool fieldIsEmpty(const Point& randomApple, const coordinateVector& snakeVector);
