#pragma once
class ExitDoor
{
public:
	ExitDoor() = default;
	ExitDoor(int row, int col, char symbol);
	int getRow() const;
	int getCol() const;
	char getSymbol() const;
private:
	int row, col;
	char symbol;
};