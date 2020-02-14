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

// Main Program

#include "minesweeper_functions.h"
// #include "minesweeper_functions.cpp"
#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;

int main() {
    
    int welcomeChoice = welcome();
                            if (DEBUG) {
                                cout << "welcomeChoice: " 
                                     << welcomeChoice << endl;
                            }

    int rows = 0;
    int columns = 0;
    int bombs = 0;
    // set size of board if new game else load existing game board if loading saved game
    if (welcomeChoice == 1) {
        setSize(rows, columns, bombs);
    } else { 
        // get row and column info from file
        int temp = 1;
        temp = get_array_info(rows, columns, bombs);
        // end program if file doesn't open
        if (temp == 0) {
            cout << "Error: File didn't open.";
            return 0;
        }
    }
    
                            if (DEBUG) {
                                cout << endl
                                     << "Debug: " << endl
                                     << "rows = " << rows << endl
                                     << "columns = " << columns << endl
                                     << "bombs = " << bombs << endl;
                            }

    // display board specs
    cout << endl
         << "Your Game Board has:" << endl
         << "- " << rows << " rows" << endl
         << "- " << columns << " columns" << endl
         << "- " << bombs << " bombs" << endl;
    
    // initialize arrays
    char answerArray[rows][MAX_COL];
    char gameArray[rows][MAX_COL];
    
    // fill arrays with data from file if choosing to load game
    if (welcomeChoice == 2) {
        int temp = 1;
        temp = load_game(answerArray, gameArray, rows, columns);
        // end program if file doesn't open
        if (temp == 0) {
            cout << "Error: File didn't open.";
            return 0;
        }
        
        // export answer game array
        temp = 1;
        temp = output_answerArray(answerArray, rows, columns);
        // end program if file doesn't open
        if (temp == 0) {
            cout << "Error: File didn't open.";
            return 0;
        }
    }

    
    // fill gameArray if choosing to create new game
    if (welcomeChoice == 1) {
        make_gameArray(gameArray, rows, columns);
    }
    
    
    // export gameArray
    int temp = 1;
    temp = output_gameArray(gameArray, rows, columns);
    // end program if file doesn't open
    if (temp == 0) {
        cout << "Error: File didn't open.";
        return 0;
    }
    
    // Explain where gameboard is
    cout << endl
         << "===============================================" << endl
         << "Open \"game_board.txt\" to see your game board" << endl
         << "in real time!" << endl
         << "===============================================" << endl;
    
    // prompt coordinate input
    int r = 0;   // used to store row number for guess
    int c = 0;   // used to store column number for guess
    char action; // used to store action (flag or uncover)
    
    cout << "Enter 'action' letter " << endl
         << "   A: to uncover the cell," << endl
         << "   B: to flag the cell for a bomb," << endl
         << "   C: to save your game and quit, or" << endl
         << "   D: to quit without saving." << endl
         << "Then enter the row and column numbers of the" << endl
         << "cell you'd like to uncover." << endl
         << "===============================================" << endl;
    
    bool notDone = true;
    int i = 1;    // used as counter to only create answer board the first time
    bool loss = false; // changes to true if user uncovers bomb
    // main loop for gameplay
    do {
        // get coordinate input
        getCoordinates(gameArray, r, c, rows, columns, action, i);
        
        // save game if requested
        if (action == 'C') {
            
            temp = 1;
            temp = save_game(answerArray, gameArray, rows, columns, bombs);
            // end program if file doesn't open
            if (temp == 0) {
            cout << "Error: File didn't open.";
            return 0;
            }
            // output goodbye message
            cout << endl << "Have a nice day!" << endl
                 << "Your progress is saved in \"savegame.txt\"." << endl;
            return 0;
        }
        
        // quit without saving if requested
        if (action == 'D') {
            cout << endl << "Have a nice day!" << endl
                 << "Progress was not saved.";
            return 0;
        }
        
        /* fill answerArray only if first time through loop and user
           chooses to create new game */
        if ((i == 1) && (welcomeChoice == 1)) {
            // fill answerArray based on coordinate input
            make_answerArray(answerArray, rows, columns, r, c, bombs);
            
            // export answerArray to external file for reference
            temp = 1;
            temp = output_answerArray(answerArray, rows, columns);
            // end program if file doesn't open
            if (temp == 0) {
                cout << "Error: File didn't open.";
                return 0;
            }
        }
        
        // update gameboard based off answer gameboard
        loss = update_gameArray(answerArray, gameArray, rows, columns, r, c, action);
        
        // if loss
        if (loss) {
            cout << endl
                 << "BOOM!!! You uncovered a bomb! You lose!" << endl
                 << "Thanks for playing!";
            return 0;
        }
        
        // export gameArray after update
        temp = 1;
        temp = output_gameArray(gameArray, rows, columns);
        // end program if file doesn't open
        if (temp == 0) {
            cout << "Error: File didn't open.";
            return 0;
        }
        
        //check for victory
        if (check_victory(answerArray, gameArray, rows, columns)) {
            cout << "Congratulations!! You win!!";
            return 0;
        }
        
        // increment counter
        i++;
    }
    while(notDone);
    
    
    return 0;
}
