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
	int maze_row, maze_col,robot_row, robot_col,post_row,post_col;
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
				door = ExitDoor(i, j,'O');
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
	this->robots = vecrobot; // vetor de robots inicializado
	this->posts = vecpost; // inicializar o vetor de postes
}
void Game::play() {
    showGameDisplay(); 
}
bool Game::isValid() {
    if (player.isAlive() == false) { return false; }
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
               /* cout << it->getRow() << " and " << it->getCol() << endl;*/
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
    cout << "Action? "; cin >> action;
    if (action == 's' || action == 'S') {
        for (auto robot = begin(robots); robot != end(robots); robot++) {
            robot_movement(robot);
        }
    }
    else {
        player_movement(action, vec_maze);
        for (auto robot = begin(robots); robot != end(robots); robot++) {
            robot_movement(robot);
        }
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
void Game::player_movement(char action,vector<string> vec_maze) {
    switch (action){
    case 'C':
    case 'c':
        if (vec_maze[player.getRow()+1][player.getCol() + 1] != '*' && vec_maze[player.getRow() + 1][player.getCol() + 1] != 'R'&& vec_maze[player.getRow() + 1][player.getCol() + 1]!= 'r' && vec_maze[player.getRow() + 1][player.getCol() + 1] != '+' && vec_maze[player.getRow() + 1][player.getCol() + 1] != 'O') {
            player.setRow(player.getRow() + 1);
            player.setCol(player.getCol() + 1);
        }
        else if ((vec_maze[player.getRow()+1][player.getCol() + 1] == '*') || (vec_maze[player.getRow()][player.getCol() + 1] == 'R')) {
            player.setRow(player.getRow() + 1);
            player.setCol(player.getCol() + 1);
            player.setAsDead();
        }
        else if (vec_maze[player.getRow()+ 1][player.getCol() + 1] == 'r' || vec_maze[player.getRow() +1][player.getCol()+1] == '+') {
            cout << "Invalid action. There is a dead robot over there!" << endl;
            return showGameDisplay();
        }
        else if (vec_maze[player.getRow() + 1][player.getCol() + 1] == 'O') {
            player.setRow(player.getRow() + 1);
            player.setCol(player.getCol() + 1);
            cout << "You won!" << endl;
        }
        break;
    case 'X':
    case 'x':
        if (vec_maze[player.getRow() + 1][player.getCol()] != '*' && vec_maze[player.getRow() + 1][player.getCol()] != 'R' && vec_maze[player.getRow() + 1][player.getCol()] != 'r' && vec_maze[player.getRow() + 1][player.getCol()] != '+' && vec_maze[player.getRow() + 1][player.getCol()] != 'O') {
            player.setRow(player.getRow() +1);
        }
        else if ((vec_maze[player.getRow() + 1][player.getCol()] == '*') || (vec_maze[player.getRow() + 1][player.getCol()] == 'R')) {
            cout << "lol" << endl;
            player.setRow(player.getRow() + 1);
            player.setAsDead();
        }
        else if (vec_maze[player.getRow() + 1][player.getCol()] == 'r' || vec_maze[player.getRow() +1][player.getCol()] == '+') {
            cout << "Invalid action. There is a dead robot over there!" << endl;
            return showGameDisplay();
        }
        else if (vec_maze[player.getRow() + 1][player.getCol() ] == 'O') {
            player.setRow(player.getRow() + 1);
            
            cout << "You won!" << endl;
        }
        break;
    case 'Z':
    case 'z':
        if (vec_maze[player.getRow() + 1][player.getCol()-1] != '*' && vec_maze[player.getRow() + 1][player.getCol() - 1] != 'R'&& vec_maze[player.getRow() + 1][player.getCol() - 1] != 'r'&&vec_maze[player.getRow() + 1][player.getCol() - 1] != '+' && vec_maze[player.getRow() + 1][player.getCol() - 1] != 'O') {
            player.setRow(player.getRow() + 1);
            player.setCol(player.getCol() -1);
        }
        else if ((vec_maze[player.getRow() + 1][player.getCol() - 1] == '*') || (vec_maze[player.getRow() + 1][player.getCol() - 1] == 'R')) {
            player.setRow(player.getRow() + 1);
            player.setCol(player.getCol() - 1);
            player.setAsDead();
        }
        else if (vec_maze[player.getRow() + 1][player.getCol() - 1] == 'r' || vec_maze[player.getRow() + 1][player.getCol()-1] == '+') {
            cout << "Invalid action. There is a dead robot over there!" << endl;
            return showGameDisplay();
        }
        else if (vec_maze[player.getRow()+1][player.getCol() - 1] == 'O') {
            player.setRow(player.getRow() + 1);
            player.setCol(player.getCol() - 1);
            cout << "You won!" << endl;
        }
        break;
    case 'E':
    case 'e':
        if (vec_maze[player.getRow() -1][player.getCol() +1] != '*' && vec_maze[player.getRow() - 1][player.getCol() + 1] != '+' && vec_maze[player.getRow() - 1][player.getCol() + 1] != 'R'&&vec_maze[player.getRow() - 1][player.getCol() + 1] != 'r' && vec_maze[player.getRow() - 1][player.getCol() + 1] != 'O') {
            player.setRow(player.getRow() -1);
            player.setCol(player.getCol() +1);
        }
        else if ((vec_maze[player.getRow() - 1][player.getCol() + 1] == '*') || (vec_maze[player.getRow() - 1][player.getCol() + 1] == 'R')) {
            player.setRow(player.getRow() - 1);
            player.setCol(player.getCol() + 1);
            player.setAsDead();
        }
        else if (vec_maze[player.getRow() - 1][player.getCol() + 1] == 'r' || vec_maze[player.getRow() - 1][player.getCol()+1] == '+') {
            cout << "Invalid action. There is a dead robot over there!" << endl;
            return showGameDisplay();
        }
        else if (vec_maze[player.getRow() - 1][player.getCol() + 1] == 'O') {
            player.setRow(player.getRow() - 1);
            player.setCol(player.getCol() + 1);
            cout << "You won!" << endl;
        }
        break;
    case 'Q':
    case 'q':
        if (vec_maze[player.getRow() - 1][player.getCol() - 1] != '*' && vec_maze[player.getRow() - 1][player.getCol() - 1] != 'r'&& vec_maze[player.getRow() - 1][player.getCol() - 1] != 'R*'&& vec_maze[player.getRow() - 1][player.getCol() - 1] != '+'&& vec_maze[player.getRow() - 1][player.getCol() - 1] != 'O') {
            player.setRow(player.getRow() - 1);
            player.setCol(player.getCol() -1);
        }
        else if ((vec_maze[player.getRow() - 1][player.getCol() - 1] == '*') || (vec_maze[player.getRow() - 1][player.getCol() - 1] == 'R')) {
            player.setRow(player.getRow() - 1);
            player.setCol(player.getCol() - 1);
            player.setAsDead();
        }
        else if (vec_maze[player.getRow() - 1][player.getCol() - 1] == 'r' || vec_maze[player.getRow() - 1][player.getCol()-1] == '+') {
            cout << "Invalid action. There is a dead robot over there!" << endl;
            return showGameDisplay();
        }
        break;
    case 'S':
    case 's':
        //invocar funçao de mexer os robos todos
        showGameDisplay();
    case 'A':
    case 'a':
        if (vec_maze[player.getRow()][player.getCol() - 1] != '*' && vec_maze[player.getRow()][player.getCol() - 1] != 'r'&& vec_maze[player.getRow()][player.getCol() - 1] != 'R'&& vec_maze[player.getRow()][player.getCol() - 1] != '+'&&vec_maze[player.getRow()][player.getCol() - 1] != 'O') {
            player.setCol(player.getCol() - 1);
        }
        else if ((vec_maze[player.getRow()][player.getCol() - 1] == '*') || (vec_maze[player.getRow()][player.getCol() - 1] == 'R')) {
            player.setCol(player.getCol() - 1);
            player.setAsDead();
        }
        else if (vec_maze[player.getRow()][player.getCol() - 1] == 'r' || vec_maze[player.getRow() ][player.getCol()-1] == '+') {
            cout << "Invalid action. There is a dead robot over there!" << endl;
            return showGameDisplay();
        }
        break;
    case 'D':
    case 'd':
        if (vec_maze[player.getRow()][player.getCol() + 1] != '*' && vec_maze[player.getRow()][player.getCol() + 1] != 'r'&& vec_maze[player.getRow()][player.getCol() + 1] != 'R'&& vec_maze[player.getRow()][player.getCol() + 1] != '+'&& vec_maze[player.getRow()][player.getCol() + 1] != 'O') {
            player.setCol(player.getCol() +1);
        }

        else if ((vec_maze[player.getRow()][player.getCol() + 1] =='*')|| (vec_maze[player.getRow()][player.getCol() + 1] == 'R')) {
            player.setCol(player.getCol() +1);
            player.setAsDead();
        }
        else if (vec_maze[player.getRow()][player.getCol() + 1] == 'r' || vec_maze[player.getRow() ][player.getCol()+1] == '+') {
            cout << "Invalid action. There is a dead robot over there!" << endl;
            return showGameDisplay();
        }
        break;
    case 'W':
    case 'w':
        if (vec_maze[player.getRow()-1][player.getCol() ] != '*' && vec_maze[player.getRow() - 1][player.getCol()] != 'R'&& vec_maze[player.getRow() - 1][player.getCol()] != 'r'&& vec_maze[player.getRow() - 1][player.getCol()] != '+'&& vec_maze[player.getRow() - 1][player.getCol()] != 'O') {
            player.setRow(player.getRow() - 1);
        }
        else if ((vec_maze[player.getRow() - 1][player.getCol()] == '*') || (vec_maze[player.getRow() - 1][player.getCol()] == 'R')) {
            player.setRow(player.getRow() - 1);
            player.setAsDead();
        }
        else if (vec_maze[player.getRow() - 1][player.getCol()] == 'r'|| vec_maze[player.getRow() - 1][player.getCol()] == '+') {
            cout << "Invalid action. There is a dead robot over there!" << endl;
            return showGameDisplay();
        }
        break;

    default:
        cout << "Incorrect action!" << endl;
        return showGameDisplay();
    }
}
void Game::robot_movement(vector<Robot>::iterator robot) {
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
                    cout << "new robot row = " << new_robot_row << endl;
                };
                if ((abs(player.getCol() - (robot->getCol() + j))) < min_y && min_y != abs(player.getCol() - (robot->getCol() + j))) {
                    min_y = abs(player.getCol() - (robot->getCol() + j));
                    new_robot_col = robot->getCol() + j;
                    
                };
            }
        }
        robot->setRow(new_robot_row);
        robot->setCol(new_robot_col);
}
void Game::clear() {
    cout << "\x1B[2J\x1B[H";
}
bool Game::collide(Robot& robot, Robot& robot2) {

}

bool Game::collide(Player& player, ExitDoor& door) {
}