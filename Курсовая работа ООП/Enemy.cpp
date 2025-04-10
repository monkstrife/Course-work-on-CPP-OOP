#include "Enemy.h"

extern float offsetX;

extern char TitleMap[];

void Enemy::update(float time)
{
	FloatRect rect = get_rect();
	Sprite sprite = get_sprite();

	rect.left += dx * time;
	set_rect(rect);

	CollisionX();
	rect = get_rect();

	currentFrame += 0.005 * time;
	if (currentFrame > 2)
	{
		currentFrame -= 2;
	}

	if (dx < 0)
	{
		sprite.setTextureRect(IntRect(11 + 24 * int(currentFrame), 18, 16, 16));
	}
	else if (dx > 0)
	{
		sprite.setTextureRect(IntRect(11 + 24 * int(currentFrame) + 16, 18, -16, 16));
	}

	if (!life)
	{
		sprite.setTextureRect(IntRect(59, 82, 16, 16));
	}

	sprite.setPosition(rect.left - offsetX, rect.top);
	set_sprite(sprite);
}

void Enemy::CollisionX()
{
	FloatRect rect = get_rect();
	for (int i = rect.top / 16; i < (rect.top + 16) / 16; i++)
	{
		for (int j = rect.left / 16; j < (rect.left + 16) / 16; j++)
		{

			if (((int)TitleMap[i * 200 + j] - 48 >= 1 && (int)TitleMap[i * 200 + j] - 48 <= 7) || TitleMap[i * 200 + j] == 'e')
			{
				if (dx > 0)
				{
					rect.left = j * 16 - 16;
					direction = 0;
				}
				if (dx < 0)
				{
					rect.left = j * 16 + 16;
					direction = 1;
				}
			}
		}
	}
	set_rect(rect);
}

bool Enemy::get_life()
{
	return life;
}

void Enemy::set_life(bool new_life)
{
	life = new_life;
}