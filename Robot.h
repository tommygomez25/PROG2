#pragma once
///////////////////////////////////////////////////////////////////////////////
#include "Maze.h"
class Robot
{
public:
	Robot() = default;
	Robot(int row, int col, bool alive, int id);
	int getID() const;

	// get char representation of robot (R if alive, r if dead)
	char getSymbol() const; 

	//get row
	int getRow() const;

	//get col
	int getCol() const;

	//tell if robot is alive (yes -> true / no -> false)
	bool isAlive() const;

	//modify robot's row
	void setRow(int x);

	//modify robot's col
	void setCol(int y);

	//modify robot's health (dead)
	void setAsDead();
private:
	static int robotCounter; //used to attribute automatically the id to the robots
	int id;
	int row, col;
	bool alive;
	// other attributes (?)
};

