/*#include "raylib.h"

int main(){

    const int screenWidth = 800;
    const int screenHeight = 500;

    InitWindow(screenWidth, screenHeight, "raylib ");

    Image cellular = GenImageCellular(screenWidth, screenHeight, 32);

    Texture2D textures;
    textures = LoadTexture("./A.png");


    UnloadImage(cellular);

    SetTargetFPS(60);

    Vector2 player = { screenWidth/2, screenHeight/2 };
    Camera2D camera = { 0 };
    camera.target = { player.x + 20.0f, player.y + 20.0f };
    camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    int speed = 5;
    while (!WindowShouldClose()){


        if (IsKeyDown(KEY_RIGHT)) player.x += speed;
        if (IsKeyDown(KEY_LEFT)) player.x -= speed;
        if (IsKeyDown(KEY_UP)) player.y -= speed;
        if (IsKeyDown(KEY_DOWN)) player.y += speed;







        camera.target = { player.x + 20, player.y + 20 };
        camera.zoom += ((float)GetMouseWheelMove() * 0.05f);
        if (camera.zoom > 3.0f)
            camera.zoom = 3.0f;
        else if (camera.zoom < 0.1f)
            camera.zoom = 0.1f;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);

        DrawTexture(textures, 0, 0, WHITE);
        DrawCircle(player.x, player.y, 10, YELLOW);

        EndMode2D();

        EndDrawing();
    }
    UnloadTexture(textures);
    CloseWindow();
    return 0;
}*/