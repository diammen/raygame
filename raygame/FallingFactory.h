#pragma once
#include "raylib.h"
#include "Sprite.h"
#include <random>
#include <chrono>
#include <vector>
using std::vector;

class FallingFactory
{
private:

	FallingFactory();
	FallingFactory(FallingFactory const&);
	void operator=(FallingFactory const&) {}
public:
	Sprite * spriteMasters;
	size_t spriteCount;

	Sprite * getRandom();// returns a random sprite from all sprites loaded
	Sprite * getFromType(const std::string & _sprType);// Returns a random sprite from this type of sprites.
	static FallingFactory& GetInstance();


	~FallingFactory();
};