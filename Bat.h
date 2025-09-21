#pragma once
#include<SFML/Graphics.hpp>

using namespace std;

class Bat {
    private:
        sf::Vector2f m_Position;
        sf::RectangleShape m_Shape;

        float m_Speed = 1000.0f;
        bool m_MovingRight = false, m_MovingLeft = false;

    public:
        Bat(float startX, float startY){
            m_Position.x = startX;
            m_Position.y = startY;

            m_Shape.setSize({100, 5});
            m_Shape.setPosition(m_Position);
        }

        sf::FloatRect getPosition(){
            return m_Shape.getGlobalBounds();
        }

        sf::RectangleShape getShape(){
            return m_Shape;
        }

        void moveLeft(){
            m_MovingLeft = true;
        }

        void moveRight(){
            m_MovingRight = true;
        }

        void stopLeft(){
            m_MovingLeft = false;
        }

        void stopRight(){
            m_MovingRight = false;
        }

        void update(sf::Time dt){
            if(m_MovingLeft) m_Position.x -= m_Speed * dt.asSeconds();
            if(m_MovingRight) m_Position.x += m_Speed * dt.asSeconds();
            m_Shape.setPosition(m_Position);
        }

};