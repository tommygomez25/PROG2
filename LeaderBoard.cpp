#include "LeaderBoard.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

bool sortbytime(const string s1, const string s2) {
	return stoi(s1.substr(18, 22)) < stoi(s2.substr(18, 22));
}
LeaderBoard::LeaderBoard(const string& mazenumber) {
	vector<string> vec_players_times;
	string lines;

	ifstream infile("MAZE_" + mazenumber + "_WINNERS.txt"); // abrir stream para ler o ficheiro 
	string file = "MAZE_" + mazenumber + "_WINNERS.txt";


	if (infile.is_open()) {
		getline(infile, lines); //"Player          - Time"
		getline(infile, lines); //"----------------------"
		while (getline(infile, lines)) {
			vec_players_times.push_back(lines);
		}
		infile.close();
	}
	else {
		ofstream outfile;
		outfile.open("..\\MAZE_" + mazenumber + "_WINNERS.txt");
		outfile << "Player          - Time" << endl << "----------------------" << endl;
		outfile.close();
	}

	records = "Player          - Time\n----------------------\n";
	for (int i = 0; unsigned(i) < vec_players_times.size(); i++) {
		records += vec_players_times[i] + "\n";
	}
	this->filename = file;
	this->players_times = vec_players_times;
}

void LeaderBoard::display() {
	cout << records;
}

void LeaderBoard::addLine(string name, int time) {
	string time_s = to_string(time);

	int difName = 15 - name.length();
	int difTime = 4 - time_s.length();

	string newWinner = name + string(difName, ' ') + " - " + string(difTime, ' ') + time_s;

	players_times.push_back(newWinner);

	sort(players_times.begin(), players_times.end(), sortbytime);

	records = "Player          - Time\n----------------------\n";
	for (int i = 0; unsigned(i) < players_times.size(); i++) {
		records += players_times[i] + "\n";
	}

	ofstream outfile;
	outfile.open(filename);
	outfile << records;
	outfile.close();
}