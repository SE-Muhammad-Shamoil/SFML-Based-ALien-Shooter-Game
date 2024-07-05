#include "level.h"
#include <cmath>

void level::draw(sf::RenderWindow &window, float deltaTime)
{
    drawbg(window, deltaTime);
    window.draw(mangekyou);
    window.draw(lvl_txt);
    if (!drago_check)
    {
        for (int count = 0; count < enemy_number; count++)
        {
            window.draw(eship_ptr[count]->enemy);
            eship_ptr[count]->drawBombs(window);
        }
    }
    else if (drago_check)
    {
        window.draw(drago.enemy);
        window.draw(drago.fire);
    }
}

void level::updt(float deltaTime, SpaceShip  *player)
{
    if (!drago_check)
    {
        for (int count = 0; count < enemy_number; count++)
        {
            if (eship_ptr[count]->destroyed)
            {
                // Move destroyed enemies off-screen
                eship_ptr[count]->enemy.setPosition(-100, -100);
                continue; // Skip further processing for destroyed enemies
            }

            // Move enemies according to selector
            if (selector == 2)
            {
                eship_ptr[count]->h_move();
            }
            else if (selector == 3 || selector == 1)
            {
                eship_ptr[count]->v_move();
            }

            // Handle enemy attacks
            if (attack_select == count)
            {
                eship_ptr[count]->attack();
                // Randomly select a new attack target
                do
                {
                    attack_select = rand() % enemy_number;
                } while (eship_ptr[attack_select]->destroyed);
            }

            // Update bombs for each enemy
            eship_ptr[count]->updateBombs(deltaTime);
        }

        updateBombs(deltaTime);
    }
    else
    {
        drago.attack(player->sprite.getPosition());
    }
}

void lvl1::Shapes()
{

    if (selector == 1) // Hollow Triangle
    {
        // Adjust array size for the specified number of invaders
        int startX = 700 / 4;     // Start X position for the leftmost side
        int startY = 700 / 4;    // Start Y position for the uppermost side
        int sideLength = 700 / 2; // Length of each side

        for (int i = 0; i < enemy_number / 2; ++i)
        {
            // Top left to bottom right diagonal
            int x1 = startX + i * (sideLength / (enemy_number / 2 - 1));
            int y1 = startY + i * (sideLength / (enemy_number / 2 - 1));
            // Bottom left to top right diagonal
            int x2 = startX + i * (sideLength / (enemy_number / 2 - 1));
            int y2 = startY + (sideLength - i * (sideLength / (enemy_number / 2 - 1)));

            eship_ptr[i]->enemy.setPosition(x1, y1);
            eship_ptr[enemy_number - 1 - i]->enemy.setPosition(x2, y2);
        }
    }
    else if (selector == 2) // Hollow Square
    {
        int startX = 700 / 4;
        int startY = 700 / 4;
        int side = 700 / 2;

        for (int i = 0; i < 20; ++i)
        {
            int x, y;
            if (i < 5) // Top side of the square
            {
                x = startX + i * (side / 5);
                y = startY;
            }
            else if (i < 10) // Right side of the square
            {
                x = startX + side;
                y = startY + (i - 5) * (side / 5);
            }
            else if (i < 15) // Bottom side of the square
            {
                x = startX + (15 - i) * (side / 5);
                y = startY + side;
            }
            else // Left side of the square
            {
                x = startX;
                y = startY + (20 - i) * (side / 5);
            }
            eship_ptr[i]->enemy.setPosition(x, y);
        }
    }
    else if (selector == 3) // Hollow X
    {
        // Adjust array size for the specified number of invaders
        int startX = 700 / 4;     // Start X position for the leftmost side
        int startY = 700/ 4;    // Start Y position for the uppermost side
        int sideLength = 700 / 2; // Length of each side

        for (int i = 0; i < enemy_number / 2; ++i)
        {
            // Top left to bottom right diagonal
            int x1 = startX + i * (sideLength / (enemy_number / 2 - 1));
            int y1 = startY + i * (sideLength / (enemy_number / 2 - 1));
            // Bottom left to top right diagonal
            int x2 = startX + i * (sideLength / (enemy_number / 2 - 1));
            int y2 = startY + (sideLength - i * (sideLength / (enemy_number / 2 - 1)));

            eship_ptr[i]->enemy.setPosition(x1, y1);
            eship_ptr[enemy_number - 1 - i]->enemy.setPosition(x2, y2);
        }
    }
}

void lvl2::Shapes()
{
    int screenWidth = 750;
    int screenHeight = 950; 

    if (selector == 1)
    {
        int centerX = screenWidth / 2;
        int centerY = screenHeight / 3;
        int radius = screenWidth / 4;

        for (int count = 0; count < 20; ++count)
        {
            float angle = (float)count / 20 * 2 * M_PI;
            int x = centerX + radius * cos(angle);
            int y = centerY + radius * sin(angle);
            eship_ptr[count]->enemy.setPosition(x, y);
        }
    }
    else if (selector == 2) // Hollow Heart
    {
        int centerX = screenWidth / 2;
        int centerY = screenHeight / 3;
        int radius = screenWidth / 4;

        for (int count = 0; count < 20; ++count)
        {
            float angle = (float)count / 20 * 2 * M_PI;
            int x = centerX + radius * cos(angle);
            int y = centerY + radius * sin(angle);
            eship_ptr[count]->enemy.setPosition(x, y);
        }
    }
    else if (selector == 3) // Hollow Diamond
    {

        sf::Vector2f points[] = {
            sf::Vector2f(screenWidth / 2, screenHeight / 3),     // Top point of the diamond
            sf::Vector2f(screenWidth / 3, screenHeight / 2),     // Left point of the diamond
            sf::Vector2f(screenWidth / 2, screenHeight * 2 / 3), // Bottom point of the diamond
            sf::Vector2f(screenWidth * 2 / 3, screenHeight / 2)  // Right point of the diamond
        };

        for (int i = 0; i < 20; ++i)
        {
            int sideIndex = i / 5;        
            float t = (float)(i % 5) / 4; 
            sf::Vector2f p1, p2;
            if (sideIndex == 0)
            {
                p1 = points[0] + t * (points[1] - points[0]);
                p2 = points[1] + t * (points[2] - points[1]);
            }
            else if (sideIndex == 1)
            {
                p1 = points[1] + t * (points[2] - points[1]);
                p2 = points[2] + t * (points[3] - points[2]);
            }
            else if (sideIndex == 2)
            {
                p1 = points[2] + t * (points[3] - points[2]);
                p2 = points[3] + t * (points[0] - points[3]);
            }
            else
            {
                p1 = points[3] + t * (points[0] - points[3]);
                p2 = points[0] + t * (points[1] - points[0]);
            }
            if (i < enemy_number)
            {
                eship_ptr[i]->enemy.setPosition(p1);
            }
            if (i + 5 < enemy_number)
            {
                eship_ptr[i + 5]->enemy.setPosition(p2);
            }
        }
    }
}

void lvl3::Shapes()
{
    cout << selector;
    if (selector == 1)
    {
       
        int rows = 4;    
        int cols = 8;     
        int marginX = 50;  
        int marginY = 50;  
        int spacingX = 10; 
        int spacingY = 10; 

      
        int cellWidth = (750 - 2 * marginX - (cols - 1) * spacingX) / cols;
        int cellHeight = (950 - 2 * marginY - (rows - 1) * spacingY) / rows;

       
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
               
                int posX = marginX + j * (cellWidth + spacingX);
                int posY = marginY + i * (cellHeight + spacingY);

                
                int index = i * cols + j;

                
                if (index < enemy_number)
                {
                    eship_ptr[index]->enemy.setPosition(posX, posY);
                }
            }
        }
    }
    else if (selector == 2)
    {
      
        int rows = 4;     
        int cols = 8;     
        int marginX = 50;  
        int marginY = 50;  
        int spacingX = 10;
        int spacingY = 10; 

        int cellWidth = (750 - 2 * marginX - (cols - 1) * spacingX) / cols;
        int cellHeight = (950 - 2 * marginY - (rows - 1) * spacingY) / rows;

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                int posX = marginX + j * (cellWidth + spacingX);
                int posY = marginY + i * (cellHeight + spacingY);

                int index = i * cols + j;

                if (index < enemy_number)
                {
                    eship_ptr[index]->enemy.setPosition(posX, posY);
                }
            }
        }
    }
    else if (selector == 3)
    {
        int rows = 4;      
        int cols = 8;    
        int marginX = 50;  
        int marginY = 50; 
        int spacingX = 10; 
        int spacingY = 10; 


        int cellWidth = (750 - 2 * marginX - (cols - 1) * spacingX) / cols;
        int cellHeight = (950 - 2 * marginY - (rows - 1) * spacingY) / rows;

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                int posX = marginX + j * (cellWidth + spacingX);
                int posY = marginY + i * (cellHeight + spacingY);

                int index = i * cols + j;

                if (index < enemy_number)
                {
                    eship_ptr[index]->enemy.setPosition(posX, posY);
                }
            }
        }
    }
}

void level::updateBombs(float deltaTime)
{
    for (int i = 0; i < enemy_number; ++i)
    {
        eship_ptr[i]->updateBombs(deltaTime);
    }
}

void level::checkEnemyBulletCollision(SpaceShip  *player, int &kill_no, int &score)
{
    if (!drago_check)
    {
        for (int i = 0; i < enemy_number; ++i)
        {
            sf::FloatRect enemyBounds = eship_ptr[i]->enemy.getGlobalBounds();

            for (size_t j = 0; j < player->bullets.size(); ++j)
            {
                sf::FloatRect bulletBounds = player->bullets[j].getBounds();

                if (enemyBounds.intersects(bulletBounds))
                {
                    eship_ptr[i]->destroyed = true;
                    switch (eship_ptr[i]->enemy_lvl)
                    {
                    case 1:
                        score += randomizer * lvl_no;
                        break;
                    case 2:
                        score += 20 * lvl_no;
                        break;
                    case 3:
                        score += 30 * lvl_no;
                        break;
                    }
                    kill_no++;
                    player->bullets.erase(player->bullets.begin() + j);
                    std::cout << "\nScore : " << score;
                    std::cout << "\nEnemies Killed : " << kill_no;
                    break;
                }
            }
        }
    }
    else
    {
    }
}

void level::checkEnemyPlayerCollision(SpaceShip  *player, int &kill_no, int &score)
{
    if (!drago_check)
    {
        for (int i = 0; i < enemy_number; ++i)
        {
            sf::FloatRect enemyBounds = eship_ptr[i]->enemy.getGlobalBounds();
            sf::FloatRect playerBounds = player->sprite.getGlobalBounds();

            if (enemyBounds.intersects(playerBounds))
            {
                player->life -= 1;
                std::cout << "\nPlayer collided with enemy! Life remaining: " << player->life;
                eship_ptr[i]->destroyed = true;
                kill_no++;
                player->sprite.setPosition(375, 900);
                player->took_damage = true;
                break;
            }
        }
    }
    else
    {
        sf::FloatRect dragoBounds(
            drago.enemy.getPosition().x,
            drago.enemy.getPosition().y,
            drago.enemy.getGlobalBounds().width,
            drago.enemy.getGlobalBounds().height - 300);

        sf::FloatRect playerBounds = player->sprite.getGlobalBounds();
        sf::FloatRect firebounds(            
            drago.fire.getPosition().x,
            drago.fire.getPosition().y,
            drago.fire.getGlobalBounds().width - 50,
            drago.fire.getGlobalBounds().height);

        if (dragoBounds.intersects(playerBounds) || firebounds.intersects(playerBounds) )
        {
            player->life -= 1;
            std::cout << "\nPlayer collided with Dragon! Life remaining: " << player->life;
            player->sprite.setPosition(375, 900);
            player->took_damage = true;
        }
    }
}

void level::checkBombPlayerCollision(SpaceShip  *player)
{
    if (!drago_check)
    {
        for (int i = 0; i < enemy_number; ++i)
        {
            for (size_t j = 0; j < eship_ptr[i]->bombs.size(); ++j)
            {
                sf::FloatRect bombBounds = eship_ptr[i]->bombs[j].getGlobalBounds();
                sf::FloatRect playerBounds = player->sprite.getGlobalBounds();

                if (bombBounds.intersects(playerBounds))
                {
                    eship_ptr[i]->bombs.erase(eship_ptr[i]->bombs.begin() + j);
                    --j;
                    player->life -= 1;
                    player->sprite.setPosition(375, 900);
                    player->took_damage = true;
                    std::cout << "\nPlayer collided with enemy bomb! Life remaining: " << player->life;
                    break;
                }
            }
        }
    }
}

void level::lvl_run(sf::RenderWindow &window, SpaceShip  *p, int &enemies_destroyed, int &score, float deltaTime, bool pause_check)
{
    if (!pause_check)//Check if game is paused
    {
        if (!(p->shield))
        {
            checkEnemyPlayerCollision(p, enemies_destroyed, score);
            checkBombPlayerCollision(p);
        }

        checkEnemyBulletCollision(p, enemies_destroyed, score);
        p->damagecheck();
        p->shieldcheck();
        p->updateBullets();
        updt(deltaTime, p);
    }  
    window.clear(sf::Color::Black); 
    draw(window, deltaTime);

    p->draw(window);

    if (dragon_show(window))    //Danger Sign for Dragon
    {
        score += 50;
    }
    mangekyou_updt();                   //Updating Mangekyou
}

bool level::dragon_show(sf::RenderWindow &window)
{
    if (music.getStatus() != sf::Sound::Playing)
    {
        music.play();
    }

    if (dragon_clock.getElapsedTime().asSeconds() > drago_interval - 5)
    {
        window.draw(danger);
    }

    if (dragon_clock.getElapsedTime().asSeconds() > drago_interval)
    {
        drago_check = true;
        dragon_clock.restart();

        for (int i = 0; i < enemy_number; ++i) // To erase all enemy bombs
        {
            for (size_t j = 0; j < eship_ptr[i]->bombs.size(); ++j)
            {
                eship_ptr[i]->bombs.erase(eship_ptr[i]->bombs.begin() + j);
                --j;
            }
        }
        drago.firesound.play();
    }

    else if (dragon_clock.getElapsedTime().asSeconds() > 5 && drago_check)
    {
        drago_check = false;
        return true;
    }
}

void level::mangekyou_updt()
{
    float elapsed = mangekyou_clock.getElapsedTime().asSeconds();

    if (elapsed < 17)
    {
        mangekyou.setFillColor(sf::Color::Transparent);
        background1.setFillColor(sf::Color::White);
        background2.setFillColor(sf::Color::White);
    }
    else if (elapsed < 20)
    {
        mangekyou_status = true;
        mangekyou.setFillColor(sf::Color::White);
        mangekyou_sound.play();

        if (mangekyou.getScale().x > 1)
        {
            mangekyou.setScale(mangekyou.getScale().x - 0.1f, mangekyou.getScale().y - 0.1f);
        }
        else
        {
            background1.setFillColor(sf::Color::Red);
            background2.setFillColor(sf::Color::Red);
            mangekyou.rotate(0.3f);
        }
    }
    else if (mangekyou.getScale().x < 50)
    {
        mangekyou.setScale(mangekyou.getScale().x + 0.1f, mangekyou.getScale().y + 0.1f);
    }
    else
    {
        mangekyou_clock.restart();
        mangekyou_status=false;
    }
}
