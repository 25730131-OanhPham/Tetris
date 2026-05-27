#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "Block.h"

using namespace std;

class Board {
private:
    static const int HEIGHT = 20;
    static const int WIDTH = 15;
    char grid[HEIGHT][WIDTH];
    int score;
    int fallSpeed;

public:
    Board();
    ~Board();
    
    // Board management
    void init();
    void draw() const;
    void clearLine();
    
    // Block operations on board
    void placeBlock(int x, int y, const Block& block);
    void removeBlock(int x, int y, const Block& block);
    
    // Collision detection
    bool canMove(int x, int y, const Block& block, int dx, int dy) const;
    bool canRotate(int x, int y, const Block& block) const;
    bool isGameOver(int x, int y, const Block& block) const;
    
    // Getter/Setter
    int getScore() const { return score; }
    void addScore(int points) { score += points; }
    int getFallSpeed() const { return fallSpeed; }
    void updateFallSpeed();
    
    // Debug
    void printGrid() const;
    
    // Helper
    char getCell(int row, int col) const;
    void setCell(int row, int col, char value);
    int getHeight() const { return HEIGHT; }
    int getWidth() const { return WIDTH; }
};

#endif
