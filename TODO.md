## Implement the classical snake game for the linux terminal.
(something like nsnake: https://www.tecmint.com/nsnake-a-clone-of-old-classic-snake-game-play-in-linux-terminal/)

the steps are the following:
1. game frame should be displayed after build. OK.
2. snake, basic movements: both wasd and arrow keys should drive the snake to move in the proper direction. OK.
3. random apple should appear. OK.
4. snake should be able to "eat" the apple, and thus the apple must disapear. OK.
5. snake length is growing as an apple is eaten. OK.
6. scoreboard, level counter, speed should also be displayed. OK.
7. as time passes the game should be harder (the speed of the snake should be increased gradually.) OK. 

8. A. random rocks, if the player confuses a rock with an apple and snake's head hits the rock, the snake dies. OK.
8. B. array of random rocks? OK.
9. walls vs. no walls modes.
+ menu (GameMode class, at the moment game modes might be rock or no rock mode.)

still todo:
+ 10. multiplayer mode. (max. 4 terminal users could play the game at the same time 
each with its own snake and fight for the same apples.) 
this would also mean that each snake would have its own thread. 
(it's possible that each entity would have their own thread,
entities are: snake, rock and apple.)

+ Formatting
Pay attention to this standard:
"If one function calls another, they should be vertically close,
and the caller should be above the callee, if at all possible."

+ Note:
const functions!

+ Unit tests
Test every function!
How to test snake movement?
How to test random events?