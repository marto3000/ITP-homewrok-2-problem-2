#include <iostream>
#include <cstring>
using namespace std;

void findPaths(char** map, int rows, int cols, int maxPathLeng, int& shortesetPath, int currentRow, int currentCol, char* currentPath, bool** marked)
{
	currentPath[strlen(currentPath) + 1] = '\0';
	currentPath[strlen(currentPath)] = map[currentRow][currentCol];
	marked[currentRow][currentCol] = true;
	if (map[currentRow][currentCol] == 'E')
	{
		if (strlen(currentPath) < shortesetPath)
		{
			shortesetPath = strlen(currentPath);
		}
		return;
	}
	else
	{
		if (currentCol - 1 >= 0 && marked[currentRow][currentCol - 1] == false && (map[currentRow][currentCol] == 'S' || (map[currentRow][currentCol - 1] == 'E' && map[currentRow][currentCol] == 'z') || (map[currentRow][currentCol - 1] - map[currentRow][currentCol] == 1 || map[currentRow][currentCol - 1] - map[currentRow][currentCol] == 0)))//left
		{
			findPaths(map, rows, cols, maxPathLeng, shortesetPath, currentRow, currentCol - 1, currentPath, marked);
			currentPath[strlen(currentPath) - 1] = '\0';
			marked[currentRow][currentCol - 1] = false;
		}
		if (currentCol + 1 < cols && marked[currentRow][currentCol + 1] == false && (map[currentRow][currentCol] == 'S' || (map[currentRow][currentCol + 1] == 'E' && map[currentRow][currentCol] == 'z') || (map[currentRow][currentCol + 1] - map[currentRow][currentCol] == 1 || map[currentRow][currentCol + 1] - map[currentRow][currentCol] == 0)))//right
		{
			findPaths(map, rows, cols, maxPathLeng, shortesetPath, currentRow, currentCol + 1, currentPath, marked);
			currentPath[strlen(currentPath) - 1] = '\0';
			marked[currentRow][currentCol + 1] = false;
		}
		if (currentRow - 1 >= 0 && marked[currentRow - 1][currentCol] == false && (map[currentRow][currentCol] == 'S' || (map[currentRow - 1][currentCol] == 'E' && map[currentRow][currentCol] == 'z') || (map[currentRow - 1][currentCol] - map[currentRow][currentCol] == 1 || map[currentRow - 1][currentCol] - map[currentRow][currentCol] == 0)))//up
		{
			findPaths(map, rows, cols, maxPathLeng, shortesetPath, currentRow - 1, currentCol, currentPath, marked);
			currentPath[strlen(currentPath) - 1] = '\0';
			marked[currentRow - 1][currentCol] = false;
		}
		if (currentRow + 1 < rows && marked[currentRow + 1][currentCol] == false && (map[currentRow][currentCol] == 'S' || (map[currentRow + 1][currentCol] == 'E' && map[currentRow][currentCol] == 'z') || (map[currentRow + 1][currentCol] - map[currentRow][currentCol] == 1 || map[currentRow + 1][currentCol] - map[currentRow][currentCol] == 0)))//down
		{
			findPaths(map, rows, cols, maxPathLeng, shortesetPath, currentRow + 1, currentCol, currentPath, marked);
			currentPath[strlen(currentPath) - 1] = '\0';
			marked[currentRow + 1][currentCol] = false;
		}
		return;
	}
}

int shortestPathLeng(char** map, int rows, int cols)
{
	int maxPathLeng = rows * cols + 1;
	int shortesetPath = rows * cols;

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

	findPaths(map, rows, cols, maxPathLeng, shortesetPath, 0, 0, currentPath, marked);
	cout << shortesetPath;

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

	return 0;
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
	for (int i = 0; i < rows; i++)
	{
		cin.getline(map[i], cols + 1);
	}

	shortestPathLeng(map, rows, cols);

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