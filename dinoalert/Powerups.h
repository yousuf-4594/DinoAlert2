#pragma once

#include "raylib.h"

class powerup {
    int x;
    int y;
    static int timer;
    static int count;
    Rectangle img;

public:
    powerup();
    void setcoord(int a, int b);
    static void clock_up();
    void drawpowerup(Texture2D powerup_sprite);
    static int getclock();
    int getx();
    int gety();
    static void inccount();
    static int getcount();
    static void deccount();
};
