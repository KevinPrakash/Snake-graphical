#include<iostream>
#include"assetmanager.h"
#include"screen.h"
#include"buttons.h"

int main()
{
	assetmanager a;
	screen main;
	while (main.window.isOpen())
	{
		main.setscreen();
		sf::Event event;
		while (main.window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed)
			{
				main.window.close();
			}
			if ((event.type == sf::Event::EventType::LostFocus)&&(main.getscreenno()==1))
			{
				main.setscreenno(2);
			}
		}
	}
	return 0;
}

