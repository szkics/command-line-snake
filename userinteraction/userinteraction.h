#include "../headers/headers.h"

// TODO: mock
// UserInteractionInterface
class UserInteraction
{
public:
    size_t getNumberOfRocks();
    void   cleanInputBuffer();
    char   getInputOnKeyPressed(char& input);

private:
    char getInput();
};