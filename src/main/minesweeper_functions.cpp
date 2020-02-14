/****************************************************************************
 *
 * Proj.03: An implementation of the MineSweeper game
 *
 * File Name: minesweeper_functions.cpp
 * Name:      Luke Irvine
 * Course:    CPTR 141
 * Date:      March 18, 2019
 *
 */


#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include "minesweeper_functions.h"
using namespace std;

// FUNCTIONS

int getInput(int min, int max, string prompt) {
    int userInput = 0;    // used to collect user input
    bool invalid = false; // flag to determine if proper input
    
    do {
        invalid = false;
        
        cout << prompt;
        cin >> userInput;
        
        // print error
        if (!cin || (userInput < min) || (userInput > max)) {
            cerr << endl << "Error: Please enter proper input." << endl;
            // clear and ignore
            cin.clear();
            cin.ignore(1000, '\n');
            invalid = true;
        }
    }
    while(invalid);
    
    
    
    return userInput;
}

//======================================================================

char getInput(char min, char max, string prompt) {
    char userInput;    // used to collect user input
    bool invalid = false; // flag to determine if proper input
    
    do {
        invalid = false;
        
        cout << prompt;
        cin >> userInput;
        
        // print error
        if (!cin || (userInput < min) || (userInput > max)) {
            cerr << endl << "Error: Please enter proper input." << endl;
            // clear and ignore
            cin.clear();
            cin.ignore(1000, '\n');
            invalid = true;
        }
    }
    while(invalid);
    
    return userInput;
}

//======================================================================

int welcome() {
    cout << endl 
         << "           Welcome to Mine Sweeper!" << endl
         << "===============================================" << endl
         << "Would you like to" << endl
         << "   1: Start a new game, or" << endl
         << "   2: Load a saved game?" << endl;
    
    // calls function to get input and verify it
    return getInput(1, 2, "Enter the number of your desired option: ");
}

//======================================================================

void setSize(int &rows, int &columns, int &bombs) {
    cout << endl 
         << "          \"New Game\" selected" << endl
         << "===============================================" << endl
         << "How large would you like the game board to be? " << endl
         << "Minimum: 7, Maximum: 18" << endl;
    
    // get input for rows and columns
    rows = getInput(7, 18, "Rows: ");
    columns = getInput(7, 18, "Columns: ");
    
    // used to calculate number of bombs
    double percentage = 0;
    int area = rows * columns;
    
    // set percentage based on area of board
    if (area <= 100) {
        percentage = 0.125;
    }
    if ((area > 100) && (area <= 196)) {
        percentage = 0.14;
    }
    if (area > 196) {
        percentage = 0.16;
    }
    
    // calculate number of bombs (rounded to be whole number)
    bombs = (area * percentage) + 0.5;
}

//======================================================================

void make_answerArray(char answerArray[][MAX_COL], int rows, int columns, int guessR, int guessC, int bombs) {
    // seed the random function to the time
    srand(time(0));
    
    // used to hold random row and column value
    int row = 0;
    int column = 0;
    
    // set bombs in array
    for (int i = 0; i < bombs; i++) {
        row = (rand() % rows);
        column = (rand() % columns);
        
        // massive if statement to ensure first cell clicked is '0'
        if ((answerArray[row][column] != 'X') && 
            // cell in center
            !((row == guessR) && (column == guessC)) &&
            // upper left
            !((row == guessR - 1) && (column == guessC - 1)) &&
            // upper mid
            !((row == guessR - 1) && (column == guessC)) &&
            // upper right
            !((row == guessR - 1) && (column == guessC + 1)) &&
            // mid left
            !((row == guessR) && (column == guessC - 1)) &&
            // mid right
            !((row == guessR) && (column == guessC + 1)) &&
            // bottom left
            !((row == guessR + 1) && (column == guessC - 1)) &&
            // bottom mid
            !((row == guessR + 1) && (column == guessC)) &&
            // bottom right
            !((row == guessR + 1) && (column == guessC + 1))) {
            
            answerArray[row][column] = 'X';
        } else {
            // used to go back an iteration and try again
            i = i - 1;
            continue;
        }
    }
    
    /* fill rest of array with zeros
     * after rest of numbers are added, zeros will be
     * converted to spaces */
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            if (answerArray[r][c] != 'X') {
                answerArray[r][c] = '0';
            }
        }
    }
    
    // fill in array with numbers
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            
            // top left corner
            if ((r == 0) && (c == 0)) {
                if (answerArray[r][c] == 'X') {
                    if (answerArray[r + 1][c] != 'X') {
                        answerArray[r + 1][c]++;
                    }
                    if (answerArray[r + 1][c + 1] != 'X') {    
                        answerArray[r + 1][c + 1]++;
                    }
                    if (answerArray[r][c + 1] != 'X') {
                        answerArray[r][c + 1]++;
                    }
                }
            }
            // top row
            if ((r == 0) && (c > 0) && (c < columns - 1)) {
                if (answerArray[r][c] == 'X') {
                    if (answerArray[r][c - 1] != 'X') {
                        answerArray[r][c - 1]++;
                    }
                    if (answerArray[r][c + 1] != 'X') {
                        answerArray[r][c + 1]++;
                    }
                    if (answerArray[r + 1][c - 1] != 'X') {
                        answerArray[r + 1][c - 1]++;
                    }
                    if (answerArray[r + 1][c] != 'X') {
                        answerArray[r + 1][c]++;
                    }
                    if (answerArray[r + 1][c + 1] != 'X') {
                        answerArray[r + 1][c + 1]++;
                    }
                }
            }
            // top right corner
            if ((r == 0) && (c == columns - 1)) {
                if (answerArray[r][c] == 'X') {
                    if (answerArray[r + 1][c] != 'X') {
                        answerArray[r + 1][c]++;
                    }
                    if (answerArray[r + 1][c - 1] != 'X') {
                        answerArray[r + 1][c - 1]++;
                    }
                    if (answerArray[r][c - 1] != 'X') {
                        answerArray[r][c - 1]++;
                    }
                }
            }
            // left-most column
            if ((r > 0) && (r < rows - 1) && (c == 0)) {
                if (answerArray[r][c] == 'X') {
                    if (answerArray[r - 1][c] != 'X') {
                        answerArray[r - 1][c]++;
                    }
                    if (answerArray[r + 1][c] != 'X') {
                        answerArray[r + 1][c]++;
                    }
                    if (answerArray[r - 1][c + 1] != 'X') {
                        answerArray[r - 1][c + 1]++;
                    }
                    if (answerArray[r][c + 1] != 'X') {
                        answerArray[r][c + 1]++;
                    }
                    if (answerArray[r + 1][c + 1] != 'X') {
                        answerArray[r + 1][c + 1]++;
                    }
                }
            }
            // Whole middle section
            if ((r > 0) && (r < rows - 1) && (c > 0) && (c < columns - 1)) {
                if (answerArray[r][c] == 'X') {
                    if (answerArray[r - 1][c - 1] != 'X') {    
                        answerArray[r - 1][c - 1]++;
                    }
                    if (answerArray[r - 1][c] != 'X') {
                        answerArray[r - 1][c]++;
                    }
                    if (answerArray[r - 1][c + 1] != 'X') {
                        answerArray[r - 1][c + 1]++;
                    }
                    if (answerArray[r][c + 1] != 'X') {
                        answerArray[r][c + 1]++;
                    }
                    if (answerArray[r + 1][c + 1] != 'X') {
                        answerArray[r + 1][c + 1]++;
                    }
                    if (answerArray[r + 1][c] != 'X') {
                        answerArray[r + 1][c]++;
                    }
                    if (answerArray[r + 1][c - 1] != 'X') {
                        answerArray[r + 1][c - 1]++;
                    }
                    if (answerArray[r][c - 1] != 'X') {
                        answerArray[r][c - 1]++;
                    }
                }
            }
            // Right-most column
            if ((r > 0) && (r < rows - 1) && (c == columns - 1)) {
                if (answerArray[r][c] == 'X') {
                    if (answerArray[r - 1][c] != 'X') {
                        answerArray[r - 1][c]++;
                    }
                    if (answerArray[r - 1][c - 1] != 'X') {
                        answerArray[r - 1][c - 1]++;
                    }
                    if (answerArray[r][c - 1] != 'X') {
                        answerArray[r][c - 1]++;
                    }
                    if (answerArray[r + 1][c - 1] != 'X') {
                        answerArray[r + 1][c - 1]++;
                    }
                    if (answerArray[r + 1][c] != 'X') {
                        answerArray[r + 1][c]++;
                    }
                }
            }
            // Bottom, left corner
            if ((r == rows - 1) && (c == 0)) {
                if (answerArray[r][c] == 'X') {    
                    if (answerArray[r - 1][c] != 'X') {
                        answerArray[r - 1][c]++;
                    }
                    if (answerArray[r - 1][c + 1] != 'X') {
                        answerArray[r - 1][c + 1]++;
                    }
                    if (answerArray[r][c + 1] != 'X') {
                        answerArray[r][c + 1]++;
                    }
                }
            }
            // Bottom row
            if ((r == rows - 1) && (c > 0) && (c < columns - 1)) {
                if (answerArray[r][c] == 'X') {
                    if (answerArray[r][c - 1] != 'X') {
                        answerArray[r][c - 1]++;
                    }
                    if (answerArray[r - 1][c - 1] != 'X') {
                        answerArray[r - 1][c - 1]++;
                    }
                    if (answerArray[r - 1][c] != 'X') {
                        answerArray[r - 1][c]++;
                    }
                    if (answerArray[r - 1][c + 1] != 'X') {
                        answerArray[r - 1][c + 1]++;
                    }
                    if (answerArray[r][c + 1] != 'X') {
                        answerArray[r][c + 1]++;
                    }
                }
            }
            // Bottom, right corner
            if ((r == rows - 1) && (c == columns - 1)) {
                if (answerArray[r][c] == 'X') {
                    if (answerArray[r][c - 1] != 'X') {
                        answerArray[r][c - 1]++;
                    }
                    if (answerArray[r - 1][c - 1] != 'X') {
                        answerArray[r - 1][c - 1]++;
                    }
                    if (answerArray[r - 1][c] != 'X') {
                        answerArray[r - 1][c]++;
                    }
                }
            }
        }
    }
    
    // replace zeros with spaces
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            if (answerArray[r][c] == '0') {
                answerArray[r][c] = ' ';
            }
        }
    }
}

//======================================================================

int output_answerArray(char answerArray[][MAX_COL], int rows, int columns) {
    ofstream fout;
    
    // open file
    fout.open("answer_game_board.txt");
    if (!fout.is_open()) {
        cout << "Could not open file answer_game_board.txt." << endl;
        return 0;
    }
    
    // loop through columns
    for (int r = 1; r <= (rows * 2 + 2); r++) {
        // print column (c) numbers
        if (r == 1) {
            fout << "     ";
            for (int c = 1; c <= columns; c++) {
                if (c < 10) {
                    fout << c << "   ";
                }
                if (c >= 10) {
                    fout << c << "  ";
                }
            }
            fout << endl;
        }
        // print row lines between cells
        if (r % 2 == 0) {
            fout << "   ";
            for (int c = 1; c <= columns; c++) {
                fout << "----";
            }
            fout << "-" << endl;
        }
        // print row numbers and rows
        int row = 0;
        if ((r % 2 == 1) && (r != 1)) {
            // convert loop iteration number into number of actual row in answerArray
            row = (r - 1) / 2;
            if (row < 10) {
                fout << row << "  |";
            }
            if (row >= 10) {
                fout << row << " |";
            }
            for (int c = 1; c <= columns; c++) {
                fout << " " << answerArray[row - 1][c - 1] << " |";
            }
            fout << endl;
        }
    }
    
    // Close file
    fout.close();
    
    return 1;
}

//======================================================================

void make_gameArray(char gameArray[][MAX_COL], int rows, int columns) {
    
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            gameArray[r][c] = '@';
        }
    }
}

//======================================================================

int output_gameArray(char gameArray[][MAX_COL], int rows, int columns) {
    ofstream fout;
    
    // open file
    fout.open("game_board.txt");
    if (!fout.is_open()) {
        cout << "Could not open file game_board.txt." << endl;
        return 0;
    }
    
    // loop through columns
    for (int r = 1; r <= (rows * 2 + 2); r++) {
        // print column (c) numbers
        if (r == 1) {
            fout << "     ";
            for (int c = 1; c <= columns; c++) {
                if (c < 10) {
                    fout << c << "   ";
                }
                if (c >= 10) {
                    fout << c << "  ";
                }
            }
            fout << endl;
        }
        // print row lines between cells
        if (r % 2 == 0) {
            fout << "   ";
            for (int c = 1; c <= columns; c++) {
                fout << "----";
            }
            fout << "-" << endl;
        }
        // print row numbers and rows
        int row = 0;
        if ((r % 2 == 1) && (r != 1)) {
            // convert loop iteration number into number of actual row in gameArray
            row = (r - 1) / 2;
            if (row < 10) {
                fout << row << "  |";
            }
            if (row >= 10) {
                fout << row << " |";
            }
            for (int c = 1; c <= columns; c++) {
                fout << " " << gameArray[row - 1][c - 1] << " |";
            }
            fout << endl;
        }
    }
    
    // Close file
    fout.close();
    
    return 1;
}

//======================================================================

void getCoordinates(char gameArray[][MAX_COL], int &r, int &c, int rows, int columns, char &action, int i) {
    bool invalid = false;
    do {    
        invalid = false;
        
        // get Action indicator
        action = getInput('A', 'D', "Enter action: ");
        
        // if user wishes to save game or quit, break out of loop and function
        if ((action == 'C') || (action == 'D')) {
            break;
        }
        
        // get row number
        r = getInput(1, rows, "Enter row number: ");
        
        // get column number
        c = getInput(1, columns, "Enter column number: ");
        
        // convert guesses from row numbers into index numbers
        r = r - 1;
        c = c - 1;
        
        if ((gameArray[r][c] != '@') && (i != 1) && (action == 'A')) {
            cout << endl << "Error: You already uncovered this square! Try again!" << endl;
            invalid = true;
        }
    }
    while (invalid);
}

//======================================================================

bool update_gameArray(char answerArray[][MAX_COL], char gameArray[][MAX_COL], int rows, int columns, int r, int c, char action) {
    // if user wishes to uncover a cell
    if (action == 'A') {
        if (answerArray[r][c] != ' ') {
            gameArray[r][c] = answerArray[r][c];
            if(answerArray[r][c] == 'X') {
                gameArray[r][c] = 'L';
                return true;
            }
        }
        if (answerArray[r][c] == ' ') {
            gameArray[r][c] = answerArray[r][c];
            answerArray[r][c] = '0';
            check_adjacent_cells(answerArray, gameArray, rows, columns, r, c);
        }
    }
    // if user wishes to flag a cell
    if (action == 'B') {
        gameArray[r][c] = 'X';
    }
    return false;
}

//======================================================================

void check_adjacent_cells(char answerArray[][MAX_COL], char gameArray[][MAX_COL], int rows, int columns, int r, int c) {
    
    // // transfer over cell whose adjacents are being checked
    // gameArray[r][c] = answerArray[r][c];
    
    // check middle section not on any edge
    if ((r > 0) && (r < rows - 1) && (c > 0) && (c < columns - 1)) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                check (answerArray, gameArray, rows, columns, r, c, i, j);
            }
        }
    }
    
    // check top left corner
    if ((r == 0) && (c == 0)) {
        for (int i = 0; i <= 1; i++) {
            for (int j = 0; j <= 1; j++) {
                check (answerArray, gameArray, rows, columns, r, c, i, j);
            }
        }
    }
    
    // top row
    if ((r == 0) && (c > 0) && (c < columns - 1)) {
        for (int i = 0; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                check (answerArray, gameArray, rows, columns, r, c, i, j);
            }
        }
    }
    
    // top right corner
    if ((r == 0) && (c == columns - 1)) {
        for (int i = 0; i <= 1; i++) {
            for (int j = -1; j <= 0; j++) {
                check (answerArray, gameArray, rows, columns, r, c, i, j);
            }
        }
    }
    
    // left-most column
    if ((r > 0) && (r < rows - 1) && (c == 0)) {
        for (int i = -1; i <= 1; i++) {
            for (int j = 0; j <= 1; j++) {
                check (answerArray, gameArray, rows, columns, r, c, i, j);
            }
        }
    }
    
    // Right-most column
    if ((r > 0) && (r < rows - 1) && (c == columns - 1)) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 0; j++) {
                check (answerArray, gameArray, rows, columns, r, c, i, j);
            }
        }
    }
    
    // Bottom, left corner
    if ((r == rows - 1) && (c == 0)) {
        for (int i = -1; i <= 0; i++) {
            for (int j = 0; j <= 1; j++) {
                check (answerArray, gameArray, rows, columns, r, c, i, j);
            }
        }
    }
    
    // Bottom row
    if ((r == rows - 1) && (c > 0) && (c < columns - 1)) {
        for (int i = -1; i <= 0; i++) {
            for (int j = -1; j <= 1; j++) {
                check (answerArray, gameArray, rows, columns, r, c, i, j);
            }
        }
    }
    
    // Bottom, right corner
    if ((r == rows - 1) && (c == columns - 1)) {
        for (int i = -1; i <= 0; i++) {
            for (int j = -1; j <= 0; j++) {
                check (answerArray, gameArray, rows, columns, r, c, i, j);
            }
        }
    }
}

//======================================================================

void check(char answerArray[][MAX_COL], char gameArray[][MAX_COL], int rows, int columns, int r, int c, int i, int j) {
    // if cell is ' ' or a number > 0
    if ((answerArray[r + i][c + j] != 'X') && (answerArray[r + i][c + j] != '0')) {
        gameArray[r + i][c + j] = answerArray[r + i][c + j];
        
        // move on to next step if cell is ' '
        if (answerArray[r + i][c + j] == ' ') {
            // set ' ' cell to '0' so it is not checked again
            answerArray[r + i][c + j] = '0';
            // re-call function to check this new cell
            check_adjacent_cells(answerArray, gameArray, rows, columns, r + i, c + j);
        }
    }
}

//======================================================================

bool check_victory(char answerArray[][MAX_COL], char gameArray[][MAX_COL], int rows, int columns) {
    // loop through each cell
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            if (answerArray[r][c] == 'X') {
                if (answerArray[r][c] != gameArray[r][c]) {
                    return false;
                }
            }
        }
    }
    return true;
}

//======================================================================

int save_game(char answerArray[][MAX_COL], char gameArray[][MAX_COL], int rows, int columns, int bombs) {
    ofstream fout;
    
    // open file
    fout.open("savegame.txt");
    if (!fout.is_open()) {
        cout << "Could not open file savegame.txt." << endl;
        return 0;
    }
    
    // output number of rows and columns and bombs
    fout << rows << " " << columns << " " << bombs << endl;
    
    // output answerArray
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            // if current location is ' ', change to '0'
            if (answerArray[r][c] == ' ') {
                answerArray[r][c] = '0';
            }
            // output current location
            fout << answerArray[r][c];
        }
        fout << endl;
    }
    
    // output gameArray
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            // if current location is ' ', change to '0'
            if (gameArray[r][c] == ' ') {
                gameArray[r][c] = '0';
            }
            // output current location
            fout << gameArray[r][c];
        }
        fout << endl;
    }
    
    // close file
    fout.close();
    
}

//======================================================================

int get_array_info(int &rows, int &columns, int &bombs) {
    ifstream fin;
    
    // try to open file
    fin.open("savegame.txt");
    
    // return 0 if error
    if (!fin.is_open()) {
        cout << "Could not open file \"savegame.txt\"" << endl;
        return 0;
    }
    
    // get number of rows and columns
    string row1; // used to hold row with row and column information
    getline(fin, row1);
    
    // label where spaces are
    size_t space = row1.find(" ");
    size_t space2 = row1.find(" ", space + 1);
    
    // break into two substrings
    string rowInfo = row1.substr(0, space);
    string columnInfo = row1.substr(space + 1, space2 - 1 - space);
    string bombInfo = row1.substr(space2 + 1, row1.size() - 1 - space2);
    
    // convert to double variables
    rows = stoi(rowInfo);
    columns = stoi(columnInfo);
    bombs = stoi(bombInfo);
    
    // close file
    fin.close();
}

//======================================================================

int load_game(char answerArray[][MAX_COL], char gameArray[][MAX_COL], int rows, int columns) {
    ifstream fin;
    
    // try to open file
    fin.open("savegame.txt");
    
    // return 0 if error
    if (!fin.is_open()) {
        cout << "Could not open file \"savegame.txt\"" << endl;
        return 0;
    }
    
    // get rid of first row in file
    string trash;
    getline(fin, trash);
    
    // input answerArray
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            fin >> answerArray[r][c];
            if (answerArray[r][c] == '0') {
                answerArray[r][c] = ' ';
            }
        }
    }
    
    // input gameArray
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            fin >> gameArray[r][c];
            if (gameArray[r][c] == '0') {
                gameArray[r][c] = ' ';
            }
        }
    }
    
    fin.close();
    
    return 1;
}
