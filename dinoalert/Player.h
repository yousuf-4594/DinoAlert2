#pragma once

#include "raylib.h"
#include <iostream>

class PLAYER {
private:
    int count[9] = { 0 };
    float x;
    float y;
    int playerlife = 200;
    int score = 0;
    int gun = 1;


    Rectangle west_1 = { 16,12,144,67 };        //  { x , y , width , height }
    Rectangle west_2 = { 176,12,144,67 };
    Rectangle west_3 = { 336,12,144,67 };

    Rectangle northwest_1 = { 17,551,143,86 };
    Rectangle northwest_2 = { 161,551,143,86 };
    Rectangle northwest_3 = { 305,551,143,86 };

    Rectangle southwest_1 = { 16,192,143,98 };
    Rectangle southwest_2 = { 161 ,192,143,98 };
    Rectangle southwest_3 = { 305,192,143,98 };

    Rectangle east_1 = { 16,96,144,67 };
    Rectangle east_2 = { 176,96,144,67 };
    Rectangle east_3 = { 336,96,144,67 };

    Rectangle northeast_1 = { 17,464,143,86 };
    Rectangle northeast_2 = { 161,464,143,86 };
    Rectangle northeast_3 = { 305,464,143,86 };

    Rectangle southeast_1 = { 17,328,143,98 };
    Rectangle southeast_2 = { 161,328,143,98 };
    Rectangle southeast_3 = { 305,328,143,98 };

    Rectangle down_1 = { 590,6,74,124 };
    Rectangle down_2 = { 686,6,74,124 };

    Rectangle up_1 = { 590,156,72,121 };
    Rectangle up_2 = { 688,156,72,121 };

    Rectangle life = { 400,646,21,42 };

    Rectangle explosion_1 = { 656,283,142,122 };
    Rectangle explosion_2 = { 656,407,142,122 };
    Rectangle explosion_3 = { 656,531,142,122 };
    Rectangle explosion_4 = { 656,655,142,122 };
    Rectangle explosion_5 = { 656,283,779,122 };

protected:
    int playerdirection;

public:
    PLAYER();
    PLAYER(float a, float b);
    void setx(float a);
    void sety(float a);
    float getx();
    float gety();
    void increase_score();
    int get_score();
    void decreaselife();
    void initlife();
    void initscore();
    int getlife();
    void increase_life(int a);
    void decrease_score(int a);
    Rectangle displayplayer(bool press, float angle, bool framelimit);
    Rectangle displayplayer(bool press, float angle);
    void showdirection();
    void offsets(float* offsetx, float* offsety);
    void displaylife(Texture2D lifesprite);
    void display_score();
    bool playeralive();
};

class TURRET : protected PLAYER {
    float x;
    float y;
    float angle;

    Rectangle west = { 89,694,35,19 };        //  { x , y , width , height }
    Rectangle northwest = { 125,694,35,19 };
    Rectangle southwest = { 53,694,35,19 };
    Rectangle east = { 89,673,35,19 };
    Rectangle northeast = { 125,673,35,19 };
    Rectangle southeast = { 53,673,35,19 };
    Rectangle down = { 17,673,35,19 };
    Rectangle up = { 161,673,35,19 };

public:
    TURRET(float a, float b, int c);
    TURRET(float a, float b);
    float getx();
    float gety();
    void setx(float a);
    void sety(float a);
    float calculateangle(int mousex, int mousey);
    Rectangle displayturret(Vector2 mouse);
};
