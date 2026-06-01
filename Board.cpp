#include "Board.h"
#include <cstdlib>
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

Board::Board() : score(0), fallSpeed(200) {
    init();
}

Board::~Board() {
}

void Board::init() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                grid[i][j] = '#';
            } else {
                grid[i][j] = ' ';
            }
        }
    }
    score = 0;
    fallSpeed = 200;
}

char Board::getCell(int row, int col) const {
    if (row >= 0 && row < HEIGHT && col >= 0 && col < WIDTH) {
        return grid[row][col];
    }
    return '#'; // Out of bounds treated as wall
}

void Board::setCell(int row, int col, char value) {
    if (row >= 0 && row < HEIGHT && col >= 0 && col < WIDTH) {
        grid[row][col] = value;
    }
}

void Board::placeBlock(int x, int y, const Block& block) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block.shape[i][j] != ' ') {
                int row = y + i;
                int col = x + j;
                if (row >= 0 && row < HEIGHT && col >= 0 && col < WIDTH) {
                    grid[row][col] = block.shape[i][j];
                }
            }
        }
    }
}

void Board::removeBlock(int x, int y, const Block& block) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block.shape[i][j] != ' ') {
                int row = y + i;
                int col = x + j;
                if (row >= 0 && row < HEIGHT && col >= 0 && col < WIDTH) {
                    grid[row][col] = ' ';
                }
            }
        }
    }
}

bool Board::canMove(int x, int y, const Block& block, int dx, int dy) const {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block.shape[i][j] != ' ') {
                int newRow = y + i + dy;
                int newCol = x + j + dx;
                // Allow pieces that are above the visible board (newRow < 0)
                // but still prevent moving out of horizontal bounds or below the board.
                if (newCol < 0 || newCol >= WIDTH) {
                    return false;
                }
                if (newRow >= HEIGHT) {
                    return false;
                }
                // Only check grid contents when the target row is within the board
                if (newRow >= 0) {
                    if (grid[newRow][newCol] != ' ') {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool Board::canRotate(int x, int y, const Block& block) const {
    // Create a temporary rotated block
    char tempShape[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tempShape[i][j] = block.shape[3 - j][i];
        }
    }
    
    // Check if rotation is valid
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tempShape[i][j] != ' ') {
                int row = y + i;
                int col = x + j;
                // Allow rotation when part of the piece is above the visible board (row < 0)
                if (col < 0 || col >= WIDTH) {
                    return false;
                }
                if (row >= HEIGHT) {
                    return false;
                }
                if (row >= 0) {
                    if (grid[row][col] != ' ') {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool Board::isGameOver(int x, int y, const Block& block) const {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block.shape[i][j] != ' ') {
                int row = y + i;
                int col = x + j;
                if (row >= 0 && row < HEIGHT && col >= 0 && col < WIDTH) {
                    if (grid[row][col] != ' ') {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void Board::clearLine() {
    int lines = 0;
    
    for (int i = HEIGHT - 2; i > 0; i--) {
        bool fullLine = true;
        for (int j = 1; j < WIDTH - 1; j++) {
            if (grid[i][j] == ' ') {
                fullLine = false;
                break;
            }
        }
        
        if (fullLine) {
            // Move lines down
            for (int ii = i; ii > 1; ii--) {
                for (int jj = 0; jj < WIDTH; jj++) {
                    grid[ii][jj] = grid[ii - 1][jj];
                }
            }
            // Clear top line (keep borders)
            for (int jj = 1; jj < WIDTH - 1; jj++) {
                grid[1][jj] = ' ';
            }
            
            i++; // Check this line again
            lines++;
            
            draw();
#if defined(_WIN32) || defined(_WIN64)
            Sleep(200);
#else
            usleep(200 * 1000);
#endif
        }
    }
    
    // Add score based on number of lines cleared
    switch (lines) {
        case 1: addScore(100); break;
        case 2: addScore(300); break;
        case 3: addScore(500); break;
        case 4: addScore(800); break;
    }
}

void Board::updateFallSpeed() {
    if (score >= 1000) {
        fallSpeed = 150;
    } else {
        fallSpeed = 200;
    }
}

void Board::draw() const {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
    
    // Top border
    cout << "╔";
    for (int i = 1; i < WIDTH - 1; i++) {
        cout << "══";
    }
    cout << "╗" << endl;
    
    // Board content
    for (int i = 1; i < HEIGHT - 1; i++) {
        cout << "║";
        for (int j = 1; j < WIDTH - 1; j++) {
            if (grid[i][j] != ' ') {
                cout << "■ ";
            } else {
                cout << "  ";
            }
        }
        cout << "║" << endl;
    }
    
    // Bottom border
    cout << "╚";
    for (int i = 1; i < WIDTH - 1; i++) {
        cout << "══";
    }
    cout << "╝" << endl;
    
    cout << " Score: " << score << endl;
}

void Board::printGrid() const {
    cout << "Grid content:" << endl;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}
