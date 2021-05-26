// game2_.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "Game.h"
#include "LeaderBoard.h"
void menu();
void clear()
{
    cout << "\x1B[2J\x1B[H";
}
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
    while (value != 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Press 0 if you want to go to the menu again. "; cin >> value;
    }
    menu();
}
void menu()
{
    clear();
    int selection;
    cout << "1)Rules \n2)Play \n3)Winners \n0)Exit" << endl;
    cin >> selection;
    while (!cin) {
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
    else if (selection == 2) {
        Game g1;
        string maze_value;
        cout << "What's the maze number you want to play? " << endl; cin >> maze_value;
        while (!cin) {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "Enter a correct input.\nWhat's the maze number you want to play?" << endl; cin >> maze_value;
        }

        g1 = Game(maze_value);
        g1.play();
    }
    else if (selection == 3) {
        LeaderBoard l1;
        string maze_value;
        cout << "What's the maze number? " << endl; cin >> maze_value;
        while (!cin) {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "Enter a correct input.\nWhat's the maze number you want to play?" << endl; cin >> maze_value;
        }
        l1 = LeaderBoard(maze_value);
        l1.display();
    }
}
int main() {
    menu();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
