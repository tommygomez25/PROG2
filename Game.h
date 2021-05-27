#pragma once

#include "Player.h";
#include "Maze.h";
#include "Post.h";
#include "Robot.h";
#include "ExitDoor.h"
#include <vector>;
#include <string>;

using namespace std;

class Game
{
public:
	Game() = default;
	Game(const string& mazenumber);
	// This constructor should initialize the Maze, the vector of Robots, and the Player,
	// using the chars read from the file
	void play();
	bool isValid();
	bool player_wins();
	void clear();
	int getscore();

private:
	void ctrlzexit();
	void tryy();
	void showGameDisplay();
	void player_movement(char action);
	void robot_movement(vector<Robot>::iterator robot);
	bool collide(Robot& robot, Robot& robot2);
	bool collide(Player& player, ExitDoor& door);
	int collide(Robot& robot, Post& post); // check if robot collided with post (and possibly set it as dead)
	bool collide(Robot& robot, Player& player);
	bool collide(Player& player, Post& post);// check if human and robot collided (and possibly set human as dead)
	void starttime();
	void endtime();
	// other methods, for example:
	// to check if player is trying to move to a valid place
	// to apply a valid play and check collisions
	// to check if two robots collide (and possibly set them as dead)
	// etc.
private:
	Maze maze;
	Player player;
	ExitDoor door;
	vector<Robot> robots;
	vector<Post> posts;
	int score;
	time_t inicialTime, finalTime;
	//other attributes

};