**MAZE GAME ON UCFK4 MICRO-CONTROLLER**

A maze game run on the UCFK4 micro-controller.
- Author: Kvie Nguyen (kvn17), Zoe Sharp (zsh44)
- Date: 5th October, 2021

**FILES INCLUDED**
- game.c
- player.c
- player.h 

**RUN THE GAME**

1. In terminal, clone this repository by:

    $ git clone https://github.com/kvieeee/UCFK4-board-game.git
    
3. In terminal, navigate to folder "UCFK4-board-game" by:

    $ cd UCFK4-board-game

3. Run the game by typing "make program" in the command:

    $ make program

**GAME INSTRUCTIONS**

The aim of the game is to complete all three levels of the maze to reach the end. The end point of each maze is not indicated so its up to the player to determine where to go and find the end point. If they player tries to go through a wall it restarts their position at the start of the maze again. 

How it works:
1. Introducing game: When the app successfully runs, the blue LED will appear and the game introduction welcome will be displayed on board. Push the button to skip the introduction and start the game.

2. Starting game: The text "L1" is displayed for 2 seconds then the maze will be displayed, and the player is indicated by a flashing dot on the board. 

3. Playing the game: Use the navigation switch to move around the maze and reach the end point. Player can't move through the displayed maze walls, if they try to, it will restart the maze in the begining postion.

4. Reaching end point: When the player reach the end point, the specific level will be completed and the next level will start and a text saying "L2" is displayed for 2 seconds then the maze will be displayed, and the player will flash on the board. 

5. Steps 2-4 will be repeated for level 2 and 3. 

5. Finishing game: When player has completed all 3 levels, the text "Game Over" will be displayed and game is completed. 



