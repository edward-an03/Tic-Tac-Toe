#include <iostream>

using namespace std;

class Grid
{
	private:
		char ** gridData; //pointer to an array of char pointers. The array will be located on the heap
		int size;
	public:
		Grid(int n);
		~Grid();
		void setGrid(const int row, const int column, const char data);
		char getGrid(const int row, const int column) const;
		void resetGrid();
		void printGrid() const;
		int labelToRow(const int num) const;
		int labelToColumn(const int num) const;
		bool checkForWins(const char playerMarker) const;
		bool checkForFullGrid() const;
};

Grid::Grid(int n)
/*
 * Constructor
 * Creates and fills a size x size grid with default value ' '
 */
{
	size = n;
	gridData = new char*[size];
	for (int i=0; i<size; i++)
	{
		gridData[i] = new char[size];
		for (int j=0; j<size; j++)
		{
			gridData[i][j] = ' ';
		}
	}
}

Grid::~Grid()
/*
 * Destructor
 * Memory Deallocation
 */
{
	for (int i=0; i<size; i++)
	{
		delete [] gridData[i];
		gridData[i] = NULL;
	}
	delete gridData;
	gridData = NULL;
	size = 0;
}

void Grid::setGrid(const int row, const int column, const char data)
/*
 * Setter function
 */
{
	if (row >= 0 && row < size && column >= 0 && column < size)
	{ // This if statement prevents segmentation fault caused by referencing the address of an array index out of bounds
		gridData[row][column] = data;
	}
}

char Grid::getGrid(const int row, const int column) const
/*
 * Getter function
 */
{
	if (row >= 0 && row < size && column >= 0 && column < size)
	{ // This if statement prevents segmentation fault caused by referencing the address of an array index out of bounds
		return gridData[row][column];
	}
	else
	{
		return 0;
	}
	
}

void Grid::resetGrid()
/*
 * Reset function. Resets all the stored data on the grid to ' '
 */
{
	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size; j++)
		{
			gridData[i][j] = ' ';
		}
	}
}

void Grid::printGrid() const
/* 
 * A print function that shows how the current data is located on the grid
 */
{
	for (int i=0; i<size-1; i++)
	{
		for (int j=0; j<size-1; j++)
		{
			cout << "     |";
		}
		cout << endl;
		for (int j=0; j<size-1; j++)
		{

			cout << "  " << gridData[i][j] << "  |";
		}
		cout << "  " << gridData[i][size-1] << endl;
		for (int j=0; j<size-1; j++)
		{
			cout << "     |";
		}
		cout << endl;
		
		for (int i=0; i < (size*5 + size -1); i++)
		{
			cout << "-";
		}
		cout << endl;
	}
	
	for (int j=0; j<size-1; j++)
	{
		cout << "     |";
	}
	cout << endl;
	for (int j=0; j<size-1; j++)
	{
		cout << "  " << gridData[size-1][j] << "  |";
	}
	cout << "  " << gridData[size-1][size-1] << endl;
	for (int j=0; j<size-1; j++)
	{
		cout << "     |";
	}
	cout << endl;

}

int Grid::labelToRow(const int num) const
/* 
 * returns a row integer that corresponds to one of the nine gridspaces
 * this function works assuming that the grid is labelled in the order left to right, top to bottom
 */
{
	int row = (num - 1)/size;
	return row;
}

int Grid::labelToColumn(const int num) const
/* 
 * returns a column integer that corresponds to one of the nine gridspaces
 * this function works assuming that the grid is labelled in the order left to right, top to bottom
 */
{
	int column = (num - 1)%size;
	return column;
}

bool Grid::checkForWins(const char playerMarker) const //TODO: Create an algorithm that checks for size x size not just 3x3
/*
 * returns a boolean value that corresponds to whether there are 3 markers (X or O) in a row
 */
{
	bool wins = false;
	for (int i=0; i<3; i++)
	{
		if (gridData[i][0] == playerMarker && gridData[i][1] == playerMarker && gridData[i][2] == playerMarker)
		{
			wins = true;
		}
	}
	
	for (int j=0; j<3; j++)
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

bool Grid::checkForFullGrid() const
/*
 * returns a boolean value that corresponds to whether the grid is full or not
 */
{
	bool isFull = true;
	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size; j++)
		{
			if (gridData[i][j] == ' ')
			{
				isFull = false;
			}
		}
	}
	return isFull;
}


Grid ticTacToeGrid(3); //Creates a grid object for tic-tac-toes

void gamePlay(int playerNum, char playerMarker)
/*
 * This function takes in user input and places a player marker in the given spot on the grid. Then the grid is printed
 */
{
	int playerChoice;
	int row;
	int column;
	while(true) {
		cout << "Player " << playerNum << "'s turn. Enter a number (1-9) to place your " << playerMarker << endl;
		cin >> playerChoice;	
		if (cin.fail())
		{
			cout << "Wrong input. Please enter an integer from (1-9)\n";
			cin.clear();
			cin.ignore(256,'\n');   // ignore the line change
		}
		row = ticTacToeGrid.labelToRow(playerChoice);
		column = ticTacToeGrid.labelToColumn(playerChoice);
		char x = ticTacToeGrid.getGrid(row, column);
		if (x == ' ')
		{ //The loop checks if there are any values that are already on the chosen spot on the grid
			break; 
		}
	}
	ticTacToeGrid.setGrid(row, column, playerMarker);
	ticTacToeGrid.printGrid();
	cout << endl;
}


int main (void)
{
	cout << "Hello!" << endl;
	cout << "Welcome to tic-tac-toe. This is a two-player game.\n" << endl;
	Grid numberedGrid(3); //Creates a grid object strictly for labelling
	for (int i=0; i<3; i++)
	{
		for (int j=0; j<3; j++)
		{
			int number = i*3 + j + 1;
			int ASCII = number + 48; //convert to corresponding ASCII numbers
			numberedGrid.setGrid(i, j, ASCII); 
		}
	} //Grid is labelled 1-9 from left to right and top to bottom
	
	
	bool replay = true;
	while (replay)
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
			
			isFull = ticTacToeGrid.checkForFullGrid(); //Checks for a draw
			if (isFull == true)
			{
				cout << "It's a draw" << endl;
				break;
			}
		}
		ticTacToeGrid.resetGrid(); //Resets the grid for another round
		
		while(true)
		{
			cout << "Would you like to play again? (0 for no AND 1 for yes)" << endl;
			cin  >> replay;
			if (cin.fail()) //type checking
			{
				cout << "Wrong input. Please enter either 0 or 1 \n";
				cin.clear();
				cin.ignore(256,'\n'); // ignore the line change
			}
			else
			{
				break;
			}
		}
	}
	return 0;
}
