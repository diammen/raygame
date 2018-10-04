#include "raylib.h"
#include "helper.h"

float AddForce(float x, float speed, float force)
{
	return x += speed * force;
}