#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;
#define H 20
#define W 15

char board[H][W] = {};

char curBlock[4][4] = {};

int x, y, b;
char blocks[][4][4] ={
        // I-block (hình thẳng - dọc)
        {{' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '}},
        // I-block (hình thẳng - ngang)
        {{' ',' ',' ',' '},
         {'I','I','I','I'},
         {' ',' ',' ',' '},
         {' ',' ',' ',' '}},
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
            if (i == 0 || i == H-1 || j ==0 || j == W-1) board[i][j] = '#';
            else board[i][j] = ' ';
}
void draw(){
    system("cls");

    for (int i = 0 ; i < H ; i++, cout<<endl)
        for (int j = 0 ; j < W ; j++) cout<<board[i][j];
}
void removeLine()
{
    int i,j;
    for (i = H-2 ; i > 0 ; i-- )
        {
        for (j = 1 ; j < W-1 ; j++)
            if (board[i][j] == ' ') break;
        if (j == W-1)
        {
            for (int ii = i ; ii > 0 ; ii--)
                for (int jj = 0; jj < W-1; jj++)
                    board[ii][jj] = board[ii-1][jj];
            i++;
            draw();
            _sleep(400);
        }
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
    initBoard();
    while (1){
        boardDelBlock();
        if (kbhit()){
            char c = getch();
            if ((c == 'a' || c == 'A') && canMove(-1,0)) x--;
            if ((c == 'd' || c == 'D') && canMove( 1,0)) x++;
            if ((c == 'x' || c == 'X') && canMove( 0,1)) y++;
            if ((c == 'w' || c == 'W') && CanRotate()) Rotate();
            if (c == 'q' || c == 'Q') break;
        }
        if (canMove(0,1)) y++;
        else{
            block2Board();
            x = 5; y = 0; b = rand()%7;
            if (!canMove(0, 1)) {
                system("cls");
                cout << "Game Over!" << endl;
                break;
            }
        }
        block2Board();
        draw();
        Sleep(150);
    }
    return 0;
}
