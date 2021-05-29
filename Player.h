#pragma once

class Player
{
public:
	Player() = default;
	Player(int row, int col, char symbol);
	// get player row
	int getRow() const; 

	// get player col
	int getCol() const; 

	// get char representation of robot (R if alive, r if dead)
	char getSymbol() const; 

	//return is player is alive (yes -> true / no -> false)
	bool isAlive() const; 

	//modify bool alive = false and modify char symbol = 'h'
	void setAsDead(); 

	//modify player row
	void setRow(int row); 

	//modify player col
	void setCol(int col); 
private:
	int row, col;
	bool alive;
	char symbol;
};

