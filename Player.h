#pragma once

class Player
{
public:
	Player() = default;
	Player(int row, int col, char symbol);
	int getRow() const;
	int getCol() const;
	char getSymbol() const;
	bool isAlive() const;
	void setAsDead();
	void setRow(int row);
	void setCol(int col);
private:
	int row, col;
	bool alive;
	char symbol;
};

