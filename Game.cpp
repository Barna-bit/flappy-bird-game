#include "Game.hpp"

Game::~Game() { 
    m_bgm.stop(); 
}

Game::Game() : m_highScore("highscore.txt")
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    unsigned int width = desktop.width > 0 ? desktop.width : 1920;
    unsigned int height = desktop.height > 0 ? desktop.height : 1080;
    m_window.create(sf::VideoMode(width, height), "Flappy Bird", sf::Style::Fullscreen);
    m_window.setFramerateLimit(60);
    m_window.setKeyRepeatEnabled(false); // WSL FIX: Prevent spacebar spam from killing audio
    
    // Load Assets
    m_birdTex.loadFromFile("assets/Bird.png");
    m_pipeTex.loadFromFile("assets/Pipes.png");
    m_font.loadFromFile("assets/font.ttf");

    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(50);
    m_scoreText.setFillColor(sf::Color::Black);
    m_scoreText.setPosition(50, 50);

    m_highScoreText.setFont(m_font);
    m_highScoreText.setCharacterSize(50);
    m_highScoreText.setFillColor(sf::Color::Black);
    m_highScoreText.setPosition(width - 450, 50);
    
    m_highScore.load();
    
    // Simple Audio Setup
    if (m_bgm.openFromFile("assets/bgm.wav")) {
        m_bgm.setLoop(false); // Disable native loop to prevent race condition
        m_bgm.setVolume(40.0f);
        m_bgm.play();
    }
    
    if (m_flapBuffer.loadFromFile("assets/flap.wav")) {
        m_flapSound.setBuffer(m_flapBuffer);
    }
    
    if (m_collisionBuffer.loadFromFile("assets/collision.wav")) {
        m_collisionSound.setBuffer(m_collisionBuffer);
    }

    rebuildLayout();
    resetRun();
}

void Game::rebuildLayout() {
    sf::Vector2u sz = m_window.getSize();
    m_groundY = sz.y * 0.9f;
    m_bird = std::unique_ptr<Bird>(new Bird(m_birdTex, sf::Vector2f(sz.x * 0.3f, sz.y * 0.4f), 0.15f));
    m_pipes = PipeSystem(m_pipeTex, 100.0f);
}

void Game::resetRun() {
    m_collisionSound.stop();
    m_flapSound.stop();
    m_state = Running;
    m_score = 0;
    m_pipes.reset(m_window.getSize().x, m_groundY);
    if (m_bird) {
        m_bird->reset(sf::Vector2f(m_window.getSize().x * 0.3f, m_window.getSize().y * 0.4f));
    }
}

void Game::pollEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) m_window.close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) m_window.close();
            if (event.key.code == sf::Keyboard::Space) {
                if (m_state == Running) { 
                    if (m_bird) m_bird->flap(-650.f); 
                    if (m_flapSound.getStatus() != sf::Sound::Playing) {
                        m_flapSound.play(); 
                    }
                }
                else if (m_state == GameOver) {
                    resetRun();
                }
            }
        }
    }
}

void Game::update(float dt) {
    // WSL BUG FIX: Manually loop music 0.5s before end to prevent PulseAudio crash
    if (m_bgm.getStatus() == sf::Music::Playing) {
        if (m_bgm.getPlayingOffset().asSeconds() >= 23.5f) {
            m_bgm.setPlayingOffset(sf::seconds(0.f));
        }
    } else if (m_bgm.getStatus() == sf::Music::Stopped) {
        m_bgm.play(); // Fallback if it somehow stops
    }

    if (m_state != Running) return;
    
    if (m_bird) {
        // Apply simple physics
        m_bird->update(dt, 2200.f, 1000.f);
        
        // Strict Collision Detection
        if (m_pipes.collides(m_bird->hitbox(), m_groundY) || m_bird->hitbox().top > m_groundY) {
            if (m_state == Running && m_collisionSound.getStatus() != sf::Sound::Playing) {
                m_collisionSound.play();
            }
            m_state = GameOver;
            m_highScore.saveIfHigher(m_score);
        }
    }
    
    m_pipes.update(dt, m_window.getSize().x, m_groundY, m_score);
}

void Game::draw() {
    m_window.clear(sf::Color(70, 130, 240));
    m_pipes.draw(m_window);
    if (m_bird) m_bird->draw(m_window);
    
    sf::RectangleShape ground(sf::Vector2f((float)m_window.getSize().x, m_window.getSize().y - m_groundY));
    ground.setPosition(0, m_groundY);
    ground.setFillColor(sf::Color(50, 40, 30));
    m_window.draw(ground);

    m_scoreText.setString("SCORE: " + std::to_string(m_score));
    m_highScoreText.setString("HIGH SCORE: " + std::to_string(m_highScore.value()));
    m_window.draw(m_scoreText);
    m_window.draw(m_highScoreText);
    
    if (m_state == GameOver) {
        sf::RectangleShape overlay(sf::Vector2f((float)m_window.getSize().x, (float)m_window.getSize().y));
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        m_window.draw(overlay);

        sf::Text go("GAME OVER\nSpace to Restart", m_font, 100);
        sf::FloatRect b = go.getLocalBounds();
        go.setOrigin(b.width/2, b.height/2);
        go.setPosition(m_window.getSize().x/2.f, m_window.getSize().y/2.f);
        m_window.draw(go);
    }
    m_window.display();
}

int Game::run() {
    sf::Clock clock;
    while (m_window.isOpen()) {
        pollEvents();
        
        // Basic frame update without complex accumulators
        update(clock.restart().asSeconds());
        
        draw();
    }
    return 0;
}
