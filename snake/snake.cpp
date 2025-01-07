#include "snake.h"

void Snake::moves()
{
    Point& snakeHead = (*snakeVector.get())[0];
    if ((*snakeVector.get()).size() > 1)
    {
        Point& snakeNextSegment = (*snakeVector.get())[1];
        size_t previousXSegment = snakeNextSegment.X;
        size_t previousYSegment = snakeNextSegment.Y;
        size_t snakeXNextSegment, snakeYNextSegment;
        snakeNextSegment.X = snakeHead.X;
        snakeNextSegment.Y = snakeHead.Y;
        for (size_t i = 2; i < ((*snakeVector.get()).size()); ++i)
        {
            Point& actualSegment = (*snakeVector.get())[i];
            snakeXNextSegment    = actualSegment.X;
            snakeYNextSegment    = actualSegment.Y;
            actualSegment.X      = previousXSegment;
            actualSegment.Y      = previousYSegment;
            previousXSegment     = snakeXNextSegment;
            previousYSegment     = snakeYNextSegment;
        }
    }
}

void Snake::updateSnakeDirection(const char& input)
{
    if (input == RIGHT_D || input == RIGHT_ARROW)
    {
        Point& snakeHead = (*snakeVector.get())[0];
        snakeHead.Y++;
    }
    else if (input == LEFT_A || input == LEFT_ARROW)
    {
        Point& snakeHead = (*snakeVector.get())[0];
        snakeHead.Y--;
    }
    else if (input == UP_W || input == UP_ARROW)
    {
        Point& snakeHead = (*snakeVector.get())[0];
        snakeHead.X--;
    }
    else if (input == DOWN_S || input == DOWN_ARROW)
    {
        Point& snakeHead = (*snakeVector.get())[0];
        snakeHead.X++;
    }
    else if (input != '\n')
    {
        throw std::invalid_argument(
            "snake can be moved either by WASD or by arrow keys. any other attempt is forbidden.");
    }

    direction = NONE;
}

void Anaconda::updateSnakeDirectionWASD(const char& input)
{
    if (input == RIGHT_D)
    {
        Point& snakeHead = (*snakeVector.get())[0];
        snakeHead.Y++;
        previousDirectionWASD = RIGHT_D;
    }
    else if (input == LEFT_A)
    {
        Point& snakeHead = (*snakeVector.get())[0];
        snakeHead.Y++;
        previousDirectionWASD = LEFT_A;
    }
    else if (input == UP_W)
    {
        Point& snakeHead = (*snakeVector.get())[0];
        snakeHead.X--;
        previousDirectionWASD = UP_W;
    }
    else if (input == DOWN_S)
    {
        Point& snakeHead = (*snakeVector.get())[0];
        snakeHead.X++;
        previousDirectionWASD = DOWN_S;
    }
    else
    {
        updateSnakeDirectionWASD(previousDirectionWASD);
    }
}

void Python::updateSnakeDirectionArrowKeys(const char& input)
{
    if (input == RIGHT_ARROW)
    {
        Point& snakeHead = (*snakeVector.get())[0];
        snakeHead.Y++;
        previousDirection = RIGHT_ARROW;
    }
    else if (input == LEFT_ARROW)
    {
        Point& snakeHead = (*snakeVector.get())[0];
        snakeHead.Y--;
        previousDirection = LEFT_ARROW;
    }
    else if (input == UP_ARROW)
    {
        Point& snakeHead = (*snakeVector.get())[0];
        snakeHead.X--;
        previousDirection = UP_ARROW;
    }
    else if (input == DOWN_ARROW)
    {
        Point& snakeHead = (*snakeVector.get())[0];
        snakeHead.X++;
        previousDirection = DOWN_ARROW;
    }
    else
    {
        updateSnakeDirectionArrowKeys(previousDirection);
    }
}

Snake::Snake()
{
    direction            = NONE;
    size_t centerRows    = (ROW_NUMBER) / 2 + 1;
    size_t centerColumns = (COLUMN_NUMBER) / 2 + 1;
    snakeVector          = std::make_shared<coordinateVector>();
    Point center;
    center.X = centerRows;
    center.Y = centerColumns;
    (*(snakeVector).get()).push_back(center);
}

Anaconda::Anaconda(const size_t& x, const size_t& y)
{
    snakeVector = std::make_shared<coordinateVector>();
    Point coordinate;
    coordinate.X = x;
    coordinate.Y = y;

    (*(snakeVector).get()).push_back(coordinate);
    previousDirectionWASD = RIGHT_D;
}

Python::Python(const size_t& x, const size_t& y)
{
    snakeVector = std::make_shared<coordinateVector>();
    Point coordinate;
    coordinate.X = x;
    coordinate.Y = y;

    (*(snakeVector).get()).push_back(coordinate);
    previousDirection = RIGHT_ARROW;
}

const coordinateVector& Snake::getPositionVector() const
{
    return (*snakeVector.get());
}

bool Snake::lives(char selectedMode)
{
    bool isAlive;
    if (selectedMode == 't' || selectedMode == 'w')
    {
        isAlive = livesAndTeleports();
    }
    else
    {
        isAlive = lives();
    }

    return isAlive;
}

bool Snake::lives()
{
    if (dies())
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Snake::livesAndTeleports()
{
    if (bitesItselfTeleport())
    {
        return false;
    }

    teleports();

    return true;
}

void Snake::teleports()
{
    Point& snakeHead = (*(snakeVector.get()))[0];

    size_t snakeHeadColumn = snakeHead.Y;

    if (snakeHeadColumn == 0 && direction != LEFT)
    {
        snakeHead.Y = (COLUMN_NUMBER - 1);
        direction   = RIGHT;
    }
    else if (snakeHeadColumn == (COLUMN_NUMBER - 1) && direction != RIGHT)
    {
        snakeHead.Y = 1;
        direction   = LEFT;
    }

    size_t snakeHeadRow = snakeHead.X;
    if (snakeHeadRow == 0 && direction != DOWN)
    {
        snakeHead.X = (ROW_NUMBER - 1);
        direction   = UP;
    }
    else if (snakeHeadRow == (ROW_NUMBER - 1) && direction != UP)
    {
        snakeHead.X = 1;
        direction   = DOWN;
    }
}

bool Snake::bitesItself()
{
    if ((*snakeVector.get()).size() > 1)
    {
        Point& snakeHead = (*snakeVector.get())[0];
        size_t headX     = snakeHead.X;
        size_t headY     = snakeHead.Y;

        for (size_t i = 1; i < (*snakeVector.get()).size(); ++i)
        {
            Point& selfSegment  = (*snakeVector.get())[i];
            size_t selfSegmentX = selfSegment.X;
            size_t selfSegmentY = selfSegment.Y;

            if (headX == selfSegmentX && headY == selfSegmentY)
            {
                return true;
            }
        }
    }
    return false;
}

bool Snake::bitesItselfTeleport()
{
    if ((*snakeVector.get()).size() > 1)
    {
        Point& snakeHead = (*snakeVector.get())[0];
        size_t headX     = snakeHead.X;
        size_t headY     = snakeHead.Y;

        if ((headX > 2 && headX < ROW_NUMBER - 2) && (headY > 2 && headY < COLUMN_NUMBER - 2))
        {
            for (size_t i = 1; i < (*snakeVector.get()).size(); ++i)
            {
                Point& selfSegment  = (*snakeVector.get())[i];
                size_t selfSegmentX = selfSegment.X;
                size_t selfSegmentY = selfSegment.Y;

                if (headX == selfSegmentX && headY == selfSegmentY)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Snake::hitsWall()
{
    Point snakeHead = (*snakeVector.get())[0];
    if (snakeHead.X >= (ROW_NUMBER - 1) || snakeHead.Y >= (COLUMN_NUMBER - 1) || snakeHead.X < 1 || snakeHead.Y < 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Snake::hitsRock(const coordinateVector& rocks)
{
    Point  snakeHead       = (*snakeVector.get())[0];
    size_t snakeHeadRow    = snakeHead.X;
    size_t snakeHeadColumn = snakeHead.Y;

    coordinateVector::const_iterator rockIterator = rocks.begin();

    while (rockIterator != rocks.end())
    {
        if ((*rockIterator).X == snakeHeadRow && (*rockIterator).Y == snakeHeadColumn)
        {
            return true;
        }
        ++rockIterator;
    }
    return false;
}

bool Snake::bitesTheOtherSnake(const coordinateVector& anotherSnake)
{
    Point  snakeHead       = (*snakeVector.get())[0];
    size_t snakeHeadRow    = snakeHead.X;
    size_t snakeHeadColumn = snakeHead.Y;

    coordinateVector::const_iterator snakeIterator = anotherSnake.begin();

    while (snakeIterator != anotherSnake.end())
    {
        if ((*snakeIterator).X == snakeHeadRow && (*snakeIterator).Y == snakeHeadColumn)
        {
            return true;
        }
        ++snakeIterator;
    }
    return false;
}

bool Snake::dies()
{
    if ((hitsWall()) || (bitesItself()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Snake::eatsApple(const Point& apple)
{
    Point snakeHead = (*snakeVector.get())[0];
    if (snakeHead.X == apple.X && snakeHead.Y == apple.Y)
    {
        Point newPoint;
        newPoint.X = INITIAL_COORDINATE;
        newPoint.Y = INITIAL_COORDINATE;
        (*snakeVector.get()).push_back(newPoint);
        return true;
    }
    else
    {
        return false;
    }
}