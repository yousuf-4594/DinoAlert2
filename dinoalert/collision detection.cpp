/*#include "raylib.h"

int main(){

    const int screenWidth = 800;
    const int screenHeight = 500;

    InitWindow(screenWidth, screenHeight, "raylib ");

    SetTargetFPS(60);

    Vector2 player = { screenWidth/2, screenHeight/2 };
     
    Vector2 enemy = { 200,400 };

    Color color= BLUE;

    int speed = 5;

    while (!WindowShouldClose()){

        Rectangle player_rec = { player.x - 10,player.y - 10,20,20 };
        Rectangle enemy_rec = { enemy.x-20,enemy.y-20,40,40 };

        if (IsKeyDown(KEY_RIGHT)) player.x += speed;
        if (IsKeyDown(KEY_LEFT)) player.x -= speed;
        if (IsKeyDown(KEY_UP)) player.y -= speed;
        if (IsKeyDown(KEY_DOWN)) player.y += speed;




        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawCircle(enemy.x, enemy.y, 20, color);
        DrawCircle(player.x, player.y, 10, BLACK);


        if (CheckCollisionRecs(player_rec, enemy_rec)) {
            color = RED;
        }
        else color = BLUE;


        EndDrawing();
    }

    CloseWindow();
    return 0;
}*/