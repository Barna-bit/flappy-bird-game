#include "Bird.hpp"
#include <algorithm>

Bird::Bird(const sf::Texture& tex, sf::Vector2f pos, float scale) : m_sprite(tex), m_vy(0) {
    sf::Vector2u sz = tex.getSize();
    m_sprite.setOrigin(sz.x * 0.5f, sz.y * 0.5f);
    m_sprite.setScale(scale, scale);
    m_sprite.setPosition(pos);
    m_half = sf::Vector2f(sz.x * 0.5f * scale, sz.y * 0.5f * scale);
}

void Bird::reset(sf::Vector2f pos) {
    m_sprite.setPosition(pos);
    m_vy = 0;
    m_sprite.setRotation(0.f);
}

void Bird::flap(float impulse) {
    m_vy = impulse;
}

void Bird::update(float dt, float gravity, float maxFall) {
    m_vy += gravity * dt;
    if (m_vy > maxFall) m_vy = maxFall;
    m_sprite.move(0.f, m_vy * dt);
    
    float rotation = m_vy * 0.1f;
    if (rotation > 30.f) rotation = 30.f;
    if (rotation < -30.f) rotation = -30.f;
    m_sprite.setRotation(rotation);
}

sf::FloatRect Bird::hitbox() const {
    return m_sprite.getGlobalBounds();
}
