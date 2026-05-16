#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>

using namespace std;

#define H 20
#define W 10

struct Block {

    char shape[4][4];
    char type;

    int x;
    int y;
};

const Block TEMPLATE_BLOCKS[7] =
{   

    // I - BLOCK (Hình thẳng - dọc)
    {
        {
            {' ',' ',' ',' '},
            {'I','I','I','I'},
            {' ',' ',' ',' '},
            {' ',' ',' ',' '}
        },

        'I', 0, 0
    },

    // O - BLOCK (Hình vuông)
    {
        {
            {' ',' ',' ',' '},
            {' ','O','O',' '},
            {' ','O','O',' '},
            {' ',' ',' ',' '}
        },

        'O', 0, 0
    },

    // T - BLOCK (Hình chữ T - lên)

    {
        {
            {' ','T',' ',' '},
            {'T','T','T',' '},
            {' ',' ',' ',' '},
            {' ',' ',' ',' '}
        },

        'T', 0, 0
    },

    // S - BLOCK (Hình chữ S)   
    {
        {
            {' ','S','S',' '},
            {'S','S',' ',' '},
            {' ',' ',' ',' '},
            {' ',' ',' ',' '}
        },

        'S', 0, 0
    },

    // Z - BLOCK (Hình chữ Z)
    {
        {
            {'Z','Z',' ',' '},
            {' ','Z','Z',' '},
            {' ',' ',' ',' '},
            {' ',' ',' ',' '}
        },

        'Z', 0, 0
    },

    // J - BLOCK (Hình chữ J)
    {
        {
            {'J',' ',' ',' '},
            {'J','J','J',' '},
            {' ',' ',' ',' '},
            {' ',' ',' ',' '}
        },

        'J', 0, 0
    },

    // L - BLOCK (Hình chữ L)
    {
        {
            {' ',' ','L',' '},
            {'L','L','L',' '},
            {' ',' ',' ',' '},
            {' ',' ',' ',' '}
        },

        'L', 0, 0
    }
};

// BIẾN TOÀN CỤC

char board[H][W];

Block currentBlock;

// KHỞI TẠO BOARD

void initBoard() {

    for (int i = 0; i < H; i++) {

        for (int j = 0; j < W; j++) {

            board[i][j] = ' ';
        }
    }
}

// TẠO KHỐI MỚI

void spawnNewBlock() {

    int randomIndex = rand() % 7;

    currentBlock = TEMPLATE_BLOCKS[randomIndex];

    currentBlock.x = (W / 2) - 2;
    currentBlock.y = 0;
}

// KIỂM TRA VA CHẠM

bool canMove(int dx, int dy) {

    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 4; j++) {

            if (currentBlock.shape[i][j] != ' ') {

                int xt = currentBlock.x + j + dx;
                int yt = currentBlock.y + i + dy;

                // VA CHẠM BIÊN

                if (xt < 0 || xt >= W)
                    return false;

                if (yt < 0 || yt >= H)
                    return false;

                // VA CHẠM KHỐI ĐÃ KHÓA

                if (board[yt][xt] != ' ')
                    return false;
            }
        }
    }

    return true;
}

// NẠP KHỐI LÊN BOARD

void block2Board() {

    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 4; j++) {

            if (currentBlock.shape[i][j] != ' ') {

                board[currentBlock.y + i][currentBlock.x + j]
                    = currentBlock.shape[i][j];
            }
        }
    }
}

// XÓA KHỐI KHỎI BOARD

void boardDelBlock() {

    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 4; j++) {

            if (currentBlock.shape[i][j] != ' ') {

                board[currentBlock.y + i][currentBlock.x + j]
                    = ' ';
            }
        }
    }
}

// VẼ BOARD

void draw() {

    // ĐƯA CON TRỎ VỀ GÓC TRÊN
  
    COORD cursorPosition;

    cursorPosition.X = 0;
    cursorPosition.Y = 0;

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        cursorPosition
    );

    // VIỀN TRÊN

    wcout << L"╔";

    for (int i = 0; i < W; i++) {

        wcout << L"══";
    }

    wcout << L"╗" << endl;

    // NỘI DUNG BOARD
  
    for (int i = 0; i < H; i++) {

        // Viền trái
        wcout << L"║";

        for (int j = 0; j < W; j++) {

            // Ô chứa khối

            if (board[i][j] != ' ') {

                wcout << L"⬛";
            }

            // Ô trống

            else {

                wcout << L"  ";
            }
        }

        // Viền phải
        wcout << L"║";

        wcout << endl;
    }

    // VIỀN DƯỚI

    wcout << L"╚";

    for (int i = 0; i < W; i++) {

        wcout << L"══";
    }

    wcout << L"╝" << endl;
}

// MAIN

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);

    cursorInfo.bVisible = false;

    SetConsoleCursorInfo(out, &cursorInfo);

    // KHỞI TẠO GAME

    srand((unsigned)time(0));

    initBoard();

    spawnNewBlock();

    // GAME LOOP

    while (1) {

        boardDelBlock();

        // ĐIỀU KHIỂN

        if (kbhit()) {

            char c = getch();

            // Qua trái
            if ((c == 'a' || c == 'A') && canMove(-1, 0)) {

                currentBlock.x--;
            }

            // Qua phải
            if ((c == 'd' || c == 'D') && canMove(1, 0)) {

                currentBlock.x++;
            }

            // Rơi nhanh
            if ((c == 'x' || c == 'X') && canMove(0, 1)) {

                currentBlock.y++;
            }

            // Thoát game
            if (c == 'q' || c == 'Q') {

                break;
            }
        }

        // KHỐI TỰ RƠI

        if (canMove(0, 1)) {

            currentBlock.y++;
        }
        else {

            // Khóa khối cũ
            block2Board();

            // Sinh khối mới
            spawnNewBlock();

            // GAME OVER

            if (!canMove(0, 1)) {

                system("cls");

                wcout << endl;
                wcout << L"╔════════════════════╗" << endl;
                wcout << L"║     GAME OVER!     ║" << endl;
                wcout << L"╚════════════════════╝" << endl;

                break;
            }
        }

        // CẬP NHẬT BOARD

        block2Board();

        draw();

        Sleep(150);
    }

    return 0;
}