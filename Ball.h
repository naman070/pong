#pragma once

#include<SFML/Graphics.hpp>

using namespace std;

class Ball{
    private:
        sf::Vector2f m_Position;
        sf::RectangleShape m_Shape;

        float m_Speed = 900.0f, m_DirectionX = .2f, m_DirectionY = .2f;
        bool m_BallMoving = false;


    public:
        Ball(float startX, float startY){
            m_Position.x = startX;
            m_Position.y = startY;

            m_Shape.setSize({10, 10});
            m_Shape.setPosition(m_Position);
        }

        void resetPosition(float startX, float startY){
            m_Position.x = startX;
            m_Position.y = startY;
            m_Shape.setPosition({startX, startY});
        }

        sf::FloatRect getPosition(){
            return m_Shape.getGlobalBounds();
        }

        sf::RectangleShape getShape(){
            return m_Shape;
        }

        float getXVelocity(){
            return m_DirectionX;
        }

        float getYVelocity(){
            return m_DirectionY;
        }

        void reboundSides(){
            m_DirectionX = -m_DirectionX;
        }

        void reboundBatOrTop(){
            m_DirectionY = -m_DirectionY;
        }

        void reboundBottom(){
            m_Position.y = 0;
            m_Position.x = 500;
            m_DirectionY = -m_DirectionY;
        }

        void update(sf::Time dt){
            if(m_BallMoving){
                m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();
                m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();
                m_Shape.setPosition(m_Position);
            }
        }

        void stopBallMoving(){
            m_BallMoving = false;
        }

        void startBallMoving(){
            m_BallMoving = true;
        }

        bool isBallMoving(){
            return m_BallMoving;
        }
};