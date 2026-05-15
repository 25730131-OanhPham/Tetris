#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>

using namespace std;

const int WIDTH = 12;
const int HEIGHT = 22;

char board[HEIGHT][WIDTH];

// ================= TETROMINO =================
int shapes[7][4][4] =
{
    // I
    {
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    },

    // O
    {
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },

    // T
    {
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },

    // S
    {
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    },

    // Z
    {
        {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },

    // J
    {
        {1,0,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },

    // L
    {
        {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    }
};

// ================= CURRENT BLOCK =================
int current[4][4];

int posX;
int posY;

// ================= COLOR =================
void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// ================= INIT BOARD =================
void initBoard()
{
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            if(j==0 || j==WIDTH-1 || i==HEIGHT-1)
                board[i][j] = '#';
            else
                board[i][j] = ' ';
        }
    }
}

// ================= SPAWN BLOCK =================
void spawnBlock()
{
    int id = rand() % 7;

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            current[i][j] = shapes[id][i][j];
        }
    }

    posX = WIDTH / 2 - 2;
    posY = 0;
}

// ================= COLLISION =================
bool collision(int dx, int dy)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(current[i][j])
            {
                int nx = posX + j + dx;
                int ny = posY + i + dy;

                if(nx < 0 || nx >= WIDTH ||
                   ny < 0 || ny >= HEIGHT)
                    return true;

                if(board[ny][nx] != ' ')
                    return true;
            }
        }
    }

    return false;
}

// ================= MERGE BLOCK =================
void mergeBlock()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(current[i][j])
            {
                board[posY+i][posX+j] = 'X';
            }
        }
    }
}

// ================= CLEAR LINES =================
void clearLines()
{
    for(int i=HEIGHT-2;i>=0;i--)
    {
        bool full = true;

        for(int j=1;j<WIDTH-1;j++)
        {
            if(board[i][j] == ' ')
            {
                full = false;
                break;
            }
        }

        if(full)
        {
            for(int k=i;k>0;k--)
            {
                for(int j=1;j<WIDTH-1;j++)
                {
                    board[k][j] = board[k-1][j];
                }
            }

            i++;
        }
    }
}

// ================= DRAW =================
void draw()
{
    system("cls");

    char temp[HEIGHT][WIDTH];

    // copy board
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            temp[i][j] = board[i][j];
        }
    }

    // add current block
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(current[i][j])
            {
                temp[posY+i][posX+j] = 'X';
            }
        }
    }

    // draw
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            // viền
            if(temp[i][j] == '#')
            {
                setColor(15);
                cout << "||";
            }

            // block
            else if(temp[i][j] == 'X')
            {
                setColor(11);
                cout << "[]";
            }

            // khoảng trống
            else
            {
                cout << "  ";
            }
        }

        cout << endl;
    }

    setColor(7);

    cout << endl;
    cout << "A = LEFT | D = RIGHT | S = DOWN | Q = QUIT" << endl;
}

// ================= MAIN =================
int main()
{
    srand(time(0));

    initBoard();

    spawnBlock();

    while(true)
    {
        draw();

        Sleep(150);

        // INPUT
        if(kbhit())
        {
            char c = getch();

            if((c=='a' || c=='A') && !collision(-1,0))
                posX--;

            if((c=='d' || c=='D') && !collision(1,0))
                posX++;

            if((c=='s' || c=='S') && !collision(0,1))
                posY++;

            if(c=='q' || c=='Q')
                break;
        }

        // FALL
        if(!collision(0,1))
        {
            posY++;
        }
        else
        {
            mergeBlock();

            clearLines();

            spawnBlock();

            // GAME OVER
            if(collision(0,0))
            {
                system("cls");

                setColor(12);

                cout << "\n\n";
                cout << "        GAME OVER\n\n";

                setColor(7);

                system("pause");

                break;
            }
        }
    }

    return 0;
}