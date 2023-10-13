/*#include <raylib.h>
#include <cmath>


class PLAYER {
    int count[8] = { 0 };
    float x;
    float y;
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


public:
    PLAYER(){}
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
    Rectangle displayplayer(bool press , float angle){
        if (press) {
            if (angle < 22.5 || angle>337.5) {
                count[2]++;
                if (count[2] < 10)
                    return up_1;
                else if (count[2] < 20)
                    return up_2;
                else
                    count[2] = 0;
            }
            else if (angle < 67.5) {
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
                count[3]++;
                if (count[3] < 10)
                    return down_1;
                else if (count[3] < 20)
                    return down_2;
                else
                    count[3] = 0;
            }
            else if (angle < 247.5) {
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
    }


};


int main() {
    double angle = (628.5714286);                  //varies
    float speed = 0;                        //varies
    float maxSpeed = 8.0;                   //constant
    float acc = 0.2, dec = 0.3;             //constant
    float turnSpeed = 0.05;                 //constant
    float angleindegrees;

    bool direction = 1;

    const int w = 1200;
    const int h = 700;

    PLAYER player;

    InitWindow(w, h, "raylib ");

    Vector2 p = { w / 2,h / 2 };
    Vector2 m ={p.x,p.y};
    
    Texture2D player_car;
    player_car = LoadTexture("./car.png");

    player.setx(w / 2);
    player.sety(h / 2);

    SetTargetFPS(60);
    ToggleFullscreen();

    while (!WindowShouldClose()) {


    
        if (IsKeyDown(KEY_UP) && speed < maxSpeed) {
            if (speed < 0)  speed += dec;
            else  speed += acc;
        }
        if (IsKeyDown(KEY_DOWN) && speed > -maxSpeed) {
            if (speed > 0) speed -= dec;
            else  speed -= acc;
        }
        if (!IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN)) {
            if (speed - dec > 0) speed -= dec;
            else if (speed + dec < 0) speed += dec;
            else speed = 0;
        }
        if (IsKeyDown(KEY_RIGHT) && speed != 0) {
            angle += turnSpeed * speed / maxSpeed;
            direction = true;
        }
        if (IsKeyDown(KEY_LEFT) && speed != 0) {
            angle -= turnSpeed * speed / maxSpeed;
            direction = false;
        }
        player.setx(player.getx() + sin(angle) * 1.2 * speed);
        player.sety(player.gety() - cos(angle) * speed);



        angleindegrees = fmod(((angle * 630) / 11), 360);


        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(TextFormat("x: %f", player.getx()), 1, 1, 20, BLACK);
        DrawText(TextFormat("y: %f", player.gety()), 1, 20, 20, BLACK);
        DrawText(TextFormat("anglein rads: %f", angle ), 1, 40, 20, BLACK);
        DrawText(TextFormat("system angle: %f", ((angle*630)/11)), 1, 60, 20, BLACK);
        DrawText(TextFormat("angleindegrees: %f", angleindegrees), 1, 80, 20, BLACK);




        Rectangle playerrectangle = player.displayplayer(      (  IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_RIGHT)  || IsKeyDown(KEY_UP)  || IsKeyDown(KEY_DOWN)  )      , angleindegrees);


        DrawTextureRec(player_car, playerrectangle, Vector2{ player.getx() , player.gety() }, WHITE);

        //DrawCircle(player.getx(), player.gety(), 20, RED);
        


        EndDrawing();
    }
    UnloadTexture(player_car);
    CloseWindow();
    return 0;
}*/