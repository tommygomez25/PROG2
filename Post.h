#pragma once
class Post
{
public:
	Post() = default;
	Post(int row, int col, char type, bool electrified);

	//get post row
	int getRow() const; 

	//get post col
	int getCol() const; 

	// get char representation of Post
	char getSymbol() const; 

	// return if post is electrified (yes -> true / no -> false)
	bool isElectrified() const;
private:
	int row, col;
	char type;
	bool electrified;


};