// Final_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Luke Colehower
//Joe Westhusin 
//Angel Espinosa 

#include <iostream>
using namespace std;

struct Player
{
	char symbol;
};
void initializeBoard(char* board, int size) //Initialize Board 
{
	for (int i = 0; i < size; i++)
	{
		board[i] = ' ';
	}
}
void displayBoard(char* board, int size) // Displays board to users 
{
	cout << "- - - - - - - - - - - - -" << endl;
	for (int i = 0; i < size; i += 3)
	{
		cout << " |  " << board[i] << " | " << board[i + 1] << " | " << board[i + 2] << "  | " << endl;
		cout << "- - - - - - - - - - - -" << endl;
	}
}
bool isMoveValid(char* board, int move) //Valid if move is between 1 - 9
{
	return(move >= 1 && move <= 9 && board[move - 1] == ' ');
}
void makeMove(char* board, int move, Player* currentPlayer)
{
	board[move - 1] = currentPlayer->symbol;
}
bool checkWin(char* board, char symbol) //Checking Rows, Cols, and Diagnols
{
	for (int i = 0; i < 3; i++)
	{
		if (board[i * 3] == symbol && board[i * 3 + 1] == symbol && board[i * 3 + 2] == symbol)
			return true;
	}
	for (int i = 0; i < 3; i++)
	{
		if (board[i] == symbol && board[i + 3] == symbol && board[i + 6] == symbol) 
			return true;
	}
	if ((board[0] == symbol && board[4] == symbol && board[8] == symbol) ||
		board[2] == symbol && board[4] == symbol && board[6] == symbol) 
	{
		return true;
	}
	return false;
}
bool checkDraw(char* board) // Checks blank spacess
{
	for (int i = 0; i < 9; i++)
	{
		if (board[i] == ' ')
			return false;
	}
	return true;
}
void switchPlayer(Player** currentPlayer, Player* player1, Player* player2) //Switch between player 1 and Player 2
{
	if (*currentPlayer == player1)
	{
		*currentPlayer = player2;
	}
	else
		*currentPlayer = player1;
}
int main()
{
	const int BOARD_SIZE = 9; // array for board size
	char board[BOARD_SIZE];
	initializeBoard(board, BOARD_SIZE);

	//creating players
	Player player1 = { 'X' };
	Player player2 = { 'O' };
	Player* currentPlayer = &player1;

	int move;
	bool gameOver = false; 

	while (!gameOver)
	{
		displayBoard(board, BOARD_SIZE);
		cout << "Player " << currentPlayer->symbol << "'s turn, Enter a move (1-9): ";
		cin >> move;
		if (isMoveValid(board, move))
		{
			makeMove(board, move, currentPlayer);
			if (checkWin(board, currentPlayer->symbol))
			{
				displayBoard(board, BOARD_SIZE);
				cout << "Player " << currentPlayer->symbol << " WINS! " << endl;
				gameOver = true;
			}
			else if (checkDraw(board))
			{
				displayBoard(board, BOARD_SIZE);
				cout << "It is a Draw...." << endl;
				gameOver = true;
			}
			else
			{
				switchPlayer(&currentPlayer, &player1, &player2);

			}
		}
		else
		{
			cout << "Invalid move, try again: " << endl;
		}
	}
	return 0;
}