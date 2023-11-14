#include "raylib.h"
#include <cmath>

#include "bullet.h"

using namespace std;

int Bullet::range = 200;
int Bullet::firerate = 11;
int Bullet::gun = 1;
float Bullet::maxSpeed = 15;
int Bullet::ammo = 1000;
int Bullet::addon[4] = { 0 };
bool Bullet::deathbringer = 0;

Bullet::Bullet() {
    coord.x = 0.0;
    coord.y = 0.0;
    currentvelocity.x = 0.0;
    currentvelocity.y = 0.0;
}

void Bullet::setposition(float a, float b) {
    coord.x = a;
    coord.y = b;
}

void Bullet::setcurrentvelocity(float a, float b) {
    currentvelocity.x = a;
    currentvelocity.y = b;
}

float Bullet::getmaxspeed() {
    return maxSpeed;
}

void Bullet::move(float a, float b) {
    coord.x += a;
    coord.y += b;
}

float Bullet::getcurrentvelocityx() {
    return currentvelocity.x;
}

float Bullet::getcurrentvelocityy() {
    return currentvelocity.y;
}

float Bullet::getx() {
    return coord.x;
}

float Bullet::gety() {
    return coord.y;
}

void Bullet::setrange(int a) {
    range = a;
}

void Bullet::setmaxspeed(int a) {
    maxSpeed = a;
}

void Bullet::ondeathbringer() {
    deathbringer = true;
}

bool Bullet::check_if_deathbringer_onn() {
    return deathbringer;
}

void Bullet::increaseammo() {
    addon[1] += 100;
    addon[2] += 20;
    addon[3] += 5;
}

void Bullet::setguntype(int a) {
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
        ammo = 200 + addon[1];
    }
    if (gun == 3) {
        maxSpeed = 30.0;
        range = 500;
        firerate = 22;
        ammo = 20 + addon[2];
    }
    if (gun == 4) {
        maxSpeed = 50.0;
        range = 400;
        firerate = 60;
        ammo = 5 + addon[3];
    }
    if (gun == 5) {
        maxSpeed = 50.0;
        range = 800;
        firerate = 1;
        ammo = 1000;
    }
}

void Bullet::checkammo() {
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

int Bullet::getrange() {
    return range;
}

int Bullet::getfirerate() {
    return firerate;
}

int Bullet::getammo() {
    return ammo;
}

void Bullet::dec_ammo() {
    ammo--;
}

void Bullet::draw_gun(Texture2D gunsprite) {
    Rectangle pistol = { 582,283,71,34 };
    Rectangle machinegun = { 582,319,71,40 };
    Rectangle sniper = { 582,361,71,27 };
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

int Bullet::get_gun_type() {
    return gun;
}
