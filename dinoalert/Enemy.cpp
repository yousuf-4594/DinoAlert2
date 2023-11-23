#include "raylib.h"
#include <cmath>
#include<vector>
#include <iostream>
#include <fstream>
#include <string>
#include <omp.h>
#include "Player.h"

#include "Enemy.h"
#include <cmath>



using namespace std;




void hyp(float* a, float* b) {
    float c;
    c = sqrt((*a) * (*a) + (*b) * (*b));
    *a /= c;
    *b /= c;
}


int ENEMY::enemycount;
float ENEMY::enemyspeed = 2;

ENEMY::ENEMY() {

    x = 0;
    y = 0;
    angle = 0;
    life = 5;

}

ENEMY::ENEMY(float a, float b) {
    x = a;
    y = b;
    angle = 0;
}

void ENEMY::setx(float a) {
    x = a;
}

void ENEMY::sety(float a) {
    y = a;
}

float ENEMY::getx() {
    return x;
}

float ENEMY::gety() {
    return y;
}

void ENEMY::setlife(int a) {
    life = a;
}

void ENEMY::decreaselife(int a) {
    if (a == 3 || a == 4 || a == 5)
        life -= 5;
    else
        life--;

    if (life <= 0)
        is_enemy_dead = true;
}

bool ENEMY::allowtoerase() {
    return erase;
}

void ENEMY::set_to_erase() {
    erase = true;
}

void ENEMY::decenemycount() {
    enemycount--;
}

bool ENEMY::check_if_enemy_dead() {
    return is_enemy_dead;
}

int ENEMY::get_enemy_count() {
    return enemycount;
}

float ENEMY::calculateangle(float playerx, float playery) {


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

Rectangle ENEMY::displayenemy(PLAYER& player, bool framelimit) {


    angle = calculateangle(player.getx(), player.gety());


    if (is_enemy_dead == true) {
        //if (!framelimit)
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
        if(!framelimit)
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
        if (!framelimit)
        count[1]++;

        if (count[1] < 10)
            return northeast_21;
        else if (count[1] < 20)
            return northeast_22;
        else
            count[1] = 0;
    }
    else if (angle < 75) {
        if (!framelimit)
        count[2]++;

        if (count[2] < 10)
            return northeast_11;
        else if (count[2] < 20)
            return northeast_12;
        else
            count[2] = 0;
    }
    else if (angle < 105) {
        if (!framelimit)
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
        if (!framelimit)
        count[4]++;

        if (count[4] < 10)
            return northwest_11;
        else if (count[4] < 20)
            return northwest_12;
        else
            count[4] = 0;
    }
    else if (angle < 165) {
        if (!framelimit)
        count[5]++;

        if (count[5] < 10)
            return northwest_21;
        else if (count[5] < 20)
            return northwest_22;
        else
            count[5] = 0;
    }
    else if (angle < 195) {
        if (!framelimit)
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
        if (!framelimit)
        count[7]++;

        if (count[7] < 10)
            return southwest_21;
        else if (count[7] < 20)
            return southwest_22;
        else
            count[7] = 0;
    }
    else if (angle < 255) {
        if (!framelimit)
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
        if (!framelimit)
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
        if (!framelimit)
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
        if (!framelimit)
        count[11]++;

        if (count[11] < 10)
            return southeast_21;
        else if (count[11] < 20)
            return southeast_22;
        else
            count[11] = 0;
    }
}

void ENEMY::moveenemy(PLAYER& a) {
    if (is_enemy_dead == false) {
        float playerx = a.getx();
        float playery = a.gety();

        if (playerx < x && playery < y) {
            //4th quadrant
            minus.x = x - playerx;
            minus.y = y - playery;
            hyp(&minus.x, &minus.y);
            x -= minus.x * enemyspeed * 50 * GetFrameTime();
            y -= minus.y * enemyspeed * 50 * GetFrameTime();
        }

        else if (playerx < x && playery > y) {
            //1st quadrant
            minus.x = x - playerx;
            minus.y = playery - y;
            hyp(&minus.x, &minus.y);
            x -= minus.x * enemyspeed * 50 * GetFrameTime();
            y += minus.y * enemyspeed * 50 * GetFrameTime();
        }

        else if (playerx > x && playery > y) {
            //2nd quadrant
            minus.x = playerx - x;
            minus.y = playery - y;
            hyp(&minus.x, &minus.y);
            x += minus.x * enemyspeed * 50 * GetFrameTime();
            y += minus.y * enemyspeed * 50 * GetFrameTime();
        }

        else if (playerx > x && playery < y) {
            //3rd quadrant
            minus.x = playerx - x;
            minus.y = y - playery;
            hyp(&minus.x, &minus.y);
            x += minus.x * enemyspeed * 50 * GetFrameTime();
            y -= minus.y * enemyspeed * 50 * GetFrameTime();
        }
        else if (playerx == x && playery < y)
            y -= enemyspeed * 50 * GetFrameTime();

        else if (playerx == x && playery > y)
            y += enemyspeed * 50 * GetFrameTime();

        else if (playery == y && playerx < x)
            x -= enemyspeed * 50 * GetFrameTime();

        else if (playery == y && playerx > x)
            x += enemyspeed * 50 * GetFrameTime();
    }
}

void ENEMY::setenemycount(int a) {
    enemycount = a;
}

int ENEMY::getenemycount() {
    return enemycount;
}

void ENEMY::setenemyspeed(float a) {
    enemyspeed = a;
}

void ENEMY::displaydead() {
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
