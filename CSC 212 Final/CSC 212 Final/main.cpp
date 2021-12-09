#include <iostream>
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
//#include "Textbox.h"

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 800), "CSC 212 Final Project");
    

    MainMenu menu(window.getSize().x, window.getSize().y);
 



    //Main Loop:
    while (window.isOpen()) {

        sf::Event Event;

        //Event Loop:
        while (window.pollEvent(Event)) 
        {
            switch (Event.type) 
            {
            case sf::Event::KeyReleased:
                switch (Event.key.code)
                {
                case sf::Keyboard::Up:
                    menu.MoveUp();
                    break;

                case sf::Keyboard::Down:
                    menu.MoveDown();
                    break;

                case sf::Keyboard::Return:
                    switch (menu.getPressedItem())
                    {
                    case 0:
                        std::cout << "Play is pressed" << std::endl;
                        break;
                    case 1:
                        std::cout << "Play is pressed" << std::endl;
                        break;
                    case 2:
                        window.close();
                        break;
                    }
                }
                break;
            case sf::Event::Closed:
                window.close();
                break;
            }
        }
        window.clear();
        menu.draw(window);
        window.display();
    }
}