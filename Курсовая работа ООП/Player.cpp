#include "Player.h"

int ground = 192;

using namespace sf;

extern char TitleMap[];

extern float offsetX;

void Player::update(float time)
{
	FloatRect rect = get_rect();
	Sprite sprite = get_sprite();

	rect.left += dx * time;
	set_rect(rect);

	CollisionX();
	rect = get_rect();

	if (!onGround)
	{
		dy = dy + 0.001 * time;
	}

	rect.top += dy * time;
	set_rect(rect);
	onGround = false;

	CollisionY();
	rect = get_rect();

	if (rect.top > ground)
	{
		rect.top = ground;
		set_rect(rect);
		dy = 0;
		onGround = true;
	}

	currentFrame += 0.005 * time;
	if (currentFrame > 3)
	{
		currentFrame -= 3;
	}
	if (dx < 0)
	{
		sprite.setTextureRect(IntRect(20 + 18 * int(currentFrame) + 15, 8, -15, 16));
	}
	else if (dx > 0)
	{
		sprite.setTextureRect(IntRect(20 + 18 * int(currentFrame), 8, 15, 16));
	}
	else
	{
		sprite.setTextureRect(IntRect(2, 8, 12, 16));
	}

	sprite.setPosition(rect.left - offsetX, rect.top);
	set_sprite(sprite);
	
	dx = 0;
}

void Player::CollisionX()
{
	FloatRect rect = get_rect();
	for (int i = rect.top/16; i < (rect.top + 16)/16; i++)
	{
		for (int j = rect.left/16; j < (rect.left + 16)/16; j++)
		{
			
			if (((int)TitleMap[i * 200 + j] - 48 >= 1 && (int)TitleMap[i * 200 + j] - 48 <= 7) || TitleMap[i * 200 + j] == 'e')
			{
				if (dx > 0)
				{
					rect.left = j * 16 - 16;
				}
				if (dx < 0)
				{
					rect.left = j * 16 + 16;
				}
			}

			if (TitleMap[i * 200 + j] == 'c')
			{
				TitleMap[i * 200 + j] = ' ';
			}
		}
	}
	set_rect(rect);
}

void Player::CollisionY()
{
	FloatRect rect = get_rect();
	for (int i = rect.top / 16; i < (rect.top + 16) / 16; i++)
	{
		for (int j = rect.left / 16; j < (rect.left + 16) / 16; j++)
		{
			if (((int)TitleMap[i * 200 + j] - 48 >= 1 && (int)TitleMap[i * 200 + j] - 48 <= 7) || TitleMap[i * 200 + j] == 'e')
			{
				if (dy > 0)
				{
					rect.top = i * 16 - 16;
					dy = 0;
					onGround = true;
				}
				if (dy < 0)
				{
					rect.top = i * 16 + 16;
					dy = 0;
				}
			}

			if (TitleMap[i * 200 + j] == 'c')
			{
				TitleMap[i * 200 + j] = ' ';
			}
		}
	}
	set_rect(rect);
}

bool Player::get_onGround()
{
	return onGround;
}

void Player::set_onGround(bool new_onGround)
{
	onGround = new_onGround;
}