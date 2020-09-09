#include <stdio.h>
#include "defs.h"


void printBitB(U64 bb)
{
  U64 shiftMe = 1ULL;

  int row = 0;
  int column =0;
  int sq =0;
  int sq64=0;



  for(row = ROW_8; row >= ROW_1; --row) {
		for(column = COLUMN_A; column <= COLUMN_H; ++column) {
			sq = FR2SQ(column,row);
      // 120 based

			sq64=SQ64(sq);
      // 60 based


      if((shiftMe<<sq64) & bb)
      {
        // using bitwise operator to check wheather there is a bit(1) present or not

        printf("X");

        // if yes print X and if not print -
      }

      else{
        printf("-");
      }


		}
    printf("\n");
	}
  printf("\n");
}
