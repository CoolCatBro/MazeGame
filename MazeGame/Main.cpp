#include "Maze.hpp"
#include <ctime>
int main()
{
	srand(time(nullptr));
	Maze mz(5,5);
	mz.createMaze();
	mz.display();
	system("pause");
	return 0;
}