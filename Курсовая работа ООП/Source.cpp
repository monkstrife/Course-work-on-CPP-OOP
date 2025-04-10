#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Object.h"
#include <cstdio>
#include <map>
#include <iostream>

using namespace std;
using namespace sf;

float offsetX = 0;

const int H = 13;
const int W = 200;

char TitleMap[H * W];

String MainMenu[10] =
{
	"1111111111",
	"11lcr11111",
	"1111111111",
	"1lcr11lcr1",
	"1111111111",
	"1123456711",
	"1111111111",
	"1111111111",
	"1111111111",
	"gggggggggg"
};

int main()
{
	map <string, Sound> sound;

	FILE* file;
	file = fopen("map.txt", "r");

	char a;
	int h = 0;
	int w = 0;
	while ((a = fgetc(file)) != EOF)
	{
		if (a == '\n')
		{
			w = 0;
			h++;
			continue;
		}
		TitleMap[h * W + w] = a;
		w++;
	}

	RenderWindow menu(VideoMode(640, 640), "Menu!");

	Texture t_m;
	t_m.loadFromFile("play.png");
	Sprite tile_menu(t_m);

	Music music_menu;
	music_menu.openFromFile("menu.ogg");
	music_menu.setLoop(true);
	music_menu.play();

	while (menu.isOpen())
	{
		Event event;
		while (menu.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				return 0;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			music_menu.pause();
			menu.close();
			break;
		}

		menu.clear(Color::White);

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (MainMenu[i][j] == '1')
				{
					tile_menu.setTextureRect(IntRect(4, 96, 64, 64));
				}
				if (MainMenu[i][j] == '2')
				{
					tile_menu.setTextureRect(IntRect(4, 26, 64, 64));
				}
				if (MainMenu[i][j] == '3')
				{
					tile_menu.setTextureRect(IntRect(74, 26, 64, 64));
				}
				if (MainMenu[i][j] == '4')
				{
					tile_menu.setTextureRect(IntRect(143, 26, 64, 64));
				}
				if (MainMenu[i][j] == '5')
				{
					tile_menu.setTextureRect(IntRect(212, 26, 64, 64));
				}
				if (MainMenu[i][j] == '6')
				{
					tile_menu.setTextureRect(IntRect(281, 26, 64, 64));
				}
				if (MainMenu[i][j] == '7')
				{
					tile_menu.setTextureRect(IntRect(351, 26, 64, 64));
				}
				if (MainMenu[i][j] == 'g')
				{
					tile_menu.setTextureRect(IntRect(74, 96, 64, 64));
				}
				if (MainMenu[i][j] == 'l')
				{
					tile_menu.setTextureRect(IntRect(143, 96, 64, 64));
				}
				if (MainMenu[i][j] == 'c')
				{
					tile_menu.setTextureRect(IntRect(212, 96, 64, 64));
				}
				if (MainMenu[i][j] == 'r')
				{
					tile_menu.setTextureRect(IntRect(281, 96, 64, 64));
				}

				tile_menu.setPosition(j * 64, i * 64);
				menu.draw(tile_menu);
			}
		}

		menu.display();
	}

	int death = 0;
	int win = 0;

	SoundBuffer buffer;
	buffer.loadFromFile("Jump.ogg");
	Sound track(buffer);
	sound["jump"] = track;

	SoundBuffer buffer1;
	buffer1.loadFromFile("death.ogg");
	Sound track1(buffer1);
	sound["death"] = track1;

	SoundBuffer buffer2;
	buffer2.loadFromFile("win.ogg");
	Sound track2(buffer2);
	sound["win"] = track2;

	Music music;
	music.openFromFile("Mario_Theme.ogg");
	music.setLoop(true);
	music.play();

	Texture t1;
	Texture t2;
	Texture t3;
	Texture t4;
	t1.loadFromFile("sprites.png");
	t2.loadFromFile("tileset.png");
	t3.loadFromFile("enemies1.png");
	t4.loadFromFile("tileset.png");

	float currentFrame = 0;

	Player p(t1, 2, 10);
	Enemy* e[3];
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			e[i] = new Enemy(t3, 65, 10);
		}
		else if (i == 1)
		{
			e[i] = new Enemy(t3, 128, 10);
		}
		else
		{
			e[i] = new Enemy(t3, 153, 7);
		}
	}
	Object q(t4, 196 * 16, 10 * 16);

	Sprite ins;
	ins.setTexture(t4);
	ins.setTextureRect(IntRect(349, 78, 16, 16));
	Object* zone[200];
	for (int i = 0; i < 200; i++)
	{
		zone[i] = new Object(t4, i * 16, 12 * 16);
		zone[i]->set_sprite(ins);
	}

	Sprite tile(t2);

	RenderWindow window(VideoMode(640, 192), "Test!"); //окно 200 на 200 getDesktopMode() (640, 192)

	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 800;


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		if (death == 1 || win == 1)
		{
			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				break;
			}
			continue;
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			p.dx = -0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			p.dx = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::Up))
		{
			if (p.get_onGround())
			{
				p.dy = -0.4;
				p.set_onGround(false);
				sound["jump"].play();
			}
		}

		p.update(time);
		for(int i = 0; i<3;i++)
			e[i]->update(time);

		for (int i = 0; i < 200; i++)
		{
			if (p.get_rect().intersects(zone[i]->get_rect()))
			{
				Sprite copy = p.get_sprite();
				copy.setColor(Color::Red);
				p.set_sprite(copy);
				music.pause();
				sound["death"].play();
				death = 1;
			}
		}

		for (int i = 0; i < 3; i++)
		{
			if (p.get_rect().intersects(e[i]->get_rect()))
			{
				if (p.dy > 0)
				{
					e[i]->dx = 0;
					p.dy = -0.5;
					e[i]->set_life(false);
				}
				else
				{
					Sprite copy = p.get_sprite();
					copy.setColor(Color::Red);
					p.set_sprite(copy);
					music.pause();
					sound["death"].play();
					death = 1;
				}
			}
		}

		if (p.get_rect().intersects(q.get_rect()))
		{
			music.pause();
			sound["win"].play();
			win = 1;
		}

		for (int i = 0; i < 3; i++)
		{
			if (e[i]->get_life())
			{
				if (e[i]->direction == 0)
				{
					e[i]->dx = -0.1;
				}
				else
				{
					e[i]->dx = 0.1;
				}
			}
		}

		if (p.get_rect().left > 320 && p.get_rect().left < 2880)offsetX = p.get_rect().left - 320;

		window.clear(Color::White);

		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				if (TitleMap[i * W + j] == 'c')
				{
					tile.setTextureRect(IntRect(298, 95, 16, 16));
				}
				if (TitleMap[i * W + j] == ' ')
				{
					tile.setTextureRect(IntRect(349, 33, 16, 16));
				}
				if (TitleMap[i * W + j] == '1')
				{
					tile.setTextureRect(IntRect(17, 196, 16, 16));
				}
				if (TitleMap[i * W + j] == '2')
				{
					tile.setTextureRect(IntRect(0, 196, 16, 16));
				}
				if (TitleMap[i * W + j] == '3')
				{
					tile.setTextureRect(IntRect(34, 196, 16, 16));
				}
				if (TitleMap[i * W + j] == '4')
				{
					tile.setTextureRect(IntRect(51, 196, 16, 16));
				}
				if (TitleMap[i * W + j] == '5')
				{
					tile.setTextureRect(IntRect(68, 196, 16, 16));
				}
				if (TitleMap[i * W + j] == '6')
				{
					tile.setTextureRect(IntRect(85, 196, 16, 16));
				}
				if (TitleMap[i * W + j] == '7')
				{
					tile.setTextureRect(IntRect(34, 16, 16, 16));
				}
				if (TitleMap[i * W + j] == '8')
				{
					tile.setTextureRect(IntRect(298, 16, 16, 16));
				}
				if (TitleMap[i * W + j] == '9')
				{
					tile.setTextureRect(IntRect(315, 16, 16, 16));
				}
				if (TitleMap[i * W + j] == '0')
				{
					tile.setTextureRect(IntRect(332, 16, 16, 16));
				}
				if (TitleMap[i * W + j] == 'e')
				{
					tile.setTextureRect(IntRect(349, 33, 16, 16));
				}
				if (TitleMap[i * W + j] == 'w')
				{
					tile.setTextureRect(IntRect(298, 78, 16, 16));
				}
				
				tile.setPosition(j * 16 - offsetX, i * 16);
				window.draw(tile);
			}
		}

		for (int i = 0; i < 3; i++)
		{
			window.draw(e[i]->get_sprite());
		}
		window.draw(p.get_sprite());
		window.display();
	}

	for (int i = 0; i < 3; i++)
	{
		delete e[i];
	}

	for (int i = 0; i < 200; i++)
	{
		delete zone[i];
	}
	
	return 0;
}