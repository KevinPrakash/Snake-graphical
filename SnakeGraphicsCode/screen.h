#pragma once
#include<SFML\Graphics.hpp>
#include<iostream>
#include"buttons.h"
#include"snake.h"

using namespace sf;


class screen
{
public:

	RenderWindow window;

	screen();

	void menu(void);


	void pause(void);

	void games(void);

	void setscreen(void);

	void lose(void);

	void map(void);

	bool run = true;

	virtual ~screen();

	void setscreenno(int);

	int getscreenno(void) const;

	

private:

	int screenno = 0;
	buttons play, exit,resume,wallno1,wallno2,back,layout;
	sf::RectangleShape background;
	sf::Clock clock;
	sf::Time time;
	snake game;
	int whichmap = 0;
	sf::RectangleShape mapdia;
};

