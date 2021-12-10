#include "MainMenu.h"
#include <iostream>



MainMenu::MainMenu(float width, float height)
{
	if (!font.loadFromFile("font.ttf")) {
		//handle error
	}
	//Menu option 1 for Rabin-Karp
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Rabin-Karp Visualization");
	menu[0].setPosition(sf::Vector2f(width / 6, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	//Menu option 2 for Boyer-Moore
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Boyer-Moore Visualization");
	menu[1].setPosition(sf::Vector2f(width / 6, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	//Menu option 3 for Exit
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(width / 6, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

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

	//
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
	else {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex = MAX_NUMBER_OF_ITEMS - 1;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void MainMenu::MoveDown() {

	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
	else {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex = 0;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}