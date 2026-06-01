#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <cctype>

using namespace std;

// Cross-platform helpers
#if defined(_WIN32) || defined(_WIN64)
// Windows implementations
bool kbhit_cross() { return _kbhit(); }
char getch_cross() { return _getch(); }
void sleep_ms(int ms) { Sleep(ms); }
void clear_screen() { system("cls"); }
void Game::setupTerminal() { /* no-op on Windows */ }
void Game::restoreTerminal() { /* no-op on Windows */ }
#else
// Unix (macOS / Linux)
static struct termios orig_termios;
void Game::setupTerminal() {
    struct termios newt;
    tcgetattr(STDIN_FILENO, &orig_termios);
    newt = orig_termios;
    newt.c_lflag &= ~(ICANON | ECHO); // non-canonical, no echo
    newt.c_cc[VMIN] = 0;
    newt.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}
void Game::restoreTerminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

bool kbhit_cross() {
    struct timeval tv = {0, 0};
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    return select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv) > 0;
}

char getch_cross() {
    char c = 0;
    if (read(STDIN_FILENO, &c, 1) <= 0) return 0;
    return c;
}

void sleep_ms(int ms) { usleep(ms * 1000); }
void clear_screen() { system("clear"); }
#endif

Game::Game() : blockX(0), blockY(0), isRunning(false) {
    srand((unsigned)time(0));
}

Game::~Game() {
    restoreTerminal();
}

void Game::init() {
    board.init();
    spawnNewBlock();
    isRunning = true;
    lastFallTime = std::chrono::steady_clock::now();
    setupTerminal();
}

void Game::spawnNewBlock() {
    currentBlock.spawn();
    // Center the block horizontally and spawn inside the visible area
    blockX = board.getWidth() / 2 - 2;  // center-ish
    blockY = 1;  // Spawn at the top visible row
}

void Game::handleInput() {
    if (kbhit_cross()) {
        char input = getch_cross();
        input = tolower(input);

        // Move left
        if (input == 'a' || input == 'A') {
            board.removeBlock(blockX, blockY, currentBlock);
            if (board.canMove(blockX, blockY, currentBlock, -1, 0)) {
                blockX--;
            }
            board.placeBlock(blockX, blockY, currentBlock);
        }

        // Move right
        if (input == 'd' || input == 'D') {
            board.removeBlock(blockX, blockY, currentBlock);
            if (board.canMove(blockX, blockY, currentBlock, 1, 0)) {
                blockX++;
            }
            board.placeBlock(blockX, blockY, currentBlock);
        }

        // Rotate
        if (input == 'w' || input == 'W') {
            board.removeBlock(blockX, blockY, currentBlock);
            if (board.canRotate(blockX, blockY, currentBlock)) {
                currentBlock.rotate();
            }
            board.placeBlock(blockX, blockY, currentBlock);
        }

        // Fast fall
        if (input == 'x' || input == 'X') {
            board.removeBlock(blockX, blockY, currentBlock);
            if (board.canMove(blockX, blockY, currentBlock, 0, 1)) {
                blockY++;
            }
            board.placeBlock(blockX, blockY, currentBlock);
        }

        // Quit
        if (input == 'q' || input == 'Q') {
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
    // Temporarily place the current moving block so it's visible when drawing.
    board.placeBlock(blockX, blockY, currentBlock);
    board.draw();
    board.removeBlock(blockX, blockY, currentBlock);
}

void Game::run() {
    init();

    while (isRunning) {
        update();
        render();
        sleep_ms(16);  // ~60 FPS
    }

    // Game over screen
    clear_screen();
    cout << endl;
    cout << "╔════════════════════╗" << endl;
    cout << "║     GAME OVER!     ║" << endl;
    cout << "╚════════════════════╝" << endl;
    cout << "Final Score: " << board.getScore() << endl;
    cout << endl;
}
