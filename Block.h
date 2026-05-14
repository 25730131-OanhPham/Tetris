#include <iostream>

using namespace std;

class Block{
public:
    int x, y;
    int type;

    char shape[4][4];

    char blocks[8][4][4] ={
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

    Block(){
        spawn();
    }

    void spawn(){
        x = 0; 
        y = 0;

        type = rand()%8;

        for(int i = 0; i < 4; i++ )
            for(int j = 0; j < 4; j++ )
                shape[i][j] = blocks[type][i][j];
    }

    void rotate(){
        char temp[4][4];
        
        for(int i = 0; i < 4; i++ )
            for(int j = 0; j < 4; j++ )
                temp[i][j] = shape[i][j];
        
        for(int i = 0; i < 4; i++ )
            for(int j = 0; j < 4; j++ )
                shape[i][j] = temp[3-j][i];            
    }
};