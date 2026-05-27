#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <cctype>
#include <windows.h>
#include <conio.h>

using namespace std;

// Windows input handling
bool kbhit_cross() {
    return _kbhit();
}

char getch_cross() {
    return _getch();
}

void sleep_ms(int ms) {
    Sleep(ms);
}

Game::Game() : blockX(0), blockY(0), isRunning(false) {
    srand((unsigned)time(0));
}

Game::~Game() {
}

void Game::init() {
    board.init();
    spawnNewBlock();
    isRunning = true;
    lastFallTime = std::chrono::steady_clock::now();
}

void Game::spawnNewBlock() {
    currentBlock.spawn();
    blockX = 5;  // Center of the board
    blockY = 0;  // Top of the board
}

void Game::handleInput() {
    if (kbhit_cross()) {
        char input = getch_cross();
        input = tolower(input);
        
        // Move left
        if (input == 'a') {
            board.removeBlock(blockX, blockY, currentBlock);
            if (board.canMove(blockX, blockY, currentBlock, -1, 0)) {
                blockX--;
            }
            board.placeBlock(blockX, blockY, currentBlock);
        }
        
        // Move right
        if (input == 'd') {
            board.removeBlock(blockX, blockY, currentBlock);
            if (board.canMove(blockX, blockY, currentBlock, 1, 0)) {
                blockX++;
            }
            board.placeBlock(blockX, blockY, currentBlock);
        }
        
        // Rotate
        if (input == 'w') {
            board.removeBlock(blockX, blockY, currentBlock);
            if (board.canRotate(blockX, blockY, currentBlock)) {
                currentBlock.rotate();
            }
            board.placeBlock(blockX, blockY, currentBlock);
        }
        
        // Fast fall
        if (input == 'x') {
            board.removeBlock(blockX, blockY, currentBlock);
            if (board.canMove(blockX, blockY, currentBlock, 0, 1)) {
                blockY++;
            }
            board.placeBlock(blockX, blockY, currentBlock);
        }
        
        // Quit
        if (input == 'q') {
            isRunning = false;
        }
    }
}

void Game::dropBlock() {
    auto currentTime = std::chrono::steady_clock::now();
    int elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        currentTime - lastFallTime
    ).count();
    
    if (elapsedTime >= board.getFallSpeed()) {
        board.removeBlock(blockX, blockY, currentBlock);
        
        if (board.canMove(blockX, blockY, currentBlock, 0, 1)) {
            blockY++;
            board.placeBlock(blockX, blockY, currentBlock);
        } else {
            // Can't move down, lock the block
            board.placeBlock(blockX, blockY, currentBlock);
            lockBlock();
        }
        
        lastFallTime = currentTime;
    }
}

void Game::lockBlock() {
    // Clear lines if any
    board.clearLine();
    board.updateFallSpeed();
    
    // Spawn new block
    spawnNewBlock();
    
    // Check if new block collides immediately (game over)
    if (board.isGameOver(blockX, blockY, currentBlock)) {
        isRunning = false;
        return;
    }
    
    board.placeBlock(blockX, blockY, currentBlock);
}

void Game::update() {
    handleInput();
    dropBlock();
}

void Game::render() {
    board.draw();
}

void Game::run() {
    init();
    
    while (isRunning) {
        update();
        render();
        sleep_ms(16);  // ~60 FPS
    }
    
    // Game over screen
    system("cls");
    cout << endl;
    cout << "╔════════════════════╗" << endl;
    cout << "║     GAME OVER!     ║" << endl;
    cout << "╚════════════════════╝" << endl;
    cout << "Final Score: " << board.getScore() << endl;
    cout << endl;
}
