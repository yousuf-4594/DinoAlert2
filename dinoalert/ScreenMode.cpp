#include "raylib.h"
#include <cmath>
#include<vector>
#include <iostream>
#include <fstream>
#include <string>
#include <omp.h>
#include "screenmode.h"
#include <iostream>
#include <fstream>
#include <string>



using namespace std;



int SCREENMODE::calc_highscore() {
    int* arr{ new int[100] };
    int i = 0, highest = -9999;
    std::ifstream highscore_file;

    highscore_file.open("highscore.txt", std::ios::in);

    while (highscore_file.eof() == 0) {
        highscore_file >> arr[i];
        if (arr[i] > highest)
            highest = arr[i];
        i++;
    }
    highscore_file.close();
    return highest;
}

SCREENMODE::SCREENMODE() {
    screenmode = 0;
    mainmenu = LoadTexture("./Assets/intro.png");
    options = LoadTexture("./Assets/mainmenuoptions.png");
    option_menu = LoadTexture("./Assets/option_menu.png");
    score_menu = LoadTexture("./Assets/scoreboard.png");
    gameover = LoadTexture("./Assets/gameover.png");
    highscore = calc_highscore();
}

void SCREENMODE::displaygame(int playerscore) {


    static char displaygame_name[10] = { '\0' };
    static int displaygame_conter = 0;

    Rectangle input = { 519, 483, 396, 60 };

    DrawTexture(gameover, 0, 0, WHITE);
    DrawText("ENTER YOUR NAME: ", (int)input.x, (int)input.y - 30, 20, ORANGE);

    DrawText(TextFormat("YOUR KILLS: %i", playerscore), (int)input.x, (int)input.y + 90, 15, ORANGE);

    DrawText(TextFormat("HIGHEST KILLS: %i", highscore), (int)input.x, (int)input.y + 120, 15, ORANGE);

    if (CheckCollisionPointRec(GetMousePosition(), input) && displaygame_conter < 10) {
        DrawRectangle(520, 486, 391, 56, WHITE);
        int key = GetCharPressed();

        if ((key >= 32) && (key <= 126)) {
            displaygame_name[displaygame_conter] = (char)key;
            displaygame_conter++;
        }
        if ((IsKeyPressed(KEY_ENTER))) {
            screenmode = 0;

            ofstream scoring_file("score.txt", ios::app);
            ofstream highscore_file("highscore.txt", ios::app);

            scoring_file << "player :" << displaygame_name;
            scoring_file << "\t\t\t|score:" << playerscore << endl;
            highscore_file << playerscore << endl;

            scoring_file.close();
            highscore_file.close();

            memset(&displaygame_name[0], 0, sizeof(displaygame_name));
            displaygame_conter = 0;
        }

        DrawText(displaygame_name, (int)input.x + 5, (int)input.y + 8, 40, DARKBROWN);

    }
    if (CheckCollisionPointRec(GetMousePosition(), input) && displaygame_conter >= 10) {
        DrawRectangle(520, 486, 391, 56, WHITE);
        DrawText(displaygame_name, (int)input.x + 5, (int)input.y + 8, 40, MAROON);
        int key = GetCharPressed();
        if ((IsKeyPressed(KEY_ENTER))) {
            screenmode = 0;

            ofstream scoring_file("score.txt", ios::app);
            ofstream highscore_file("highscore.txt", ios::app);

            scoring_file << "player :" << displaygame_name;
            scoring_file << "\t\t\t|score:" << playerscore << endl;
            highscore_file << playerscore << endl;

            scoring_file.close();
            highscore_file.close();


            memset(&displaygame_name[0], 0, sizeof(displaygame_name));
            displaygame_conter = 0;
        }
    }
    else if ((!IsKeyPressed(KEY_ENTER))) {
        DrawText(displaygame_name, (int)input.x + 5, (int)input.y + 8, 40, BROWN);
        int key = GetCharPressed();
        if ((IsKeyPressed(KEY_ENTER))) {
            screenmode = 0;

            ofstream scoring_file("score.txt", ios::app);
            ofstream highscore_file("highscore.txt", ios::app);

            scoring_file << "player :" << displaygame_name;
            scoring_file << "\t\t\t\t\t\t\t|score:" << playerscore << endl;
            highscore_file << playerscore << endl;

            scoring_file.close();
            highscore_file.close();


            memset(&displaygame_name[0], 0, sizeof(displaygame_name));
            displaygame_conter = 0;
        }
    }
}

void SCREENMODE::displayscoreboardmenu() {
    Rectangle back = { 14,12,56,44 };
    Rectangle back_button_graphics = { 652,0,60,48 };
    DrawTexture(score_menu, 0, 0, WHITE);
    if (CheckCollisionPointRec(GetMousePosition(), back)) {
        DrawTextureRec(options, back_button_graphics, Vector2{ 11.00 , 11.00 }, WHITE);
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            screenmode = 0;
        }
    }
    ifstream in("score.txt");
    string st;
    int gap = 0;
    while (in.eof() == 0) {

        getline(in, st);
        DrawText(st.c_str(), 261, 243 + gap, 10, ORANGE);
        gap += 11;
    }

    in.close();

}

void SCREENMODE::chosenscreenmode() {

    Rectangle start = { 640,269,152,36 };
    Rectangle option = { 607,333,218,41 };
    Rectangle scoreboard = { 553,397,322,38 };

    Rectangle Start = { 1,1,322,166 };
    Rectangle Options = { 328,185,322,166 };
    Rectangle Scoreboard = { 328,1,322,166 };
    Rectangle normal = { 1,185,322,166 };


    DrawTexture(mainmenu, 0, 0, WHITE);
    if (CheckCollisionPointRec(GetMousePosition(), start)) {
        DrawTextureRec(options, Start, Vector2{ 552 , 268 }, WHITE);
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            screenmode = 1;
        }
    }
    else if (CheckCollisionPointRec(GetMousePosition(), option)) {
        DrawTextureRec(options, Options, Vector2{ 552 , 268 }, WHITE);
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            screenmode = 2;
        }
    }
    else if (CheckCollisionPointRec(GetMousePosition(), scoreboard)) {
        DrawTextureRec(options, Scoreboard, Vector2{ 552 , 268 }, WHITE);
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            screenmode = 3;
        }
    }
    else {
        DrawTextureRec(options, normal, Vector2{ 552 , 268 }, WHITE);
    }

}

void SCREENMODE::displayoptionmenu() {
    Rectangle back = { 14,12,56,44 };
    Rectangle back_button_graphics = { 652,0,60,48 };
    DrawTexture(option_menu, 0, 0, WHITE);
    if (CheckCollisionPointRec(GetMousePosition(), back)) {
        DrawTextureRec(options, back_button_graphics, Vector2{ 11.00 , 11.00 }, WHITE);
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            screenmode = 0;
        }
    }
}

void SCREENMODE::choose_screen_type(int score) {

    if (screenmode == 0)
        chosenscreenmode();

    if (screenmode == 2)
        displayoptionmenu();

    if (screenmode == 3)
        displayscoreboardmenu();

    if (screenmode == 4)
        displaygame(score);

}

SCREENMODE::~SCREENMODE() {
    UnloadTexture(mainmenu);
    UnloadTexture(options);
    UnloadTexture(option_menu);
    UnloadTexture(score_menu);
    UnloadTexture(gameover);
}

int SCREENMODE::getscreenmode() {
    return screenmode;
}

void SCREENMODE::setscreenmode(int mode) {
    screenmode = mode;
}
