#pragma once
#include<SFML\Graphics.hpp>

class buttons
{
	public:
		buttons();

		void create(sf::Vector2f const& , sf::Vector2i const& , sf::Vector2f const& );

		bool hover(sf::Vector2f const&);

		void  setposition(sf::Vector2f const &);

		sf::RectangleShape getshape();

		sf::RectangleShape getshadow();

		virtual ~buttons();

	private:

		sf::Vector2i tex;
		sf::Vector2f pos;
		sf::Vector2f size;
		sf::RectangleShape button;
		sf::RectangleShape shadow;
};

