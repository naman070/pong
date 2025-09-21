#include "bat.h"
#include "ball.h"
#include<SFML/Graphics.hpp>
#include<sstream>

using namespace std;

int main(){
    bool paused = true;
    int score = 0, lives = 3;
    sf::RenderWindow window (sf::VideoMode ({1920u, 1080u}), "Pong");

    // Create a bat at the bottom middle of the screen.
    Bat bat(1920/2, 1080-100);
    Ball ball(1920/2, 0);

    // Create a font.
    sf::Font font;
    (void)font.openFromFile("fonts/KOMIKAP_.ttf");
    sf::Text scoreText(font);
    sf::Text messageText(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({20, 20});

    messageText.setCharacterSize(75);
    messageText.setFillColor(sf::Color::White);
    messageText.setPosition({1920/2.0f, 1080/2.0f});

    sf::Clock clock;

    while(window.isOpen()){
        while(auto event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()) window.close();
            else if(auto keyReleased = event->getIf<sf::Event::KeyReleased>()){
                if(keyReleased->code == sf::Keyboard::Key::Left) bat.stopLeft();
                else if(keyReleased->code == sf::Keyboard::Key::Right) bat.stopRight();
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape)) window.close();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Enter)){
            paused = false;
            ball.resetPosition(1920/2, 0);
            ball.startBallMoving();

            // Reset the score and lives.
            score = 0;
            lives = 3;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left)) bat.moveLeft();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right)) bat.moveRight();
        
        sf::Time dt = clock.restart();
        if(!paused){
            bat.update(dt);
            ball.update(dt);

            // Handle ball hitting the bottom
            if(ball.getPosition().position.y > window.getSize().y){
                lives -= 1;
                ball.stopBallMoving();
                ball.resetPosition(1920/2, 0);
                if(lives <= 0){
                    paused = true;
                    messageText.setString("Out of Lives!!");

                    // Reposition the text based on new size
                    sf::FloatRect textRectNew = messageText.getLocalBounds();
                    messageText.setOrigin(
                        {textRectNew.position.x + textRectNew.size.x / 2.0f, textRectNew.position.y + textRectNew.size.y / 2.0f}
                    );
                    messageText.setPosition({1920/2.0f, 1080/2.0f});
                }
                else{
                    ball.reboundBottom();
                    ball.startBallMoving();
                }
            }

            // Handle ball hitting the top
            if(ball.getPosition().position.y <= 0){
                ball.reboundBatOrTop();
                score += 1;
            }

            // Handle ball hitting sides
            if(ball.getPosition().position.x < 0 || ball.getPosition().position.x + ball.getPosition().size.x >= window.getSize().x){
                ball.reboundSides();
            }

            // Handle ball hit the bat
            if(ball.getPosition().findIntersection(bat.getPosition())){
                ball.reboundBatOrTop();
            }
        }

        // Set the updated score and lives in the text message
        stringstream ss;
        ss << "Score: " << score << "  Lives: " << lives;
        scoreText.setString(ss.str());
        window.clear();
        window.draw(scoreText);
        window.draw(bat.getShape());
        window.draw(ball.getShape());
        if(paused) window.draw(messageText);
        window.display();
    }
}
