/*#include<iostream>
#include <raylib.h>
#include<math.h>
#include<vector>
#include<cstdlib>

//LENGTH OF VECTOR: |V| = sqrt(V.x^2 + V.y^2)
//UNIT VECTOR: U = V / |V|

using namespace std;

class Bullet{
public:
	//CircleShape shape;
	Vector2 coord;
	Vector2 currentvelocity;
	float maxSpeed;

	Bullet(){
		maxSpeed=15.0;
		coord.x = 0.0;
		coord.y = 0.0;
		currentvelocity.x = 0.0;
		currentvelocity.y = 0.0;
	}
	void setposition(float a, float b) {
		coord.x = a;
		coord.y = b;

	}
	void setcurrentvelocity(float a,float b) {
		currentvelocity.x = a;
		currentvelocity.y = b;

	}
	float getmaxspeed() {
		return maxSpeed;
	}
	void move(float a, float b) {
		coord.x += a;
		coord.y += b;
	}
	float getcurrentvelocityx() {
		return currentvelocity.x;
	}
	float getcurrentvelocityy() {
		return currentvelocity.y;
	}
	float getx() {
		return coord.x;
	}
	float gety() {
		return coord.y;
	}
};

Bullet b1;
std::vector<Bullet> bullets;



void findbulletpath(Vector2 player) {
	static int count = 0;
	count++;
	Vector2 aimdirection;
	Vector2 unitvector;

	aimdirection.x = GetMouseX() - player.x;
	aimdirection.y = GetMouseY() - player.y;

	unitvector.x = aimdirection.x / (sqrt(pow(aimdirection.x, 2) + pow(aimdirection.y, 2)));
	unitvector.y = aimdirection.y / (sqrt(pow(aimdirection.x, 2) + pow(aimdirection.y, 2)));

	//Shooting
	if (count % 11 == 0) {
		if (IsKeyDown(KEY_SPACE)) {
			b1.setposition(player.x, player.y);
			b1.setcurrentvelocity(unitvector.x * b1.getmaxspeed(), unitvector.y * b1.getmaxspeed());

			bullets.push_back(Bullet(b1));
		}
	}
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].move(bullets[i].getcurrentvelocityx(), bullets[i].getcurrentvelocityy());

		//Out of bounds
//			if (bullets[i].shape.getPosition().x < 0 || bullets[i].shape.getPosition().x > window.getSize().x|| bullets[i].shape.getPosition().y < 0 || bullets[i].shape.getPosition().y > window.getSize().y){
//				bullets.erase(bullets.begin() + i);
//			}
//			else{
//				//Enemy collision
//				for (size_t k = 0; k < enemies.size(); k++){
//					if (bullets[i].shape.getGlobalBounds().intersects(enemies[k].getGlobalBounds())){
//						bullets.erase(bullets.begin() + i);
//						enemies.erase(enemies.begin() + k);
//						break;
//					}
//				}
//			}
	}

}



void displaybullet() {
	for (size_t i = 0; i < bullets.size(); i++) {
		DrawCircle(bullets[i].getx(), bullets[i].gety(), 10, RED);
	}

}













int main(){
	int width = 800, height = 440;

	InitWindow(width, height, "shoot the damn enemy");

	SetTargetFPS(120);


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

		findbulletpath(player);

		BeginDrawing();
		ClearBackground(LIGHTGRAY);

		DrawCircleV(player, 10, RED);

		displaybullet();

		EndDrawing();
	}
	CloseWindow();

	return 0;
}*/