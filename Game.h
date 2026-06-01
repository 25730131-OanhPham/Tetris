#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Block.h"
#include <chrono>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#endif

class Game {
private:
    Board board;
    Block currentBlock;
    int blockX;
    int blockY;
    bool isRunning;
    std::chrono::steady_clock::time_point lastFallTime;
    
    // Internal helpers
    void spawnNewBlock();
    void dropBlock();
    
public:
    Game();
    ~Game();
    
    // Game lifecycle
    void init();
    void run();
    void update();
    void handleInput();
    void render();
    
    // Terminal setup/cleanup
    void setupTerminal();
    void restoreTerminal();
    void lockBlock();
    void checkGameOver();
    
    // Helper
    bool isGameRunning() const { return isRunning; }
    void quit() { isRunning = false; }
};

#endif
