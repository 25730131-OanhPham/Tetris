#include "Block.h"
#include <cstdlib>

Block::Block(){

    char temp[7][4][4] ={
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

    for(int k = 0; k < 7; k++ )
        for(int i = 0; i < 4; i++ )
            for(int j = 0; j < 4; j++ )
                blocks[k][i][j] = temp[k][i][j];
    
    spawn();
}


    void Block::spawn(){
        x = 0; 
        y = 0;

        type = rand()%7;

        for(int i = 0; i < 4; i++ )
            for(int j = 0; j < 4; j++ )
                shape[i][j] = blocks[type][i][j];
    }

    void Block::rotate(){
        char temp[4][4];
        
        for(int i = 0; i < 4; i++ )
            for(int j = 0; j < 4; j++ )
                temp[i][j] = shape[i][j];
        
        for(int i = 0; i < 4; i++ )
            for(int j = 0; j < 4; j++ )
                shape[i][j] = temp[3-j][i];            
    }