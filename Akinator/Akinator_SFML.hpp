#ifndef AKINATOR_SFML_HPP
#define AKINATOR_SFML_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../BinaryTree/Tree.h"
#include "../BinaryTree/TreeDump.h"

const unsigned int FPS = 60;
const unsigned int window_size_x = 960;
const unsigned int window_size_y = 640;

const sf::Color idleColor    = sf::Color(100, 0, 0, 255);
const sf::Color hoverColor   = sf::Color(180, 0, 0, 255);
const sf::Color pressedColor = sf::Color(50,  0, 0, 255);

enum class GameState {
    Menu,
    Playing,
    PlayingEnd,
    ShowTree,
};

enum ButtonState { 
    BTN_IDLE    = 0, 
    BTN_HOVER   = 1, 
    BTN_PRESSED = 2,
};

class Button {
public:
    sf::RectangleShape m_shape;
    sf::Text m_text;

    sf::Color m_idleColor;
    sf::Color m_hoverColor;
    sf::Color m_pressedColor;

    ButtonState m_state;

    Button(float x,     float y, 
           float width, float height,
           sf::Font* font, std::wstring textStr, unsigned characterSize) :
        
        m_shape         (sf::Vector2f(width, height)),
        m_text          (textStr, *font, characterSize),
        m_state         (BTN_IDLE),
        m_idleColor     (idleColor),
        m_pressedColor  (pressedColor),
        m_hoverColor    (hoverColor)

    {
        m_shape.setPosition(x, y);
        m_shape.setFillColor(m_idleColor);

        m_text.setFillColor(sf::Color::White); 

        sf::FloatRect textRect = m_text.getLocalBounds();
        m_text.setOrigin(   textRect.left + textRect.width  / 2.0f,
                            textRect.top  + textRect.height / 2.0f);
        m_text.setPosition(x + width / 2.0f, y + height / 2.0f);
    }

    void update(const sf::Vector2f& mousePos) {
        m_state = BTN_IDLE;

        if (m_shape.getGlobalBounds().contains(mousePos)) {
            m_state = BTN_HOVER;

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                m_state = BTN_PRESSED;
            }
        }

        switch (m_state) {
            case BTN_IDLE:    m_shape.setFillColor(m_idleColor);    break;
            case BTN_HOVER:   m_shape.setFillColor(m_hoverColor);   break;
            case BTN_PRESSED: m_shape.setFillColor(m_pressedColor); break;
            default:                                                break;
        }
    }

    void render(sf::RenderTarget& target) {
        target.draw(m_shape);
        target.draw(m_text);
    }

    bool isPressed() const {
        return m_state == BTN_PRESSED;
    }
};

int play_akinator_sfml (FILE* fp, Node_t* root);


#endif /* AKINATOR_SFML_HPP */