#include "FallingFactory.h"

FallingFactory& FallingFactory::GetInstance()
{
	static FallingFactory instance;
	return instance;
}

FallingFactory::FallingFactory()
{
	spriteCount = 4;
	spriteMasters = new Sprite[spriteCount];
	spriteMasters[0] = *(new Sprite("ballshade_1.png", "ball", 1));
	spriteMasters[1] = *(new Sprite("ballshade_2.png", "ball", 1));
	spriteMasters[2] = *(new Sprite("ballshade_3.png", "ball", 1));
	spriteMasters[3] = *(new Sprite("ballshade_4.png", "ball", 1));
}

FallingFactory::~FallingFactory()
{

}

Sprite * FallingFactory::getRandom()
{
	return &(spriteMasters[rand() % spriteCount]);
}

Sprite * FallingFactory::getFromType(const std::string & _sprType)
{
	vector<Sprite> newArr;
	for (int i = 0; i < spriteCount; ++i)
	{
		if (spriteMasters[i].sprType == _sprType)
		{
			newArr.push_back(spriteMasters[i]);
		}
	}
	return &(newArr[rand() % newArr.size()]);
}