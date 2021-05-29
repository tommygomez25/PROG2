#include "Robot.h"
Robot::Robot(int row, int col, bool alive, int id) {
	this->row = row;
	this->col = col;
	this->alive = alive;
	this->id = id;
}
int Robot::getID() const {
	return id;
}

char Robot::getSymbol() const {
	if (isAlive()) { return 'R'; }
	else {
		return 'r';
	}
}
int Robot::getRow() const {
	return row;
}
int Robot::getCol() const {
	return col;
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
void Robot::setAsDead() {
	this->alive = false;
}