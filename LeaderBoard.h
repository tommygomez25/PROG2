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
	void display();
	void addLine(string name, int score);
private:
	string filename, records;
	vector<string> players_times;
};

