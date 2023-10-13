/*#include <raylib.h>
#include <cmath>
#include <iostream>

using namespace std;



class ENEMY {
    float x;
    float y;
    float angle;
    int count[12] = { 0 };
    int enemyspeed = 1;

    Rectangle east_1 = { 335 , 229 , 113 , 90 };       //    { x , y , width , height }
    Rectangle east_2 = { 335 , 745 ,113 , 90 };
    Rectangle east_3 = { 335 , 1232 ,113 , 90 };

    Rectangle  northeast_11 = { 45 , 106 , 98 ,105 };
    Rectangle  northeast_12 = { 45 , 622 , 98 , 105 };

    Rectangle  northeast_21 = { 215 , 1 , 119 ,89 };
    Rectangle  northeast_22 = { 215 , 517 , 119 , 89 };

    Rectangle  north_1 = { 359 , 108 , 63 , 113 };
    Rectangle  north_2 = { 359 , 624 , 63 , 113 };
    Rectangle  north_3 = { 359 , 1111 , 63 , 113 };

    Rectangle  northwest_21 = { 168 , 229 ,119 , 89 };
    Rectangle  northwest_22 = { 181 , 745 , 106 , 89 };

    Rectangle  northwest_11 = { 359 , 334 ,98 , 105 };
    Rectangle  northwest_12 = { 359 ,850 ,98 , 105 };

    Rectangle west_1 = { 54 , 1 ,113 ,90 };
    Rectangle west_2 = { 54 , 517 , 113 , 90 };
    Rectangle west_3 = { 54 , 1004 , 113 , 90 };
                                                                //          NW1 | NE1
                                                                //       NW2 '     '  NE2
    Rectangle  southwest_21 = { 336 , 1 ,132 , 89 };            //        '           '
    Rectangle  southwest_22 = { 336 , 517, 132 , 89 };          //      _               _
                                                                //        '           '
    Rectangle  southwest_11 = { 208 , 338 ,118 ,93 };           //      SW2 '       ' SE2
    Rectangle  southwest_12 = { 208 ,854 , 116 , 93 };          //         SW1  |  SE1
    Rectangle  southwest_13 = { 208 ,1341 , 116 , 93 };

    Rectangle  south_1 = { 538 , 7 ,66 , 110 };
    Rectangle  south_2 = { 539 ,523 ,66 , 110 };
    Rectangle  south_3 = { 538 , 1010 , 66 , 110 };

    Rectangle  southeast_11 = { 176 , 110 , 118 , 94 };
    Rectangle  southeast_12 = { 178 ,626 ,116 , 93 };
    Rectangle  southeast_13 = { 178 ,1113 , 116 , 93 };

    Rectangle  southeast_21 = { 34 , 229 , 102 , 89 };
    Rectangle  southeast_22 = { 34 ,745 , 102 , 89 };

public:
    ENEMY(float a, float b) {
        x = a;
        y = b;
        angle = 0;
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
    float calculateangle(float playerx, float playery) {


        if (playerx > x && playery < y)              //1st quadrant
            return ((630 / 11) * (atan((y - playery) / (playerx - x))));

        else if (playerx < x && playery < y)         //2nd quadrant
            return (180 - ((630 / 11) * (atan((y - playery) / (x - playerx)))));

        else if (playerx < x && playery > y)         //3rd quadrant
            return (180 + ((630 / 11) * (atan((playery - y) / (x - playerx)))));

        else if (playerx > x && playery > y)           //4th quadrant
            return (360 - ((630 / 11) * (atan((playery - y) / (playerx - x)))));

        else if (playerx == x && playery < y)
            return 90;
        else if (playerx < x && playery == y)
            return 180;
        else if (playerx == x && playery > y)
            return 270;
        else if (playerx > x && playery == y)
            return 360;

    }


    Rectangle displayenemy(PLAYER &player) {

        angle = calculateangle(player.getx(),player.gety());

        if (angle<15 || angle >345) {
            count[0]++;
            if (count[0] < 10)
                return east_1;
            else if (count[0] < 20)
                return east_2;
            else if (count[0] < 30)
                return east_3;
            else
                count[0] = 0;
        }
        else if (angle<45) {
            count[1]++;
            if (count[1] < 10)
                return northeast_11;
            else if (count[1] < 20)
                return northeast_12;
            else
                count[1] = 0;
        }
        else if (angle <75 ) {
            count[2]++;
            if (count[2] < 10)
                return northeast_21;
            else if (count[2] < 20)
                return northeast_22;
            else
                count[2] = 0;
        }
        else if (angle <105 ) {
            count[3]++;
            if (count[3] < 10)
                return north_1;
            else if (count[3] < 20)
                return north_2;
            else if (count[3] < 30)
                return north_3;
            else
                count[3] = 0;
        }
        else if (angle <135 ) {
            count[4]++;
            if (count[4] < 10)
                return northwest_11;
            else if (count[4] < 20)
                return northwest_12;
            else
                count[4] = 0;
        }
        else if (angle <165 ) {
            count[5]++;
            if (count[5] < 10)
                return northwest_21;
            else if (count[5] < 20)
                return northwest_22;
            else
                count[5] = 0;
        }
        else if (angle <195 ) {
            count[6]++;
            if (count[6] < 10)
                return west_1;
            else if (count[6] < 20)
                return west_2;
            else if (count[6] < 30)
                return west_3;
            else
                count[6] = 0;
        }
        else if (angle <225 ) {
            count[7]++;
            if (count[7] < 10)
                return southwest_21;
            else if (count[7] < 20)
                return southwest_22;
            else
                count[7] = 0;
        }
        else if (angle <255 ) {
            count[8]++;
            if (count[8] < 10)
                return southwest_11;
            else if (count[8] < 20)
                return southwest_12;
            else if (count[8] < 30)
                return southwest_13;
            else
                count[8] = 0;
        }
        else if (angle <285 ) {
            count[9]++;
            if (count[9] < 10)
                return south_1;
            else if (count[9] < 20)
                return south_2;
            else if (count[9] < 30)
                return south_3;
            else
                count[9] = 0;
        }
        else if (angle <315 ) {
        count[10]++;
        if (count[10] < 10)
            return southeast_11;
        else if (count[10] < 20)
            return southeast_12;
        else if (count[10] < 30)
            return southeast_13;
        else
            count[10] = 0;
        }
        else if (angle <345 ) {
        count[11]++;
        if (count[11] < 10)
            return southeast_21;
        else if (count[11] < 20)
            return southeast_22;
        else
            count[11] = 0;
        }
    }

    void moveenemy(PLAYER &a) {

        float playerx = player.getx();
        float playery = player.gety();

        if (playerx < x && playery < y) {
            //4th quadrant
            minus.x = x - playerx;
            minus.y = y - playery;
            hyp(&minus.x, &minus.y);
            x-=minus.x;
            y-=minus.y;
        }

        else if (playerx < x && playery > y) {
            //1st quadrant
            minus.x = x - playerx;
            minus.y = playery - y;
            hyp(&minus.x, &minus.y);
            x-=minus.x;
            y+=minus.y;
        }

        else if (playerx > x && playery > y) {
            //2nd quadrant
            minus.x = playerx - x;
            minus.y = playery - y;
            hyp(&minus.x, &minus.y);
            x+=minus.x;
            y+=minus.y;
        }

        else if (playerx > x && playery < y) {
            //3rd quadrant
            minus.x = playerx - x;
            minus.y = y - playery;
            hyp(&minus.x, &minus.y);
            x+=minus.x;
            y-=minus.y;
        }
        else if (playerx == x && playery < y)
            y -=enemyspeed;

        else if (playerx == x && playery > y)
            y += enemyspeed;

        else if (playery == y && playerx < x)
            x -= enemyspeed;

        else if (playery == y && playerx > x)
            x += enemyspeed;

    }









};
*/