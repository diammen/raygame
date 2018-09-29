#pragma once

struct Enemy
{
	Rectangle rec;
	Vector2 pos;
	Vector2 dir;
	float speed;
	int health;
	bool active;
};

float lerp(float a, float b, float f);

void AddForce(Vector2 dir);