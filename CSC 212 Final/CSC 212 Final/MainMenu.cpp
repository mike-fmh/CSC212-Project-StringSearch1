#include "MainMenu.h"
#include <iostream>



MainMenu::MainMenu(float width, float height)
{
	if(!font.loadFromFile("arial.ttf")) {
		//handle error
	}
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Rabin-karp");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Boyre Morre");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	selectedItemIndex = 0;
}

MainMenu::~MainMenu()
{
}

void MainMenu::draw(sf::RenderWindow& window)
{

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void MainMenu::MoveUp() {

	if (selectedItemIndex - 1 >= 0) 
	{
		std::cout << selectedItemIndex << std::endl;
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
	std::cout << selectedItemIndex << std::endl;
}

void MainMenu::MoveDown() {

	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		std::cout << selectedItemIndex << std::endl;
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
	std::cout << selectedItemIndex << std::endl;
}