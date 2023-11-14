#pragma once

#include "raylib.h"

class Bullet {
    static int addon[4];
    Vector2 coord;
    Vector2 currentvelocity;
    static float maxSpeed;
    static int gun;
    static int range;
    static int firerate;
    static int ammo;
    static bool deathbringer;

public:
    Bullet();
    void setposition(float a, float b);
    void setcurrentvelocity(float a, float b);
    float getmaxspeed();
    void move(float a, float b);
    float getcurrentvelocityx();
    float getcurrentvelocityy();
    float getx();
    float gety();
    static void setrange(int a);
    static void setmaxspeed(int a);
    static void ondeathbringer();
    static bool check_if_deathbringer_onn();
    static void increaseammo();
    static void setguntype(int a);
    static void checkammo();
    static int getrange();
    static int getfirerate();
    static int getammo();
    static void dec_ammo();
    static void draw_gun(Texture2D gunsprite);
    static int get_gun_type();
};
