#include <stdio.h>
#include "defs.h"

void resetBoard(Board_struct *pos)
{

int i=0;

for(int i = 0; i < BOARD_NUMBER; ++i)
{
  pos->pices[i]= OFFBOARD;
}

for(i = 0; i < 64; ++i)
{
  pos->pices[SQ120(i)]= EMPTY;
}

for(i=0; i<3; ++i){
  pos->bigPieces[i]=0;
  pos->majorPieces[i]=0;
  pos->minorPieces[i]=0;
  pos->pawns[i]=0ULL;

}

for(i = 0; i < 13; ++i)
{
  pos->picesNumber[i]= 0;
}

pos->kingSquare[WHITE] = pos->kingSquare[BLACK] = NO_SQ;

pos->side = BOTH;
pos->enPas = NO_SQ;
pos->fiftyMove = 0;

pos->ply = 0;
pos->ply1 = 0;

pos->castlingPermission=0;
pos->postionKey=0ULL;

}
