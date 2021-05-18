#include "Player.h"
Player::Player(int r, int c, char s){
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
}
bool Player::move(Movement delta) {
	row += delta.dRow;
	col += delta.dCol;
	return true;
}