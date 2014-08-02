// This is a simple commandline sudoku program.

#include<iostream>
#include<cstdlib>

using namespace std;

//returns the next letter in the input
char read_char()
{
	char car;
	while((car == toupper(car)) && (car == tolower(car)))
		cin.get(car);
	return car;
}//read_char

//Returns the first single integer decimal in the input
int read_int()
{
	char car = ' ';
	while(car < '0' || car > '9')
	{
		cin.get(car);
	}//while
	return car - '0';
}//read_int

// Draws a pretty line
void fancy_line()
{
	int j;
	for(j = 0; j <= 9; j++)
	{
		if(j%3 == 0)
		{
			cout << "+";
		}//if
		if(j != 9)
			cout << "-";
	}//for
	cout << "\n";
}//fancy_line

// Class sudoku
class sudoku
{
	private:
		int grid[9][9];
		int temp[9];
		void clear_temp();
		bool check_row(int);
		bool check_col(int);
		//bool check_subgrid(int,int);
		//bool check_win();
		bool int_in_row(int,int);
		bool int_in_col(int,int);
		bool int_in_subgrid(int,int,int);
		void row_solve(int);
		void col_solve(int);
	public:
		sudoku();
		void draw();
		void set_cell(int, int, int);
		void fill_rand(int);
		void clear_grid();
		void solve();
};

// Constructor for sudoku
sudoku::sudoku()
{
	int i,j;
	for(i = 0; i < 9; i++)
		for(j = 0; j < 9; j++)
			grid[i][j] = 0;
}//sudoku::sudoku

// Displays the sudoku
void sudoku::draw()
{
	int i,j;
	cout << "\n";
	fancy_line();
	for(i = 0; i < 9; i++)
	{
		cout << "|";
		for(j = 0; j < 9; j++)
		{
			if(grid[i][j] == 0)
			{
				cout << " ";
			}//if
			else
			{
				cout << grid[i][j];
			}//else
			if(j%3 == 2)
				cout << "|";
		}//for
		if(check_row(i))
		{
			cout << " V\n";
		}//if
		else
		{
			cout << " X\n";
		}//else
		if(i%3 == 2)
		{
			fancy_line();
		}//if
	}//for
	cout << " ";
	for(j = 0; j < 9; j++)
	{
		if(check_col(j))
		{
			cout << "V";
		}//if
		else
		{
			cout << "X";
		}//else
		if(j%3 == 2)
			cout << " ";
	}//for
	return;
}//sudoku::draw

// Checks if the given row is correct
bool sudoku::check_row(int row)
{
	int j;
	int sum = 0;
	int check[9] = {0,0,0,0,0,0,0,0,0};
	for(j = 0; j < 9; j++)
	{
		if(grid[row][j] != 0)
			check[grid[row][j]-1] = 1;
	}//for
	for(j = 0; j < 9; j++)
	{
		sum = check[j] + sum;
	}//for
	if(sum == 9)
	{
		return true;
	}//if
	return false;
}//sudoku::check_row

// Checks if the given col is correct
bool sudoku::check_col(int col)
{
	int i;
	int sum = 0;
	int check[9] = {0,0,0,0,0,0,0,0,0};
	for(i = 0; i < 9; i++)
	{
		if(grid[i][col] != 0)
			check[grid[i][col]-1] = 1;
	}//for
	for(i = 0; i < 9; i++)
	{
		sum = check[i] + sum;
	}//for
	if(sum == 9)
	{
		return true;
	}//if
	return false;
}//sudoku::check_row

// Set the cell at (x,y) to number n
void sudoku::set_cell(int x, int y, int n)
{
	grid[y][x] = n;
}//sudoku::set_num

// Returns true if the integer is present in the given row
bool sudoku::int_in_row(int n, int row)
{
	int j;
	for(j = 0; j < 9; j++)
	{
		if(grid[row][j] == n)
		{
			return true;
		}//if
	}//for
	return false;
}//sudoku::int_in_row

// Returns true if the integer is present in the given col
bool sudoku::int_in_col(int n, int col)
{
	int i;
	for(i = 0; i < 9; i++)
	{
		if(grid[i][col] == n)
		{
			return true;
		}//if
	}//for
	return false;
}//sudoku::int_in_row

// Returns true if the given integer is present in the subgrid
bool sudoku::int_in_subgrid(int x, int y, int n)
{
	int i, j;
	int xcor, ycor;
	xcor = x - x%3;
	ycor = y - y%3;
	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 3; j++)
		{
			if(grid[ycor + i][xcor + j] == n)
			{
				return true;
			}//if
		}//for
	}//for
	return false;
}//sudoku::int_in_subgrid

// Fills the grid with random integers from 1-9
void sudoku::fill_rand(int m)
{
	int k = 0;
	int x, y, n;
	while(k < m)
	{
		x = rand()%9;
		y = rand()%9;
		if(grid[y][x] == 0)
		{
			n = rand()%9 + 1;
			if(!int_in_col(n, x) && !int_in_row(n, y) && !int_in_subgrid(x, y, n))
			{
				grid[y][x] = n;
				k++;
			}//if
		}//if
	}//while
}//fill_rand

// Clears the sudoku grid
void sudoku::clear_grid()
{
	int i, j;
	for(i = 0; i < 9; i++)
		for(j = 0; j < 9; j++)
			grid[i][j] = 0;
}//sudoku::clear_grid

// Clears the temp array
void sudoku::clear_temp()
{
	int i;
	for(i = 0; i < 9; i++)
		temp[i] = 0;
}//sudoku::clear_temp

// Solves the rows of the sudoku
void sudoku::row_solve(int n)
{
	int i, j;
	int sum = 0;
	clear_temp();
	for(i = 0; i < 9; i++)
	{
		if(!int_in_row(n, i))
		{
			for(j = 0; j < 9; j++)
			{
				if(grid[i][j] == 0)
				{
					if(!int_in_col(n, j) && !int_in_subgrid(j, i, n))
					{
						temp[j] = 1;
						sum++;
					}
				}//if
			}//for
			if(sum == 1)
			{
				for(j = 0; j < 9; j++)
				{
					if(temp[j] == 1)
					{
						grid[i][j] = n;
						break;
					}
				}//for
			}//if
		}//if
		clear_temp();
		sum = 0;
	}//for
}//sudoku::row_solve()

// Solves the colums of the sudoku
void sudoku::col_solve(int n)
{
	int i, j;
	int sum = 0;
	clear_temp();
	for(j = 0; j < 9; j++)
	{
		if(!int_in_col(n, j))
		{
			for(i = 0; i < 9; i++)
			{
				if(grid[i][j] == 0)
				{
					if(!int_in_row(n, i) && !int_in_subgrid(j, i, n))
					{
						temp[i] = 1;
						sum++;
					}
				}//if
			}//for
			if(sum == 1)
			{
				for(i = 0; i < 9; i++)
				{
					if(temp[i] == 1)
					{
						grid[i][j] = n;
						break;
					}
				}//for
			}//if
		}//if
		clear_temp();
		sum = 0;
	}//for
}//sudoku::col_solve()

// Tries to solve the given sudoku
void sudoku::solve()
{
	int n;

	for(n = 1; n <= 9; n++)
	{
		row_solve(n);
		col_solve(n);
	}//for
}//sudoku::solve

// Menu where the user can preform actions
void menu(sudoku &sud)
{
	int n;
	int x, y;
	char car = ' ';
	cout << "Welcome to this humble commandline implementation of sudoku" << endl;

	while(car != 'E')
	{
		cout << "\n[S]et cell, [D]raw, [R]andom fill, S[O]lve, [C]lear grid, [E]xit\n";
		car = read_char();
		switch(car)
		{
			case 'S':
				cout << "Give the location of the cell.\nx= ";
				x = read_int();
				cout << "y= ";
				y = read_int();
				cout << "n= ";
				n = read_int();
				cout << "\n";
				sud.set_cell(x-1,y-1,n);
				break;
			case 'D':
				cout << "Drawing the grid.\n";
				sud.draw();
				break;
			case 'R':
				cout << "Filling the grid randomly. n= ";
				cin >> n;
				sud.fill_rand(n);
				break;
			case 'O':
				cout << "Solving sudoku\n";
				sud.solve();
				break;
			case 'C':
				cout << "Clearing grid\n";
				sud.clear_grid();
				break;
		}//switch
		sud.draw();
	}//while
}//menu

// main of the program
int main()
{
	sudoku sud;
	menu(sud);
	return 0;
}//main
