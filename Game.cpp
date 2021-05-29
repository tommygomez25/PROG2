#include "Game.h"
#include <fstream>;
#include <string>;
#include <sstream>;
#include <iostream>
#include <time.h>

using namespace std;
Game::Game(const string& mazenumber) {
	vector<Robot>vecrobot;
	vector<string>vec_maze;
	vector<Post>vecpost;
	vector<ExitDoor>vecdoor;
	int maze_row, maze_col, robot_row, robot_col, post_row, post_col, door_row, door_col;
	int player_row = 0;
	int player_col = 0;
	int rbtcounter = 0;
	char xx;
	Robot robot;
	Post post;
	ExitDoor door;
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
				robot = Robot(robot_row, robot_col, true, rbtcounter);
				vecrobot.push_back(robot); // sempre que há um robot, este é adicionado ao vetor de robots
				rbtcounter += 1;
			}
			else if (vec_maze[i][j] == 'O') {
				door_col = j;
				door_row = i;
				door = ExitDoor(door_row, door_col, 'O');
				vecdoor.push_back(door); // sempre que há uma porta, este é adicionado ao vetor de portas
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
	player = Player(player_row, player_col, 'H'); // inicializar Player
	this->doors = vecdoor; // vetor de doors inicializado
	this->robots = vecrobot; // vetor de robots inicializado
	this->posts = vecpost; // inicializar o vetor de postes
	this->score = 0;
	this->inicialTime = 0;
	this->finalTime = 0;
}


void Game::play() {
	// marca o tempo inicial
	starttime(); 
	// enquanto o jogador esteja vivo e que nao chegou a uma das portas
	while (isValid()) { 
		// mostra a maze
		showGameDisplay(); 
		// pergunta pela acao
		tryy(); 
	}
	// se chegou a uma das portas
	if (player_wins()) { 
		// marca o tempo final e atualiza a pontuacao
		endtime(); 
		showGameDisplay();
		cout << "GG, you won! Your score was: " << score << endl;
	}
}

// verifica se o jogo acabou ou nao
bool Game::isValid() { 

	// se o jogador estiver morto ou tocado numa das portas, acabou (false)
	if (player.isAlive() == false || player_wins() == true) { return false; }

	// se nao (jogador vivo e que nao chegou a uma das portas), continua (true)
	else return true;
}


void Game::showGameDisplay() {
	clear();
	vector<string> vec_maze;
	string c = " ";
	string s;
	s = string(maze.getnumCols(), ' '); //serve para depois criar um vetor com empty spaces
	int x = 0;
	unsigned char action;

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
			for (auto it = begin(doors); it != end(doors); it++) {
				if (it->getRow() == i && it->getCol() == j) {
					vec_maze[i][j] = it->getSymbol();
				}
			}
			if (player.getRow() == i && player.getCol() == j) { vec_maze[i][j] = player.getSymbol(); }
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

void Game::robot_movement(vector<Robot>::iterator robot) {
	int pre_robot_row = robot->getRow();
	int pre_robot_col = robot->getCol();
	int new_robot_row = robot->getRow();
	int new_robot_col = robot->getCol();
	int min_x = abs(player.getRow() - robot->getRow());
	int min_y = abs(player.getCol() - robot->getCol());
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			// if the distance between them is minor , store the new coordenate of the enemy
			if ((abs(player.getRow() - (robot->getRow() + i))) < min_x && min_x != abs(player.getRow() - (robot->getRow() + i))) {
				min_x = abs(player.getRow() - (robot->getRow() + i));
				new_robot_row = robot->getRow() + i;
			};
			if ((abs(player.getCol() - (robot->getCol() + j))) < min_y && min_y != abs(player.getCol() - (robot->getCol() + j))) {
				min_y = abs(player.getCol() - (robot->getCol() + j));
				new_robot_col = robot->getCol() + j;
			};
		}
	}
	robot->setRow(new_robot_row);
	robot->setCol(new_robot_col);
	for (auto door = begin(doors); door != end(doors); door++) {
		if (collide(*robot, *door)) {
		robot->setRow(pre_robot_row);
		robot->setCol(pre_robot_col);
		}
	}

	// verifica a colisao entre robot e player
	if (collide(*robot, player)) { 
		player.setAsDead();
		robot->setAsDead();
		robot->setRow(pre_robot_row);
		robot->setCol(pre_robot_col);
		showGameDisplay();
		cout << "GG, you collided against a robot" << endl;
	}
	
	// verifica a colisao entre robot e cada post
	for (auto post = begin(posts); post != end(posts); post++) { 
		if (collide(*robot, *post) == 2) {
			robot->setRow(pre_robot_row);
			robot->setCol(pre_robot_col);
		}
	}

	// verifica a colisao entre robots
	for (auto robot2 = begin(robots) + 1; robot2 != end(robots); robot2++) {
		if (robot->getID() != robot2->getID() && collide(*robot, *robot2)){
			robot->setRow(pre_robot_row);
			robot->setCol(pre_robot_col);
		}
	}
}

void Game::clear() {
	cout << "\x1B[2J\x1B[H";
}

//colisao entre robot e post
int Game::collide(Robot& robot, Post& post) {
	if (robot.getCol() == post.getCol() && robot.getRow() == post.getRow() && post.isElectrified() == false) {
		robot.setAsDead();
		post = Post(post.getRow(), post.getCol(), 'r', false);
		return 1;
	}
	else if (robot.getCol() == post.getCol() && robot.getRow() == post.getRow() && post.isElectrified() == true) {
		robot.setAsDead();
		post = Post(post.getRow(), post.getCol(), '+', false);
		return 2;
	}
	else return 0;
}

//colisao entre robot e player
bool Game::collide(Robot& robot, Player& player) {
	if (robot.getCol() == player.getCol() && robot.getRow() == player.getRow() && robot.getSymbol() == 'R') {
		return true;
	}
	else if (robot.getCol() == player.getCol() && robot.getRow() == player.getRow() && robot.getSymbol() == 'r') {
		return true;
	}
	else return false;
}


//colisao entre robots
bool Game::collide(Robot& robot, Robot& robot2) {
	if (robot.getRow() == robot2.getRow() && robot.getCol() == robot2.getCol()) {
		robot.setAsDead();
		robot2.setAsDead();
		return true;
	}
	else return false;
}

//colisao entre player e door
bool Game::collide(Player& player, ExitDoor& door) {
	if (player.getRow() == door.getRow() && player.getCol() == door.getCol()) {
		door = ExitDoor(door.getRow(), door.getCol(), 'H');
		return true; // wins
	}
	else return false;
}

// colisao entre player e post
bool Game::collide(Player& player, Post& post) {
	if (player.getRow() == post.getRow() && player.getCol() == post.getCol() && post.getSymbol() == '*') {
		player.setAsDead();
		return true;
	}
	else if (player.getRow() == post.getRow() && player.getCol() == post.getCol() && post.getSymbol() == '+') {
		return true;
	}
	return false;
}

//movimentos 
void Game::player_movement(char action) {
	switch (action) {
	case'C':
	case'c':
		player.setRow(player.getRow() + 1);
		player.setCol(player.getCol() + 1);
		for (auto post = begin(posts); post != end(posts); post++) {
			while (collide(player, *post) && post->getSymbol() == '+') {
				player.setRow(player.getRow() - 1);
				player.setCol(player.getCol() - 1);
				cout << "Invalid move. There is a non eletrified post over there!\nAction ? "; cin >> action;
				player_movement(action);
			}
			if (collide(player, *post)) {
				player.setRow(player.getRow() - 1);
				player.setCol(player.getCol() - 1);
				showGameDisplay();
				cout << "GG, you collided against a post" << endl;
			}
		}
		for (auto robot = begin(robots); robot != end(robots); robot++) {
			while (collide(*robot, player) && robot->getSymbol() == 'r') {
				player.setRow(player.getRow() - 1);
				player.setCol(player.getCol() - 1);
				cout << "Invalid move. There is a dead robot over there!\nAction? "; cin >> action;
				player_movement(action);
			}
			if (collide(*robot, player) && robot->getSymbol() == 'R') {
				robot->setAsDead();
				player.setAsDead();
				player.setRow(player.getRow() - 1);
				player.setCol(player.getCol() - 1);
				showGameDisplay();
				cout << "GG, you collided against a robot";
			}
		}
		break;
	case'X':
	case'x':

		player.setRow(player.getRow() + 1);
		for (auto post = begin(posts); post != end(posts); post++) {
			while (collide(player, *post) && post->getSymbol() == '+') {
				player.setRow(player.getRow() - 1);
				cout << "Invalid move. There is a non eletrified post over there!\nAction ? "; cin >> action;
				player_movement(action);
			}
			if (collide(player, *post)) {
				player.setRow(player.getRow() - 1);
				showGameDisplay();
				cout << "GG, you collided against a post" << endl;
			}
		}
		for (auto robot = begin(robots); robot != end(robots); robot++) {
			while (collide(*robot, player) && robot->getSymbol() == 'r') {
				player.setRow(player.getRow() - 1);
				cout << "Invalid move. There is a dead robot over there!\nAction? "; cin >> action;
				player_movement(action);
			}
			if (collide(*robot, player) && robot->getSymbol() == 'R') {
				robot->setAsDead();
				player.setAsDead();
				player.setRow(player.getRow() - 1);
				showGameDisplay();
				cout << "GG, you collided against a robot";
			}
		}
		break;

	case'Z':
	case'z':

		player.setRow(player.getRow() + 1);
		player.setCol(player.getCol() - 1);
		for (auto post = begin(posts); post != end(posts); post++) {
			while (collide(player, *post) && post->getSymbol() == '+') {
				player.setRow(player.getRow() - 1);
				player.setCol(player.getCol() + 1);
				cout << "Invalid move. There is a non eletrified post over there!\nAction ? "; cin >> action;
				player_movement(action);
			}
			if (collide(player, *post)) {
				player.setRow(player.getRow() - 1);
				player.setCol(player.getCol() + 1);
				showGameDisplay();
				cout << "GG, you collided against a post" << endl;
			}
		}
		for (auto robot = begin(robots); robot != end(robots); robot++) {
			while (collide(*robot, player) && robot->getSymbol() == 'r') {
				player.setRow(player.getRow() - 1);
				player.setCol(player.getCol() + 1);
				cout << "Invalid move. There is a dead robot over there!\nAction? "; cin >> action;
				player_movement(action);
			}
			if (collide(*robot, player) && robot->getSymbol() == 'R') {
				robot->setAsDead();
				player.setAsDead();
				player.setRow(player.getRow() - 1);
				player.setCol(player.getCol() + 1);
				showGameDisplay();
				cout << "GG, you collided against a robot";
			}
		}
		break;

	case'e':
	case'E':

		player.setRow(player.getRow() - 1);
		player.setCol(player.getCol() + 1);
		for (auto post = begin(posts); post != end(posts); post++) {
			while (collide(player, *post) && post->getSymbol() == '+') {
				player.setRow(player.getRow() + 1);
				player.setCol(player.getCol() - 1);
				cout << "Invalid move. There is a non eletrified post over there!\nAction ? "; cin >> action;
				player_movement(action);
			}
			if (collide(player, *post)) {
				player.setRow(player.getRow() + 1);
				player.setCol(player.getCol() - 1);
				showGameDisplay();
				cout << "GG, you collided against a post" << endl;
			}
		}
		for (auto robot = begin(robots); robot != end(robots); robot++) {
			while (collide(*robot, player) && robot->getSymbol() == 'r') {
				player.setRow(player.getRow() + 1);
				player.setCol(player.getCol() - 1);
				cout << "Invalid move. There is a dead robot over there!\nAction? "; cin >> action;
				player_movement(action);
			}
			if (collide(*robot, player) && robot->getSymbol() == 'R') {
				robot->setAsDead();
				player.setAsDead();
				player.setRow(player.getRow() + 1);
				player.setCol(player.getCol() - 1);
				showGameDisplay();
				cout << "GG, you collided against a robot";
			}
		}
		break;

	case'Q':
	case'q':

		player.setRow(player.getRow() - 1);
		player.setCol(player.getCol() - 1);
		for (auto post = begin(posts); post != end(posts); post++) {
			while (collide(player, *post) && post->getSymbol() == '+') {
				player.setRow(player.getRow() + 1);
				player.setCol(player.getCol() + 1);
				cout << "Invalid move. There is a non eletrified post over there!\nAction ? "; cin >> action;
				player_movement(action);
			}
			if (collide(player, *post)) {
				player.setRow(player.getRow() + 1);
				player.setCol(player.getCol() + 1);
				showGameDisplay();
				cout << "GG, you collided against a post" << endl;
			}
		}
		for (auto robot = begin(robots); robot != end(robots); robot++) {
			while (collide(*robot, player) && robot->getSymbol() == 'r') {
				player.setRow(player.getRow() + 1);
				player.setCol(player.getCol() + 1);
				cout << "Invalid move. There is a dead robot over there!\nAction? "; cin >> action;
				player_movement(action);
			}
			if (collide(*robot, player) && robot->getSymbol() == 'R') {
				robot->setAsDead();
				player.setAsDead();
				player.setRow(player.getRow() + 1);
				player.setCol(player.getCol() + 1);
				showGameDisplay();
				cout << "GG, you collided against a robot";
			}
		}

		break;

	case 'S':
	case's':
		cout << player.getRow();
		cout << player.getCol();
		break;
	case 'A':
	case'a':

		player.setCol(player.getCol() - 1);
		for (auto post = begin(posts); post != end(posts); post++) {
			while (collide(player, *post) && post->getSymbol() == '+') {
				player.setCol(player.getCol() + 1);
				cout << "Invalid move. There is a non eletrified post over there!\nAction ? "; cin >> action;
				player_movement(action);
			}
			if (collide(player, *post)) {
				player.setCol(player.getCol() + 1);
				showGameDisplay();
				cout << "GG, you collided against a post" << endl;
			}
		}
		for (auto robot = begin(robots); robot != end(robots); robot++) {
			while (collide(*robot, player) && robot->getSymbol() == 'r') {
				player.setCol(player.getCol() + 1);
				cout << "Invalid move. There is a dead robot over there!\nAction? "; cin >> action;
				player_movement(action);
			}
			if (collide(*robot, player) && robot->getSymbol() == 'R') {
				robot->setAsDead();
				player.setAsDead();
				player.setCol(player.getCol() + 1);
				showGameDisplay();
				cout << "GG, you collided against a robot";
			}
		}
		break;

	case'D':
	case'd':

		player.setCol(player.getCol() + 1);
		for (auto post = begin(posts); post != end(posts); post++) {
			while (collide(player, *post) && post->getSymbol() == '+') {
				player.setCol(player.getCol() - 1);
				cout << "Invalid move. There is a non eletrified post over there!\nAction ? "; cin >> action;
				player_movement(action);
			}
			if (collide(player, *post)) {
				player.setCol(player.getCol() - 1);
				showGameDisplay();
				cout << "GG, you collided against a post" << endl;
			}
		}
		for (auto robot = begin(robots); robot != end(robots); robot++) {
			while (collide(*robot, player) && robot->getSymbol() == 'r') {
				player.setCol(player.getCol() - 1);
				cout << "Invalid move. There is a dead robot over there!\nAction? "; cin >> action;
				player_movement(action);
			}
			if (collide(*robot, player) && robot->getSymbol() == 'R') {
				robot->setAsDead();
				player.setAsDead();
				player.setCol(player.getCol() - 1);
				showGameDisplay();
				cout << "GG, you collided against a robot";
			}
		}
		break;

	case'W':
	case'w':

		player.setRow(player.getRow() - 1);
		for (auto post = begin(posts); post != end(posts); post++) {
			while (collide(player, *post) && post->getSymbol() == '+') {
				player.setRow(player.getRow() + 1);
				cout << "Invalid move. There is a non eletrified post over there!\nAction ? "; cin >> action;
				player_movement(action);
			}
			if (collide(player, *post)) {
				player.setRow(player.getRow() + 1);
				showGameDisplay();
				cout << "GG, you collided against a post" << endl;
			}
		}
		for (auto robot = begin(robots); robot != end(robots); robot++) {
			while (collide(*robot, player) && robot->getSymbol() == 'r') {
				player.setRow(player.getRow() + 1);
				cout << "Invalid move. There is a dead robot over there!\nAction? "; cin >> action;
				player_movement(action);
			}
			if (collide(*robot, player) && robot->getSymbol() == 'R') {
				robot->setAsDead();
				player.setAsDead();
				player.setRow(player.getRow() + 1);
				showGameDisplay();
				cout << "GG, you collided against a robot";
			}
		}
		break;
	default:
		ctrlzexit();
		cout << "Incorrect action!" << endl;
		cout << "Action? "; cin >> action;
		player_movement(action);
	}
}

//player's and robots' actions
void Game::tryy() {
	unsigned char action;
	cout << "Action? "; cin >> action;
	player_movement(action);
	for (auto robot = begin(robots); robot != end(robots); robot++) {
		if (robot->getSymbol() == 'R') // o robot só se move se ainda nao estiver morto 
			robot_movement(robot);
	}
}
// check if player won
bool Game::player_wins() {
	for (auto door = begin(doors); door != end(doors); door++) {
		if (collide(player, *door)) return true;
	}
	return false;
}

int Game::getscore() {
	return score;
}

void Game::starttime() {
	time(&inicialTime);
}

void Game::endtime() {
	time(&finalTime);
	int score = difftime(finalTime, inicialTime);
	this->score = score;
}

void Game::ctrlzexit() {
	if (cin.eof())
	{
		cout << "bye ...";
		exit(0);
	}
}

// colisao entre robot e door
bool Game::collide(Robot& robot, ExitDoor& door) {
	if (robot.getCol() == door.getCol() && robot.getRow() == door.getRow()) {
		return true;
	}
	else return false;
}