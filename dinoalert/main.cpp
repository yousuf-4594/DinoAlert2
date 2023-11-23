#include "raylib.h"
#include <cmath>
#include<vector>
#include <iostream>
#include <fstream>
#include <string>
#include <omp.h>
#include "Powerups.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"
#include "ScreenMode.h"
#include <vector>



using namespace std;


/*
Hello there!
This project is made by:

    Yousuf ahmed siddiqui   21K4594
    Sufiyaan usmani         21k3239
    Qasim hasan             21k3210

    Section 5J

Course: Parallel and Distributed Computing
*/

float deltaTime;

bool analytics=true;

Camera2D camera = { 0 };


powerup entity;
std::vector<powerup> Entity;


ENEMY Enemy;
std::vector<ENEMY> enemies;


Bullet b1;
std::vector<Bullet> bullets;

void generate_powerup() {
    static int time_to_add = powerup::getclock() + GetRandomValue(400, 1000);
    if (powerup::getclock() >= time_to_add && powerup::getcount() <= 2) {
        entity.setcoord(GetRandomValue(-1471, 1396), GetRandomValue(-598, 530));
        Entity.push_back(powerup(entity));
        powerup::inccount();
    }
}


void tile_spread(float bullet_x, float bullet_y) {
    if (Bullet::get_gun_type() == 4) {
        #pragma omp parallel for num_threads(8)
        for (int i = 0; i < enemies.size(); i++) {
            /*if (analytics)*/
                //cout << "\nTile spread thread:" << omp_get_thread_num();
            if (CheckCollisionCircleRec(Vector2{ bullet_x,bullet_y }, 50, Rectangle{ enemies[i].getx(),enemies[i].gety(),60,60 })) {
                enemies[i].decreaselife(4);
            }
        }
    }
}


void processBullet(int bulletIndex, Vector2 player, PLAYER& a) {
    bullets[bulletIndex].move(bullets[bulletIndex].getcurrentvelocityx(), bullets[bulletIndex].getcurrentvelocityy());

    // Out of bounds
    if (bullets[bulletIndex].getx() < player.x - (2 * Bullet::getrange()) || bullets[bulletIndex].getx() > player.x + (2 * Bullet::getrange()) || bullets[bulletIndex].gety() < player.y - Bullet::getrange() || bullets[bulletIndex].gety() > player.y + Bullet::getrange()) {
        bullets.erase(bullets.begin() + bulletIndex);
    }
    else {
        // Enemy collision
        for (int k = 0; k < enemies.size(); k++) {
            if (CheckCollisionRecs(Rectangle{ bullets[bulletIndex].getx(),bullets[bulletIndex].gety(),7,7 }, Rectangle{ enemies[k].getx() , enemies[k].gety() , 60 , 60 })) {
                tile_spread(bullets[bulletIndex].getx(), bullets[bulletIndex].gety());
                //bullets.erase(bullets.begin() + bulletIndex);
                enemies[k].decreaselife(Bullet::get_gun_type());
                break;
            }
        }
    }
}




void findbulletpath(Vector2 player, Vector2 mouse, PLAYER& a) {
    static float count = 0;
    count+= 1 * 50 * GetFrameTime();


    //blocks
    Vector2 aimdirection;
    Vector2 unitvector;

    aimdirection.x = mouse.x - player.x;
    aimdirection.y = mouse.y - player.y;

    unitvector.x = aimdirection.x / (sqrt(pow(aimdirection.x, 2) + pow(aimdirection.y, 2)));
    unitvector.y = aimdirection.y / (sqrt(pow(aimdirection.x, 2) + pow(aimdirection.y, 2)));

    //Shooting
    if (count - Bullet::getfirerate() >= 0) {
        if (IsKeyDown(KEY_SPACE)) {
            b1.setposition(player.x, player.y);
            b1.setcurrentvelocity(unitvector.x * b1.getmaxspeed() * 50 * GetFrameTime(), unitvector.y * b1.getmaxspeed() * 50 * GetFrameTime());
            Bullet::dec_ammo();
            bullets.push_back(Bullet(b1));
        }
        count = 0;
    }
    for (int i = 0; i < bullets.size(); i++) {
        processBullet(i, player, a);
    }
    for (int k = 0; k < enemies.size(); k++) {
        if (enemies[k].allowtoerase() == true) {
            enemies[k].decenemycount();
            enemies.erase(enemies.begin() + k);
            a.increase_score();

        }
    }
}



void displaybullet(float offsetx, float offsety, Texture2D bulletsprite) {
    for (int i = 0; i < bullets.size(); i++) {
        DrawCircle(bullets[i].getx() + offsetx + 18, bullets[i].gety() + offsety + 8, 10, DARKBROWN);
    }
}


void check_player_enemy_collision(PLAYER& a, Color& color) {
    #pragma omp parallel for num_threads(3)
    for (int k = 0; k < enemies.size(); k++) {
        if (CheckCollisionRecs(Rectangle{ enemies[k].getx(),enemies[k].gety(),60,60 }, Rectangle{ a.getx() , a.gety() , 100 , 90 })) {                
            color = RED;                
            // player life decrement has to be done in a critical region
            #pragma omp critical
            a.decreaselife();
        }
        else
            color = WHITE;
    }
}



void check_power_player_collision(PLAYER player) {
    int i;
    #pragma omp parallel for
    for (i = 0; i < Entity.size(); i++) {
        if (CheckCollisionRecs(Rectangle{ player.getx(),player.gety(),100,90 }, Rectangle{ (float)Entity[i].getx(),(float)Entity[i].gety(),21,15 })) {
            Entity.erase(Entity.begin() + i);
            if (Bullet::check_if_deathbringer_onn())
                Bullet::setguntype(GetRandomValue(2, 5));
            else
                Bullet::setguntype(GetRandomValue(2, 4));
            powerup::deccount();
        }

    }

}











void populate_enemy() {
    int i;
    #pragma omp for
    for (i = 0; i < ENEMY::getenemycount(); i++) {
        Enemy.setx(GetRandomValue(-2071, 1996));
        Enemy.sety(GetRandomValue(1274, 3834));
        enemies.push_back(Enemy);
    }
}



void initialise_the_game(PLAYER& player, int& wavenumber) {

    player.initlife();
    player.initscore();
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i].decenemycount();
        enemies.erase(enemies.begin() + i);
    }
    wavenumber = 0;
    ENEMY::setenemycount(0);
    ENEMY::setenemyspeed(2);
    player.setx(GetScreenWidth() / 2.0);
    player.sety(GetScreenHeight() / 2.0);
}



bool checkCollision(const Vector2& rect1, const Vector2& rect2, float width, float height) {

    if (rect1.x + width < rect2.x || rect1.x > rect2.x + width ||
        rect1.y + height < rect2.y || rect1.y > rect2.y + height) {
        return false;
    }
    return true;
}

void zupdatePosition(ENEMY& enemy) {
    int temp = std::rand() % 2;
    int temp2 = std::rand() % 2;
 
    if (temp == 1) {
        if (temp2 == 1) {
            enemy.setx(enemy.getx() + 10);
        }
        else {
            enemy.sety(enemy.gety() + 10);
        }
    }
    else {
        if (temp2 == 1) {
            enemy.setx(enemy.getx() - 10);
        }
        else {
            enemy.sety(enemy.gety() - 10);
        }
    }
}


void checkCollisionRecursive(std::vector<ENEMY>& enemies, int start, int end) {
    if (start >= end) {
        return;
    }
    Vector2 pos1 = { enemies[start].getx(), enemies[start].gety() };

    for (int j = start + 1; j <= end; j++) {
        Vector2 pos2 = { enemies[j].getx(), enemies[j].gety() };

        if (checkCollision(pos1, pos2, 80, 80)) {
            zupdatePosition(enemies[start]);
        }
    }
    checkCollisionRecursive(enemies, start + 1, end);
}


void check_enemy_into_enemy_collision() {
    int size = enemies.size();
    int quarter1 = size / 4;
    int quarter2 = size / 2;
    int quarter3 = 3 * size / 4;

    int arr[] = { 0, quarter1, quarter2, quarter3, size };

    #pragma omp parallel for num_threads(4)
    for (int i = 1; i <= 4; i++) {
        /*if (analytics)
            cout << "\nEnemy-Enemy collision threads" << omp_get_thread_num();*/
        
        checkCollisionRecursive(enemies, arr[i - 1], arr[i] - 1);
    }
}


void check_if_player_outof_bounds(PLAYER& player) {

    /*if (player.gety() >= (0.502 * player.getx() + 1200)) {
        player.setx(player.getx() + 10);
        player.sety(player.gety() - 10);
    }
    if (player.gety() >= (-0.502 * player.getx() + 1100)) {
        player.setx(player.getx() - 10);
        player.sety(player.gety() - 10);
    }
    if (player.gety() <= (-0.502 * player.getx() -1396)) {
        player.setx(player.getx() + 10);
        player.sety(player.gety() + 10);
    }
    if (player.gety() <= (0.502 * player.getx() -1300)) {
        player.setx(player.getx() - 10);
        player.sety(player.gety() + 10);
    }
    */

}






void check_buymenu(PLAYER& player, float& acc, float& maxspeed) {
    Rectangle health = { 1294,181,69,69 };
    Rectangle ammo = { 1294,254,69,69 };
    Rectangle acceleration = { 1294,328,69,69 };
    Rectangle topspeed = { 1294,401,69,69 };
    Rectangle deathbringer = { 1294,474,69,69 };

    DrawText("++HEALTH 20k", 1090, 235, 3, YELLOW);
    DrawText("++AMMO 30k", 1090, 308, 3, YELLOW);
    DrawText("++ACCELERATION 50k", 1050, 380, 3, YELLOW);
    DrawText("++TOP SPEED 50k", 1070, 451, 3, YELLOW);
    DrawText("++DEATH BRINGER 200k", 1040, 524, 3, YELLOW);


    //#pragma omp parallel
    {
        if (CheckCollisionPointRec(GetMousePosition(), health) && player.getlife() < 200 && player.get_score() >= 20) {
            DrawText("++HEALTH 20k", 1090, 235, 3, RED);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                player.increase_life(40);
                player.decrease_score(20);
            }
        }
        else if (CheckCollisionPointRec(GetMousePosition(), ammo) && player.get_score() >= 30) {
            DrawText("++AMMO 30k", 1090, 308, 3, RED);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Bullet::increaseammo();
                player.decrease_score(30);
            }
        }
        else if (CheckCollisionPointRec(GetMousePosition(), acceleration) && player.get_score() >= 50) {
            DrawText("++ACCELERATION 50k", 1050, 380, 3, RED);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                acc += 0.02;
                player.decrease_score(50);
            }
        }
        else if (CheckCollisionPointRec(GetMousePosition(), topspeed) && player.get_score() >= 50) {
            DrawText("++TOP SPEED 50k", 1070, 451, 3, RED);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                maxspeed += 2.00;
                player.decrease_score(50);
            }
        }
        else if (CheckCollisionPointRec(GetMousePosition(), deathbringer) && player.get_score() >= 200 && Bullet::check_if_deathbringer_onn() == false) {
            DrawText("++DEATH BRINGER 200k", 1040, 524, 3, RED);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Bullet::ondeathbringer();
                player.decrease_score(200);
            }
        }
    }
}

int main() {
    omp_set_nested(1);


    int frameCounter = 0;
    float frameAccumulator = 0;
    int maxIterations = 1;

    int w = 1160, h = 765;

    int wavenumber = 1;

    Color player_color = RAYWHITE;

    int enemy_count = 4500;
    ENEMY::setenemycount(enemy_count);




    float offsetx = 0.00, offsety = 0.00;

    int i=0,temp=0,counter=0;


    PLAYER player(w/2, h/2);
    Bullet::setguntype(4);

    TURRET Turretv(w/2 , h/2);
    //PROJECTILE projectile;

    double angle = (628.5714286);                  //varies
    float speed = 0;                        //varies
    float maxSpeed = 11.0;                   //constant
    float acc = 0.05, dec = 0.2;             //constant
    float turnSpeed = 0.05;                 //constant
    float angleindegrees=0;

    populate_enemy();

    InitWindow(w, h, "DinoAlert");
    
    
    //----------------------------------------------------------------   TEXTURES   ---------------------------------------
    Texture2D textures[9], player_car, enemysprite, intro, hud, bg;
    textures[0] = LoadTexture("./Assets/map1.png");
    textures[1] = LoadTexture("./Assets/map2.png");
    textures[2] = LoadTexture("./Assets/map3.png");
    textures[3] = LoadTexture("./Assets/map4.png");
    textures[4] = LoadTexture("./Assets/map5.png");
    textures[5] = LoadTexture("./Assets/map6.png");
    textures[6] = LoadTexture("./Assets/map7.png");
    textures[7] = LoadTexture("./Assets/map8.png");
    textures[8] = LoadTexture("./Assets/map9.png");
    player_car = LoadTexture("./Assets/car.png");
    enemysprite = LoadTexture("./Assets/enemysprite.png");
    intro = LoadTexture("./Assets/intro.png");
    hud = LoadTexture("./Assets/hud.png");
    bg = LoadTexture("./Assets/background.png");

    //---------------------------------------------------------------------------------------------------------------------

    SCREENMODE screenmode;


    SetTargetFPS(360);


    
    camera.target = { player.getx() + 20.0f, player.gety() + 20.0f};
    camera.offset = { w / 2.0f, h / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;


    //ToggleFullscreen();

    while (!WindowShouldClose()) {
        
        if (screenmode.getscreenmode() == 0) {
            initialise_the_game(player, wavenumber);
        }
        

        if (screenmode.getscreenmode() == 1) {

            if (player.playeralive()) {
                //#pragma omp parallel reduction(+:speed)
                {
                    if (IsKeyDown(KEY_I)) {
                        analytics = !analytics;
                    }
                    if (IsKeyDown(KEY_W) && speed < maxSpeed) {
                        if (speed < 0)  speed += dec * 100 * GetFrameTime();
                        else  speed += acc * 100 * GetFrameTime();
                    }
                    if (IsKeyDown(KEY_S) && speed > -maxSpeed) {
                        if (speed > 0) speed -= dec * 100 * GetFrameTime();
                        else  speed -= acc * 100 * GetFrameTime();
                    }
                    if (!IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)) {
                        if (speed - dec > 0) speed -= dec * 100 * GetFrameTime();
                        else if (speed + dec < 0) speed += dec * 100 * GetFrameTime();
                        else speed = 0;
                    }
                    if (IsKeyDown(KEY_D) && speed != 0) {
                        angle += turnSpeed * 100 * GetFrameTime() * speed / maxSpeed;
                    }
                    if (IsKeyDown(KEY_A) && speed != 0) {
                        angle -= turnSpeed * 100 * GetFrameTime() * speed / maxSpeed;
                    }
                    player.setx(player.getx() + sin(angle) * 1.2 * speed * 100 * GetFrameTime());
                    player.sety(player.gety() - cos(angle) * speed * 100 * GetFrameTime());

                    Turretv.setx(player.getx());
                    Turretv.sety(player.gety());

                    angleindegrees = fmod(((angle * 630) / 11), 360);
                }
            }

            findbulletpath(Vector2{ player.getx(), player.gety() }, (GetScreenToWorld2D(GetMousePosition(), camera)), player);

            
            #pragma omp parallel for num_threads(8)
            for (int i = 0; i < enemies.size(); i++) {
               /* if(analytics)
                    cout << "\nEnemies movement thread: "<<omp_get_thread_num();*/

                enemies[i].moveenemy(player);
            }

                          
            

            camera.target = { player.getx() + 20, player.gety() + 20 };      //  CAMERA
            camera.zoom += ((float)GetMouseWheelMove() * 0.05f);            //
            if (camera.zoom > 3.0f)                                         //
                camera.zoom = 3.0f;                                         //
            else if (camera.zoom <= 0.1f)                                    //
                camera.zoom = 0.1f;                                        //  CAMERA





        }



        BeginDrawing();
        ClearBackground(RAYWHITE);

        screenmode.choose_screen_type(player.get_score());


        if (screenmode.getscreenmode() == 1) {

            DrawTexture(bg, 0, 0, WHITE);

            if (wavenumber >= 8) {
                ENEMY::setenemyspeed(8.00);
            }
            else if (wavenumber >= 6) {
                ENEMY::setenemyspeed(6.00);
            }
            else if (wavenumber >= 3) {
                ENEMY::setenemyspeed(4.00); 
            }

           //5120x2576

            BeginMode2D(camera);

            #pragma omp sections
            {
                /*if (analytics) {
                    cout << "\nMap display Total Threads : " << omp_get_num_threads();
                    cout << "\nMap display Thread Number: " << omp_get_thread_num();
                }*/
                #pragma omp section
                DrawTexture(textures[0], -2560, -1288, WHITE);                 //1    
                
                #pragma omp section
                DrawTexture(textures[1], -5120, -7, WHITE);                     //2+7
        
                #pragma omp section
                DrawTexture(textures[2], 0, -7, WHITE);                         //3+7

                #pragma omp section
                DrawTexture(textures[3], -7680, 1274, WHITE);                  //4+14

                #pragma omp section
                DrawTexture(textures[4], -2560, 1274, WHITE);                  //5+14

                #pragma omp section
                DrawTexture(textures[5], 2560, 1274, WHITE);                   //6+14

                #pragma omp section
                DrawTexture(textures[6], -5120, 2555, WHITE);                  //7+21

                #pragma omp section
                DrawTexture(textures[7], 0, 2555, WHITE);                      //8+21
    
                #pragma omp section
                DrawTexture(textures[8], -2560, 3836, WHITE);                  //9+28
            }

            check_if_player_outof_bounds(player);


            if (GetFPS() % GetFPS()/2 && frameCounter <= maxIterations) {
                #pragma omp for
                for (int i = 0; i < enemies.size(); i++) {
                    Rectangle enemyrectangle = enemies[i].displayenemy(player,true);
                    DrawTextureRec(enemysprite, enemyrectangle, Vector2{ enemies[i].getx() , enemies[i].gety() }, WHITE);                    
                }
            }
            else {
                #pragma omp for
                for (int i = 0; i < enemies.size(); i++) {
                    Rectangle enemyrectangle = enemies[i].displayenemy(player, false);
                    DrawTextureRec(enemysprite, enemyrectangle, Vector2{ enemies[i].getx() , enemies[i].gety() }, WHITE);
                }
            }



            player.offsets(&offsetx, &offsety);

            Rectangle turretloc = Turretv.displayturret(GetScreenToWorld2D(GetMousePosition(), camera));


            
            if (GetFPS() % 2 && frameCounter <= maxIterations) {
                Rectangle playerrectangle = player.displayplayer((IsKeyDown(KEY_A) || IsKeyDown(KEY_D) || IsKeyDown(KEY_W) || IsKeyDown(KEY_S)), angleindegrees, true);
                DrawTextureRec(player_car, playerrectangle, Vector2{ player.getx() , player.gety() }, WHITE);
            }
            else {
                Rectangle playerrectangle = player.displayplayer((IsKeyDown(KEY_A) || IsKeyDown(KEY_D) || IsKeyDown(KEY_W) || IsKeyDown(KEY_S)), angleindegrees, false);
                DrawTextureRec(player_car, playerrectangle, Vector2{ player.getx() , player.gety() }, WHITE);
            }




            if (GetFPS() % 2 && frameCounter <= maxIterations) {
                frameCounter++;
            }


            check_player_enemy_collision(player, player_color);





            if (player.playeralive())
                DrawTextureRec(player_car, turretloc, Vector2{ (Turretv.getx() + offsetx), (Turretv.gety() + offsety) }, WHITE);
            else {
                temp++;
                if(temp>100)
                screenmode.setscreenmode(4);
            }

            #pragma omp parallel
            {
                #pragma omp for
                for (int i = 0; i < Entity.size(); i++) {
                    Entity[i].drawpowerup(player_car);
                }
            }

            Bullet::checkammo();

            if(enemies.size()>enemy_count*0.05)
                check_enemy_into_enemy_collision();

            check_power_player_collision(player);


            displaybullet(offsetx, offsety, player_car);


            frameAccumulator += GetFrameTime();

            if (frameAccumulator >= 1) {
                frameCounter = 0;
            }


            EndMode2D();

            #pragma omp sections
            {
                /*if (analytics)
                    cout << "\nHUD threads:" << omp_get_thread_num();*/
                #pragma omp section
                {
                    DrawTexture(hud, 0, 0, WHITE); 
                }
                #pragma omp section
                {
                    player.displaylife(player_car); 
                }
                #pragma omp section
                {
                    player.display_score(); 
                }
                #pragma omp section
                {
                    DrawText(TextFormat("dino alive : %i", ENEMY::getenemycount()), 970, 15, 20, BLACK); 
                }
                #pragma omp section
                {
                    DrawText(TextFormat("wave number: %i", wavenumber), 1000, 40, 20, ORANGE); 
                }
                #pragma omp section
                {
                    DrawText(TextFormat("FPS: %i", GetFPS()), 1010, 70, 20, GREEN); 
                }
                #pragma omp section
                {
                    Bullet::draw_gun(player_car); 
                }
            }
                check_buymenu(player, acc, maxSpeed);

            if (ENEMY::getenemycount() <= 0) {
                wavenumber++;
                /*if(enemy_count * wavenumber >= 2500)
                    ENEMY::setenemycount(2500);
                else*/
                    ENEMY::setenemycount(enemy_count*wavenumber);
                populate_enemy();
                counter = 1;
            }
        }

        EndDrawing();
    }
    //UnloadTexture(textures);
    UnloadTexture(player_car);
    UnloadTexture(enemysprite);
    UnloadTexture(intro);
    UnloadTexture(hud);
    UnloadTexture(bg);




    CloseWindow();
    return 0;
}