#include "bat.h"
#include<SFML/Graphics.hpp>
#include<sstream>

using namespace std;

int main(){
    bool paused = true;
    int score = 0, lives = 3;
    sf::RenderWindow window (sf::VideoMode ({1920u, 1080u}), "Pong");

    // Create a bat at the bottom middle of the screen.
    Bat bat(1920/2, 1080-20);

    // Create a font.
    sf::Font font;
    (void)font.openFromFile("fonts/KOMIKAP_.ttf");
    sf::Text text(font);
    text.setCharacterSize(75);
    text.setFillColor(sf::Color::White);
    text.setPosition({20, 20});

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

            // Reset the score and lives.
            score = 0;
            lives = 3;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left)) bat.moveLeft();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right)) bat.moveRight();
        

        if(!paused){
            sf::Time dt = clock.restart();
            bat.update(dt);
        }

        // Set the updated score and lives in the text message
        stringstream ss;
        ss << "Score: " << score << "  Lives: " << lives;
        text.setString(ss.str());

        window.clear();
        window.draw(text);
        window.draw(bat.getShape());
        window.display();
    }

}