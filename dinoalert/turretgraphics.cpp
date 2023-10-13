/*#include <raylib.h>
#include <cmath>
#include <iostream>

using namespace std;

class TURRET {
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

    TURRET(float a, float b , int c) {
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
            return ((630/11)*(atan( (y - mousey) / (mousex - x))));

        else if (mousex < x && mousey < y)         //2nd quadrant
            return (180-((630/11)*(atan((y - mousey) / (x - mousex)))));

        else if (mousex < x && mousey > y)         //3rd quadrant
            return (180+((630/11)*(atan((mousey - y) / (x - mousex)))));

        else if (mousex > x && mousey > y)           //4th quadrant
            return (360-((630/11)*(atan((mousey - y) / (mousex - x)))));

        else if (mousex == x && mousey < y)
            return 90;
        else if (mousex < x && mousey == y)
            return 180;
        else if (mousex == x && mousey > y)
            return 270;
        else if (mousex > x && mousey == y)
            return 360;

    }
    Rectangle displayturret(int mousex , int mousey) {
        angle=calculateangle(mousex, mousey);
        if (angle < 22.5 )
            return east;

        else if (angle <67.5)
            return northeast;

        else if (angle <112.5)
            return up;

        else if (angle <157.5)
            return northwest;

        else if (angle <202.5)
            return west;

        else if (angle <247.5)
            return southwest;

        else if (angle <292.5)
            return down;

        else if (angle <337.5)
            return southeast;

    }


};


int main() {
    int screenWidth = 800;
    int screenHeight = 450;


    InitWindow(screenWidth, screenHeight, "turret");

    Texture2D turret;
    turret = LoadTexture("./car.png");

    SetTargetFPS(60);


    TURRET Turretv( screenWidth / 2, screenHeight / 2 );
    int speed = 4;

    while (!WindowShouldClose()) {



        if (IsKeyDown(KEY_D))
            Turretv.setx (Turretv.getx() + speed);
        if (IsKeyDown(KEY_A))
            Turretv.setx (Turretv.getx() - speed);
        if (IsKeyDown(KEY_W))
            Turretv.sety(Turretv.gety() - speed);
        if (IsKeyDown(KEY_S))
            Turretv.sety(Turretv.gety() + speed);


        BeginDrawing();

        ClearBackground(WHITE);


        Rectangle turretloc = Turretv.displayturret(GetMouseX(), GetMouseY());

        DrawTextureRec(turret , turretloc, Vector2{  Turretv.getx(), Turretv.gety() }, WHITE);



        EndDrawing();
    }
    CloseWindow();
    return 0;
}*/