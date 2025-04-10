#include "Object.h"

FloatRect Object::get_rect()
{
	return rect;
}


Sprite Object::get_sprite()
{
	return sprite;
}

void Object::set_rect(FloatRect new_rect)
{
	rect = new_rect;
}

void Object::set_sprite(Sprite new_sprite)
{
	sprite = new_sprite;
}