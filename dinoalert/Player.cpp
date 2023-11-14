#include "player.h"
#include <cmath>

using namespace std;


PLAYER::PLAYER() {}

PLAYER::PLAYER(float a, float b) {
    x = a;
    y = b;
}

void PLAYER::setx(float a) {
    x = a;
}

void PLAYER::sety(float a) {
    y = a;
}

float PLAYER::getx() {
    return x;
}

float PLAYER::gety() {
    return y;
}

void PLAYER::increase_score() {
    score++;
}

int PLAYER::get_score() {
    return score;
}

void PLAYER::decreaselife() {
    playerlife--;
}

void PLAYER::initlife() {
    playerlife = 200;
}

void PLAYER::initscore() {
    score = 0;
}

int PLAYER::getlife() {
    return playerlife;
}

void PLAYER::increase_life(int a) {
    playerlife += a;
}

void PLAYER::decrease_score(int a) {
    score -= a;
}

Rectangle PLAYER::displayplayer(bool press, float angle) {
    if (press && playerlife > 0) {
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

void PLAYER::showdirection() {
    cout << playerdirection << endl;
}

void PLAYER::offsets(float* offsetx, float* offsety) {
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

void PLAYER::displaylife(Texture2D lifesprite) {
    int i, gap = 170;
    for (i = 0; i <= 20; i++) {
        DrawTextureRec(lifesprite, Rectangle{ 378,656,21,41 }, Vector2{ (float)gap , 736.00 }, WHITE);
        gap += 23;
    }
    gap = 170;
    for (i = 0; i <= playerlife / 10; i++) {
        DrawTextureRec(lifesprite, life, Vector2{ (float)gap , 724.00 }, WHITE);
        gap += 23;
    }
    // Get current screen width

}

void PLAYER::display_score() {
    DrawText(TextFormat("kill count : %i ", score), 1100, 734, 10, ORANGE);
}

bool PLAYER::playeralive() {
    if (playerlife > 0)
        return 1;
    else if (playerlife <= 0)
        return 0;
}

TURRET::TURRET(float a, float b, int c) {
    x = a;
    y = b;
    angle = c;
}

TURRET::TURRET(float a, float b) {
    x = a;
    y = b;
    angle = 0;
}

float TURRET::getx() {
    return x;
}

float TURRET::gety() {
    return y;
}

void TURRET::setx(float a) {
    x = a;
}

void TURRET::sety(float a) {
    y = a;
}

float TURRET::calculateangle(int mousex, int mousey) {


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

Rectangle TURRET::displayturret(Vector2 mouse) {
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
