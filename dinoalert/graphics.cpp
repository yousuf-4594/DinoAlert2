/*#include "raylib.h"

int main(){
    int screenWidth = 800;
    int screenHeight = 450;
    int c = 0,d=0;
    bool e = 0, a = 0, b = 0, f = 0;
    InitWindow(screenWidth, screenHeight, "graphics");
    Texture2D textures;
    textures = LoadTexture("./abc.png");

    SetTargetFPS(60);
    Vector2 player = { screenWidth/2, screenHeight/2 };
    while (!WindowShouldClose()){

        if (IsKeyDown(KEY_RIGHT)) {
            player.x += 2;
            a = 1;
        }
        else
            a = 0;

        if (IsKeyDown(KEY_LEFT)) {
            player.x -= 2;
            b = 1;
        }
        else
            b = 0;

        if (IsKeyDown(KEY_UP)) {
            player.y -= 2;
            f = 1;
        }
        else
            f = 0;

        if (IsKeyDown(KEY_DOWN)) {
            player.y += 2;
            e = 1;
        }
        else
            e = 0;


        BeginDrawing();

        ClearBackground(RED);
        //down
        if (c % 11 == 0 && e == 1 ) {
                if (d >= 0 && d <= 10) {
                    DrawTextureRec(textures, Rectangle{ 14, 18, 34, 40 }, Vector2{ player.x , player.y }, RED);
                    d++;
                }
                if (d > 10 && d <= 20) {
                    DrawTextureRec(textures, Rectangle{ 78, 18, 34, 43 }, Vector2{ player.x , player.y }, RED);
                    d++;
                }
                if (d > 20 && d <= 30) {
                    DrawTextureRec(textures, Rectangle{ 206, 19, 34, 44 }, Vector2{ player.x , player.y }, RED);
                    d++;
                    if (d > 30)
                        d = 0;
                }
        }

        //up
        if (c % 11 == 0 && f == 1) {
            if (d >= 0 && d <= 10) {
                DrawTextureRec(textures, Rectangle{ 14, 209, 34, 40 }, Vector2{ player.x , player.y }, RED);
                d++;
            }
            if (d > 10 && d <= 20) {
                DrawTextureRec(textures, Rectangle{ 76, 206, 34, 46 }, Vector2{ player.x , player.y }, RED);
                d++;
            }
            if (d > 20 && d <= 30) {
                DrawTextureRec(textures, Rectangle{ 207, 206 , 34, 46 }, Vector2{ player.x , player.y }, RED);
                d++;
                if (d > 30)
                    d = 0;
            }
        }

        //left
        if (c % 11 == 0 && b == 1) {
            if (d >= 0 && d <= 10) {
                DrawTextureRec(textures, Rectangle{ 16, 80, 28, 44 }, Vector2{ player.x , player.y }, RED);
                d++;
            }
            if (d > 10 && d <= 20) {
                DrawTextureRec(textures, Rectangle{ 78, 78, 28, 44 }, Vector2{ player.x , player.y }, RED);
                d++;
            }
            if (d > 20 && d <= 30) {
                DrawTextureRec(textures, Rectangle{ 206, 78, 30, 44 }, Vector2{ player.x , player.y }, RED);
                d++;
                if (d > 30)
                    d = 0;
            }
        }

        //right
        if (c % 11 == 0 && a == 1) {
            if (d >= 0 && d <= 10) {
                DrawTextureRec(textures, Rectangle{ 20, 144, 28, 44 }, Vector2{ player.x , player.y }, RED);
                d++;
            }
            if (d > 10 && d <= 20) {
                DrawTextureRec(textures, Rectangle{ 79, 140, 30, 44 }, Vector2{ player.x , player.y }, RED);
                d++;
            }
            if (d > 20 && d <= 30) {
                DrawTextureRec(textures, Rectangle{ 210, 140, 28, 48 }, Vector2{ player.x , player.y }, RED);
                d++;
                if (d > 30)
                    d = 0;
            }
        }


        if (IsKeyUp(KEY_UP) && IsKeyUp(KEY_DOWN) && IsKeyUp(KEY_RIGHT) && IsKeyUp(KEY_LEFT))
            DrawTextureRec(textures, Rectangle{ 14, 18, 34, 40 }, Vector2{ player.x , player.y }, RED);







        EndDrawing();
    }
    CloseWindow();
    return 0;
}*/