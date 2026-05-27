#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Block.h"
#include <chrono>
#include <windows.h>
#include <conio.h>

class Game {
private:
    Board board;
    Block currentBlock;
    int blockX;
    int blockY;
    bool isRunning;
    std::chrono::steady_clock::time_point lastFallTime;
    
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
    d lockBlock();
    void checkGameOver();
    
    // Helper
    bool isGameRunning() const { return isRunning; }
    void quit() { isRunning = false; }
};

#endif
