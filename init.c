#include "defs.h"


int Sq120ToSq64[BOARD_NUMBER];
int Sq64ToSq120[64];


U64 SetMask[64];
U64 ClearMask[64];

void InitBitMask()
{
	int index=0;

	for(index=0 ; index<64; index++)
	{
		SetMask[index]= 0ULL;
		ClearMask[index]= 0ULL;
	}

	for(index=0 ; index<64; index++)
	{
		SetMask[index] |= (1ULL << index);
		ClearMask[index]= ~SetMask[index];
	}
}


void InitSq120To64() {

	int index = 0;
	int column = COLUMN_A;
	int row = ROW_1;
	int sq = A1;
	int sq64 = 0;
	for(index = 0; index < BOARD_NUMBER; ++index) {
		Sq120ToSq64[index] = 65;
	}

	for(index = 0; index < 64; ++index) {
		Sq64ToSq120[index] = 120;
	}

	for(row = ROW_1; row <= ROW_8; ++row) {
		for(column = COLUMN_A; column <= COLUMN_H; ++column) {
			sq = FR2SQ(column,row);
			Sq64ToSq120[sq64] = sq;
			Sq120ToSq64[sq] = sq64;
			sq64++;
		}
	}

  // ek row me 8 columns hote
  // therefore after 8 columns row needs to be chnaged
}

void allInit(){

  InitSq120To64();
	InitBitMask();

}


// 6

// MinGW32-make
