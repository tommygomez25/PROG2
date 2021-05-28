#include "LeaderBoard.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>


//funcao sort (necessita de #include <algorithm>), compara o tempo que corresponde a substring
bool sortbytime(const string s1, const string s2) {
	return stoi(s1.substr(18, 22)) < stoi(s2.substr(18, 22));
}

LeaderBoard::LeaderBoard(const string& mazenumber) {
	vector<string> vec_players_times;
	string lines;
	string file = "MAZE_" + mazenumber + "_WINNERS.txt";
	ifstream infile(file); // abrir stream para ler o ficheiro 
	
	// obter o vetor de cada linha de player e tempo
	if (infile.is_open()) {
		getline(infile, lines); //"Player          - Time"
		getline(infile, lines); //"----------------------"
		while (getline(infile, lines)) {
			vec_players_times.push_back(lines);
		}
		infile.close();
	}

	sort(vec_players_times.begin(), vec_players_times.end(), sortbytime);

	//records servira para dar out e vetor para organizar (dar sort)
	records = "Player          - Time\n----------------------\n";
	for (int i = 0; unsigned(i) < vec_players_times.size(); i++) {
		records += vec_players_times[i] + "\n";
	}
	this->filename = file;
	this->players_times = vec_players_times;
}

void LeaderBoard::display() {
	//se o vetor players_times estiver vazia (nao ter nenhum jogador), cout de "Empty list"
	if (players_times.empty())
		cout << "Empty list" << endl;
	//se nao, cout de records
	else {
		cout << records;
	}
}

// adicionar uma linha a leaderboard
void LeaderBoard::addLine(string name, int time) {
	string time_s = to_string(time);

	int difName = 15 - name.length();
	int difTime = 4 - time_s.length();

	string newWinner = name + string(difName, ' ') + " - " + string(difTime, ' ') + time_s;

	//adicionar ao vetor que contem os jogadores e as pontuacoes
	players_times.push_back(newWinner);

	sort(players_times.begin(), players_times.end(), sortbytime);

	//atualizar records
	records = "Player          - Time\n----------------------\n";
	for (int i = 0; unsigned(i) < players_times.size(); i++) {
		records += players_times[i] + "\n";
	}

	//atualizar o ficheiro
	ofstream outfile;
	outfile.open(filename);
	outfile << records;
	outfile.close();
}