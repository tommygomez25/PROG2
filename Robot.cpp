#include "Robot.h"
Robot::Robot(int row,int col) {
	this->row = row;
	this->col = col;
}
int Robot::getID() const {
	return robotCounter;
}
char Robot::getSymbol() const {
	if (isAlive()) { return 'R'; }
	else { 
		return 'r'; }
}
int Robot::getRow() const {
	return row;
}
int Robot::getCol() const {
	return col;
}
Position Robot::getPosition() const {
	
}
bool Robot::isAlive() const {
	if (alive == true) { return true; }
	else { return false; }
}
void Robot::setRow(int x) {
	this->row = x;
}
void Robot::setCol(int y) {
	this->col = y;
}
void Robot::setPosition(const Position& pos) {
	pos.row = row;
	pos.col = col;
}
void Robot::setAsDead() {
	this->alive = false;
}