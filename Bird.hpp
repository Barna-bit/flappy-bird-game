#ifndef BIRD_HPP
#define BIRD_HPP

#include <SFML/Graphics.hpp>

class Bird {
private:
    sf::Sprite m_sprite;
    sf::Vector2f m_half;
    float m_vy;

public:
    Bird(const sf::Texture& tex, sf::Vector2f pos, float scale);
    void reset(sf::Vector2f pos);
    void flap(float impulse);
    void update(float dt, float gravity, float maxFall);
    void draw(sf::RenderWindow& rw) { rw.draw(m_sprite); }
    sf::FloatRect hitbox() const;
};

#endif
