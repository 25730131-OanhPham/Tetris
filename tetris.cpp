#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

#define H 22
#define W 16

char board[H][W];

int x, y, b;

// ================= BLOCKS =================
char blocks[][4][4] =
{
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
void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void initBoard()
{
    for(int i=0;i<H;i++)
    {
        for(int j=0;j<W;j++)
        {
            if(i==0 || i==H-1 || j==0 || j==W-1)
                board[i][j] = '*';
            else
                board[i][j] = ' ';
        }
    }
}

void draw()
{
    system("cls");

    for(int i=0;i<H;i++)
    {
        for(int j=0;j<W;j++)
        {
            char c = board[i][j];

            // Viền
            if(c == '*')
            {
                setColor(15);
                cout << "+";
            }

            // Block
            else if(c != ' ')
            {
                setColor(15);
                cout << char(219) << char(219);
            }

            // Khoảng trống
            else
            {
                cout << "  ";
            }
        }

        cout << endl;
    }

    setColor(7);

    cout << endl;
    cout << "A: Left  D: Right  S: Down  Q: Quit" << endl;
}

bool canMove(int dx, int dy)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(blocks[b][i][j] != ' ')
            {
                int newX = x + j + dx;
                int newY = y + i + dy;

                if(newX <= 0 || newX >= W-1 ||
                   newY <= 0 || newY >= H-1)
                    return false;

                if(board[newY][newX] != ' ')
                    return false;
            }
        }
    }

    return true;
}
void placeBlock()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(blocks[b][i][j] != ' ')
            {
                board[y+i][x+j] = blocks[b][i][j];
            }
        }
    }
}

void removeBlock()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(blocks[b][i][j] != ' ')
            {
                board[y+i][x+j] = ' ';
            }
        }
    }
}

void clearLines()
{
    for(int i=1;i<H-1;i++)
    {
        bool full = true;

        for(int j=1;j<W-1;j++)
        {
            if(board[i][j] == ' ')
            {
                full = false;
                break;
            }
        }

        if(full)
        {
            for(int k=i;k>1;k--)
            {
                for(int j=1;j<W-1;j++)
                {
                    board[k][j] = board[k-1][j];
                }
            }

            for(int j=1;j<W-1;j++)
            {
                board[1][j] = ' ';
            }
        }
    }
}

int main()
{
    srand(time(0));

    initBoard();

    x = 5;
    y = 1;
    b = rand()%8;

    while(true)
    {
        removeBlock();
        
        if(kbhit())
        {
            char c = getch();

            if((c=='a' || c=='A') && canMove(-1,0))
                x--;

            if((c=='d' || c=='D') && canMove(1,0))
                x++;

            if((c=='s' || c=='S') && canMove(0,1))
                y++;

            if(c=='q' || c=='Q')
                break;
        }
        if(canMove(0,1))
        {
            y++;
        }
        else
        {
            placeBlock();

            clearLines();

            x = 5;
            y = 1;
            b = rand()%8;

            if(!canMove(0,0))
            {
                system("cls");

                setColor(12);
                cout << "\n\n";
                cout << "        GAME OVER!\n";

                setColor(7);

                break;
            }
        }

        placeBlock();

        draw();

        Sleep(180);
    }

    return 0;
}