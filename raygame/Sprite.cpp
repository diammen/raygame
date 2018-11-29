#include "Sprite.h"

void Sprite::translate(Vector2 delta)
{
	r2.y += delta.y * GetFrameTime();
}

void Sprite::draw()
{
	DrawTexturePro(texture, r1, r2, { 0,0 }, rot, WHITE);
}

Sprite Sprite::clone()
{
	return Sprite(this);
}

Sprite::Sprite() {}

Sprite::Sprite(Sprite * other)
{
	texture = (*other).texture;
	pos = (*other).pos;
	rot = (*other).rot;
	r1.x = (*other).r1.x;
	r1.y = (*other).r1.y;
	r1.width = (*other).r1.width;
	r1.height = (*other).r1.height;
	r2.x = rand() % 800;
	r2.y = -(*other).texture.height;
	r2.width = (*other).r2.width;
	r2.height = (*other).r2.height;
}

Sprite::Sprite(const std::string & filename, const std::string _sprType, float scale)
{
	texture = LoadTexture(filename.c_str());
	pos = Vector2{ 0,0 };
	rot = 0;
	r1.x = 0;
	r1.y = 0;
	r1.width = texture.width;
	r1.height = texture.height;
	r2.x = rand() % 800;
	r2.y = -r2.height;
	r2.width = r1.width * scale;
	r2.height = r1.height * scale;
	sprType = _sprType;
}

Sprite::~Sprite() {}