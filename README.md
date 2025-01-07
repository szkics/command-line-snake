### command line sn@ke project
#### a high-level overview


##### Snake

 - void updateSnakeDirection(const char& input);
 - bool lives(char selectedMode);
 - void moves();
 - bool eatsApple(const Point& apple);
 - bool hitsRock(const coordinateVector& rocks);
 - bool bitesTheOtherSnake(const coordinateVector& anotherSnake);
 - bool bitesItself();


##### Anaconda (a Snake descendant)

 - void updateSnakeDirectionWASD(const char& input);
 - void createAtGivenCoordinates(const size_t& x, const size_t& y);


##### Python (another Snake descendant)

 - void updateSnakeDirectionArrowKeys(const char& input);
 - void createAtGivenCoordinates(const size_t& x, const size_t& y);


##### StaticEntity

 - Point getRandomPoint() const;


##### Apple (a StaticEntity descendant)

 - Point generateApple(const coordinateVector& snakeVector) const;
 - Point generateApple(const coordinateVector& snakeVector, const coordinateVector& rockVector) const;


##### Rock (another StaticEntity descendant)

 - const coordinateVector& generateRocks(const size_t& numberOfRocks);
 - size_t                  getNumberOfRocks();


##### GameBoard

 - void          initialize();
 - void          initialize(const coordinateVector& rockVector);
 - void          initializeMultiplayer();
 - const matrix& getMatrix();


###### Game

 - void        start(GameBoard& gameBoard);
 - void        updateGameState(const coordinateVector& snakeVector, const Point& apple, std::ostream& outputStream);
 - void        updateGameStateMultiplayer(const coordinateVector& snakeVectorA, const coordinateVector& snakeVectorB,
 -                                        const Point& apple, std::ostream& outputStream);
 - void        updateScoreBoard();
 - void        updateScoreBoard(char pointWinner);
 - bool        playerHasWon();
 - std::string buildReply(const coordinateVector& snakeVector, const Point& apple);
 - ScoreBoard  getScoreBoard();


##### GameMode 

 - int  playSelectedMode(const char& selectedGameMode, std::ostream& outputStream);
 - int  handleUserInput(Game& game, Snake& snake, Apple& apple, Point& generatedApple, std::ostream& outputStream,
 -                      char input);
 - int  handleUserInput(Game& game, Snake& snake, Apple& apple, Point& generatedApple, coordinateVector& rockVector,
 -                      std::ostream& outputStream, char input);
 - void handleUserInput(Game& game, Anaconda& anaconda, Python& python, Apple& apple, Point& generatedApple,
 -                      std::ostream& outputStream, char input);


###### UserInteraction

 - size_t getNumberOfRocks();
 - void   cleanInputBuffer();
 - char   getInputOnKeyPressed(char& input);


###### Timer

 - void   setSignal(const size_t& flag);
 - size_t getSignal();
