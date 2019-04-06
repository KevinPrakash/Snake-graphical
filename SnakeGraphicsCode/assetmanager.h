#pragma once
#include<SFML\Graphics.hpp>
#include<map>

using namespace sf;

class assetmanager
{
public:
	assetmanager();

	virtual ~assetmanager();

	static sf::Texture& gettexture(std::string const&filename);

private:

	std::map<std::string, sf::Texture> m_text;

	 static assetmanager* sinstance;
};

