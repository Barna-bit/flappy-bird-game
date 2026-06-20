#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>
#include "Bird.hpp"
#include "PipeSystem.hpp"
#include "HighScore.hpp"

class Game {
private:
    sf::RenderWindow m_window;
    
    sf::Texture m_birdTex;
    sf::Texture m_pipeTex;
    sf::Font m_font;
    
    std::unique_ptr<Bird> m_bird;
    PipeSystem m_pipes;
    
    enum State { Running, Paused, GameOver };
    State m_state;
    int m_score;
    float m_groundY;
    
    HighScore m_highScore;
    sf::Text m_scoreText;
    sf::Text m_highScoreText;
    
    // Simple SFML Audio
    sf::Music m_bgm;
    sf::SoundBuffer m_flapBuffer;
    sf::Sound m_flapSound;
    sf::SoundBuffer m_collisionBuffer;
    sf::Sound m_collisionSound;

    void rebuildLayout();
    void resetRun();
    void pollEvents();
    void update(float dt);
    void draw();

public:
    Game();
    ~Game();
    int run();
};

#endif
