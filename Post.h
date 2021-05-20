#pragma once
class Post
{
public:
	Post() = default;
	Post(int row, int col, char type,bool electrified);
	int getRow() const;
	int getCol() const;
	char getSymbol() const; // get char representation of Post
	bool isElectrified() const;
	void setNonelectrified();
	//other methods
private:
	int row, col;
	char type;
	bool electrified;
	// '*' - electrified; '+'- non-electrified
	// other attributes (?)
	// could also have a state, like the robot(?)

};

