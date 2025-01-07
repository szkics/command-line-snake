Data structures:

1. the frame of the game, the area in which the snake moves is static.
	Thus using a std::array<T, N> would be proper.
	The representation of the space would be a N\*M matrix.
2. the snake size is dynamic, so the snake itself should be respresented by two vectors,
which would cleanly represent our purpose:
	snakePositionX (tells position of a certain part of the snake on the x axis.)
	snakePositionY (tells position of a certain part of the snake on the y axis.)
better naming:
	rowPositionSnake
	columnPositionSnake
or:
	one vector: snakePosition which would have std::tuple<size_t,size_t> elements.

The snake's size would be equal to the size of the vectors.
The snake's head is the first, 0. element of the vector.

3. The apples such as the rocks should be random tuples,
	std::tuple<size_t,size_t> rock;
	std::tuple<size_t,size_t> apple.

	if snakePostion vector's first element's (head of the snake) both x and y coordinate values are equal
	to either a rock or an apple than game state should be modified adequately.

Actions:

1. before every key is pressed (to be more specific: pressed + released), the keylistener should sleep for 
a certain amount of time. this time at the beginning could be 1 second, then as more and more apples are 
eaten and the user starts to get used to the game this time should be less and less: 200, 100 milliseconds and so on.

2. Snake class has a start method which listens continuously to the keys which might be pressed by the user.
If a certain key is pressed then the proper method should be called and the correct action should take place.

choose smart names, as if it were written prose:

GameBoard gameBoard;
Snake snake;
snake.create(); or snake.isBorn();

while (snake.isAlive()) { /\* or snake.lives()\*/
	snake.render(); or snake.moves(); /\*this method would draw the snake in each frame, and iterate over the snakePostion vector over and over again.
	it would draw a certain ASCII character at each (x,y) position of the gameboard matrix where the snakePostion array orders so.
	in this render method would also be a listener which chages the snakePostion as a direction key is pressed.\*/
}

snake.destroy(); or snake.dies();

use enums!
use typedefs!

enum direction {
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3
}

Design Decisions: 

1. using carriage return and backspace: \r and \b for updating output. 
we don't want to print the gameboard over and over again.
we would like the gameboard to be updated and only the snake should change its position depending on user input.