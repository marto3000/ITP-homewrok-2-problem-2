#include <iostream>
#include <cstring>
using namespace std;

bool validMap(char** map, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (!((map[i][j] >= 'a' && map[i][j] <= 'z') || map[i][j] == 'S' || map[i][j] == 'E'))
			{
				return false;
			}
		}
	}
	return true;
}

char* findPaths(char** map, int rows, int cols, int maxPathLeng, int& shortesetPathLeng, int currentRow, int currentCol, char* currentPath, bool** marked, char* shortestPath)
{
	currentPath[strlen(currentPath) + 1] = '\0';
	currentPath[strlen(currentPath)] = map[currentRow][currentCol];
	marked[currentRow][currentCol] = true;
	if (map[currentRow][currentCol] == 'E')
	{
		if (strlen(currentPath) < shortesetPathLeng)
		{
			shortesetPathLeng = strlen(currentPath);
			strcpy_s(shortestPath, maxPathLeng, currentPath);
		}
	}
	else
	{
		if (currentCol - 1 >= 0 && marked[currentRow][currentCol - 1] == false && (map[currentRow][currentCol] == 'S' || (map[currentRow][currentCol - 1] == 'E' && map[currentRow][currentCol] == 'z') || (map[currentRow][currentCol - 1] - map[currentRow][currentCol] >= -1 && map[currentRow][currentCol - 1] - map[currentRow][currentCol] <= 1)))//left
		{
			findPaths(map, rows, cols, maxPathLeng, shortesetPathLeng, currentRow, currentCol - 1, currentPath, marked, shortestPath);
			currentPath[strlen(currentPath) - 1] = '\0';
			marked[currentRow][currentCol - 1] = false;
		}
		if (currentCol + 1 < cols && marked[currentRow][currentCol + 1] == false && (map[currentRow][currentCol] == 'S' || (map[currentRow][currentCol + 1] == 'E' && map[currentRow][currentCol] == 'z') || (map[currentRow][currentCol + 1] - map[currentRow][currentCol] >= -1 && map[currentRow][currentCol + 1] - map[currentRow][currentCol] <= 1)))//right
		{
			findPaths(map, rows, cols, maxPathLeng, shortesetPathLeng, currentRow, currentCol + 1, currentPath, marked, shortestPath);
			currentPath[strlen(currentPath) - 1] = '\0';
			marked[currentRow][currentCol + 1] = false;
		}
		if (currentRow - 1 >= 0 && marked[currentRow - 1][currentCol] == false && (map[currentRow][currentCol] == 'S' || (map[currentRow - 1][currentCol] == 'E' && map[currentRow][currentCol] == 'z') || (map[currentRow - 1][currentCol] - map[currentRow][currentCol] >= -1 && map[currentRow - 1][currentCol] - map[currentRow][currentCol] <= 1)))//up
		{
			findPaths(map, rows, cols, maxPathLeng, shortesetPathLeng, currentRow - 1, currentCol, currentPath, marked, shortestPath);
			currentPath[strlen(currentPath) - 1] = '\0';
			marked[currentRow - 1][currentCol] = false;
		}
		if (currentRow + 1 < rows && marked[currentRow + 1][currentCol] == false && (map[currentRow][currentCol] == 'S' || (map[currentRow + 1][currentCol] == 'E' && map[currentRow][currentCol] == 'z') || (map[currentRow + 1][currentCol] - map[currentRow][currentCol] >= -1 && map[currentRow + 1][currentCol] - map[currentRow][currentCol] <= 1)))//down
		{
			findPaths(map, rows, cols, maxPathLeng, shortesetPathLeng, currentRow + 1, currentCol, currentPath, marked, shortestPath);
			currentPath[strlen(currentPath) - 1] = '\0';
			marked[currentRow + 1][currentCol] = false;
		}
	}
	return shortestPath;
}

void resetValues(char* currentPath, bool** marked, int rows, int cols)
{
	int currentPathLeng = strlen(currentPath);
	for (int i = 0; i < currentPathLeng; i++)
	{
		currentPath[i] = '\0';
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			marked[i][j] = false;
		}
	}
}

void shortestPath(char** map, int rows, int cols)
{
	int maxPathLeng = rows * cols + 1;
	int shortesetPathLeng = rows * cols + 1;

	//new marked
	bool** marked = new bool* [rows];
	for (int i = 0; i < rows; i++)
	{
		marked[i] = new bool[cols];
		for (int j = 0; j < cols; j++)
		{
			marked[i][j] = false;
		}
	}
	//

	//new currentPath
	char* currentPath = new char[maxPathLeng];
	currentPath[0] = '\0';
	//

	//new shortestPath
	char* shortestPath = new char[maxPathLeng];
	shortestPath[0] = '\0';
	//

	findPaths(map, rows, cols, maxPathLeng, shortesetPathLeng, 0, 0, currentPath, marked, shortestPath);
	if (shortesetPathLeng == rows * cols + 1)
	{
		cout << "No path found!" << endl;
		return;
	}
	
	resetValues(currentPath, marked, rows, cols);

	cout << shortesetPathLeng << endl;
	
	//new bestPath
	char* bestPath = new char[maxPathLeng + 1];
	//

	for (int i = 0; i < maxPathLeng; i++)
	{
		bestPath[i] = 'a';
	}
	bestPath[maxPathLeng] = '\0';
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (map[i][j] == 'a' && (strlen(findPaths(map, rows, cols, maxPathLeng, shortesetPathLeng, i, j, currentPath, marked, shortestPath)) < strlen(bestPath)))
			{
				resetValues(currentPath, marked, rows, cols);

				strcpy_s(bestPath, maxPathLeng, findPaths(map, rows, cols, maxPathLeng, shortesetPathLeng, i, j, currentPath, marked, shortestPath));

				resetValues(currentPath, marked, rows, cols);
			}
			else
			{
				resetValues(currentPath, marked, rows, cols);
			}
		}
	}
	cout << bestPath;

	//delete bestPath
	delete[] bestPath;
	bestPath = nullptr;
	//

	//delete shortestPath
	delete[] shortestPath;
	shortestPath = nullptr;
	//

	//delete currentPath
	delete[] currentPath;
	currentPath = nullptr;
	//

	//delete marked
	for (int i = 0; i < rows; i++)
	{
		delete[] marked[i];
		marked[i] = nullptr;
	}
	delete[] marked;
	marked = nullptr;
	//

}

int main()
{
	int rows, cols;
	do
	{
		cin >> rows >> cols;
	} while (rows < 1 || cols < 1);
	
	//new map
	char** map = new char* [rows];
	for (int i = 0; i < rows; i++)
	{
		map[i] = new char[cols + 1];
	}
	//
	/*
	Sabqponm
	abcryxxl
	accszExk
	acctuvwj
	abdefghi
	*/
	cin.ignore();
	do
	{
		for (int i = 0; i < rows; i++)
		{
			cin.getline(map[i], cols + 1);
		}
		if (validMap(map, rows, cols))
		{
			break;
		}
	} while (true);

	shortestPath(map, rows, cols);

	//delete map
	for (int i = 0; i < rows; i++)
	{
		delete[] map[i];
		map[i] = nullptr;
	}
	delete[] map;
	map = nullptr;
	//

	return 0;
}