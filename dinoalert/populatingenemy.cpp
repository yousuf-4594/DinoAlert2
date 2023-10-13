/*#include "raylib.h"





class enemy {
    float x;
    float y;

public:
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


};



void populate(enemy *a) {
    int i;
    for (i = 0; i < 10; i++) {
        (a + i)->setx (GetRandomValue(0, 800));
        (a + i)->sety(GetRandomValue(0, 500));
    }

}






int main() {
    int i;


    enemy a[10];


    populate(&a[0]);

    const int screenWidth = 800;
    const int screenHeight = 500;

    InitWindow(screenWidth, screenHeight, "raylib ");
    SetTargetFPS(60);

    Vector2 player = { screenWidth / 2, screenHeight / 2 };
    int speed = 5;
    while (!WindowShouldClose()) {


        if (IsKeyDown(KEY_RIGHT)) player.x += speed;
        if (IsKeyDown(KEY_LEFT)) player.x -= speed;
        if (IsKeyDown(KEY_UP)) player.y -= speed;
        if (IsKeyDown(KEY_DOWN)) player.y += speed;







        BeginDrawing();
        ClearBackground(RAYWHITE);


        for(i=0;i<10;i++)
            DrawCircle(a[i].getx(), a[i].gety(), 10, YELLOW);

        DrawCircle(player.x, player.y, 10, YELLOW);


        EndDrawing();
    }

    CloseWindow();
    return 0;
}*/