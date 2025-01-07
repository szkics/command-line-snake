#include "entities.h"

Point StaticEntity::getRandomPoint() const
{
    srand(rand() * time(NULL));
    size_t rowIndex    = (rand() % (ROW_NUMBER - 3)) + 2;
    size_t columnIndex = (rand() % (COLUMN_NUMBER - 3)) + 2;
    Point  point;
    point.X = rowIndex;
    point.Y = columnIndex;
    return point;
}

bool fieldIsEmpty(const Point& randomApple, const coordinateVector& snakeVector)
{
    size_t appleRowIndex    = (randomApple).X;
    size_t appleColumnIndex = (randomApple).Y;
    for (size_t i = 0; i < snakeVector.size(); ++i)
    {
        Point snakeSegment = snakeVector[i];
        if (snakeSegment.X == appleRowIndex && snakeSegment.Y == appleColumnIndex)
        {
            return false;
        }
    }
    return true;
}

bool fieldIsEmpty(const Point& randomApple, const coordinateVector& snakeVector, const coordinateVector& rockVector)
{
    size_t appleRowIndex    = (randomApple).X;
    size_t appleColumnIndex = (randomApple).Y;
    for (size_t i = 0; i < snakeVector.size(); ++i)
    {
        Point snakeSegment = snakeVector[i];
        if (snakeSegment.X == appleRowIndex && snakeSegment.Y == appleColumnIndex)
        {
            return false;
        }
    }

    for (size_t i = 0; i < rockVector.size(); ++i)
    {
        Point rock = rockVector[i];
        if (rock.X == appleRowIndex && rock.Y == appleColumnIndex)
        {
            return false;
        }
    }

    return true;
}

Point Apple::generateApple(const coordinateVector& snakeVector) const
{
    Point randomApple = getRandomPoint();
    while (!fieldIsEmpty(randomApple, snakeVector))
    {
        randomApple = getRandomPoint();
    }
    return randomApple;
}

Point Apple::generateApple(const coordinateVector& snakeVector, const coordinateVector& rockVector) const
{
    Point randomApple = getRandomPoint();
    while (!fieldIsEmpty(randomApple, snakeVector, rockVector))
    {
        randomApple = getRandomPoint();
    }
    return randomApple;
}

const std::vector<Point>& Rock::generateRocks(const size_t& numberOfRocks)
{
    size_t i = 0;
    while (i < numberOfRocks)
    {
        Point randomRock = getRandomPoint();
        rockVector.push_back(randomRock);
        ++i;
    }

    return rockVector;
}