#pragma once

#include <SFML/Graphics.hpp>

#define MAX_NUMBER_OF_ITEMS 3

class MainMenu
{
private:

	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];



public:
	MainMenu(float width, float height);
	~MainMenu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int getPressedItem()
	{
		return selectedItemIndex;
	}


};

