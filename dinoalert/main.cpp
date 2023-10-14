#include "raylib.h"
#include <cmath>
#include<vector>
#include <iostream>
#include <fstream>
#include <string>
#include <omp.h>


using namespace std;

void hyp(float* a, float* b) {
    float c;
    c = sqrt((*a) * (*a) + (*b) * (*b));
    *a /= c;
    *b /= c;
}



class Bullet{
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
    Bullet(){
        coord.x = 0.0;
        coord.y = 0.0;
        currentvelocity.x = 0.0;
        currentvelocity.y = 0.0;
    }
    void setposition(float a, float b) {
        coord.x = a;
        coord.y = b;

    }
    void setcurrentvelocity(float a,float b) {
        currentvelocity.x = a;
        currentvelocity.y = b;

    }
    float getmaxspeed() {
        return maxSpeed;
    }
    void move(float a, float b) {
        coord.x += a;
        coord.y += b;
    }
    float getcurrentvelocityx() {
        return currentvelocity.x;
    }
    float getcurrentvelocityy() {
        return currentvelocity.y;
    }
    float getx() {
        return coord.x;
    }
    float gety() {
        return coord.y;
    }
    static void setrange(int a) {
        range = a;
    }
    static void setmaxspeed(int a) {
        maxSpeed = a;
    }
    static void ondeathbringer() {
        deathbringer = true;
    }
    static bool check_if_deathbringer_onn() {
        return deathbringer;
    }
    static void increaseammo() {
        addon[1] += 100;
        addon[2] += 20;
        addon[3] += 5;
    }
    static void setguntype(int a) {
        gun = a;
        if (gun == 1) {
            maxSpeed = 15.0;
            range = 200;
            firerate = 11;
            ammo = 1000;
        }
        if (gun == 2) {
            maxSpeed = 15.0;
            range = 200;
            firerate = 3;
            ammo = 200+addon[1];
        }
        if (gun == 3) {
            maxSpeed = 30.0;
            range = 500;
            firerate = 22;
            ammo = 20+ addon[2];
        }
        if (gun == 4) {
            maxSpeed = 50.0;
            range = 400;
            firerate = 60;
            ammo = 5+ addon[3];
        }
        if (gun == 5) {
            maxSpeed = 50.0;
            range = 800;
            firerate = 1;
            ammo = 1000;
        }

    }
    static void checkammo() {
        if (gun == 2 && ammo <= 0)
            setguntype(1);
        if (gun == 4 && ammo <= 0)
            setguntype(1);
        if (gun == 5 && ammo <= 0)
            setguntype(1);
        if (gun == 3 && ammo <= 0)
            setguntype(1);
        if (gun == 1 && ammo <= 0)
            setguntype(1);
    }
    static int getrange() {
        return range;
    }
    static int getfirerate() {
        return firerate;
    }
    static int getammo() {
        return ammo;
    }
    static void dec_ammo() {
        ammo--;
    }
    static void draw_gun(Texture2D gunsprite) {
        Rectangle pistol = {582,283,71,34};
        Rectangle machinegun = {582,319,71,40};
        Rectangle sniper = {582,361,71,27};
        Rectangle misslelauncher = { 582,412,71,32 };
        Rectangle death_bringer = { 582,447,71,29 };

        if (gun == 1) {
            DrawTextureRec(gunsprite, pistol, Vector2{ 10 ,12 }, WHITE);
            DrawText(TextFormat("ammo: %i", ammo), 85, 16, 20, ORANGE);
        }
        if (gun == 2) {
            DrawTextureRec(gunsprite, machinegun, Vector2{ 10 ,12 }, WHITE);
            DrawText(TextFormat("ammo: %i", ammo), 85, 16, 20, ORANGE);
        }
        if (gun == 3) {
            DrawTextureRec(gunsprite, sniper, Vector2{ 10 ,12 }, WHITE);
            DrawText(TextFormat("ammo: %i", ammo), 85, 16, 20, ORANGE);
        }
        if (gun == 4) {
            DrawTextureRec(gunsprite, misslelauncher, Vector2{ 10 ,12 }, WHITE);
            DrawText(TextFormat("ammo: %i", ammo), 85, 16, 20, ORANGE);
        }
        if (gun == 5) {
            DrawTextureRec(gunsprite, death_bringer, Vector2{ 10 ,12 }, WHITE);
            DrawText(TextFormat("ammo: %i", ammo), 85, 16, 20, ORANGE);
        }

    }
    static int get_gun_type() {
        return gun;
    }
};

int Bullet::range = 200;
int Bullet::firerate = 11;
int Bullet::gun = 1;
float Bullet::maxSpeed = 15;
int Bullet::ammo=1000;
int Bullet::addon[4] = { 0 };
bool Bullet::deathbringer = 0;










class PLAYER {
private:
    int count[9] = { 0 };
    float x;
    float y;
    int playerlife=200;
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
    PLAYER() {}
    PLAYER(float a, float b) {
        x = a;
        y = b;
    }
    void setx(float a) {
        x = a;
    }
    void sety(float a) {
        y = a;
    }
    float getx() {
        return x;
    }
    float gety() {
        return y;
    }
    void increase_score() {
        score++;
    }
    int get_score() {
        return score;
    }
    void decreaselife() {
        playerlife--;
    }
    void initlife() {
        playerlife = 200;
    }
    void initscore() {
        score = 0;
    }
    int getlife() {
        return playerlife;
    }
    void increase_life(int a) {
        playerlife += a;
    }
    void decrease_score(int a) {
        score -= a;
    }

    Rectangle displayplayer(bool press, float angle) {
        if (press && playerlife>0) {
            if (angle < 22.5 || angle>337.5) {
                playerdirection = 1;
                count[2]++;
                if (count[2] < 10)
                    return up_1;
                else if (count[2] < 20)
                    return up_2;
                else
                    count[2] = 0;
            }
            else if (angle < 67.5) {
                playerdirection = 2;
                count[6]++;
                if (count[6] < 10)
                    return northeast_1;
                else if (count[6] < 20)
                    return northeast_2;
                else if (count[6] < 30)
                    return northeast_3;
                else
                    count[6] = 0;
            }
            else if (angle < 112.5) {
                playerdirection = 3;
                count[1]++;
                if (count[1] < 10)
                    return east_1;
                else if (count[1] < 20)
                    return east_2;
                else if (count[1] < 30)
                    return east_3;
                else
                    count[1] = 0;
            }
            else if (angle < 157.5) {
                playerdirection = 4;
                count[4]++;
                if (count[4] < 10)
                    return southeast_1;
                else if (count[4] < 20)
                    return southeast_2;
                else if (count[4] < 30)
                    return southeast_3;
                else
                    count[4] = 0;
            }
            else if (angle < 202.5) {
                playerdirection = 5;
                count[3]++;
                if (count[3] < 10)
                    return down_1;
                else if (count[3] < 20)
                    return down_2;
                else
                    count[3] = 0;
            }
            else if (angle < 247.5) {
                playerdirection = 6;
                count[5]++;
                if (count[5] < 10)
                    return southwest_1;
                else if (count[5] < 20)
                    return southwest_2;
                else if (count[5] < 30)
                    return southwest_3;
                else
                    count[5] = 0;
            }
            else if (angle < 292.5) {
                playerdirection = 7;
                count[0]++;
                if (count[0] < 10)
                    return west_1;
                else if (count[0] < 20)
                    return west_2;
                else if (count[0] < 30)
                    return west_3;
                else
                    count[0] = 0;
            }
            else if (angle < 337.5) {
                playerdirection = 8;
                count[7]++;
                if (count[7] < 10)
                    return northwest_1;
                else if (count[7] < 20)
                    return northwest_2;
                else if (count[7] < 30)
                    return northwest_3;
                else
                    count[7] = 0;

            }
        }
        else if (playerlife <= 0) {
            count[8]++;
            if (count[8] < 10)
                return explosion_1;
            else if (count[8] < 20)
                return explosion_2;
            else if (count[8] < 30)
                return explosion_3;
            else if (count[8] < 30)
                return explosion_4;
            else if (count[8] < 30)
                return explosion_5;
            else
                return Rectangle{ 0,0,0,0 };
                
        }


    }
    void showdirection() {
        cout << playerdirection << endl;
    }

    void offsets(float* offsetx, float* offsety) {
        if (playerdirection == 1) {
            cout << "north";
            (*offsetx) = 18;
            (*offsety) = 10;
        }
        else if (playerdirection == 2) {
            (*offsetx) = 71;
            (*offsety) = 0;
        }
        else if (playerdirection == 3) {
            (*offsetx) = 69;
            (*offsety) = -3;
        }
        else if (playerdirection == 4) {
            (*offsetx) = 67;
            (*offsety) = 24;
        }
        else if (playerdirection == 5) {
            (*offsetx) = 20;
            (*offsety) = 42;
        }
        else if (playerdirection == 6) {
            (*offsetx) = 42;
            (*offsety) = 23;
        }
        else if (playerdirection == 7) {
            (*offsetx) = 40;
            (*offsety) = -3;
        }
        else if (playerdirection == 8) {
            (*offsetx) = 39;
            (*offsety) = 0;
        }



    }
    void displaylife(Texture2D lifesprite) {
        int i,gap=170;
        for (i = 0; i <= 20; i++) {
            DrawTextureRec(lifesprite, Rectangle{378,656,21,41}, Vector2{(float)gap , 736.00}, WHITE);
            gap += 23;
        }
        gap = 170;
        for (i = 0; i <= playerlife/10 ; i++) {
            DrawTextureRec(lifesprite, life, Vector2{(float)gap , 724.00}, WHITE);
            gap += 23;
        }
                                                       // Get current screen width
        
    }
    void display_score() {
        DrawText(TextFormat("kill count : %i ", score),  1100, 734,10, ORANGE);


    }
    bool playeralive() {
        if (playerlife > 0)
            return 1;
        else if(playerlife <=0)
            return 0;
    }


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

    TURRET(float a, float b, int c) {
        x = a;
        y = b;
        angle = c;
    }
    TURRET(float a, float b) {
        x = a;
        y = b;
        angle = 0;
    }
    float getx() {
        return x;
    }
    float gety() {
        return y;
    }
    void setx(float a) {
        x = a;
    }
    void sety(float a) {
        y = a;
    }
    float calculateangle(int mousex, int mousey) {


        if (mousex > x && mousey < y)              //1st quadrant
            return ((630 / 11) * (atan((y - mousey) / (mousex - x))));

        else if (mousex < x && mousey < y)         //2nd quadrant
            return (180 - ((630 / 11) * (atan((y - mousey) / (x - mousex)))));

        else if (mousex < x && mousey > y)         //3rd quadrant
            return (180 + ((630 / 11) * (atan((mousey - y) / (x - mousex)))));

        else if (mousex > x && mousey > y)           //4th quadrant
            return (360 - ((630 / 11) * (atan((mousey - y) / (mousex - x)))));

        else if (mousex == x && mousey < y)
            return 90;
        else if (mousex < x && mousey == y)
            return 180;
        else if (mousex == x && mousey > y)
            return 270;
        else if (mousex > x && mousey == y)
            return 360;

    }
    Rectangle displayturret(Vector2 mouse) {
        angle = calculateangle(mouse.x, mouse.y);
        cout << angle << "\t" << mouse.x << "\t" << mouse.y << "\t" << x << "\t" << y << "\n";
        if (angle < 22.5)
            return east;

        else if (angle < 67.5)
            return northeast;

        else if (angle < 112.5)
            return up;

        else if (angle < 157.5)
            return northwest;

        else if (angle < 202.5)
            return west;

        else if (angle < 247.5)
            return southwest;

        else if (angle < 292.5)
            return down;

        else if (angle < 337.5)
            return southeast;

    }


};













class ENEMY {
    static int enemycount;
    float x;
    float y;
    float angle;
    int count[13] = { 0 };
    static float enemyspeed;
    bool is_enemy_dead = false;      //bool of if player is dead;
    bool erase = false;
    int life;


    Vector2 minus;

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
    ENEMY() {

        x = 0;
        y = 0;
        angle = 0;
        life = 5;

    }
    ENEMY(float a, float b) {
        x = a;
        y = b;
        angle = 0;
    }
    void setx(float a) {
        x = a;
    }
    void sety(float a) {
        y = a;
    }
    float getx() {
        return x;
    }
    float gety() {
        return y;
    }
    void setlife(int a) {
        life = a;
    }


    void decreaselife(int a) {

        if (a == 3 || a == 4 || a==5)
            life -= 5;
        else
            life--;
        
        if(life<=0)
        is_enemy_dead = true;
    }
    bool allowtoerase() {
        return erase;
    }
    void set_to_erase() {
        erase = true;
    }
    void decenemycount() {
        enemycount--;
    }
    bool check_if_enemy_dead() {
        return is_enemy_dead;
    }
    static int get_enemy_count() {
        return enemycount;
    }
    float calculateangle(float playerx, float playery) {


        if (playerx > x && playery < y)              //1st quadrant
            return ((630 / 11) * (atan((y - playery) / (playerx - x))));

        else if (playerx < x && playery < y)         //2nd quadrant
            return (180 - ((630 / 11) * (atan((y - playery) / (x - playerx)))));

        else if (playerx < x && playery > y)         //3rd quadrant
            return (180 + ((630 / 11) * (atan((playery - y) / (x - playerx)))));

        else if (playerx > x && playery > y)           //4th quadrant
            return (360 - ((630 / 11) * (atan((playery - y) / (playerx - x)))));

        else if (playerx == x && playery < y)
            return 90;
        else if (playerx < x && playery == y)
            return 180;
        else if (playerx == x && playery > y)
            return 270;
        else if (playerx > x && playery == y)
            return 360;

    }


    Rectangle displayenemy(PLAYER& player) {

        angle = calculateangle(player.getx(), player.gety());


        if (is_enemy_dead == true) {

            count[12]++;
            if (count[12] < 10)
                return enemydead_1;
            else if (count[12] < 20)
                return enemydead_2;
            else if (count[12] < 30)
                return enemydead_3;
            else if (count[12] < 60)
                return enemydead_4;
            else
                erase = true;

        }

        else if (angle < 15 || angle >345) {
            count[0]++;
            if (count[0] < 10)
                return east_1;
            else if (count[0] < 20)
                return east_2;
            else if (count[0] < 30)
                return east_3;
            else
                count[0] = 0;
        }
        else if (angle < 45) {
            count[1]++;
            if (count[1] < 10)
                return northeast_21;
            else if (count[1] < 20)
                return northeast_22;
            else
                count[1] = 0;
        }
        else if (angle < 75) {
            count[2]++;
            if (count[2] < 10)
                return northeast_11;
            else if (count[2] < 20)
                return northeast_12;
            else
                count[2] = 0;
        }
        else if (angle < 105) {
            count[3]++;
            if (count[3] < 10)
                return north_1;
            else if (count[3] < 20)
                return north_2;
            else if (count[3] < 30)
                return north_3;
            else
                count[3] = 0;
        }
        else if (angle < 135) {
            count[4]++;
            if (count[4] < 10)
                return northwest_11;
            else if (count[4] < 20)
                return northwest_12;
            else
                count[4] = 0;
        }
        else if (angle < 165) {
            count[5]++;
            if (count[5] < 10)
                return northwest_21;
            else if (count[5] < 20)
                return northwest_22;
            else
                count[5] = 0;
        }
        else if (angle < 195) {
            count[6]++;
            if (count[6] < 10)
                return west_1;
            else if (count[6] < 20)
                return west_2;
            else if (count[6] < 30)
                return west_3;
            else
                count[6] = 0;
        }
        else if (angle < 225) {
            count[7]++;
            if (count[7] < 10)
                return southwest_21;
            else if (count[7] < 20)
                return southwest_22;
            else
                count[7] = 0;
        }
        else if (angle < 255) {
            count[8]++;
            if (count[8] < 10)
                return southwest_11;
            else if (count[8] < 20)
                return southwest_12;
            else if (count[8] < 30)
                return southwest_13;
            else
                count[8] = 0;
        }
        else if (angle < 285) {
            count[9]++;
            if (count[9] < 10)
                return south_1;
            else if (count[9] < 20)
                return south_2;
            else if (count[9] < 30)
                return south_3;
            else
                count[9] = 0;
        }
        else if (angle < 315) {
            count[10]++;
            if (count[10] < 10)
                return southeast_11;
            else if (count[10] < 20)
                return southeast_12;
            else if (count[10] < 30)
                return southeast_13;
            else
                count[10] = 0;
        }
        else if (angle < 345) {
            count[11]++;
            if (count[11] < 10)
                return southeast_21;
            else if (count[11] < 20)
                return southeast_22;
            else
                count[11] = 0;
        }
    }

    void moveenemy(PLAYER& a) {
        if (is_enemy_dead == false) {
            float playerx = a.getx();
            float playery = a.gety();

            if (playerx < x && playery < y) {
                //4th quadrant
                minus.x = x - playerx;
                minus.y = y - playery;
                hyp(&minus.x, &minus.y);
                x -= minus.x * enemyspeed;
                y -= minus.y * enemyspeed;
            }

            else if (playerx < x && playery > y) {
                //1st quadrant
                minus.x = x - playerx;
                minus.y = playery - y;
                hyp(&minus.x, &minus.y);
                x -= minus.x * enemyspeed;
                y += minus.y * enemyspeed;
            }

            else if (playerx > x && playery > y) {
                //2nd quadrant
                minus.x = playerx - x;
                minus.y = playery - y;
                hyp(&minus.x, &minus.y);
                x += minus.x * enemyspeed;
                y += minus.y * enemyspeed;
            }

            else if (playerx > x && playery < y) {
                //3rd quadrant
                minus.x = playerx - x;
                minus.y = y - playery;
                hyp(&minus.x, &minus.y);
                x += minus.x * enemyspeed;
                y -= minus.y * enemyspeed;
            }
            else if (playerx == x && playery < y)
                y -= enemyspeed;

            else if (playerx == x && playery > y)
                y += enemyspeed;

            else if (playery == y && playerx < x)
                x -= enemyspeed;

            else if (playery == y && playerx > x)
                x += enemyspeed;
        }
    }
    static void setenemycount(int a) {
        enemycount = a;
    }
    static int getenemycount() {
        return enemycount;
    }
    static void setenemyspeed(float a) {
        enemyspeed = a;
    }
    
    void displaydead() {
        Texture2D enemysprite;
        enemysprite = LoadTexture("./Assets/enemysprite.png");

        count[12]++;
        if (count[12] < 10)
            DrawTextureRec(enemysprite, enemydead_1, Vector2{ x , y }, WHITE);
        else if (count[12] < 20)
            DrawTextureRec(enemysprite, enemydead_2, Vector2{ x , y }, WHITE);
        else if (count[12] < 30)
            DrawTextureRec(enemysprite, enemydead_3, Vector2{ x , y }, WHITE);
        else if (count[12] < 60)
            DrawTextureRec(enemysprite, enemydead_4, Vector2{ x , y }, WHITE);

    }

    







};
float ENEMY::enemyspeed = 2;
int ENEMY::enemycount;



class SCREENMODE {
    int screenmode = 0;

    Texture2D mainmenu = LoadTexture("./Assets/intro.png");
    Texture2D options = LoadTexture("./Assets/mainmenuoptions.png");
    Texture2D option_menu = LoadTexture("./Assets/option_menu.png");
    Texture2D score_menu = LoadTexture("./Assets/scoreboard.png");
    Texture2D gameover = LoadTexture("./Assets/gameover.png");





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


    int highscore = calc_highscore();

public:

    SCREENMODE() {
        screenmode = 0;
    }



    void displaygame(int playerscore) {


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

    void displayscoreboardmenu() {
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

    void chosenscreenmode() {

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

    void displayoptionmenu() {
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
    void choose_screen_type(int score) {

        if (screenmode == 0)
            chosenscreenmode();

        if (screenmode == 2)
            displayoptionmenu();

        if (screenmode == 3)
            displayscoreboardmenu();

        if (screenmode == 4)
            displaygame(score);

    }
    ~SCREENMODE() {
        UnloadTexture(mainmenu);
        UnloadTexture(options);
        UnloadTexture(option_menu);
        UnloadTexture(score_menu);
        UnloadTexture(gameover);
    }
    int getscreenmode() {
        return screenmode;
    }
    void setscreenmode(int mode) {
        screenmode = mode;
    }





};



class powerup {
    int x=0;
    int y=0;
    static int timer;
    static int count;
    Rectangle img = { 582,391,21,15 };
public:
    powerup() {
        x = 0;
        y = 0;
    }
    void setcoord(int a,int b) {
        x = a;
        y = b;
    }
    static void clock_up() {
        timer++;
    }
    void drawpowerup(Texture2D powerup_sprite) {
        DrawTextureRec(powerup_sprite, img, Vector2{ (float)x , (float)y }, WHITE);
    }
    static int getclock() {
        return timer;
    }
    int getx() {
        return x;
    }
    int gety() {
        return y;
    }
    static void inccount() {
        count++;
    }
    static int getcount() {
        return count;
    }
    static void deccount() {
        count--;
    }

};
int powerup::timer;
int powerup::count;


powerup entity;
std::vector<powerup> Entity;


void generate_powerup() {
    static int time_to_add = powerup::getclock() + GetRandomValue(400, 1000);
    if (powerup::getclock() >= time_to_add && powerup::getcount() <= 2) {
        entity.setcoord(GetRandomValue(-1471, 1396), GetRandomValue(-598, 530));
        Entity.push_back(powerup(entity));
        powerup::inccount();
    }
}



















ENEMY Enemy;
std::vector<ENEMY> enemies;





Bullet b1;
std::vector<Bullet> bullets;










void tile_spread(float bullet_x,float bullet_y) {
    if (Bullet::get_gun_type() == 4) {
        for (int i=0; i < enemies.size(); i++) {
            if (CheckCollisionCircleRec(Vector2{ bullet_x,bullet_y }, 50, Rectangle{ enemies[i].getx(),enemies[i].gety(),60,60 })) {
                enemies[i].decreaselife(4);
            }
        }
    }
}









void findbulletpath(Vector2 player, Vector2 mouse , PLAYER &a) {
    static int count = 0;
    count++;
    
   
            //blocks
    Vector2 aimdirection;
    Vector2 unitvector;

    aimdirection.x = mouse.x - player.x;
    aimdirection.y = mouse.y - player.y;

    unitvector.x = aimdirection.x / (sqrt(pow(aimdirection.x, 2) + pow(aimdirection.y, 2)));
    unitvector.y = aimdirection.y / (sqrt(pow(aimdirection.x, 2) + pow(aimdirection.y, 2)));

    //Shooting
    if (count % Bullet::getfirerate() == 0) {
        if (IsKeyDown(KEY_SPACE)) {
            b1.setposition(player.x, player.y);
            b1.setcurrentvelocity(unitvector.x * b1.getmaxspeed(), unitvector.y * b1.getmaxspeed());
            Bullet::dec_ammo();
            bullets.push_back(Bullet(b1));
        }
    }
    for (int i = 0; i < bullets.size(); i++) {
        bullets[i].move(bullets[i].getcurrentvelocityx(), bullets[i].getcurrentvelocityy());

        //Out of bounds
        if (bullets[i].getx() < player.x - (2 * Bullet::getrange()) || bullets[i].getx() > player.x + (2 * Bullet::getrange()) || bullets[i].gety() < player.y - Bullet::getrange() || bullets[i].gety() > player.y + Bullet::getrange()) {
            bullets.erase(bullets.begin() + i);
        }
        else{
        	//Enemy collision
        	for (int k = 0; k < enemies.size(); k++){
        		if ( CheckCollisionRecs(    Rectangle { bullets[i].getx(),bullets[i].gety(),7,7}, Rectangle{enemies[k].getx() , enemies[k].gety() , 60 , 60})) {
                    tile_spread(bullets[i].getx(), bullets[i].gety());
        			bullets.erase(bullets.begin() + i);
                    //enemies.erase(enemies.begin() + k);
                    enemies[k].decreaselife(Bullet::get_gun_type());


                   
        			break;
        		}
                //if (enemies[k].allowtoerase() == true)
                  //  enemies.erase(enemies.begin() + k);

        	}
       	}
    }
    for (int k = 0; k < enemies.size(); k++) {
        if (enemies[k].allowtoerase() == true) {
            enemies[k].decenemycount();
            enemies.erase(enemies.begin() + k);
            a.increase_score();
            
        }
    }

}



void displaybullet(float offsetx, float offsety, Texture2D bulletsprite) {
    for (int i = 0; i < bullets.size(); i++) {
        DrawCircle(bullets[i].getx() + offsetx + 18, bullets[i].gety() + offsety + 8, 5, DARKBROWN);
    }

}


void check_player_enemy_collision(PLAYER& a , Color &color) {

    for (int k = 0; k < enemies.size(); k++) {
        
        if (CheckCollisionRecs(Rectangle{ enemies[k].getx(),enemies[k].gety(),60,60 }, Rectangle{ a.getx() , a.gety() , 100 , 90 })) {
            color = RED;
            a.decreaselife();
        }
        else
            color = WHITE;
    }
}



void check_power_player_collision(PLAYER player) {
    int i;
    for (i = 0; i < Entity.size(); i++) {
        if (       CheckCollisionRecs(Rectangle{ player.getx(),player.gety(),100,90 }, Rectangle{ (float)Entity[i].getx(),(float)Entity[i].gety(),21,15 }) ){
            Entity.erase(Entity.begin() + i);
            if (Bullet::check_if_deathbringer_onn())
            Bullet::setguntype(  GetRandomValue(2, 5)  );
            else 
                Bullet::setguntype(GetRandomValue(2, 4));
            powerup::deccount();
        }
        
    }

}











void populate_enemy() {
    int i;
    for (i = 0; i < ENEMY::getenemycount(); i++) {
        Enemy.setx(GetRandomValue(-1471, 1396));
        Enemy.sety(GetRandomValue(-598, 530));
        enemies.push_back(Enemy);
    }

}



void initialise_the_game(PLAYER& player, int& wavenumber) {

    player.initlife();
    player.initscore();
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i].decenemycount();
        enemies.erase(enemies.begin() + i);
    }
    wavenumber = 0;
    ENEMY::setenemycount(0);
    player.setx(GetScreenWidth() / 2.0);
    player.sety(GetScreenHeight() / 2.0);
}








void check_enemy_into_enemy_collision() {
    int i,j;
    for (i = 0; i < enemies.size(); i++) {
        Vector2 enemy1 = { enemies[i].getx() ,enemies[i].gety() };
        for (j = i+1; j < enemies.size(); j++) {
            Vector2 enemy2 = { enemies[j].getx(), enemies[j].gety() };
            if (CheckCollisionRecs(Rectangle{ enemy1.x,enemy1.y , 40,40 }, Rectangle{ enemy2.x,enemy2.y ,40,40 })) {
                int temp = GetRandomValue(1, 2);
                int temp2 = GetRandomValue(1, 2);
                if (temp == 1) {
                    if (temp == 1) {
                        enemies[i].setx(enemies[i].getx() + 1);
                    }
                    else {
                        enemies[i].sety(enemies[i].gety() + 1);
                    }
                }
                else {
                    if (temp == 1) {
                        enemies[i].setx(enemies[i].getx() - 1);
                    }
                    else {
                        enemies[i].sety(enemies[i].gety() - 1);
                    }
                }
               
            }

        }

    }


}








void check_if_player_outof_bounds(PLAYER &player) {

    /*if (player.gety() >= (0.502 * player.getx() + 1200)) {
        player.setx(player.getx() + 10);
        player.sety(player.gety() - 10);
    }
    if (player.gety() >= (-0.502 * player.getx() + 1100)) {
        player.setx(player.getx() - 10);
        player.sety(player.gety() - 10);
    }
    if (player.gety() <= (-0.502 * player.getx() -1396)) {
        player.setx(player.getx() + 10);
        player.sety(player.gety() + 10);
    }
    if (player.gety() <= (0.502 * player.getx() -1300)) {
        player.setx(player.getx() - 10);
        player.sety(player.gety() + 10);
    }
    */

}






void check_buymenu(PLAYER &player  , float &acc , float &maxspeed) {
    Rectangle health = { 1294,181,69,69 };
    Rectangle ammo = { 1294,254,69,69 };
    Rectangle acceleration = { 1294,328,69,69 };
    Rectangle topspeed = { 1294,401,69,69 };
    Rectangle deathbringer = { 1294,474,69,69 };
     
    DrawText("++HEALTH 20k", 1290, 235, 3, YELLOW);
    DrawText("++AMMO 30k", 1290, 308, 3, YELLOW);
    DrawText("++ACCELERATION 50k", 1250, 380, 3, YELLOW);
    DrawText("++TOP SPEED 50k", 1270, 451, 3, YELLOW);
    DrawText("++DEATH BRINGER 200k", 1240, 524, 3, YELLOW);

    if ( CheckCollisionPointRec(GetMousePosition(), health) && player.getlife()<200 && player.get_score()>=20 ) {
        DrawText("++HEALTH 20k", 1290, 235, 3, RED);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            player.increase_life(40);
            player.decrease_score(20);
        }
    }
    if (CheckCollisionPointRec(GetMousePosition(), ammo) && player.get_score() >= 30) {
        DrawText("++AMMO 30k", 1290, 308, 3, RED);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Bullet::increaseammo();
            player.decrease_score(30);
        }
    }
    if (CheckCollisionPointRec(GetMousePosition(), acceleration) &&  player.get_score() >= 50) {
        DrawText("++ACCELERATION 50k", 1250, 380, 3, RED);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            acc += 0.02;
            player.decrease_score(50);
        }
    }
    if (CheckCollisionPointRec(GetMousePosition(), topspeed) &&  player.get_score() >= 50) {
        DrawText("++TOP SPEED 50k", 1270, 451, 3, RED);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            maxspeed += 2.00;
            player.decrease_score(50);
        }
    }
    if (CheckCollisionPointRec(GetMousePosition(), deathbringer) && player.get_score() >= 200 && Bullet::check_if_deathbringer_onn()==false ) {
        DrawText("++DEATH BRINGER 200k", 1240, 524, 3, RED);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Bullet::ondeathbringer();
            player.decrease_score(200);
        }
    }
}



int main() {
    int w = 1360, h = 765;

    int wavenumber = 1;

    Color player_color = RAYWHITE;

    int enemy_count = 10;
    ENEMY::setenemycount(enemy_count);




    float offsetx = 0.00, offsety = 0.00;

    int i=0,temp=0;


    PLAYER player(w/2, h/2);


    TURRET Turretv(w/2 , h/2);
    //PROJECTILE projectile;

    double angle = (628.5714286);                  //varies
    float speed = 0;                        //varies
    float maxSpeed = 11.0;                   //constant
    float acc = 0.05, dec = 0.2;             //constant
    float turnSpeed = 0.05;                 //constant
    float angleindegrees=0;

    populate_enemy();

    InitWindow(w, h, "yousuf ");
    cout << "fdsafsfafafsdsdfdsafs";
    
    //----------------------------------------------------------------   TEXTURES   ---------------------------------------
    Texture2D textures,player_car,enemysprite,intro,hud,bg;
    textures = LoadTexture("./Assets/A.png");
    player_car = LoadTexture("./Assets/car.png");
    enemysprite = LoadTexture("./Assets/enemysprite.png");
    intro = LoadTexture("./Assets/intro.png");
    hud = LoadTexture("./Assets/hud.png");
    bg = LoadTexture("./Assets/background.png");

    //---------------------------------------------------------------------------------------------------------------------

    SCREENMODE screenmode;


    SetTargetFPS(60);


    Camera2D camera = { 0 };
    camera.target = { player.getx() + 20.0f, player.gety() + 20.0f};
    camera.offset = { w / 2.0f, h / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;


    //ToggleFullscreen();

    while (!WindowShouldClose()) {

        
        if (screenmode.getscreenmode() == 0) {
            initialise_the_game(player, wavenumber);
        }
        

        if (screenmode.getscreenmode() == 1) {

            if (player.playeralive()) {

                if (IsKeyDown(KEY_W) && speed < maxSpeed) {
                    if (speed < 0)  speed += dec;
                    else  speed += acc;
                }
                if (IsKeyDown(KEY_S) && speed > -maxSpeed) {
                    if (speed > 0) speed -= dec;
                    else  speed -= acc;
                }
                if (!IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)) {
                    if (speed - dec > 0) speed -= dec;
                    else if (speed + dec < 0) speed += dec;
                    else speed = 0;
                }
                if (IsKeyDown(KEY_D) && speed != 0) {
                    angle += turnSpeed * speed / maxSpeed;
                }
                if (IsKeyDown(KEY_A) && speed != 0) {
                    angle -= turnSpeed * speed / maxSpeed;
                }
                player.setx(player.getx() + sin(angle) * 1.2 * speed);
                player.sety(player.gety() - cos(angle) * speed);

                Turretv.setx(player.getx());
                Turretv.sety(player.gety());

                angleindegrees = fmod(((angle * 630) / 11), 360);

            }

            findbulletpath(Vector2{ player.getx(), player.gety() }, (GetScreenToWorld2D(GetMousePosition(), camera)), player);

            

            for (int i = 0; i < enemies.size(); i++) {
                enemies[i].moveenemy(player);
            }

                          
            

            camera.target = { player.getx() + 20, player.gety() + 20 };      //  CAMERA
            camera.zoom += ((float)GetMouseWheelMove() * 0.05f);            //
            //if (camera.zoom > 3.0f)                                         //
            //    camera.zoom = 3.0f;                                         //
            //else if (camera.zoom < 0.1f)                                    //
            //    camera.zoom = 0.1f;                                         //  CAMERA





        }



        BeginDrawing();
        ClearBackground(RAYWHITE);

        screenmode.choose_screen_type(player.get_score());


        if (screenmode.getscreenmode() == 1) {

            DrawTexture(bg, 0, 0, WHITE);

            if (wavenumber >= 8) {
                ENEMY::setenemyspeed(8.00);
            }
            else if (wavenumber >= 6) {
                ENEMY::setenemyspeed(6.00);
            }
            else if (wavenumber >= 3) {
                ENEMY::setenemyspeed(4.00);
            }

           //5120x2576

            BeginMode2D(camera);

            DrawTexture(textures, -5120, 2576, WHITE);     //isometric   tileset
            DrawTexture(textures, 0, 2576, WHITE);
            DrawTexture(textures, -5120, 0, WHITE);
            DrawTexture(textures, 0, 0, WHITE);

            DrawTexture(textures, -2560, -1288, WHITE);
            DrawTexture(textures, -2560, 1288, WHITE);
            DrawTexture(textures, -2560, 3864, WHITE);
            DrawTexture(textures, -7680, 1288, WHITE);
            DrawTexture(textures, 2560, 1288, WHITE);


            check_if_player_outof_bounds(player);

            for (int i = 0; i < enemies.size(); i++) {

                Rectangle enemyrectangle = enemies[i].displayenemy(player);
                DrawTextureRec(enemysprite, enemyrectangle, Vector2{ enemies[i].getx() , enemies[i].gety() }, WHITE);
            }




            player.offsets(&offsetx, &offsety);

            Rectangle turretloc = Turretv.displayturret(GetScreenToWorld2D(GetMousePosition(), camera));




            Rectangle playerrectangle = player.displayplayer((IsKeyDown(KEY_A) || IsKeyDown(KEY_D) || IsKeyDown(KEY_W) || IsKeyDown(KEY_S)), angleindegrees);


            check_player_enemy_collision(player, player_color);


            DrawTextureRec(player_car, playerrectangle, Vector2{ player.getx() , player.gety() }, WHITE);



            if (player.playeralive())
                DrawTextureRec(player_car, turretloc, Vector2{ (Turretv.getx() + offsetx), (Turretv.gety() + offsety) }, WHITE);
            else {
                temp++;
                if(temp>100)
                screenmode.setscreenmode(4);
            }

            for (int i = 0; i < Entity.size(); i++) {
                Entity[i].drawpowerup(player_car);
            }

            check_enemy_into_enemy_collision();

            check_power_player_collision(player);

            Bullet::checkammo();

            generate_powerup();
            powerup::clock_up();

            displaybullet(offsetx, offsety, player_car);


            



            EndMode2D();

            DrawTexture(hud, 0, 0, WHITE);
            player.displaylife(player_car);
            player.display_score();
            DrawText(TextFormat("wave number: %i",wavenumber), 1210 , 70 , 20, DARKBLUE);
            DrawText(TextFormat("dino alive : %i", ENEMY::getenemycount()), 1210, 40, 20, RED);
            check_buymenu(player,acc,maxSpeed);

            Bullet::draw_gun(player_car);

            if (ENEMY::getenemycount() <= 0) {
                wavenumber++;
                ENEMY::setenemycount(enemy_count*wavenumber);
                populate_enemy();
            }



        }


        EndDrawing();
    }
    UnloadTexture(textures);
    UnloadTexture(player_car);
    UnloadTexture(enemysprite);
    UnloadTexture(intro);
    UnloadTexture(hud);
    UnloadTexture(bg);




    CloseWindow();
    return 0;
}