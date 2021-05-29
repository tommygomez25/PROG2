#include "ExitDoor.h"
ExitDoor::ExitDoor(int row, int col, char symbol) {
	this->row = row;
	this->col = col;
	this->symbol = symbol;
}
int ExitDoor::getCol() const {
	return col;
}
int ExitDoor::getRow() const {
	return row;
}
char ExitDoor::getSymbol() const {
	return symbol;
}
