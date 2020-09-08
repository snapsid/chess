#include "defs.h"


int Sq120ToSq64[BOARD_NUMBER];
int Sq64ToSq120[64];


void InitSq120To64() {

	int index = 0;
	int file = COLUMN_A;
	int rank = ROW_1;
	int sq = A1;
	int sq64 = 0;
	for(index = 0; index < BOARD_NUMBER; ++index) {
		Sq120ToSq64[index] = 65;
	}

	for(index = 0; index < 64; ++index) {
		Sq64ToSq120[index] = 120;
	}

	for(rank = ROW_1; rank <= ROW_8; ++rank) {
		for(file = COLUMN_A; file <= COLUMN_H; ++file) {
			sq = FR2SQ(file,rank);
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

}


// 6

// MinGW32-make
