#pragma once

#include "raylib.h"
#include "Player.h"  // Assuming this is the header for the Player class

class ENEMY {
    static int enemycount;
    float x;
    float y;
    float angle;
    int count[13];
    static float enemyspeed;
    bool is_enemy_dead;
    bool erase;
    int life;
    Vector2 minus;

    // Rectangle declarations

    Rectangle east_1 = { 335 , 229 , 113 , 90 };       //    { x , y , width , height }
    Rectangle east_2 = { 335 , 745 ,113 , 90 };
    Rectangle east_3 = { 335 , 1232 ,113 , 90 };

    Rectangle  northeast_11 = { 45 , 106 , 98 ,105 };
    Rectangle  northeast_12 = { 45 , 622 , 98 , 105 };

    Rectangle  northeast_21 = { 215 , 1 , 106 ,89 };
    Rectangle  northeast_22 = { 215 , 517 , 106 , 89 };

    Rectangle  north_1 = { 359 , 108 , 63 , 113 };
    Rectangle  north_2 = { 359 , 624 , 63 , 113 };
    Rectangle  north_3 = { 359 , 1111 , 63 , 113 };

    Rectangle  northwest_21 = { 183 , 229 ,104 , 89 };
    Rectangle  northwest_22 = { 183 , 745 , 104 , 89 };

    Rectangle  northwest_11 = { 359 , 334 ,98 , 105 };
    Rectangle  northwest_12 = { 359 ,850 ,98 , 105 };

    Rectangle west_1 = { 54 , 1 ,113 ,90 };
    Rectangle west_2 = { 54 , 517 , 113 , 90 };
    Rectangle west_3 = { 54 , 1004 , 113 , 90 };
    //                                                          //          NW1 | NE1
    //                                                          //       NW2 '     '  NE2
    Rectangle  southwest_21 = { 366 , 1 ,102 , 89 };            //        '           '
    Rectangle  southwest_22 = { 366 , 517, 102 , 89 };          //      _               _
                                                                //        '           '
    Rectangle  southwest_11 = { 208 , 338 ,118 ,93 };           //      SW2 '       ' SE2
    Rectangle  southwest_12 = { 208 ,854 , 116 , 93 };          //         SW1  |  SE1
    Rectangle  southwest_13 = { 208 ,1341 , 116 , 93 };

    Rectangle  south_1 = { 538 , 7 ,66 , 110 };
    Rectangle  south_2 = { 539 ,523 ,66 , 110 };
    Rectangle  south_3 = { 538 , 1010 , 66 , 110 };

    Rectangle  southeast_11 = { 176 , 110 , 118 , 94 };
    Rectangle  southeast_12 = { 178 ,626 ,116 , 93 };
    Rectangle  southeast_13 = { 178 ,1113 , 116 , 93 };

    Rectangle  southeast_21 = { 34 , 229 , 102 , 89 };
    Rectangle  southeast_22 = { 34 ,745 , 102 , 89 };


    Rectangle enemydead_1 = { 689 ,17 ,110 ,101 };
    Rectangle enemydead_2 = { 801 ,17 ,110 ,101 };
    Rectangle enemydead_3 = { 913 ,17 ,110 ,101 };
    Rectangle enemydead_4 = { 1025 ,17 ,110 ,101 };

public:
    ENEMY();
    ENEMY(float a, float b);
    void setx(float a);
    void sety(float a);
    float getx();
    float gety();
    void setlife(int a);
    void decreaselife(int a);
    bool allowtoerase();
    void set_to_erase();
    void decenemycount();
    bool check_if_enemy_dead();
    static int get_enemy_count();
    float calculateangle(float playerx, float playery);
    Rectangle displayenemy(PLAYER& player);
    void moveenemy(PLAYER& a);
    static void setenemycount(int a);
    static int getenemycount();
    static void setenemyspeed(float a);
    void displaydead();
};
