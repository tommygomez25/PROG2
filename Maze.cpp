#include "Maze.h";
#include "Post.h";


Maze::Maze(int numRows, int numCols) {
	this->numRows = numRows;
	this->numCols = numCols;
}
bool Maze::addPost(const Post& post, const Position& position) {
	return true;
}
int Maze::getnumRows() const {
	return numRows;
}
int Maze::getnumCols() const {
	return numCols;
}
