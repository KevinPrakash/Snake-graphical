#include "screen.h"
#include"buttons.h"
#include"assetmanager.h"
#include"snake.h"
#include<SFML\graphics.hpp>

using namespace sf;


screen::screen()
{
	window.create(VideoMode(768, 638), "Snake");
	window.setFramerateLimit(60);
	window.setPosition(sf::Vector2i(100, 50));
	background.setSize(sf::Vector2f(768, 638));
	background.setTexture(&assetmanager::gettexture("snake.jpg"));
	background.setTextureRect(sf::IntRect(0, 0, 768, 638));
	mapdia.setSize(sf::Vector2f(300, 300));
	mapdia.setPosition(400, 200);
}


void screen::setscreen()
{
	game.setmapno(whichmap);
	switch (screenno)
	{
	case 0:
		screen::menu();
			break;
	case 1:
		screen::games();
		break;
	case 2:
		screen::pause();
		break;
	case 3:
		screen::lose();
		break;
	case 4:
		screen::map();
		break;
	}
}

void screen::menu()
{
	play.create(sf::Vector2f(284, 450), sf::Vector2i(0,0), sf::Vector2f(200, 60));
	exit.create(sf::Vector2f(284, 530), sf::Vector2i(202,0), sf::Vector2f(200, 60));
	sf::Vector2f mousepos(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	window.draw(background);
	if (!play.hover(mousepos))
	{
		window.draw(play.getshadow());
		window.draw(play.getshape());
	}
	else
	{
		window.draw(play.getshape());
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			screenno = 1;
	}

	if (!exit.hover(mousepos))
	{
		window.draw(exit.getshadow());
		window.draw(exit.getshape());
	}
	else
	{
		window.draw(exit.getshape());
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			window.close();
	}
	window.display();
}

void screen::pause()
{
	mapdia.setTexture(&assetmanager::gettexture("layout.png"));
	time += clock.restart();
	resume.create(sf::Vector2f(284, 300), sf::Vector2i(400, 0), sf::Vector2f(200, 60));
	exit.setposition(sf::Vector2f(284, 500));
	layout.create(sf::Vector2f(284, 400), sf::Vector2i(0, 61), sf::Vector2f(200, 60));
	window.clear();
	sf::Vector2f mousepos(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	if (!resume.hover(mousepos))
	{
		window.draw(resume.getshadow());
		window.draw(resume.getshape());
	}
	else
	{
		window.draw(resume.getshape());
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			screenno = 1;
	}
	if (!exit.hover(mousepos))
	{
		window.draw(exit.getshadow());
		window.draw(exit.getshape());
	}
	else
	{
		window.draw(exit.getshape());
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			game.~snake();
			window.close();
		}
	}
	if (time.asMilliseconds()>1000)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			screenno = 1;
		}
	if (!layout.hover(mousepos))
	{
		window.draw(layout.getshadow());
		window.draw(layout.getshape());
	}
	else
	{
		window.draw(layout.getshape());
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			screenno = 4;
		}
	}
	window.display();
}

void screen::games()
{
	mapdia.setTexture(&assetmanager::gettexture("layout.png"));
	time += clock.restart();
	if (time.asMilliseconds()>100)
	{
		if (game.getstate())
		{
			game.update();
			game.printmap(window);
			screenno=game.statuscheck();
			if (screenno == 3)
			{
				time -= time;
				while (time.asMilliseconds() > 1000)
					time += clock.restart();
			}
		}
		time -= time;
	}
}

void screen::lose(void)
{
	mapdia.setTexture(&assetmanager::gettexture("layout.png"));
	time += clock.restart();
	while (time.asMilliseconds() < 500)
	{
		time += clock.restart();
	}
	window.clear();
	sf::Vector2f mousepos(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	play.setposition(sf::Vector2f(284, 300));
	exit.setposition(sf::Vector2f(284, 400));
	if (!play.hover(mousepos))
	{
		window.draw(play.getshadow());
		window.draw(play.getshape());
	}
	else
	{
		window.draw(play.getshape());
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			game.initial();
			screenno = 1;
		}
	}

	if (!exit.hover(mousepos))
	{
		window.draw(exit.getshadow());
		window.draw(exit.getshape());
	}
	else
	{
		window.draw(exit.getshape());
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			window.close();
	}
	window.display();
}

void screen::map(void)
{
	mapdia.setTexture(&assetmanager::gettexture("layout.png"));
	wallno1.create(sf::Vector2f(100, 150), sf::Vector2i(201, 61), sf::Vector2f(200, 60));
	wallno2.create(sf::Vector2f(100, 250), sf::Vector2i(401, 61), sf::Vector2f(200, 60));
	back.create(sf::Vector2f(100, 350), sf::Vector2i(0, 122), sf::Vector2f(200, 60));
	window.clear();
	sf::Vector2f mousepos(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	if (!wallno1.hover(mousepos))
	{
		window.draw(wallno1.getshadow());
		window.draw(wallno1.getshape());
		mapdia.setTextureRect(sf::IntRect(0, 0, 300, 300));
		window.draw(mapdia);
	}
	else
	{
		window.draw(wallno1.getshape());
		mapdia.setTextureRect(sf::IntRect(0, 0, 300, 300));
		window.draw(mapdia);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			game.setmapno(0);
			game.makemap();
			game.initial();
			screenno = 2;
		}
	}
	if (!wallno2.hover(mousepos))
	{
		window.draw(wallno2.getshadow());
		window.draw(wallno2.getshape());
		mapdia.setTextureRect(sf::IntRect(300, 0, 300, 300));
		window.draw(mapdia);
	}
	else
	{
		window.draw(wallno2.getshape());
		mapdia.setTextureRect(sf::IntRect(300, 0, 300, 300));
		window.draw(mapdia);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			game.setmapno(1);
			game.makemap();
			game.initial();
			screenno = 2;
		}
	}
	if (!back.hover(mousepos))
	{
		window.draw(back.getshadow());
		window.draw(back.getshape());
	}
	else
	{
		window.draw(back.getshape());
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			screenno = 2;
		}
	}
	window.display();
}
int screen::getscreenno(void) const
{
	return screenno;
}
void screen::setscreenno(int a)
{
	screenno = a;
}

screen::~screen()
{
}