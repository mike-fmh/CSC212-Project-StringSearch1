#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
//#include "Textbox.h"
using namespace std;

void r_screen(sf::RenderWindow* window, std::string* query, std::string* text, std::vector<sf::Texture>* letters, std::vector<sf::Sprite>* letterSprites, int* framnum);
void badChar(vector<int>* bChars, string* query);
void rabin(sf::RenderWindow* window, std::string* query, std::string* text, std::vector<sf::Texture>* letters, std::vector<sf::Sprite>* letterSprites);
void BM(sf::RenderWindow* window, std::string* query, std::string* text, std::vector<sf::Texture>* letters, std::vector<sf::Sprite>* letterSprites);
void main_menu();

int main() {
    main_menu();
}

void main_menu() {
    std::string query, text;
    //creates a window
    sf::RenderWindow window(sf::VideoMode(1000, 800), "CSC 212 Final Project");

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
                    if (menu.getPressedItem() == 0) {
                        std::cout << "Play is pressed" << std::endl;
                        query = "hello";
                        std::vector<sf::Texture> letters;
                        std::vector<sf::Sprite> Lsprites;
                        rabin(&window, &query, &text, &letters, &Lsprites);
                       
                    }
                    else if (menu.getPressedItem() == 1) {
                        std::cout << "Play is pressed" << std::endl;
                        query = "hello";
                        std::vector<sf::Texture> letters;
                        std::vector<sf::Sprite> Lsprites;
                        BM(&window, &query, &text, &letters, &Lsprites);
                        break;
                    }
                    else if (menu.getPressedItem() == 2) {
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
        //window.clear(sf::Color::White);
        window.clear();

        menu.draw(window);
        window.display();
    }
}

void r_screen(sf::RenderWindow* window, std::string* query, std::string* text, std::vector<sf::Texture>* letters, std::vector<sf::Sprite>* letterSprites, int* framnum) {
    // reset the screen for the algorithms
    (*framnum)++;
    cout << "\nframe #" << (*framnum);
    window->clear(sf::Color::White);
    sf::Font f;
    f.loadFromFile("font.ttf");
    sf::Text t("Text: " + (*text) + "      Query: " + (*query), f);
    t.setPosition(50, 50);
    t.setFillColor(sf::Color::Black);
    window->draw(t);

    (*letters) = {};
    (*letterSprites) = {};
    
    for (int i = 0; i < text->size(); i++) {
        sf::Texture newTexture;
        letters->push_back(newTexture);
        cout << tolower((*text)[i]) << " ";
        (*letters)[i].loadFromFile(std::to_string(std::tolower((*text)[i])) + ".png");
        letterSprites->push_back(sf::Sprite((*letters)[i]));
        (*letterSprites)[i].setPosition(40 + i * 70, 400);

        window->draw((*letterSprites)[i]);
        
    }
}


void rabin(sf::RenderWindow* window, std::string* query, std::string* text, std::vector<sf::Texture>* letters, std::vector<sf::Sprite>* letterSprites) {
    (*query) = "world";
    (*text) = "hello, world";

    window->setFramerateLimit(1); // wait 1 sec between updating screens

    int framenum = 0;

    r_screen(window, query, text, letters, letterSprites, &framenum);
    window->display();

    vector<int> matchIndices;
    int prime = 101; // any prime number
    int numLetters = 256; // length of alphabet

    int h = 1;
    for (int i = 0; i < query->size() - 1; i++) {
        h = (h * numLetters) % prime;

    }

    int patternHash = 0;
    int textHash = 0;
    for (int i = 0; i < query->size(); i++) {
        patternHash = (numLetters * patternHash + int(query->at(i))) % prime;
        textHash = (numLetters * textHash + int(text->at(i))) % prime;
    }

    for (int i = 0; i < (text->size() - query->size() + 1); i++) {
        cout << " " << i << std::endl;
        r_screen(window, query, text, letters, letterSprites, &framenum);
        for (int n = 0; n < query->size(); n++) {
            (*letterSprites)[n + i].setColor(sf::Color::Yellow);
            window->draw((*letterSprites)[i + n]);
        }
        window->display();
        if (patternHash == textHash) {

            int j; // initialize outside for loop so the next if statement can use j
            for (j = 0; j < query->size(); j++) {
                r_screen(window, query, text, letters, letterSprites, &framenum);
                for (int n = 0; n < query->size(); n++) {
                    (*letterSprites)[n + i].setColor(sf::Color::Yellow);
                    window->draw((*letterSprites)[i + n]);
                }
                (*letterSprites)[j + i].setColor(sf::Color::Red);
                window->draw((*letterSprites)[i + j]);
                window->display();

                if (text->at(i + j) != query->at(j)) {

                    break;
                }
            }
            if (j == query->size()) {
                matchIndices.push_back(i);
            }
        }
        if (i < text->size() - query->size()) {
            textHash = (numLetters * (textHash - int(text->at(i)) * h) + int(text->at(i + query->size()))) % prime;
            if (textHash < 0) {
                textHash += prime;
            }
        }
    }

    cout << "\n>>\"";
    for (int i = 0; i < text->size(); i++) {
        for (int n = 0; n < matchIndices.size(); n++) {
            if (i == matchIndices[n]) {
                cout << "[";
            }
            if (i == matchIndices[n] + query->size()) {
                cout << "]";
            }
        }
        cout << (*text)[i];
    }
    if (matchIndices[matchIndices.size() - 1] + query->size() == text->size()) {
        // if there needs to be a "]" at the end
        cout << "]";
    }
    cout << "\"\n\n";


    r_screen(window, query, text, letters, letterSprites, &framenum);
    for (int i = 0; i < letterSprites->size(); i++) {

        for (int n = 0; n < matchIndices.size(); n++) {
            if (i >= matchIndices[n] && i < matchIndices[n] + query->size()) {
                (*letterSprites)[i].setColor(sf::Color::Red);
                window->draw((*letterSprites)[i]);
            }
        }
    }
    window->display();


    bool s = 1;
    // wait for esc press
    while (s) {
        sf::Event Event;
        MainMenu menu(window->getSize().x, window->getSize().y);
        //Event Loop:
        while (window->pollEvent(Event))
        {
            switch (Event.type)
            {
            case sf::Event::KeyReleased:
                switch (Event.key.code)
                {
                case sf::Keyboard::Escape:
                    s = 0;
                }
            }
        }
    }
    window->close();
    main_menu();
}


void badChar(vector<int>* bChars, string* query) {
    int CHARNUM = 256; // length of alphabet
    for (int i = 0; i < CHARNUM; i++) {
        bChars->push_back(-1);
    }
    for (int i = 0; i < query->size(); i++) {
        bChars->at(int(query->at(i))) = i;
    }
}

void BM(sf::RenderWindow* window, std::string* query, std::string* text, std::vector<sf::Texture>* letters, std::vector<sf::Sprite>* letterSprites) {
    window->setFramerateLimit(1); // wait 1 sec between updating screens
    (*query) = "world";
    (*text) = "hello, world";
    int framenum = 0;

    r_screen(window, query, text, letters, letterSprites, &framenum);
    window->display();
    


    vector<int> bChars, matches;
    badChar(&bChars, query);
    int shift = 0;
    while (shift <= text->size() - query->size()) {
        int j = query->size() - 1;

        r_screen(window, query, text, letters, letterSprites, &framenum);
        for (int n = 0; n < query->size(); n++) {
            if (n == query->size() - 1) {
                (*letterSprites)[n + shift].setColor(sf::Color::Green);
            }
            else {
                (*letterSprites)[n + shift].setColor(sf::Color::Yellow);
            }
            window->draw((*letterSprites)[shift + n]);
        }
        window->display();

        while ((j >= 0) && (text->at(shift + j) == query->at(j))) {
            j--;
        }
        if (j < 0) {
            matches.push_back(shift);
            if (shift + query->size() < text->size()) {
                shift += query->size() - bChars.at(int(text->at(shift + query->size())));
            }
            else {
                shift++;
            }
        }
        else {
            // change shift by n if n>1, otherwise change it by 1
            int n = j - bChars.at(int(text->at(shift + j)));
            if (n > 1) {
                shift += n;
            }
            else {
                shift++;
            }
        }
    }

    r_screen(window, query, text, letters, letterSprites, &framenum);
    for (int i = 0; i < letterSprites->size(); i++) {

        for (int n = 0; n < matches.size(); n++) {
            if (i >= matches[n] && i < matches[n] + query->size()) {
                (*letterSprites)[i].setColor(sf::Color::Red);
                window->draw((*letterSprites)[i]);
            }
        }
    }
    window->display();






    bool s = 1;
    // wait for esc press
    while (s) {
        sf::Event Event;
        MainMenu menu(window->getSize().x, window->getSize().y);
        //Event Loop:
        while (window->pollEvent(Event))
        {
            switch (Event.type)
            {
            case sf::Event::KeyReleased:
                switch (Event.key.code)
                {
                case sf::Keyboard::Escape:
                    s = 0;
                }
            }
        }
    }
    window->close();
    main_menu();

}