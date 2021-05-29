#include "Maze.h";
#include "Post.h";


Maze::Maze(int numRows, int numCols) {
	this->numRows = numRows;
	this->numCols = numCols;
}
int Maze::getnumRows() const {
	return numRows;
}
int Maze::getnumCols() const {
	return numCols;
}