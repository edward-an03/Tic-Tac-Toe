#include <iostream>

using namespace std;
const int N = 3;

class Grid 
{
	private:
		char ** gridData; //pointer to an array of char pointers. The array will be located on the heap
	public:
		Grid();
		~Grid();
		void setGridData(int row, int column, const char data);
		void resetGrid();
		void printGrid();
		int labelToRow(const int num);
		int labelToColumn(const int num);
		bool checkForOverlap(const int row, const int column);
		bool checkForWins(char playerMarker);
		bool checkForFullGrid();
};

Grid::Grid()
/*
 * Constructor
 */
{
	gridData = new char*[N];
	for (int i=0; i<N; i++)
	{
		gridData[i] = new char[N];
		for (int j=0; j<N; j++)
		{
			gridData[i][j] = ' ';
		}
	}
}

Grid::~Grid()
/*
 * Destructor
 */
{
	for (int i=0; i<N; i++)
	{
		delete [] gridData[i];
		gridData[i] = NULL;
	}
	delete gridData;
	gridData = NULL;
}

void Grid::setGridData(int row, int column, const char data)
/*
 * Setter function. Sets one index at a time
 */
{
	if (row >= 0 && row < N && column >= 0 && column < N)
	{
		gridData[row][column] = data;
	}
}

void Grid::resetGrid()
{
	for (int i=0; i<N; i++)
	{
		for (int j=0; j<N; j++)
		{
			gridData[i][j] = ' ';
		}
	}
}

void Grid::printGrid()
/* 
 * Print function that shows how the current data is located on the grid
 */
{
	cout << "     |     |" << endl;
	cout << "  " << gridData[0][0] << "  |  " << gridData[0][1] << "  |  " << gridData[0][2] << endl;
	cout << "     |     |" << endl;
	
	for (int i=0; i<17; i++)
	{
		cout << "-";
	}
	cout << endl;
	
	cout << "     |     |" << endl;
	cout << "  " << gridData[1][0] << "  |  " << gridData[1][1] << "  |  " << gridData[1][2] << endl;
	cout << "     |     |" << endl;
	
	for (int i=0; i<17; i++)
	{
		cout << "-";
	}
	cout << endl;
	
	cout << "     |     |" << endl;
	cout << "  " << gridData[2][0] << "  |  " << gridData[2][1] << "  |  " << gridData[2][2] << endl;
	cout << "     |     |" << endl;
	
}

int Grid::labelToRow(const int num)
/* 
 * returns a row integer that corresponds to one of the nine gridspaces
 */
{
	int row = (num - 1)/N;
	return row;
}

int Grid::labelToColumn(const int num)
/* 
 * returns a column integer that corresponds to one of the nine gridspaces
 */
{
	int column = (num - 1)%N;
	return column;
}

bool Grid::checkForOverlap(const int row, const int column)
/*
 * returns a boolean value that corresponds to whether a particular space on the grid is preoccupied or not
 */
{
	if (gridData[row][column]!= ' ')
	{
		bool isOverlap = true;
		return isOverlap;
	}
	else
	{
		bool isOverlap = false;
		return isOverlap;
	}
}

bool Grid::checkForWins(char playerMarker)
/*
 * returns a boolean value that corresponds to whether there is a 3 markers (X or O) in a row
 */
{
	bool wins = false;
	for (int i=0; i<N; i++)
	{
		if (gridData[i][0] == playerMarker && gridData[i][1] == playerMarker && gridData[i][2] == playerMarker)
		{
			wins = true;
		}
	}
	
	for (int j=0; j<N; j++)
	{
		if (gridData[0][j] == playerMarker && gridData[1][j] == playerMarker && gridData[2][j] == playerMarker)
		{
			wins = true;
		}
	}
	
	if (gridData[0][0] == playerMarker && gridData[1][1] == playerMarker && gridData[2][2] == playerMarker)
	{
		wins = true;
	}
	
	if (gridData[0][2] == playerMarker && gridData[1][1] == playerMarker && gridData[2][0] == playerMarker)
	{
		wins = true;
	}
	return wins;
}

bool Grid::checkForFullGrid()
/*
 * returns a boolean value that corresponds to whether the grid is full or not
 */
{
	bool isFull = true;
	for (int i=0; i<N; i++)
	{
		for (int j=0; j<N; j++)
		{
			if (gridData[i][j] == ' ')
			{
				isFull = false;
			}
		}
	}
	return isFull;
}

void gamePlay(int playerNum, char playerMarker)
/*
 * This function takes in user input and places a player marker in the given spot on the grid. Then the grid is printed
 */
{
	int playerChoice;
	int row;
	int column;
	bool isOverlap;
	do {
		cout << "Player " << playerNum << "'s turn. Enter a number (1-9) to place your " << playerMarker << endl;
		cin >> playerChoice;
		row = ticTacToeGrid.labelToRow(playerChoice);
		column = ticTacToeGrid.labelToColumn(playerChoice);
		isOverlap = ticTacToeGrid.checkForOverlap(row, column);
	}
	while (isOverlap == true || playerChoice < 1 || playerChoice > 9);
	ticTacToeGrid.setGridData(row, column, playerMarker);
	ticTacToeGrid.printGrid();
	cout << endl;
}

Grid ticTacToeGrid; //Creates a grid for tic-tac-toe

int main (void)
{
	cout << "Hello!" << endl;
	cout << "Welcome to tic-tac-toe. This is a two-player game.\n" << endl;
	
	Grid numberedGrid; //Creates a grid strictly for labelling
	for (int i=0; i<N; i++)
	{
		for (int j=0; j<N; j++)
		{
			int number = i*3 + j + 1;
			int ASCII = number + 48; //convert to corresponding ASCII numbers
			numberedGrid.setGridData(i, j, ASCII); 
		}
	} //Labels for gridspace (1-9)
	
	bool repeat = true;
	while (repeat)
	{
		cout << "The grids are numbered as follows." << endl; 
		numberedGrid.printGrid();
		cout << "Please enter the corresponding number to place your marker.\n\n" << endl;
		while (true)
		{
			
			gamePlay(1, 'X');
			bool wins = ticTacToeGrid.checkForWins('X'); //Checks for player 1 win
			if (wins == true)
			{
				cout << "player 1 wins" << endl;
				break;
			}
			
			bool isFull = ticTacToeGrid.checkForFullGrid(); //Checks for a draw
			if (isFull == true)
			{
				cout << "It's a draw" << endl;
				break;
			}
			
			gamePlay(2, 'O');
			wins = ticTacToeGrid.checkForWins('O'); //Checks for player 2 win
			if (wins == true)
			{
				cout << "player 2 wins" << endl;
				break;
			}
		}
		ticTacToeGrid.resetGrid(); //Resets the grid for another round
		cout << "Would you like to play again? (0 or 1)" << endl;
		cin  >> repeat;
	}
	return 0;
}

//FIXME: IOEXception for playerChoice and repeat so that the program doesn't crash
