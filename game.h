#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include "level.cpp"
#include "scores.h"
using namespace std;
using namespace sf;

class Game
{
private:
    Sprite background; // Game background sprite
    RectangleShape pause;
    RectangleShape pause_screen;
    Texture bg_texture;
    Texture pause_txt;
    SpaceShip  *p; // player   
    int score = 0;
    int enemies_destroyed = 0;
    lvl1 lvl_one;
    lvl2 lvl_two;
    lvl3 lvl_three;
    sf::Image cursor_Image;
    sf::Cursor cursor;
    float deltaTime = 0.0f;
    float timer = 0;
    bool paused = false;
    bool animation = false;
    bool space_attempt = false;
    string Pname;
    Font lvl_font;
    Text lvl_txt;
    sf::RectangleShape dashshape;
    Texture dashtex;
    Clock clock;
    Clock gameclock;
    Scores score_obj;
    int *top_scores;
    sf::RectangleShape medal;
    sf::Texture medaltex;
    sf::Texture medaltex2;
    sf::Texture medaltex3;
    sf::SoundBuffer shootbuffer;
    sf::Sound shoot;
    bool save = false;
    sf::Clock savesclk;
    sf::RectangleShape savescreen;
    sf::Texture save_tex;
    int save_count = 0;

public:
    Game() : pause(sf::Vector2f(75, 75)), pause_screen(sf::Vector2f(750, 1000)), dashshape(sf::Vector2f(500, 70)), medal(sf::Vector2f(30, 60)), savescreen(sf::Vector2f(750, 950))
    {
        p = new SpaceShip ("img/PNG/playerShip2_orange.png");
        bg_texture.loadFromFile("img/background.jpg");
        background.setTexture(bg_texture);
        background.setScale(2, 1.5);
        cursor_Image.loadFromFile("img/PNG/UI/cursor.png");
        cursor.loadFromPixels(cursor_Image.getPixelsPtr(), cursor_Image.getSize(), sf::Vector2u(0, 0));
        pause_txt.loadFromFile("img/pause.png");
        pause.setTexture(&pause_txt);
        pause.setOrigin(37.5, 37.5);
        pause.setPosition(25, 25);
        pause_screen.setFillColor(sf::Color(0, 0, 0, 200));
        lvl_font.loadFromFile("score.ttf");
        lvl_txt.setFont(lvl_font);
        lvl_txt.setFillColor(sf::Color::White);
        dashtex.loadFromFile("img/dashboard.png");
        dashshape.setTexture(&dashtex);
        dashshape.setPosition(80, 5);
        lvl_font.loadFromFile("Welcome_font.otf");
        lvl_txt.setFont(lvl_font);
        top_scores = score_obj.getscore(); //Array of top scores
        medaltex.loadFromFile("img/medal1.png");
        medaltex2.loadFromFile("img/medal2.png");
        medaltex3.loadFromFile("img/medal3.png");
        save_tex.loadFromFile("img/saving.png");
        savescreen.setTexture(&save_tex);

        if (!shootbuffer.loadFromFile("sounds/shoot.wav"))
        {
            cout << "Unable to open shoot sound";
        }
        shoot.setBuffer(shootbuffer);
    }

    void start_game(sf::RenderWindow &window , bool save_check)
    {
        gameclock.restart();
        srand(time(0));
        bool temp = false;

        if(!save_check)
            nameEnter(window);
        else
        {loadgame();}
        

        window.setMouseCursor(cursor);
        while (window.isOpen())
        {
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;
            deltaTime = time;
            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed) 
                    window.close();       
                if (e.type == sf::Event::KeyReleased)
                {
                    if (e.key.code == Keyboard::Space && level::mangekyou_status == false)
                    {
                        p->fireBullet();
                        shoot.play();
                    }

                    if (e.key.code == Keyboard::Escape)
                    {
                        paused = !paused;
                    }
                }

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                    
                    if (pause.getGlobalBounds().contains(mousePosF))
                    {
                        paused = !paused;
                    }
                }
            }

        if(level::mangekyou_status==false)
        {
            p->sprite.setRotation(0.0f);
            if (Keyboard::isKeyPressed(Keyboard::W))
                p->move("w");
            if (Keyboard::isKeyPressed(Keyboard::S))
                p->move("s");
            if (Keyboard::isKeyPressed(Keyboard::D))
                p->move("d");
            if (Keyboard::isKeyPressed(Keyboard::A))
                p->move("a");
            if(p->sprite.getColor()==sf::Color::Blue)
                p->sprite.setColor(sf::Color::White);
        }
        else
        {
            p->sprite.setColor(sf::Color::Blue);
        }

            if (enemies_destroyed < 20 && p->life != 0)
            {
                lvl_one.lvl_run(window, p, enemies_destroyed, score, deltaTime, paused);
                dash_draw(window);
                savesclk.restart();
            }
            else if (enemies_destroyed == 20)
            {
                if (savesclk.getElapsedTime().asSeconds() < 2)
                    window.draw(savescreen);
                else
                {
                    p->sprite.setPosition(375, 900);
                    lvl_one.music.stop();
                    enemies_destroyed++;
                    savegame();
                }
            }
            else if (enemies_destroyed < 41 && p->life != 0)
            {
                lvl_two.lvl_run(window, p, enemies_destroyed, score, deltaTime, paused);
                dash_draw(window);
                savesclk.restart();
            }
            else if (enemies_destroyed == 41)
            {
                if (savesclk.getElapsedTime().asSeconds() < 2)
                    window.draw(savescreen);
                else
                {
                    p->sprite.setPosition(375, 900);
                    lvl_two.music.stop();
                    enemies_destroyed++;
                    savegame();
                }
            }
            else if (enemies_destroyed < 81 && p->life != 0)
            {
                lvl_three.lvl_run(window, p, enemies_destroyed, score, deltaTime, paused);
                dash_draw(window);
            }
            else if (enemies_destroyed == 82)
            {
                Event evnt;
                window.clear(sf::Color::Black);
                game_win(window);
                while (window.pollEvent(evnt))
                {
                    if (evnt.type = sf::Event::KeyReleased)
                    {
                        if (evnt.key.code == Keyboard::Enter)
                        {
                            score_obj.addScore(Pname, score);
                            return;
                        }
                    }
                }
            }
            else if(enemies_destroyed == 81)
            {
                
            }
            else if (p->life < 1)
            {
                Event evnt;
                window.clear(sf::Color::Black);
                game_over(window);
                while (window.pollEvent(evnt))
                {
                    if (evnt.type = sf::Event::KeyReleased)
                    {
                        if (evnt.key.code == Keyboard::Enter)
                        {
                            score_obj.addScore(Pname, score);
                            return;
                        }
                    }
                }
            }

            if (paused)
            {
                pause_draw(window);
            }

            window.draw(pause);
            window.display(); 
        }
    }

    void game_over(sf::RenderWindow &window)
    {
        Sprite over;
        sf::Texture over_txt;
        over_txt.loadFromFile("img/game_over.png");
        over.setTexture(over_txt);
        over.setPosition(100, 400);

        sf::Font over_font;
        over_font.loadFromFile("Welcome_font.otf");

        sf::Text over_text;
        sf::Text over_score;
        over_score.setFont(over_font);
        over_text.setFont(over_font);
        over_score.setString("Score : " + to_string(score));
        over_text.setString("Press Enter to Return to Main Menu");
        over_text.setPosition(180, 900);
        over_score.setPosition(400, 500);

        window.draw(over);
        window.draw(over_text);
        window.draw(over_score);

        pause.setPosition(-100, -100);
    }

    void dash_draw(sf::RenderWindow &window)
    {
        lvl_txt.setString("Score : " + to_string(score));
        lvl_txt.setPosition(150, 15);
        window.draw(lvl_txt);

        if (score > top_scores[0])
        {
            medal.setTexture(&medaltex);
            medal.setFillColor(sf::Color::White);
        }
        else if (score > top_scores[1])
        {
            medal.setTexture(&medaltex2);
            medal.setFillColor(sf::Color::White);
        }
        else if (score > top_scores[2])
        {
            medal.setTexture(&medaltex3);
            medal.setFillColor(sf::Color::White);
        }
        else
            medal.setFillColor(sf::Color::Transparent);

        medal.setPosition(120, 0);
        window.draw(medal);
        lvl_txt.setString(to_string(static_cast<int>(gameclock.getElapsedTime().asSeconds() / 60)) + ":" + to_string(static_cast<int>(gameclock.getElapsedTime().asSeconds())));
        lvl_txt.setPosition(400, 15);
        window.draw(lvl_txt);
        window.draw(dashshape);
    }

    void game_win(sf::RenderWindow &window)
    {
        RectangleShape over(sf::Vector2f(600, 200));
        sf::Texture over_txt;
        over_txt.loadFromFile("img/game_win.png");
        over.setTexture(&over_txt);
        over.setPosition(170, 300);

        sf::Font over_font;
        over_font.loadFromFile("Welcome_font.otf");

        sf::Text over_text;
        sf::Text over_score;
        over_score.setFont(over_font);
        over_text.setFont(over_font);
        over_score.setString("Score : " + to_string(score));
        over_text.setString("Press Enter to Return to Main Menu");
        over_text.setPosition(180, 900);
        over_score.setPosition(400, 500);

        window.draw(over);
        window.draw(over_text);
        window.draw(over_score);

        pause.setPosition(-100, -100);
    }

    void pause_draw(RenderWindow &window)
    {
        window.draw(pause_screen);

        sf::Font p_font;
        p_font.loadFromFile("Welcome_font.otf");

        sf::Text p_text;
        p_text.setFont(p_font);
        p_text.setString("Press Escape to Resume");
        p_text.setPosition(250, 425);
        window.draw(p_text);
    }

    void nameEnter(RenderWindow &window)
    {
        sf::Font font;
        font.loadFromFile("score.ttf");

        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setString("Enter your name:");
        text.setPosition(50, 50);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                if (event.type == sf::Event::TextEntered)
                {
                    if (event.text.unicode == '\b' && !Pname.empty())
                    {
                        Pname.pop_back(); 
                    }
                    else if (event.text.unicode >= 32 && event.text.unicode <= 126)
                    {
                        Pname += static_cast<char>(event.text.unicode); 
                    }
                }
            }

            window.clear(sf::Color::White);
            window.draw(background);
            window.draw(text);

            sf::Text nameText(Pname, font, 24);
            nameText.setFillColor(sf::Color::White);
            nameText.setPosition(50, 100);
            window.draw(nameText);
            window.display();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                return;
        }
    }

    void loadgame()
    {
        int clk;
        ifstream file("save.txt");
        if (!file.is_open())
        {
            cout << "Failed to open file: " << "scores.txt" << endl;
            return;
        }
        file >> Pname >> score >> enemies_destroyed >> p->life;
        file.close();
    }

    void savegame()
    {
        ofstream file("save.txt");
        if (!file.is_open())
        {
            cout << "Failed to open file: " << "scores.txt" << endl;
            return;
        }
        file << Pname << " " << score << " " << enemies_destroyed << " " << p->life;
        file.close();
    }
};
