#pragma once

#include<SFML\Graphics.hpp>
#include<vector>

class snake
{
public:
	snake();

	void update(void);

	bool getstate(void) const;

	void printmap(sf::RenderWindow&);

	int statuscheck(void);

	void makemap(void);

	void setmapno(int);

	void initial(void);

	virtual ~snake();

private:

	int dir(void);
	void genfood(void);
	void shift(void);
	void move(int, int);
	void collision(sf::Vector2i);
	int orient(void);
	sf::Event ev;
	int map[22][22];
	int wallno=0;
	std::vector <sf::Vector3i> snakepos;
	std::vector <bool> type;
	sf::Vector2i food,headpos;
	int direction,prevdir;
	bool foodgen = true,running =true;
	bool pause = false;
	sf::RectangleShape snakerect;
	sf::RectangleShape border;
	sf::RectangleShape foodshape;
	sf::RectangleShape wallrect;
	sf::Time t;
	sf::Clock c;
	int mapno;
	int wallmap[22][22];
};

