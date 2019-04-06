#include "snake.h"
#include"assetmanager.h"
#include<vector>
#include<cstdlib>
#include<ctime>
#include<iostream>


snake::snake()
{
	direction = 0, food.x = 0, food.y = 0,prevdir=0,mapno=0;
	snakepos.push_back(sf::Vector3i(11,9,1));
	snakepos.push_back(sf::Vector3i(11, 10,1));
	snakepos.push_back(sf::Vector3i(11, 11,1));
	type.push_back(false);
	type.push_back(false);
	type.push_back(false);
	makemap();
	snakerect.setTexture(&assetmanager::gettexture("skin.png"));
	snakerect.setSize(sf::Vector2f(28, 28));
	border.setSize(sf::Vector2f(616, 616));
	border.setPosition(10, 10);
	border.setOutlineThickness(6);
	border.setTexture(&assetmanager::gettexture("grass.jpg"));
	border.setOutlineColor(sf::Color::Blue);
	border.setFillColor(sf::Color(236,145,83,150));
    foodshape.setSize(sf::Vector2f(28, 28));
	foodshape.setTexture(&assetmanager::gettexture("skin.png"));
	foodshape.setTextureRect(sf::IntRect(448, 0, 112, 112));
	snakerect.setOrigin(sf::Vector2f(14, 14));
	wallrect.setSize(sf::Vector2f(28, 28));
	wallrect.setOrigin(sf::Vector2f(14, 14));
	wallrect.setTexture(&assetmanager::gettexture("skin.png"));
	wallrect.setTextureRect(sf::IntRect(0, 112, 112, 112));
}

int snake::dir(void)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		if (direction != 2)
		{
			prevdir = direction;
			direction = 0;
			return 0;
		}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		if (direction != 3)
		{
			prevdir = direction;
			direction = 1;
			return 0;
		}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		if (direction != 0)
		{
			prevdir = direction;
			direction = 2;
			return 0;
		}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		if (direction != 1)
		{
			prevdir = direction;
			direction = 3;
			return 0;
		}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) && (t.asMilliseconds() > 1000))
	{
		pause = true;
		t -= t;
	}
	return 0;
}
void snake::update()
{
	if (foodgen)
		genfood();
	dir();
	t += c.restart();
	switch (direction)
	{
	case 0:move(0, -1);
		break;
	case 1:move(-1, 0);
		break;
	case 2:move(0, 1);
		break;
	case 3:move(1, 0);
		break;
	}
	if(running==true)
		shift();
}

void snake::move(int x,int y)
{
	headpos.x = snakepos[0].x + x;
	headpos.y = snakepos[0].y + y;
	collision(headpos);
}

void snake::collision(sf::Vector2i head)
{
	if (head.x > 21)
		headpos.x = 0;
	if (head.x < 0)
		headpos.x = 21;
	if (head.y > 21)
		headpos.y = 0;
	if (head.y < 0)
		headpos.y = 21;
	if (headpos == food)
	{
		foodgen = true;
		snakepos.push_back(sf::Vector3i(0,0,0));
		type.push_back(false);
	}
	if (map[headpos.x][headpos.y] == 2)
		running = false;
}

void snake::shift(void)
{
	for (unsigned int i = 0; i < snakepos.size(); i++)
	{
		if (foodgen == true && (i == snakepos.size()) - 1)
			break;
		map[snakepos[i].x][snakepos[i].y] = 0;
	}
	for (unsigned int i = snakepos.size()-1; i > 0; i--)
	{
		snakepos[i]= snakepos[i - 1];
		type[i] = type[i - 1];
	}
	for (unsigned int j = 1; j<snakepos.size(); j++)
		if ((snakepos[j].x ==headpos.x)&&(snakepos[j].y==headpos.y))
			running = false;
	snakepos[0].x = headpos.x;
	snakepos[0].y = headpos.y;
	snakepos[0].z = direction;
	snakepos[1].z = orient();
	for (unsigned int i = 0; i < snakepos.size(); i++)
	{
		map[snakepos[i].x][snakepos[i].y] = 1;
	}
}

void snake::genfood()
{
	int random,num=0;
	srand((unsigned) time(0));
	random =(rand()*rand())% (484 - snakepos.size() -wallno);
	for (int i = 0; i<22; i++)
	{
		for (int j = 0; j<22; j++)
		{

			if (map[i][j] == 0)
			{
				num++;
				if (num == random)
				{
					food.x = j;
					food.y = i;
					num++;
					break;
				}
			}
		}
	}
	foodgen = false;
}

void snake::printmap(sf::RenderWindow& window)
{
	window.clear();
	window.draw(border);
	foodshape.setPosition((food.x * 28) + 10, (food.y * 28) + 10);
	window.draw(foodshape);
	for (unsigned int i = 1; i < snakepos.size() - 1; i++)
	{
		if (!type[i])
			snakerect.setTextureRect(sf::IntRect(112, 0, 112, 112));
		else
			snakerect.setTextureRect(sf::IntRect(336, 0, 112, 112));
		snakerect.setPosition((snakepos[i].x * 28) + 24, (snakepos[i].y * 28) + 24);
		snakerect.rotate(90.0f*snakepos[i].z);
		window.draw(snakerect);
		snakerect.rotate(-snakerect.getRotation());
	}
	int z;
	switch (snakepos[snakepos.size() - 1].z)
	{
	case -1:
		z = 2;
		break;
	case 6:
		z = 1;
		break;
	case 5:
		z = 0;
		break;
	case 4:
		z = -1;
		break;
	default:
		z = snakepos[snakepos.size() - 1].z;
	}
	snakerect.rotate(90.f*z);
	snakerect.setTextureRect(sf::IntRect(224, 0, 112, 112));
	snakerect.setPosition((snakepos[snakepos.size()-1].x * 28) + 24, (snakepos[snakepos.size()-1].y * 28) + 24);
	window.draw(snakerect);
	snakerect.rotate(-snakerect.getRotation());
	snakerect.rotate(-90.f*(snakepos[0].z - 1));
	snakerect.setTextureRect(sf::IntRect(0, 0, 112, 112));
	snakerect.setPosition((snakepos[0].x * 28) + 24, (snakepos[0].y * 28) + 24);
	window.draw(snakerect);
	snakerect.rotate(-snakerect.getRotation());
	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 22; j++)
		{
			if (map[i][j] == 2)
			{
				wallrect.setPosition((i * 28)+24, (j * 28)+24);
				window.draw(wallrect);
			}
		}
	}

	window.display();
	prevdir = direction;
}

bool snake::getstate(void) const
{
	return running;
}

int snake::statuscheck(void)
{
	if (pause)
	{
		pause = false;
		return 2;
	}
	if (!running)
		return 3;
	return 1;
}
void snake::initial(void)
{
	direction = 0, food.x = 0, food.y = 0, prevdir = 0;
	pause = false, running = true, foodgen = true;
	for (unsigned int j = snakepos.size() - 1; j > 0; j--)
		snakepos.pop_back();
	snakepos.insert(snakepos.begin(),sf::Vector3i(11, 9, 2));
	snakepos.push_back(sf::Vector3i(11, 10, 2));
	snakepos.push_back(sf::Vector3i(11, 11, 2));
	for (int i = 0; i < 22; i++)
		for (int j = 0; j < 22; j++)
			map[i][j] = 0;
	for (unsigned int j = type.size() - 1; j > 0; j--)
		type.pop_back();
	type.push_back(false);
	type.push_back(false);
	type.push_back(false);
	makemap();
}

int snake::orient(void)
{
	if(prevdir!=direction)
	switch (prevdir)
	{
	case 0:
		switch (direction)
		{
		case 1:
			type[1] = true;
			return 0;
		case 3:
			type[1] = true;
			return -1;
		}
	case 1:
		switch (direction)
		{
		case 0:
			type[1] = true;
			return 6;
		case 2:
			type[1] = true;
			return 3;
		}
	case 2:
		switch (direction)
		{
		case 1:
			type[1] = true;
			return 5;
		case 3:
			type[1] = true;
			return 2;
		}
	case 3:
		switch (direction)
		{
		case 2:
			type[1] = true;
			return 4;
		case 0:
			type[1] = true;
			return 1;
		}
	}
	else
		switch (direction)
		{
		case 0:
			type[1] = false;
			return 1;
		case 1:
			type[1] = false;
			return 0;
		case 3:
			type[1] = false;
			return 2;
		case 2:
			type[1] = false;
			return 3;
		}
	return 1;

}

void snake::makemap(void)
{

	switch (mapno)
	{
	case 1:
		for (int i = 0;i < 22; i++)
		{
			wallmap[0][i] = 2;
			wallmap[i][0] = 2;
			wallmap[21][i] = 2;
			wallmap[i][21] = 2;
		}
	 //wallmap[22][22] = {
		//				{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
		//				{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
		//			    { 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
		// 			    { 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
		//   		    { 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
		//			    { 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
		//			    { 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
		//			    { 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
		//			    { 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
		//			    { 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
		//			    { 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
		//			    { 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
		//			    { 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
		//			    { 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
		//			    { 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
		//			    { 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
		//			    { 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
		//			    { 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
		//			    { 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
		//			    { 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
		//			    { 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
		//			    { 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 }
		//		};
	 for (int i = 0; i < 22; i++)
		 for (int j = 0; j < 22; j++)
			 map[i][j] = wallmap[i][j];
	 wallno = 86;
		break;
	case 0:
		for (int i = 0; i < 22; i++)
			for (int j = 0; j < 22; j++)
				map[i][j] = 0;
		break;
	}

}

void snake::setmapno(int a)
{
	mapno = a;
}
snake::~snake()
{
}
