#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"

using namespace sf;

class Enemy : public Object
{
private:
	bool life;
	float currentFrame;
public:
	float dx, dy;
	int direction = 0;

	Enemy(Texture& image, float x, float y) : Object(image, x * 16, y * 16)
	{
		life = true;
		dx = 0;
		dy = 0;
		currentFrame = 0;
	}

	virtual void update(float time);
	virtual void CollisionX();

	bool get_life();
	void set_life(bool new_life);
};