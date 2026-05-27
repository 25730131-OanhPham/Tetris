#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <block.h>

using namespace std;

#define H 20
#define W 15
int fallSleep = 200;  // toc do roi ( ms )
char board[H][W] = {};
int score = 0;

char curBlock[4][4] = {};

int x, y, b;
char blocks[][4][4] ={
        // I-block (hình thẳng - dọc)
        {{' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '}},
        // O-block (hình vuông)
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        // T-block (hình T - lên)
        {{' ',' ',' ',' '},
         {' ','T',' ',' '},
         {'T','T','T',' '},
         {' ',' ',' ',' '}},
        // S-block (hình S)
        {{' ',' ',' ',' '},
         {' ','S','S',' '},
         {'S','S',' ',' '},
         {' ',' ',' ',' '}},
        // Z-block (hình Z)
        {{' ',' ',' ',' '},
         {'Z','Z',' ',' '},
         {' ','Z','Z',' '},
         {' ',' ',' ',' '}},
        // J-block (hình J)
        {{' ',' ',' ',' '},
         {'J',' ',' ',' '},
         {'J','J','J',' '},
         {' ',' ',' ',' '}},
        // L-block (hình L)
        {{' ',' ',' ',' '},
         {' ',' ','L',' '},
         {'L','L','L',' '},
         {' ',' ',' ',' '}}
};

bool canMove(int dx, int dy){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (blocks[b][i][j] != ' ') {
                int xt = x + j + dx;
                int yt = y + i + dy;
                if (xt < 1 || xt >= W-1 || yt < 1 || yt >= H-1 ) return false;
                if (board[yt][xt] != ' ') return false;
            }
  
    return true;
}

void block2Board(){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (blocks[b][i][j] != ' ')
                board[y+i][x+j] = blocks[b][i][j];
}

void boardDelBlock(){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (blocks[b][i][j] != ' ')
                board[y+i][x+j] = ' ';
}

void initBoard(){
    for (int i = 0 ; i < H ; i++)
        for (int j = 0 ; j < W ; j++)
            if (i == 0 || i == H-1 || j ==0 || j == W-1) 
              board[i][j] = '#';
            else board[i][j] = ' ';
}

void draw(){
    system("cls");

    // Vien tren
    wcout << "╔";
    for (int i = 0; i < W; i++) {
        cout << "══";
    }
    wcout << "╗" << endl;
    
    // Noi dung BOARD
    for (int i = 0; i < H; i++) {
        wcout << "║";
        for (int j = 0; j < W; j++) {
            if (board[i][j] != ' ') {
                wcout << "██";
            } else {
                wcout << "  ";
            }
        }
        wcout << "║" << endl;
    }
    
    // Vien duoi
    wcout << "╚";
    for (int i = 0; i < W; i++) {
        wcout << "══";
    }
    wcout << "╝" << endl;
    
    wcout << " Score: " << score << endl;
        
}
void capNhatTocDo(){
    if (score >= 1000){
        fallSleep = 150;
    }
    else {
        fallSleep = 200;
   }
}

void removeLine(){    
    int i, j , lines = 0;
    for (i = H-2; i > 0; i-- ){
        for ( j = 0; j < W; j ++)
            if (board [i][j] == ' ') break;
        
        if (j == W) {
            for (int ii = i; ii > 0; ii --)
            for (int jj = 0; jj < W; jj ++)
            board [ii][jj] = board [ii - 1][jj];

            i++;
            lines++;
            draw();
            _sleep(200);
        }    
    }
    
    switch (lines)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;    
    case 3:
        score += 500;
        break;
    case 4:
        score += 800;
        break;        
    }
}

bool CanRotate(){
    char temp[4][4];

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            temp[i][j] = curBlock[3-j][i];
        }
    }
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++)
            if (temp[i][j] != ' '){
                int xt = x + j;
                int yt = y + i;
                if (xt < 1 || xt >= W-1 || yt < 1 || yt >= H-1 ) return false;
                if (board[yt][xt] != ' ') return false;
            }
    }
};

void Rotate(){

    char temp[4][4];

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            temp[i][j] = curBlock[i][j];

    for(int i = 0; i < 4; i ++)
        for(int j  = 0; j < 4; j++)
            curBlock[i][j] = temp[3-j][i];
};

int main()
{
    srand(time(0));
    x = 5; y = 0; b = rand()%7;
int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);

    // KHỞI TẠO GAME
    srand((unsigned)time(0));
    initBoard();
    
    x = 5;
    y = 0;
    b = rand() % 7;

    // GAME LOOP
    while (1) {

        boardDelBlock();

        // ĐIỀU KHIỂN
        if (kbhit()) {
            char c = getch();
            if ((c == 'a' || c == 'A') && canMove(-1,0)) x--;
            if ((c == 'd' || c == 'D') && canMove( 1,0)) x++;
            if ((c == 'x' || c == 'X') && canMove( 0,1)) y++;
            if ((c == 'w' || c == 'W') && CanRotate()) Rotate();
            if (c == 'q' || c == 'Q') break;

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
            y++;
        }
        else {

            // Khóa khối cũ
            block2Board();
            removeLine();
            capNhatTocDo();
          
            x = 5; y = 0; b = rand()%7;
          
            if (!canMove(0, 1)) {
                system("cls");
                wcout << endl;
                wcout << L"╔════════════════════╗" << endl;
                wcout << L"║     GAME OVER!     ║" << endl;
                wcout << "║  Score: " << score << "        ║" << endl;
                wcout << L"╚════════════════════╝" << endl;

                break;
            }
        }

        block2Board();
        draw();
        Sleep(fallSleep);
    }

    return 0;
}
