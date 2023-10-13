/*
#include <iostream>
#include <fstream>


using namespace std;



int calc_highscore() {
    int* arr{ new int[100] };
    int i = 0, highest = -9999;
    ifstream highscore_file;

    highscore_file.open("highscore.txt", ios::in);

    while (highscore_file.eof() == 0) {
        highscore_file >> arr[i];
        if (arr[i] > highest)
            highest = arr[i];
        i++;
    }
    highscore_file.close();
    return highest;
}


int main() {

    int playerscore = 69;
    string playername = "ali";
    int score;
    string name;


    int highscore = calc_highscore();

    const int screenWidth = 800;
    const int screenHeight = 500;
    //if player dead;
    score = playerscore;
    name = playername;

    ofstream scoring_file("score.txt", ios::app);
    ofstream highscore_file("highscore.txt", ios::app);

    scoring_file << "player :" << name;
    scoring_file << "\t\t\t|score:" << score << endl;
    highscore_file << score << endl;

    scoring_file.close();
    highscore_file.close();
    cout << highscore;

    return 0;
} */