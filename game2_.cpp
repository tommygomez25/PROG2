// game2_.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "Game.h"
#include "LeaderBoard.h"

using namespace std;
void menu();

// ctrl-z para sair do jogo quando quiser
void ctrlzexit() {
    if (cin.eof())
    {
        cout << "bye ...";
        exit(0);
    }
}
//selecao: voltar/sair
void playagain() {
    int selection;
    cout << "1)Go back \n0)Exit" << endl; cin >> selection;
    while (!cin || selection < 0 || selection > 1) {
        ctrlzexit();
        cin.clear();
        cin.ignore(9999, '\n');
        cout << "Enter a correct input.\n1)Go back \n0)Exit" << endl; cin >> selection;
    }
    if (selection == 1) {
        menu();
    }
    else if (selection == 0) {
        exit(0);

    }
}

//recebe o nome, adiciona a leaderboard e mostra a leaderboard
void save(Game g1, LeaderBoard l1) {
    string name;
    cout << "Enter your name: "; cin.ignore(); getline(cin, name);
    while (name.size()>15){
        ctrlzexit();
        cin.clear();
        cout << "Enter a correct input.\nEnter your name: "; getline(cin, name);
    }
    l1.addLine(name, g1.getscore());
    l1.display();
}

//selecao: guardar/voltar/sair
void saveselect(Game g1, LeaderBoard l1) {
    int saveselect;
    cout << "1)Save score \n2)Go back \n0)Exit" << endl; cin >> saveselect;
    while (!cin || saveselect < 0 || saveselect > 2) {
        ctrlzexit();
        cin.clear();
        cin.ignore(9999, '\n');
        cout << "Enter a correct input.\n1)Save score \n2)Go back \n0)Exit" << endl; cin >> saveselect;
    }
    if (saveselect == 1) {
        save(g1, l1);
        playagain();
    }
    else if (saveselect == 2)
        menu();
    else if (saveselect == 0)
        exit(0);
}

// \x1b[2J is the code for clearing the screen and set cursor to home
// \x1b[H is the code for returning the cursor to the home position
void clear()
{
    cout << "\x1B[2J\x1B[H";
}

// funcao rules, le RULES.txt, da output do conteudo e voltar a menu se pressionar 0
void rules() {
    int value;
    clear();
    vector<string> vec;
    int i = 0;
    string lines;
    ifstream infile("RULES.txt"); 
    while (getline(infile, lines)) {
        if (lines.size() > 0)
            vec.push_back(lines);
    }
    infile.close();
    for (string& line : vec)
        cout << line << endl;
    cout << "Press 0 if you want to go to the menu again. "; cin >> value;
    while (!cin || value != 0) {
        ctrlzexit();
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Press 0 if you want to go to the menu again. "; cin >> value;
    }
    menu();
}

// vefica se o ficheiro MAZE_XX.txt com o respetivo numero existe ou nao
bool verifyfile(string maze_value) {
    ifstream infile("MAZE_" + maze_value + ".txt"); // abrir stream para ler o ficheiro 
    if (infile) 
        return true;
    return false;
}

// verifica se o ficheiro MAZE_XX_WINNERS.txt com o respetivo numero existe ou nao
bool verifysavefile(string maze_value) {
    ifstream infile("MAZE_" + maze_value + "_WINNERS.txt"); // abrir stream para ler o ficheiro 
    if (infile)
        return true;
    return false;
}

// menu, selecao: Rules/Play/Winners/Exit
void menu()
{
    clear();

    int selection;
    cout << "1)Rules \n2)Play \n3)Winners \n0)Exit" << endl;
    cin >> selection;
    while (!cin || selection < 0 || selection > 3) {
        ctrlzexit();
        cin.clear();
        cin.ignore(99999, '\n');
        cout << "1)Rules \n2)Play \n3)Winners \n0)Exit" << endl;
        cin >> selection;
    }
    if (selection == 0) {
        exit(0);
    }
    else if (selection == 1) {
        rules();
    }
    else if (selection == 2) { //inicializa um objeto game, leaderboard e maze_value
        Game g1;
        LeaderBoard l1;
        string maze_value;
        cout << "What's the maze number you want to play? " << endl; cin >> maze_value;
        while (!cin) {
            ctrlzexit();
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "Enter a correct input.\nWhat's the maze number you want to play?" << endl; cin >> maze_value;
        }

        if (verifyfile(maze_value)){ //verifica se existe o ficheiro MAZE_XX.txt, caso exista, constroi o jogo e leaderboard do jogo e jogo
            g1 = Game(maze_value);
            l1 = LeaderBoard(maze_value);
            g1.play();
            if (g1.player_wins()) { // se ganhar, pergunta se quer guardar a pontuacao
                saveselect(g1, l1);
            }
            else
                playagain(); // se morrer, pergunta se quer voltar a menu
        }
        else { // se nao existe o ficheiro MAZE_XX.txt da output
            cout << "File doesn't exist" << endl;
            playagain();
        }
    }
    else if (selection == 3) { // inicializa um objeto leaderboard
        LeaderBoard l1;
        string maze_value;
        cout << "What's the maze number? " << endl; cin >> maze_value;
        while (!cin || maze_value.size() != 2) {
            ctrlzexit();
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "Enter a correct input.\nWhat's the maze number you want to play?" << endl; cin >> maze_value;
        }

        if (verifysavefile(maze_value)) { // verifica se exist o ficheiro MAZE_XX_WINNERS.txt, caso exista, controi a leaderboard e mostra o conteudo
            l1 = LeaderBoard(maze_value);
            l1.display();
            playagain();
        }
        else{ // se nao existe o ficheiro MAZE_XX_WINNERS.txt, da output
            cout << "File doesn't exist" << endl;
            playagain();
        }

    }
}
int main() {
    menu();
    return 0;
}