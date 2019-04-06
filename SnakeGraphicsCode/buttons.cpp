#include "buttons.h"
#include<SFML\Graphics.hpp>
#include<iostream>
#include"assetmanager.h"


buttons::buttons()
{
	button.setTexture(&assetmanager::gettexture("buttons.jpg"));
}

 void buttons::create(sf::Vector2f const& posa, sf::Vector2i const& texture, sf::Vector2f const& sizea)
{
	size = sizea;
	pos = posa;
	tex = texture;
	button.setSize(size);
	button.setPosition(pos);
	button.setTextureRect(sf::IntRect(tex.x,tex.y,200,60));
}


bool buttons::hover(sf::Vector2f const& mousepos)
{
	sf::RectangleShape cursor(sf::Vector2f(1,1));
	cursor.setPosition(mousepos);
	if (cursor.getGlobalBounds().intersects(button.getGlobalBounds()))
		return true;
	return false;
}

sf::RectangleShape buttons::getshape()
{
	return button;
}

sf::RectangleShape buttons::getshadow()
{
	sf::Vector2f sizeshad(size.x + 5.0f, size.y + 5.0f);
	sf::Vector2f posshad(pos.x - 2.5f, pos.y - 2.5f);
	shadow.setSize(sizeshad);
	shadow.setPosition(posshad);
	shadow.setFillColor(sf::Color(143,143,143,200));
	return shadow;

}

void buttons::setposition(sf::Vector2f const& posa)
{
	pos = posa;
	button.setPosition(pos);
}
buttons::~buttons()
{
}
