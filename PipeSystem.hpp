#ifndef PIPESYSTEM_HPP
#define PIPESYSTEM_HPP

#include <SFML/Graphics.hpp>
#include <vector>

struct PipePair {
    float x;
    float gapY;
    bool active;
    bool scored;
};

class PipeSystem {
private:
    std::vector<PipePair> m_pipes;
    sf::Texture m_tex;
    float m_width;
    float m_gapH;

public:
    PipeSystem() : m_width(100.f), m_gapH(250.f) {}
    PipeSystem(const sf::Texture& t, float w);
    void reset(float startX, float groundY);
    void update(float dt, float windowW, float groundY, int& score);
    void draw(sf::RenderWindow& rw);
    bool collides(const sf::FloatRect& bird, float groundY) const;
};

#endif
