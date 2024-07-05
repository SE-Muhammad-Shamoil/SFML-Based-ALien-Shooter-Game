#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
#include "game.h"

//----------------------------- Class Declaration -----------------------------

class Menu
{
private:
    sf::RenderWindow window; // Main window
    bool selection;
    sf::Font font; // Font for the menu text
    sf::Text menuOptions[5]; // Array of menu options
    int selectedIndex; // Index of the selected menu option
    Scores score; // Object to manage scores
    sf::SoundBuffer menu_music; // Buffer to hold menu music
    sf::Sound music; // Sound object for playing menu music
    sf::RectangleShape startup; // Startup screen rectangle
    sf::Texture startup_tex; // Texture for startup screen
    sf::SoundBuffer startupbuff; // Buffer to hold startup sound
    sf::Sound sound; // Sound object for playing startup sound

public:
    // Constructor
    Menu() : window(sf::VideoMode(750, 950), "OOP-Project, Spring-2024", sf::Style::Default), selectedIndex(0), startup(sf::Vector2f(750, 950))
    {
        // Load font
        font.loadFromFile("Freedom.ttf");

        // Initialize menu options
        string options[] = {"New Game", "Load Game", "Instructions", "LeaderBoard", "Exit"};
        for (int i = 0; i < 5; ++i)
        {
            menuOptions[i].setFont(font);
            menuOptions[i].setString(options[i]);
            menuOptions[i].setCharacterSize(50);
            menuOptions[i].setFillColor(sf::Color::White);
            menuOptions[i].setPosition(230, 400 + i * 70);
        }
        menuOptions[0].setFillColor(sf::Color::Red); // Highlight the first option

        // Load menu music
        if (!menu_music.loadFromFile("sounds/menu.wav"))
        {
            cout << "failed to open menu music\n";
        }
        music.setBuffer(menu_music);

        // Load startup sound
        if (!startupbuff.loadFromFile("sounds/startup.wav"))
        {
            cout << "failed to open startup sound\n";
        }
        sound.setBuffer(startupbuff);
    }

    //----------------------------- Display Menu -----------------------------
    void display_menu()
    {
        sound.play(); // Play startup sound
        Clock start; // Clock for managing startup screen timing
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                else if (event.type == sf::Event::KeyPressed) // Navigation control
                {
                    if (start.getElapsedTime().asSeconds() > 7)
                    {
                        if (event.key.code == sf::Keyboard::W)
                        {
                            moveUp();
                        }
                        else if (event.key.code == sf::Keyboard::S)
                        {
                            moveDown();
                        }
                        else if (event.key.code == sf::Keyboard::Enter)
                        {
                            Selection();
                        }
                    }
                }
            }

            if (start.getElapsedTime().asSeconds() < 10) // Display startup screen
            {
                if (start.getElapsedTime().asSeconds() < 2)
                {
                    startup_tex.loadFromFile("img/startup1.png"); // Loading screen 1
                }
                else if (start.getElapsedTime().asSeconds() < 5)
                {
                    startup_tex.loadFromFile("img/startup2.png"); // Loading screen 2
                }
                else if (start.getElapsedTime().asSeconds() < 7)
                {
                    startup_tex.loadFromFile("img/startup3.png"); // Loading screen 3
                }
                else
                {
                    startup_tex.loadFromFile("img/startup.png"); // Loading screen 4
                }
                startup.setTexture(&startup_tex);
                window.draw(startup);
            }
            else
            {
                if (music.getStatus() != sf::Sound::Playing)
                {
                    music.play(); // Play menu music
                }
                window.clear();
                drawMenu(); // Draw menu options
            }
            window.display();
        }
    }

    //----------------------------- Instructions Screen -----------------------------
    void instructions()
    {
        while (window.isOpen())
        {
            sf::RectangleShape instruct(sf::Vector2f(750, 950));
            sf::Texture instruct_tex;
            instruct_tex.loadFromFile("img/instructions.png");
            instruct.setTexture(&instruct_tex);
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                else if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        return; // Return to the main menu
                    }
                }
            }

            window.clear();
            window.draw(instruct); // Draw instructions
            window.display();
        }
    }

    //----------------------------- Menu Navigation -----------------------------
    void moveUp()
    {
        if (selectedIndex - 1 >= 0)
        {
            menuOptions[selectedIndex].setFillColor(sf::Color::White);
            selectedIndex--;
            menuOptions[selectedIndex].setFillColor(sf::Color::Red);
        }
    }

    void moveDown()
    {
        if (selectedIndex + 1 < 5)
        {
            menuOptions[selectedIndex].setFillColor(sf::Color::White);
            selectedIndex++;
            menuOptions[selectedIndex].setFillColor(sf::Color::Red);
        }
    }

    //----------------------------- Menu Selection -----------------------------
    void Selection()
    {
        switch (selectedIndex)
        {
        case 0: // New Game
        {
            startGame(false);
            break;
        }
        case 1: // Load Game
        {
            startGame(true);
            break;
        }
        case 2: // Instructions
        {
            instructions();
            break;
        }
        case 3: // Leaderboard
        {
            score.run(window);
            break;
        }
        case 4: // Exit
        {
            window.close();
            break;
        }
        }
    }

    //----------------------------- Start Game -----------------------------
    void startGame(bool save_state)
    {
        music.stop(); // Stop menu music
        Game *g = new Game;
        g->start_game(window, save_state); // Start game
        delete g;
        g = nullptr;
    }

    //----------------------------- Draw Menu -----------------------------
    void drawMenu()
    {
        sf::RectangleShape welcome(sf::Vector2f(750, 950));
        sf::Texture welcome_bg;
        welcome_bg.loadFromFile("img/start_screen.jpg");
        welcome.setTexture(&welcome_bg);
        sf::RectangleShape logo(sf::Vector2f(500, 250));
        sf::Texture logo_tex;
        logo_tex.loadFromFile("img/logo.png");
        logo.setTexture(&logo_tex);
        logo.setPosition(140, 140);

        window.draw(welcome);
        window.draw(logo);   

        // Draw menu options
        for (int i = 0; i < 5; ++i)
        {
            window.draw(menuOptions[i]);
        }
    }
};
