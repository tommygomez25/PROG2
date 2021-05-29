#pragma once
#include <string>
#include <vector>
#include <utility>

using namespace std;

class LeaderBoard
{
public:
	LeaderBoard() = default;
	LeaderBoard(const string& mazenumber);

	//show leaderboard (records)
	void display(); 

	//add a new winner
	void addLine(string name, int score); 

private:
	//in this class:
	//name of the file is used to access the respective file in order to read/modify 
	//records is used to 
	//the vector players_times contains lines with player's name and respective score (time)
	string filename, records;
	vector<string> players_times;
};

