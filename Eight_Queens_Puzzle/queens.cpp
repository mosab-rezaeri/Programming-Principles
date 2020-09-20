#include <iostream>
#include <iomanip>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

int counter = 1;     //Counter for the solution number
bool board[8][8];    //The game board.


/**
 * Initializing all element at the board[8][8] by "false"
 *
 * @param board  A 2D Array of The game board.
 * 
 * @note  Calls by main and just for one time.
 ****************************************************************************/
void initialize_board(bool board[8][8])
{
	for (int i=0; i<8; ++i)
	{
		for (int j=0; j<8; ++j)
		{
			board[i][j] = false;
		}
	}
}


/**
 * Display the game board in output.
 *
 * @param board  A 2D Array of The game board.
 * @param n      Number of the solution. it feeds by counter. 
 * 
 * @note  Here "X" is for queens and "-" is for empty location.
 ****************************************************************************/
void print_solution(bool board[8][8], int n)
{
	cout << "solution " << n << endl;

	for (int i=0; i<8; ++i)
	{
		for (int j=0; j<8; ++j)
		{
			if (board[i][j])
				cout << 'X';
			else
				cout << '-';
			
			if (j < 7)
				cout <<' ';
		}
		cout << endl;
	}
}


/**
 * Checks for the other queens threat.
 *
 *
 * @param board  A 2D Array of The game board.
 * @param row    Row index of the Queen position.
 * @param col    Col index of the Queen position.
 *
 * @return  True if (Row,Col) location is threatened. 
 *          False if (Row,Col) location is safe.
 * 
 * @note  Checks the 3 dangerous lines for the other queens.
 *        vertical line, and two diagonal lines. 
 ****************************************************************************/
bool check_attacking(bool board[8][8], int row, int col) 
{ 
    int i;
    int j; 

    for (i = row; i >= 0; i--)
        if (board[i][col])
          	return false;
  
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) 
        if (board[i][j]) 
            return false; 
  
    for (i = row, j = col; i >= 0 && j < 8; i--, j++) 
        if (board[i][j]) 
            return false; 
  
    return true; 
} 


/**
 * Places one queen at safe place is each row.
 *
 *
 * @param board  A 2D Array of The game board.
 * @param row    Row index of the game board.
 * 
 * @return  True when safe location is found at the row. 
 *          False when safe location is not found at the row. 
 *
 * @note  Call print_solution founction when All rows were specified by 
 *        one queen at a safe location. 
 ****************************************************************************/
bool place_eight(bool board[8][8], int row)
{
	if (row == 8) // All rows were specified by one queen.
	{
		print_solution(board,counter);
		counter++;
	}

	for (int j = 0; j < 8; j++)
	{
		if (check_attacking(board, row, j))
		{
			board[row][j] = true;

			if (place_eight(board, row + 1))
				return true;

			board[row][j] = false;
		}
	}
	return false;
}


/**
 * Main founction of the Eight Queens Puzzle.
 *
 * @note The program Displays all 92 solution for Eight Queens Puzzle.
 * 
 ****************************************************************************/
int main()
{
	
	initialize_board(board);
	
	place_eight(board, 0);  // 0 is the index of the first row of the game board.

	return 0;
}