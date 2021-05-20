#include "Game.h"
#include <fstream>;
#include <string>;
#include <sstream>;
#include <iostream>
#include <conio.h>
using namespace std;
Game::Game(const string& mazenumber) {
	vector<Robot>vecrobot;
	vector<string>vec;
	int maze_row, maze_col, player_col, player_row, robot_row, robot_col;
	int counter = 0;
	char xx;
	Robot robot;

	string first_line, lines;
	ifstream infile("MAZE_" + mazenumber + ".txt"); // abrir stream para ler o ficheiro 
	string file = "MAZE_" + mazenumber;
	if (infile.is_open()) {
		getline(infile, first_line); // ler a primeira linha do ficheiro , que corresponde a rows x cols
	}
	stringstream ss;
	ss << first_line;
	ss >> maze_row >> xx >> maze_col;
	maze = Maze(maze_row, maze_col); // inicializar Maze
	if (infile.is_open()) {
		while (getline(infile, lines)) {
			if (lines.size() > 0)
				vec.push_back(lines);
		}
		infile.close();
	}
	// loop para ver onde est?situado o Player
	for (int i = 0; unsigned(i) < vec.size(); i++) {
		for (int j = 0; unsigned(j) < vec[i].size(); j++) {
			if (vec[i][j] == 'H') {
				player_col = j;
				player_row = i;
			}
		}
	}
	player = Player(player_row, player_col, 'H'); // inicializar Player
	//loop para ver onde estão os robots
	for (int i = 0; unsigned(i) < vec.size(); i++) {
		for (int j = 0; unsigned(j) < vec[i].size(); j++) {
			if (vec[i][j] == 'R') {
				robot_col = j;
				robot_row = i;
				robot = Robot(robot_row, robot_col, true, counter);
				vecrobot.push_back(robot); // sempre que há um robot, este é adicionado ao vetor de robots
				counter += 1;
			}
		}
	}
	robots = vecrobot; // vetor de robots ?inicializado
}
bool Game::play() {
	while (player.isAlive()) {
	
	}
	return true;
}
bool Game::isValid() {
	return true;
}
void Game::showGameDisplay() const {
	cout << string(50, '\n');
	//showmaze
}
bool Game::collide(Robot& robot, Post& post) { // check if robot collided with post (and possibly set it as dead)
	if (robot.getCol() == post.getCol() && robot.getRow() == post.getRow()) { robot.setAsDead(); post.setNonelectrified(); return true; }
	else return false;
}
bool Game::collide(Robot& robot, Player& player) {
	if (robot.getCol() == player.getCol() && robot.getRow() == player.getRow()) { robot.setAsDead(); player.setAsDead(); return true; }
	else return false;
}