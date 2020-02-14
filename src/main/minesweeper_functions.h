/****************************************************************************
 *
 * Proj.03: An implementation of the MineSweeper game
 *
 * File Name: minesweeper_functions.h
 * Name:      Luke Irvine
 * Course:    CPTR 141
 * Date:      March 18, 2019
 *
 */

// Function Prototypes

#ifndef SRC_MAIN_MINESWEEPER_FUNCTIONS_H_
#define SRC_MAIN_MINESWEEPER_FUNCTIONS_H_

#include <iostream>
#include <fstream>
#include <string>
#include "const.h"
using namespace std;

/*****************************
 * Function: getInput (overloaded)
 * Preparamter: - minimum value for input, 
 *              - maximum value for input,
 *              - and string to display the prompt
 * Purpose: checks cin for type and range errors
 * Postparamter: Returns a value from cin once it
 *               has been checked.
 */
int getInput(int min, int max, string prompt);

/*****************************
 * Function: getInput (overloaded)
 * Preparamter: - minimum value for input in 'x' format, 
 *              - maximum value for input in 'x' format,
 *              - and string to display the prompt
 * Purpose: checks cin for type and range errors
 * Postparamter: Returns a value from cin once it
 *               has been checked.
 */
char getInput(char min, char max, string prompt);

/*****************************
 * Function: welcome
 * Preparamter: none
 * Purpose: Prints out a welcome screen that prompts user
 *          to either start a new game or load an old one.
 * Postparamter: Returns an int either 1 or 2 to specify
 *               which menu option has been chosen.
 */
int welcome();

/*****************************
 * Function: setSize
 * Preparamter: number of columns, rows, and bombs as ints
 * Purpose: Prompts user to give dimensions of game board
 *          with some suggestions and calculates number of
 *          bombs used on board based on percentage of the
 *          the board's area.
 * Postparamter: Returns values to columns, rows, and bombs
 *               by reference.
 */
void setSize(int&, int&, int&);

/*****************************
 * Function: make_answerArray
 * Preparamter: - empty array with max number of columns 
 *                and parameter with 
 *              - number of rows, columns, row guess number, column
 *                guess number, and number of bombs.
 * Purpose: Fills in array with bombs and numbers on cells
 *          around the bombs.
 * Postparamter: none
 */
void make_answerArray(char[][MAX_COL], int, int, int, int, int);

/*****************************
 * Function: output_answerArray
 * Preparamter: filled answerArray with bombs and numbers,
 *              another paramter with number of rows, and
 *              a final parameter with the ofstream variable.
 * Purpose: exports the answerArray game board to an external
 *          file.
 * Postparamter: integer of 0 if file doesn't open
 *               Otherwise: Return 1.
 */
int output_answerArray(char[][MAX_COL], int, int);

/*****************************
 * Function: make_gameArray
 * Preparamter: empty array, and int parameters for the number
 *              of rows and columns
 * Purpose: fills the gameArray with '@' to signify a covered
 *          cell.
 * Postparamter: none
 */
void make_gameArray(char[][MAX_COL], int, int);

/*****************************
 * Function: print_gameArray
 * Preparamter: filled array, and int parameters for the number
 *              of rows and columns
 * Purpose: prints the array in a grid with grid lines and such
 * Postparamter: integer of 0 if file doesn't open 
 *               Otherwise: Return 1.
 */
int output_gameArray(char[][MAX_COL], int, int);

/*****************************
 * Function: getCoordinates
 * Preparamter: - gameArray passed by reference
 *              - integer row number and column number passed
 *                by reference.
 *              - integers of gameboard number of rows and 
 *                columns passed by value.
 *              - character indicating action type (flag or uncover)
 *                passed by reference.
 *              - counter int i to determine when to check if
 *                cell has already been inputted
 * Purpose: prompt user to uncover or flag a cell based on 
 *          coordinates
 * Postparamter: none
 */
void getCoordinates(char[][MAX_COL], int&, int&, int, int, char&, int);

/*****************************
 * Function: update_gameArray
 * Preparamter: - answerArray current state by reference.
 *              - gameArray current state by reference.
 *              - int number of rows and columns for both 
 *                arrays.
 *              - int row number and column number guessed
 *                by user.
 *              - char 'A' or 'B' indicating whether cell
 *                should be uncovered or flagged.
 * Purpose: prompt user to uncover
 * Postparamter: returns true if lost, returns false otherwise
 */
bool update_gameArray(char[][MAX_COL], char[][MAX_COL], int, int, int, int, char);

/*****************************
 * Function: update_gameArray
 * Preparamter: - answerArray current state by reference.
 *              - gameArray current state by reference.
 *              - int number of rows and columns for both 
 *                arrays.
 *              - int row number and column number guessed
 *                by user.
 * Purpose: check adjacent cells if a cell is zero and then
 *          check adjacent cells of adjacent cell if it is zero
 * Postparamter: none
 */
void check_adjacent_cells(char[][MAX_COL], char[][MAX_COL], int, int, int, int);

/*****************************
 * Function: check
 * Preparamter: - answerArray current state by reference.
 *              - gameArray current state by reference.
 *              - int number of rows and columns for both 
 *                arrays.
 *              - int row number and column number guessed
 *                by user.
 *              - int i and j to indicate address of cell being checked
 * Purpose: Check single adjacent cell with address passed by value
 *          given ints i and j.
 * Postparamter: none
 */
void check(char answerArray[][MAX_COL], char gameArray[][MAX_COL], int rows, int columns, int r, int c, int i, int j);

/*****************************
 * Function: check_victory
 * Preparamter: - answerArray passed by reference
 *              - gameArray passed by reference
 *              - two int parameters with number of rows
 *                and columns.
 * Purpose: checks each cell in answerArray with the corresponding
 *          cell in gameArray to see if all cells without bombs
 *          have been uncovered.
 * Postparamter: returns true if all cells without bombs are
 *               uncovered, returns false otherwise
 */
bool check_victory(char[][MAX_COL], char[][MAX_COL], int, int);

/*****************************
 * Function: save_game
 * Preparamter: - answerArray passed by reference
 *              - gameArray passed by reference
 *              - two int parameters with number of rows
 *                and columns and bombs.
 * Purpose: saves both arrays to file "savegame.txt" to be
 *          loaded later when user wants to continue game
 * Postparamter: returns 0 if file couldn't be opened, returns
 *               1 otherwise.
 */
int save_game(char[][MAX_COL], char[][MAX_COL], int, int, int);

/*****************************
 * Function: get_array_info
 * Preparamter: - number of rows, columns, and bombs passed
 *                by reference.
 * Purpose: reads first line of "savegame.txt" to get row
 *          and column info and input them into int variable
 *          types.
 * Postparamter: returns 0 if file couldn't be opened, returns
 *               1 otherwise.
 */
int get_array_info(int&, int&, int&);

/*****************************
 * Function: load_game
 * Preparamter: - answerArray passed by reference
 *              - gameArray passed by reference
 *              - number of rows and columns passed by
 *                variable.
 * Purpose: reads input from file savegame.txt and loads info
 *          into the two arrays
 * Postparamter: returns 0 if file couldn't be opened, returns
 *               1 otherwise.
 */
int load_game(char[][MAX_COL], char[][MAX_COL], int, int);

#endif  // SRC_MAIN_MINESWEEPER_FUNCTIONS_H_
