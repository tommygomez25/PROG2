#include "Player.h"


Player::Player(int r, int c, char s) {
	row = r; col = c; symbol = s; alive = true;
	if (symbol == 'H')
		alive = true;
	else if (symbol == 'h')
		alive = false;
}
int Player::getRow() const {
	return row;
}
int Player::getCol() const {
	return col;
}
char Player::getSymbol() const {
	return symbol;
}
bool Player::isAlive() const {
	return alive;
}
void Player::setAsDead() {
	alive = false;
	symbol = 'h';
}
void Player::setRow(int r) {
	row = r;
}
void Player::setCol(int c) {
	col = c;
}