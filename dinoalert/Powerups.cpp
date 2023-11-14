#include "Powerups.h"



using namespace std;


int powerup::timer;
int powerup::count;

powerup::powerup() {
    x = 0;
    y = 0;
    img = { 582,391,21,15 };
}

void powerup::setcoord(int a, int b) {
    x = a;
    y = b;
}

void powerup::clock_up() {
    timer++;
}

void powerup::drawpowerup(Texture2D powerup_sprite) {
    DrawTextureRec(powerup_sprite, img, Vector2{ (float)x, (float)y }, WHITE);
}

int powerup::getclock() {
    return timer;
}

int powerup::getx() {
    return x;
}

int powerup::gety() {
    return y;
}

void powerup::inccount() {
    count++;
}

int powerup::getcount() {
    return count;
}

void powerup::deccount() {
    count--;
}
