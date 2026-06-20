#include "PipeSystem.hpp"
#include <cstdlib>

PipeSystem::PipeSystem(const sf::Texture& t, float w) : m_tex(t), m_width(w), m_gapH(250.0f) {}

void PipeSystem::reset(float startX, float groundY) {
    m_pipes.clear();
    for(int i=0; i<3; ++i) {
        float x = startX + i * 400.0f;
        PipePair p;
        p.x = x;
        p.gapY = 200.f + (rand()%300);
        p.active = true;
        p.scored = false;
        m_pipes.push_back(p);
    }
}

void PipeSystem::update(float dt, float windowW, float groundY, int& score) {
    for (size_t i = 0; i < m_pipes.size(); ++i) {
        m_pipes[i].x -= 300.0f * dt;
        if (m_pipes[i].x < -m_width) {
            m_pipes[i].x = windowW;
            m_pipes[i].gapY = 200.f + (rand()%300);
            m_pipes[i].scored = false;
        }
        if (!m_pipes[i].scored && m_pipes[i].x < windowW * 0.3f) {
            m_pipes[i].scored = true;
            score++;
        }
    }
}

void PipeSystem::draw(sf::RenderWindow& rw) {
    for (size_t i = 0; i < m_pipes.size(); ++i) {
        sf::RectangleShape top(sf::Vector2f(m_width, m_pipes[i].gapY));
        top.setPosition(m_pipes[i].x, 0.f);
        top.setFillColor(sf::Color::Green);
        rw.draw(top);

        sf::RectangleShape bot(sf::Vector2f(m_width, 1500.f));
        bot.setPosition(m_pipes[i].x, m_pipes[i].gapY + m_gapH);
        bot.setFillColor(sf::Color::Green);
        rw.draw(bot);
    }
}

bool PipeSystem::collides(const sf::FloatRect& bird, float groundY) const {
    for (size_t i = 0; i < m_pipes.size(); ++i) {
        sf::FloatRect top(m_pipes[i].x, 0.f, m_width, m_pipes[i].gapY);
        sf::FloatRect bot(m_pipes[i].x, m_pipes[i].gapY + m_gapH, m_width, groundY - (m_pipes[i].gapY + m_gapH));
        if (bird.intersects(top) || bird.intersects(bot)) return true;
    }
    return false;
}
