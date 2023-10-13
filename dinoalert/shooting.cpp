/*#include <raylib.h>
#include <cmath>
#include <iostream>


using namespace std;




class PROJECTILE {
    bool flag2 = true, flag = false,trigger2=0;
    float hyp;
    float projectilespeed = 2.00;
    Vector2 projectile,minus,mouse,temp;
    int count = 0;
    int range = 20;         //range is in loop iterations form              iska matlab loop 50 baar chalega tou next ball throw krskte
    Rectangle pixels = { 0,0,5,5 };


public:
    void moveprojectile(bool trigger,float startingx , float startingy ,float offsetx, float offsety , Texture2D bullet_sprite , Vector2 mouse_current_location) {


        //if (flag2 == true && enemydeath == true) {
        //        flag = true;
        //        flag2 = false;
        //}




        if (trigger == true && flag == false) {
            if (trigger2 == 0) {
                projectile.x = startingx;
                projectile.y = startingy;
                mouse.x = mouse_current_location.x;
                mouse.y = mouse_current_location.y;
                temp.x = startingx;
                temp.y = startingy;
                minus.x = 0;
                minus.y = 0;

                if (temp.x < mouse.x && temp.y < mouse.y) {           //4th
                    minus.x = mouse_current_location.x - startingx;
                    minus.y = mouse_current_location.y - startingy;
                }
                else if (temp.x < mouse.x && temp.y > mouse.y) {      //1st
                    minus.x = mouse_current_location.x - startingx;
                    minus.y = startingy - mouse_current_location.y;
                }
                else if (temp.x > mouse.x && temp.y > mouse.y) {      //2nd
                    minus.x = startingx - mouse_current_location.x;
                    minus.y = startingy - mouse_current_location.y;
                }
                else if (temp.x > mouse.x && temp.y < mouse.y) {      //3rd
                    minus.x = startingx - mouse_current_location.x;
                    minus.y = mouse_current_location.y - startingy;
                }
                else if (temp.x == mouse.x && temp.y < mouse.y)
                    minus.y = mouse_current_location.y - startingy;
                else if (temp.x == mouse.x && temp.y > mouse.y)
                    minus.y = startingy - mouse_current_location.y;
                else if (temp.y == mouse.y && temp.x < mouse.x)
                    minus.x = mouse_current_location.x - startingx;
                else if (temp.y == mouse.y && temp.x > mouse.x)
                    minus.x = startingx - mouse_current_location.x;


                hyp = sqrt((minus.x * minus.x) + (minus.y * minus.y));
                minus.x /= (hyp / (10*projectilespeed));
                minus.y /= (hyp / (10*projectilespeed));
                trigger2 = 1;
            }

            if (temp.x < mouse.x && temp.y < mouse.y) {
                //4th quadrant
                projectile.x += minus.x;
                projectile.y += minus.y;
            }
            else if (temp.x < mouse.x && temp.y > mouse.y) {
                //1st quadrant
                projectile.x += minus.x;
                projectile.y -= minus.y;
            }

            else if (temp.x > mouse.x && temp.y > mouse.y) {
                //2nd quadrant
                projectile.x -= minus.x;
                projectile.y -= minus.y;
            }

            else if (temp.x > mouse.x && temp.y < mouse.y) {
                //3rd quadrant
                projectile.x -= minus.x;
                projectile.y += minus.y;
            }
            else if (temp.x == mouse.x && temp.y < mouse.y)
                projectile.y += minus.y;

            else if (temp.x == mouse.x && temp.y > mouse.y)
                projectile.y -= minus.y;

            else if (temp.y == mouse.y && temp.x < mouse.x)
                projectile.x += minus.x;

            else if (temp.y == mouse.y && temp.x > mouse.x)
                projectile.x -= minus.x;
            count++;
            cout << count<<endl;

            DrawTextureRec(bullet_sprite, pixels, Vector2{  (projectile.x + offsetx + 18) , (projectile.y + offsety + 8)  }, WHITE);




            if (count>range ) {
                trigger = 0;
                trigger2 = 0;
                count = 0;
                projectile.x = startingx;
                projectile.y = startingy;
            }

        }


    }

    float getx() {
        return projectile.x;
        cout << projectile.x;
    }
    float gety() {
        return projectile.y;
    }
    void setprojectilespeed(float s) {
        projectilespeed = s;
    }
    void setx(float a) {
        projectile.x = a;
    }
    void sety(float a) {
        projectile.y = a;
    }


};


int main() {

    int width = 800;
    int height = 450;


    InitWindow(width, height, "shoot the damn enemy");

    SetTargetFPS(120);

    PROJECTILE p;

    Vector2 player{ (float)(width / 2) , (float)(height / 2) };

    while (!WindowShouldClose()) {


        if (IsKeyDown(KEY_D))
            player.x += 2;
        if (IsKeyDown(KEY_A))
            player.x -= 2;
        if (IsKeyDown(KEY_W))
            player.y -= 2;
        if (IsKeyDown(KEY_S))
            player.y += 2;

        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        DrawCircleV(player, 10, RED);
        DrawText(TextFormat("mouse x: %d", GetMouseX()), 1, 1, 20, BLACK);
        DrawText(TextFormat("mouse y: %d", GetMouseY()), 1, 20, 20, BLACK);


        p.moveprojectile(IsKeyDown(KEY_SPACE), player.x, player.y, Vector2{ (float) GetMouseX(),(float)GetMouseY() });


        if (!IsKeyDown(KEY_SPACE)) {
            p.setx(0.00);
            p.sety(0.00);

        }






        EndDrawing();




    }
    CloseWindow();
    return 0;
}*/