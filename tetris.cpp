#include <iostream>
#include <conio.h>

using namespace std;
#define H 20
#define W 15
<<<<<<< Updated upstream
=======
int score = 0;          // điểm người chơi
int level = 1;          // cấp độ
int totalLines = 0;     // tổng số hàng đã phá

 // tốc độ rơi (ms)
int fallSpeed = 500;
>>>>>>> Stashed changes
char board[H][W] = {};

int x, y, b;
char blocks[][4][4] ={
        {{' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '}},
        {{' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'I','I','I','I'},
         {' ',' ',' ',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','T',' ',' '},
         {'T','T','T',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','S','S',' '},
         {'S','S',' ',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'Z','Z',' ',' '},
         {' ','Z','Z',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'J',' ',' ',' '},
         {'J','J','J',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ',' ','L',' '},
         {'L','L','L',' '},
         {' ',' ',' ',' '}}
};
<<<<<<< Updated upstream
=======
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
void updateLevel() // ham cap nhat level
{

    // cứ mỗi 10 hàng tăng 1 level
    level = (totalLines / 10) + 1;

    // giảm tốc độ rơi khi level tăng
    fallSpeed = 500 - (level - 1) * 40;

    // giới hạn tốc độ tối thiểu
    if (fallSpeed < 100)
    {
        fallSpeed = 100;
    }
}
// =========================
// HÀM TÍNH ĐIỂM
// linesCleared = số hàng phá được
// =========================
void calculateScore(int linesCleared)
{
    int points = 0;

    switch(linesCleared)
    {
        case 1:
            points = 100;
            break;

        case 2:
            points = 300;
            break;

        case 3:
            points = 500;
            break;

        case 4:
            points = 800;
            break;

        default:
            points = 0;
    }

    // nhân theo level
    score += points * level;

    // cộng tổng số hàng
    totalLines += linesCleared;

    // cập nhật level
    updateLevel();
}
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

    int lines;

    while(true)
    {
        cout << "\nNhap so hang vua pha (1-4, 0 de thoat): ";
        cin >> lines;

        if(lines == 0)
        {
            break;
        }

        if(lines < 1 || lines > 4)
        {
            cout << "So hang khong hop le!" << endl;
            continue;
        }

        // tính điểm
        calculateScore(lines);

        
    }
    return 0;
}
>>>>>>> Stashed changes
