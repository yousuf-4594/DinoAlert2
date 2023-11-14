#pragma once

#include "raylib.h"

class SCREENMODE {
    int screenmode;
    Texture2D mainmenu;
    Texture2D options;
    Texture2D option_menu;
    Texture2D score_menu;
    Texture2D gameover;
    int highscore;

    int calc_highscore();

public:
    SCREENMODE();
    void displaygame(int playerscore);
    void displayscoreboardmenu();
    void chosenscreenmode();
    void displayoptionmenu();
    void choose_screen_type(int score);
    ~SCREENMODE();
    int getscreenmode();
    void setscreenmode(int mode);
};
