#ifndef BLOCK_H
#define BLOCK_H

class Block{

public:
   int x, y;
   int type;
   char shape[4][4];
   char blocks[7][4][4];

   Block();

   void spawn();

   void rotate();
        
};

#endif