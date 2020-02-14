# CPTR 141: Project #3

## Problem Overview
This project comes to us from the field of entertainment.  In it, you will implement the classic game *minespweper*.  The game takes place on a rectangular game board that is divided into a grid.  Each cell in this grid is initially hidden and mines have been randomly placed throughout the board.  The object of the game is to uncover all of the empty cells without uncovering a mine (and blowing yourself up).  

The player uncovers cells one at a time.  When a cell is uncovered, one of three things can happen:

* If cell contains a mine, it blows up and the game ends
* If the cell does not contain a mine, but a neighboring cell does, then the number of neighbors that contain a mine is displayed in the uncovered cell.
* If the cell does not contain a mine and no neighboring cell contains a mine, then all neighboring cells are also uncovered.  This process then repeats for each of the newly uncovered cells.

This will continue until either all cells without mines have been uncovered and the player wins, or a cell with a mine is uncovered and the player looses.

![Minesweeper](https://www.johnweeks.com/tour/mines/mine6.gif)


## Solution Specification

Your solution to the problem outlined above must meet the following criteria.  How you choose to meet those criteria is up to you.  Be creative!

1. When the program first runs, the user should be promoted to start a new game or continue a saved game, if there is one. 
2. When starting a new game, the program should:
   1. Prompt the user for the size of the game board.  It is probably a good idea to impose some limits on the allowable size since a 1 by 1 board won't be much fun and a 1000 by 1000 board won't fit on the screen.
   2. Randomly (or not) distribute the mines across the game board.
3. When loading a saved game, the program should read in information from an external file that will allow it to pick up where the user left off.
4. Once the game has started, the game board should be displayed and the user should be given the option to:
   1. Pick a cell to uncover.  This is likely going to be done by providing coordinates of the cells (i.e. row and column numbers), but if you have more creative ideas, go for it!
   2. Save the game and quit.  This will write out the game information to an external file so that it can be loaded the next time the program is run.
   3. Quit without saving. 
5. If the user picks a cell to uncover, the game board should be updated and then the program should go back to step 4.

You are welcome to modify the sequence or specifics of this program flow as long as your program allows for logical user interactions and accomplishes the tasks outlined above.



## Game Board Representation

We have not done anything with graphics in this course, so the expectation is that your game board will be displayed using ASCII characters.  Here is a possible (but likely too mundane) representation of a 6 row by 8 column game board.

```reStructuredText
   1 2 3 4 5 6 7 8
1 |-|-|-|-|-|-|-|-|
2 |-|-|-|-|-|-|-|-|
3 |-|-|-|-|-|-|-|-|
4 |-|-|-|-|-|-|-|-|
5 |-|-|-|-|-|-|-|-|
6 |-|-|-|-|-|-|-|-|
```

In this representation, a dash indicates a covered cell.  Suppose that the cell in row 1 column 8 is uncovered by the user.  If it does not contain a mine and several of its neighbors have no mines in them either, the resulting board might look like this.

```reStructuredText
   1 2 3 4 5 6 7 8
1 |-|-|1| | | | | |
2 |-|-|1| | | | | |
3 |-|-|1|2|2|1| | |
4 |-|-|-|-|-|2|1|1|
5 |-|-|-|-|-|-|-|-|
6 |-|-|-|-|-|-|-|-|
```

You may also want to look into using *escape sequences* to either add color or do other tasks on the console.  For example, printing out the escape sequence `"\e[1;1H\e[2J"` in Cloud9 will clear the screen )this may not be portable to other C++ environments).  Again, be creative!  

## Assignment Specification
In addition to solving the problem as outlined above, your program must meet the following assignment specifications.

* You must use two-dimensional arrays in your program. 

* Your program must be divided into functions which perform well-defined and logical sub-tasks for the problem.  Before you go too far on your development, check with your professor or another student about your program structure and choice of functions.

* The file `savegame.txt` must be used to save the state of the game if the user requests it.  That way, when the program starts up again, the user can pick up where they left off.
* You must validate all user input and handle errors gracefully

* Since this is your final project in the class, show off as much of what you've learned as possible. 
  In particular, you are expected to make use of the following concepts somewhere in your program.
  * Appropriate branching and looping statements
  * Console input/output and file output using streams
  * Functions with various return and parameter types (pass-by-reference, default values, etc)
  * Global constants (likely for your maximum array dimensions)
  * Vectors and/or arrays and passing 2D arrays to functions

## Code Review and Grading
While not mandatory for this project, it is a good idea to have your instructor, a tutor at the SDC, or a fellow student do a [code review](https://en.wikipedia.org/wiki/Code_review) with you.  This [walk-through](https://en.wikipedia.org/wiki/) style review is a guided-tour of your source code in which you describe how you implemented the various features, explain why you made the choices you did, and solicit constructive input which might help improve your final product.

Your final project will be graded according tot he accompanying code review rubric.