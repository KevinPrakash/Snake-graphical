#include "assetmanager.h"
#include<iostream>
#include<assert.h>

assetmanager* assetmanager::sinstance = nullptr;

assetmanager::assetmanager()
{
	assert(sinstance == nullptr);
	sinstance = this;
}

 sf::Texture& assetmanager::gettexture(std::string const&filename)
{
	auto& textmap = sinstance-> m_text;
	auto pairfound = textmap.find(filename);
	if (pairfound != textmap.end())
	{
		return pairfound->second;
	}
	else
	{
		auto& texture = textmap[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}

 assetmanager::~assetmanager()
 {
 }