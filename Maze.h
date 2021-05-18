#pragma once
#include "Post.h";
struct Position
{
	int row, col;
};

class Maze
{
public:
	Maze() = default;
	Maze(int numRows, int numCols);
	bool addPost(const Post &post, const Position &position);
	bool addRobot();
	int getnumRows() const;
	int getnumCols() const;
	// other methods
private:
	int numRows, numCols;
	// data structure that represents the posts
};

