#pragma once
#include "Post.h";

class Maze
{
public:
	Maze() = default;
	Maze(int numRows, int numCols);
	int getnumRows() const;// return row
	int getnumCols() const;// return col
private:
	int numRows, numCols;
	// data structure that represents the posts
};
