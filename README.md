# flappy-bird-game
Flappy Bird Clone is a 2D arcade game built with C++ and SFML that recreates the classic Flappy Bird experience. The project follows object-oriented programming principles and includes realistic bird movement, procedurally generated obstacles, collision detection, sound effects, fullscreen gameplay, and file-based high-score persistence.
# 🐦 Flappy Bird Clone

A Flappy Bird-inspired 2D arcade game developed in **C++** using the **SFML (Simple and Fast Multimedia Library)** framework. This project recreates the classic gameplay experience with smooth bird physics, randomly generated pipes, sound effects, fullscreen support, and a persistent high-score system.

---

## 🎮 Gameplay

Control the bird and navigate through an endless series of pipes without colliding with obstacles or the ground. Earn points by successfully passing through pipes and try to beat your highest score.

---

## ✨ Features

- 🐦 Smooth bird movement with realistic gravity and flap mechanics
- 🚧 Procedurally generated pipe obstacles
- 💥 Accurate collision detection
- 🏆 Persistent high-score system using file handling
- 🔊 Background music and sound effects
- ⏸️ Multiple game states:
  - Running
  - Paused
  - Game Over
- 🖥️ Fullscreen gameplay experience
- 🏗️ Object-Oriented Programming (OOP) architecture
- 📁 Modular code structure for easy maintenance

---

## 🛠️ Technologies Used

| Technology | Purpose |
|------------|-----------|
| C++ | Core Programming Language |
| SFML | Graphics, Audio, Window Management |
| File Handling | High Score Persistence |
| OOP Concepts | Code Organization and Reusability |

---

## 📂 Project Structure

```
BirdGame/
│
├── main.cpp
├── Game.hpp
├── Game.cpp
├── Bird.hpp
├── Bird.cpp
├── PipeSystem.hpp
├── PipeSystem.cpp
├── HighScore.hpp
├── HighScore.cpp
├── assets/
│   ├── Bird.png
│   ├── Pipes.png
│   ├── font.ttf
│   └── bgm.wav
├── highscore.txt
└── README.md
```

---

## 🚀 Getting Started

### Prerequisites

- C++ Compiler (GCC, MinGW, MSVC, etc.)
- SFML Library (Version 2.5 or later)
- Visual Studio Code or any C++ IDE

---

### Installation

#### 1. Clone the Repository

```bash
git clone https://github.com/your-username/FlappyBird-CPP.git
cd FlappyBird-CPP
```

#### 2. Install SFML

Download SFML from:

https://www.sfml-dev.org/download.php

Configure the include directories and linker settings according to your compiler.

---

### 3. Build and Run

Compile all source files along with SFML libraries.

Example (MinGW):

```bash
g++ main.cpp Bird.cpp PipeSystem.cpp HighScore.cpp Game.cpp -o FlappyBird \
-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

Run:

```bash
./FlappyBird
```

---

## 🎯 Controls

| Key | Action |
|-------|----------|
| Space | Flap / Jump |
| P | Pause / Resume |
| Esc | Exit Game |

---

## 🏆 High Score System

The game automatically saves the highest score achieved by the player in:

```text
highscore.txt
```

The score persists even after closing the game.

---

## 📸 Screenshots

Add gameplay screenshots here.

Example:

```
screenshots/gameplay.png
screenshots/gameover.png
```

---

## 📚 Concepts Demonstrated

- Object-Oriented Programming
- Game Loop Implementation
- Event Handling
- Collision Detection
- Random Obstacle Generation
- File Handling in C++
- Audio Integration using SFML
- Resource Management

---

## 🔮 Future Improvements

- Multiple difficulty levels
- Animated bird sprites
- Main menu and settings screen
- Different themes and backgrounds
- Leaderboard system
- Mobile adaptation

---

## 🤝 Contributing

Contributions, suggestions, and improvements are welcome.

Feel free to fork the repository and submit a pull request.

---

## 📄 License

This project is developed for educational purposes and personal learning.

---

## 👨‍💻 Author

**Adityabarna Das**

B.Tech CSE Student | Aspiring Game Developer

*"Code. Play. Learn. Repeat."*
