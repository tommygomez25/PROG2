#pragma once
class ExitDoor
{
public:
	ExitDoor() = default;
	ExitDoor(int row, int col, char symbol);

	// get int row
	int getRow() const; 

	// get int col
	int getCol() const; 

	//get char 
	char getSymbol() const; 
private:
	int row, col;
	char symbol;
};