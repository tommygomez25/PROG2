#include "Post.h"

Post::Post(int r, int c, char t, bool e) {
	row = r;
	col = c;
	type = t;
	electrified = e;
	if (type == '*')
		electrified = true;
	else if (type == '+')
		electrified = false;
}
int Post::getCol() const {
	return col;
}
int Post::getRow() const {
	return row;
}
char Post::getSymbol() const {
	return type;
}
bool Post::isElectrified() const {
	return electrified;
}
