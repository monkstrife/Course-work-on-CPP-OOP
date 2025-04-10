#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Object
{
private:
	FloatRect rect;
	Sprite sprite;

public:

	Object(Texture& image, float x, float y)
	{
		sprite.setTexture(image);
		rect = FloatRect(2, 8, 16, 16);
		rect.left = x;
		rect.top = y;
		sprite.setScale(sf::Vector2f(1, 1));
	}

	FloatRect get_rect();
	Sprite get_sprite();

	void set_rect(FloatRect new_rect);
	void set_sprite(Sprite new_sprite);
};