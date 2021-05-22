#include "Game.h"
#include <fstream>;
#include <string>;
#include <sstream>;
#include <iostream>
#include <conio.h>
using namespace std;
Game::Game(const string& mazenumber) {
	vector<Robot>vecrobot;
	vector<string>vec_maze;
	vector<Post>vecpost;
	int maze_row, maze_col, robot_row, robot_col, post_row, post_col;
	int player_row = 0;
	int player_col = 0;
	int counter = 0;
	char xx;
	Robot robot;
	Post post;
	string first_line, lines;
	ifstream infile("MAZE_" + mazenumber + ".txt"); // abrir stream para ler o ficheiro 
	string file = "MAZE_" + mazenumber;
	if (infile.is_open()) {
		getline(infile, first_line); // ler a primeira linha do ficheiro , que corresponde a rows x cols
	}
	stringstream ss;
	ss << first_line;
	ss >> maze_row >> xx >> maze_col;
	this->maze = Maze(maze_row, maze_col); // inicializar Maze
	if (infile.is_open()) {
		while (getline(infile, lines)) {
			if (lines.size() > 0)
				vec_maze.push_back(lines);
		}
		infile.close();
	}
	// loop para ver onde esta situado o Player e o Robot
	for (int i = 0; unsigned(i) < vec_maze.size(); i++) {
		for (int j = 0; unsigned(j) < vec_maze[i].size(); j++) {
			if (vec_maze[i][j] == 'H') {
				player_col = j;
				player_row = i;
			}
			else if (vec_maze[i][j] == 'R') {
				robot_col = j;
				robot_row = i;
				robot = Robot(robot_row, robot_col, true, counter);
				vecrobot.push_back(robot); // sempre que há um robot, este é adicionado ao vetor de robots
				counter += 1;
			}
			else if (vec_maze[i][j] == 'O') {
				door = ExitDoor(i, j, 'O');
			}
			else if (vec_maze[i][j] == '*' || vec_maze[i][j] == '+') {
				post_col = j;
				post_row = i;
				bool eletrified = true;
				char type = vec_maze[i][j];
				if (type == '+') { eletrified = false; }
				post = Post(post_row, post_col, type, eletrified);
				vecpost.push_back(post);
			}
		}
	}
	this->player = Player(player_row, player_col, 'H'); // inicializar Player
	this->robots = vecrobot; // vetor de robots inicializado
	this->posts = vecpost; // inicializar o vetor de postes
}
void Game::play() {
	showGameDisplay();
	//while !(robos all dead or player collide (player exitdoor)){showgamedisplay();player action}
}
bool Game::isValid() {
	return true;
}
void Game::showGameDisplay() const {
	vector<string> vec_maze;
	string c = " ";
	string s;
	s = string(maze.getnumCols(), ' ');
	/*cout << string(50, '\n');*/
	int x = 0;
	// inicializar um vetor empty 
	for (int i = 0; unsigned(i) < maze.getnumRows(); i++) {
		vec_maze.push_back(s);
	}
	// adicionar ao vetor empty  o P, R, O , * , etc
	for (int i = 0; unsigned(i) < maze.getnumRows(); i++) {
		for (int j = 0; unsigned(j) < maze.getnumCols(); j++)
		{
			for (auto it = begin(robots); it != end(robots); it++) {
				if (it->getRow() == i && it->getCol() == j) { vec_maze[i][j] = it->getSymbol(); }

			}
			for (auto it = begin(posts); it != end(posts); it++) {
				if (it->getRow() == i && it->getCol() == j) {
					vec_maze[i][j] = it->getSymbol();
				}
			}
			if (player.getRow() == i && player.getCol() == j) { vec_maze[i][j] = player.getSymbol(); }
			else if (door.getRow() == i && door.getCol() == j) { vec_maze[i][j] = door.getSymbol(); }
		}
	}

	// cout da maze
	for (int i = 0; unsigned(i) < vec_maze.size(); i++) {
		;
		for (int j = 0; unsigned(j) < vec_maze[i].size(); j++) {

			cout << vec_maze[i][j];
		}
		cout << endl;
	}
}

bool Game::collide(Robot& robot, Post& post) { // check if robot collided with post (and possibly set it as dead)
	if (robot.getCol() == post.getCol() && robot.getRow() == post.getRow()) { robot.setAsDead(); post.setNonelectrified(); return true; }
	else return false;
}
bool Game::collide(Robot& robot, Player& player) {
	if (robot.getCol() == player.getCol() && robot.getRow() == player.getRow()) { robot.setAsDead(); player.setAsDead(); return true; }
	else return false;
}

bool Game::playerAction(unsigned char action) {

}

bool Game::collide(Robot& robot, Robot& robot2) {

}

bool Game::collide(Player& player, ExitDoor& door){
}