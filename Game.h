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

	// start playing
	void play();
	// coditions to continue the game play(player not dead and not)
	bool isValid();
	// check if player won (if player collided with a door - return true)
	bool player_wins(); 

	//"clear" screen
	void clear();

	// return score (difference of times)
	int getscore();

private:

	//exit anytime press ctrl z
	void ctrlzexit();

	// player's turn to play
	void tryy();

	// show maze
	void showGameDisplay();

	// player movement
	void player_movement(char action);

	// robot movement
	void robot_movement(vector<Robot>::iterator robot);

	// check if a robot collided with another robot
	bool collide(Robot& robot, Robot& robot2);

	// check if robot collided with an exit
	bool collide(Robot& robot, ExitDoor& door);

	// check if player entered an exit
	bool collide(Player& player, ExitDoor& door);

	// check if robot collided with post
	int collide(Robot& robot, Post& post); 

	// check if robot collided with player
	bool collide(Robot& robot, Player& player);

	// check if human and robot collided
	bool collide(Player& player, Post& post);

	// mark start time
	void starttime();

	// mark end time
	void endtime();

private:

	//in a game there are: 
	//- a maze formed by post(s), robot(s), door(s); 
	//- a player;
	//- a score(time) that comes from difference between finaltime and initialtime; 


	Maze maze;

	//player to control
	Player player;

	//vector with Exitdoor objects
	vector<ExitDoor> doors;

	//vector with Robot objects
	vector<Robot> robots;

	//vector with Post objects
	vector<Post> posts;

	//difference between Final and inicial Time
	int score;

	//time objects
	time_t inicialTime, finalTime;
};