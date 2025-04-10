#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"

using namespace sf;

class Player : public Object
{
private:
	bool onGround;
	float currentFrame;
public:
	float dx, dy;

	Player(Texture& image, float x, float y) : Object(image, x * 16, y * 16)
	{
		onGround = true;
		dx = 0;
		dy = 0;
		currentFrame = 0;
	}

	virtual void update(float time);
	virtual void CollisionX();
	virtual void CollisionY();

	bool get_onGround();
	void set_onGround(bool new_onGround);
};