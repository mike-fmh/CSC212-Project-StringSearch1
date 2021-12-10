#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MainMenu.h"

using namespace std;

void r_screen(sf::RenderWindow* window, std::string* query, std::string* text, std::vector<sf::Texture>* letters, std::vector<sf::Sprite>* letterSprites);
void badChar(vector<int>* bChars, string* query);
void rabin(sf::RenderWindow* window, std::string* query, std::string* text, std::vector<sf::Texture>* letters, std::vector<sf::Sprite>* letterSprites, sf::Music* music);
void BM(sf::RenderWindow* window, std::string* query, std::string* text, std::vector<sf::Texture>* letters, std::vector<sf::Sprite>* letterSprites, sf::Music* music);
int main_menu(sf::Music* music);

int main() {

    //Added music for fun!
    sf::Music music;

    if (!music.openFromFile("awesomeness.wav"))
    {
        std::cout << "ERROR" << std::endl;
    }

    music.play();
    main_menu(&music);
}

int main_menu(sf::Music* music) {

    std::string query, text;
    //creates a window
    sf::RenderWindow window(sf::VideoMode(500, 500), "CSC 212 Final Project");

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

                case sf::Keyboard::S:
                    music->pause();
                    break;
                case sf::Keyboard::P:
                    music->play();
                    break;
                case sf::Keyboard::Up:
                    menu.MoveUp();
                    break;

                case sf::Keyboard::Down:
                    menu.MoveDown();
                    break;

                case sf::Keyboard::Escape:
                    window.close();
                    return 0;

                case sf::Keyboard::Return:
                    if (menu.getPressedItem() == 0) {
                        // if rabin-karp is selected
                        window.close();
                        query = "world";
                        text = "hello world";
                        std::vector<sf::Texture> letters;
                        std::vector<sf::Sprite> Lsprites;
                        sf::RenderWindow algo_win(sf::VideoMode(840, 500), "Rabin-Karp Visualization");
                        rabin(&algo_win, &query, &text, &letters, &Lsprites, music);
                        break;
                    }
                    else if (menu.getPressedItem() == 1) {
                        // if boyer-moore is selected
                        window.close();
                        query = "world";
                        text = "hello world";
                        std::vector<sf::Texture> letters;
                        std::vector<sf::Sprite> Lsprites;
                        sf::RenderWindow algo_win(sf::VideoMode(840, 500), "Boyer-Moore Visualization");
                        BM(&algo_win, &query, &text, &letters, &Lsprites, music);
                        break;
                    }
                    else if (menu.getPressedItem() == 2) {
                        // exit
                        window.close();
                        return 0;
                    }
                }
                break;
            case sf::Event::Closed:
                window.close();
                return 0;
            }
        }
        window.clear();

        menu.draw(window);
        window.display();
    }
}

void r_screen(sf::RenderWindow* window, std::string* query, std::string* text, std::vector<sf::Texture>* letters, std::vector<sf::Sprite>* letterSprites) {
    // Resets the screen to just the text, query, and letters

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
        // generate and draw the letters that each algo will highlight
        sf::Texture newTexture;
        letters->push_back(newTexture);
        (*letters)[i].loadFromFile(std::to_string(std::tolower((*text)[i])) + ".png");
        letterSprites->push_back(sf::Sprite((*letters)[i]));

        int spacing = 70;
        int ypos = 300;
        int startx = 40;
        (*letterSprites)[i].setPosition(startx + i * spacing, ypos);

        window->draw((*letterSprites)[i]);

    }
}


void rabin(sf::RenderWindow* window, std::string* query, std::string* text, std::vector<sf::Texture>* letters, std::vector<sf::Sprite>* letterSprites, sf::Music* music) {
    window->setFramerateLimit(1); // wait 1 sec between each window->display()
    r_screen(window, query, text, letters, letterSprites);
    window->display();

    // rabin-karp implementation
    vector<int> matchIndices;
    int prime = 101;
    int numLetters = 256;
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
        // highlight the current window of text in yellow
        r_screen(window, query, text, letters, letterSprites);
        for (int n = 0; n < query->size(); n++) {
            (*letterSprites)[n + i].setColor(sf::Color::Yellow);
            window->draw((*letterSprites)[i + n]);
        }
        window->display();

        if (patternHash == textHash) {
            int j;
            for (j = 0; j < query->size(); j++) {
                // highlight each letter in red as it's being double-checked, and the window in yellow
                r_screen(window, query, text, letters, letterSprites);
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

    // highlight all matches
    r_screen(window, query, text, letters, letterSprites);
    for (int i = 0; i < letterSprites->size(); i++) {

        for (int n = 0; n < matchIndices.size(); n++) {
            if (i >= matchIndices[n] && i < matchIndices[n] + query->size()) {
                (*letterSprites)[i].setColor(sf::Color::Red);
                window->draw((*letterSprites)[i]);
            }
        }
    }
    window->display();

    // wait for esc press
    bool s = true;
    while (s) {
        sf::Event Event;
        while (window->pollEvent(Event))
        {
            switch (Event.type)
            {
            case sf::Event::KeyReleased:
                switch (Event.key.code)
                {
                case sf::Keyboard::Escape:
                    s = false;
                    // close the window and reopen main menu
                    window->close();
                    main_menu(music);
                    break;
                case sf::Keyboard::Space:
                    // rerun the current algorithm
                    window->close();
                    std::vector<sf::Texture> letters;
                    std::vector<sf::Sprite> Lsprites;
                    sf::RenderWindow algo_win(sf::VideoMode(840, 500), "Rabin-Karp Visualization");
                    rabin(&algo_win, query, text, &letters, &Lsprites, music);
                    break;
                }
            }
        }
    }
}


void badChar(vector<int>* bChars, string* query) {
    int CHARNUM = 256;
    for (int i = 0; i < CHARNUM; i++) {
        bChars->push_back(-1);
    }
    for (int i = 0; i < query->size(); i++) {
        bChars->at(int(query->at(i))) = i;
    }
}

void BM(sf::RenderWindow* window, std::string* query, std::string* text, std::vector<sf::Texture>* letters, std::vector<sf::Sprite>* letterSprites, sf::Music* music) {
    window->setFramerateLimit(1); // wait 1 sec between each window->display()
    r_screen(window, query, text, letters, letterSprites);
    window->display();

    // boyer-moore implementation
    vector<int> bChars, matches;
    badChar(&bChars, query);
    int shift = 0;
    while (shift <= text->size() - query->size()) {
        int j = query->size() - 1;

        r_screen(window, query, text, letters, letterSprites);
        for (int n = 0; n < query->size(); n++) {
            if (n == query->size() - 1) {
                // highlight the letter compared to last query letter in green
                (*letterSprites)[n + shift].setColor(sf::Color::Green);
            }
            else {
                // highlight rest of the current window in yellow
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
            int n = j - bChars.at(int(text->at(shift + j)));
            if (n > 1) {
                shift += n;
            }
            else {
                shift++;
            }
        }
    }

    // highlight all matches in red
    r_screen(window, query, text, letters, letterSprites);
    for (int i = 0; i < letterSprites->size(); i++) {
        for (int n = 0; n < matches.size(); n++) {
            if (i >= matches[n] && i < matches[n] + query->size()) {
                (*letterSprites)[i].setColor(sf::Color::Red);
                window->draw((*letterSprites)[i]);
            }
        }
    }
    window->display();

    // wait for esc press
    bool s = 1;
    while (s) {
        sf::Event Event;
        while (window->pollEvent(Event))
        {
            switch (Event.type)
            {
            case sf::Event::KeyReleased:
                switch (Event.key.code)
                {
                case sf::Keyboard::Escape:
                    s = 0;
                    // close the window and reopen main menu
                    window->close();
                    main_menu(music);
                    break;
                case sf::Keyboard::Space:
                    // rerun the current algorithm
                    window->close();
                    std::vector<sf::Texture> letters;
                    std::vector<sf::Sprite> Lsprites;
                    sf::RenderWindow algo_win(sf::VideoMode(840, 500), "Boyer-Moore Visualization");
                    BM(&algo_win, query, text, &letters, &Lsprites, music);
                    break;
                }
            }
        }
    }
}