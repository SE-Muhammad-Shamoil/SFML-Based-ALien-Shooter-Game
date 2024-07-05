#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm> // for std::sort
#include <vector>
using namespace std;

class Scores
{
private:
    sf::Font font;
    string topNames[100]; 
    int topScores[100];   
    sf::Texture backgroundTexture;
    sf::Texture medaltex;

public:
    Scores()
    {
        if (!font.loadFromFile("score.ttf"))
        {
            cerr << "Failed to load font!" << endl;
        }

        backgroundTexture.loadFromFile("img/leaderboard.png");
    }

    void readScoresFromFile()
    {

        for (int i = 0; i < 100; ++i)
        {
            topNames[i] = "";
            topScores[i] = 0;
        }

        ifstream file("scores.txt");
        if (!file.is_open())
        {
            cerr << "Failed to open file: " << "scores.txt" << endl;
            return;
        }

        for (int i = 0; i < 100; ++i)
        {
            if (file >> topNames[i] >> topScores[i])
            {
                if(topScores[i]>5000)
                    topScores[i]=0;
            }
        }
        file.close();

        for (int i = 0; i < 100; ++i)
        {
            for (int j = i + 1; j < 100; ++j)
            {
                if (topScores[i] < topScores[j])
                {
                    swap(topScores[i], topScores[j]);
                    swap(topNames[i], topNames[j]);
                }
            }
        }
    }

    int *getscore()
    {
        readScoresFromFile();
        return topScores;
    }

    void draw(sf::RenderWindow &window)
    {
        window.clear();

        sf::RectangleShape backgroundSprite(sf::Vector2f(750, 950));

        backgroundSprite.setTexture(&backgroundTexture);
        window.draw(backgroundSprite);

        sf::Text title("Top Scores", font, 40);
        title.setPosition(250, 50);
        title.setFillColor(sf::Color::White);
        window.draw(title);

        title.setString("----------------------------------------------");
        title.setPosition(90, 70);
        title.setFillColor(sf::Color::White);
        window.draw(title);

        sf::Text scoresText;
        scoresText.setFont(font);
        scoresText.setCharacterSize(30);
        scoresText.setFillColor(sf::Color::White);

        sf::RectangleShape medal(sf::Vector2f(50, 100));

        int yPos = 150;
        for (int i = 0; i < 3; ++i)
        {
            scoresText.setString(topNames[i] + "    :    " + to_string(topScores[i]));
            scoresText.setPosition(250, yPos);
            window.draw(scoresText);
            yPos += 100;

            switch (i)
            {
            case 0:
                medaltex.loadFromFile("img/medal1.png");
                medal.setPosition(200, 130);
                break;
            case 1:
                medaltex.loadFromFile("img/medal2.png");
                medal.setPosition(200, 230);
                break;
            case 2:
                medaltex.loadFromFile("img/medal3.png");
                medal.setPosition(200, 330);
                break;
            }

            medal.setTexture(&medaltex);

            window.draw(medal);
        }

        sf::Text returnText("Press ESC to return", font, 20);
        returnText.setPosition(250, 800);
        returnText.setFillColor(sf::Color::White);
        window.draw(returnText);

        title.setString("----------------------------------------------");
        title.setPosition(90, 400);
        title.setFillColor(sf::Color::White);
        window.draw(title);

        window.display();
    }

    void run(sf::RenderWindow &window)
    {
        readScoresFromFile(); 
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        return;
                    }
                }
            }

            draw(window);
        }
    }

    void addScore(const string &name, int score)
    {
        ofstream file("scores.txt", std::ios::app);
        if (!file.is_open())
        {
            cerr << "Failed to open file: " << "scores.txt" << endl;
            return;
        }

        file << name << " " << score << endl;
        file.close();
    } 
};
