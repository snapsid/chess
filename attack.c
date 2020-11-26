#include "defs.h"

const int KnDir[8] = { -8, -19,	-21, -12, 8, 19, 21, 12 };
const int RkDir[4] = { -1, -10,	1, 10 };
const int BiDir[4] = { -9, -11, 11, 9 };
const int KiDir[8] = { -1, -10,	1, 10, -9, -11, 11, 9 };


int SqAttacked(const int sq, const int side, const Board_struct *pos) {

	int pce,index,t_sq,dir;

	// for pawns
	if(side == WHITE) {
		if(pos->pices[sq-11] == wP || pos->pices[sq-9] == wP) {
			return TRUE;
		}
	}
    // for white side it will subtract 9 and 11 bcoz pawns attack in forward direction and diagonally

  else {
		if(pos->pices[sq+11] == bP || pos->pices[sq+9] == bP) {
			return TRUE;
		}
	}
  // for black it will be plus as side is opposite now



  // for knights
	for(index = 0; index < 8; ++index) {
		pce = pos->pices[sq + KnDir[index]];
		if(pce != OFFBOARD && IsKn(pce) && PieceColour[pce]==side) {
			return TRUE;
		}
	}
  // it will check if from that square - 8 is there any knight and also if its color is same as the move color
  // it wil than return true



  // for rooks and queens
  for(index = 0; index < 4; ++index) {
    dir = RkDir[index];
    t_sq = sq + dir;
    pce = pos->pices[t_sq];
    while(pce != OFFBOARD) {
      if(pce != EMPTY) {
        if(IsRQ(pce) && PieceColour[pce] == side) {
          return TRUE;
        }
        break;
      }
      t_sq += dir;
      pce = pos->pices[t_sq];
    }
  }
// here we will be looking for direction i.e square ke ek side ko pakad lia than uske next square par check kia
// if vha par koi piece hai i.e not empty aur its color is rook or queen and also its color is same as turn
// than return true and break the loop
// or increment the direction and loops continues





// for bishops and queens
for(index = 0; index < 4; ++index) {
  dir = BiDir[index];
  t_sq = sq + dir;
  pce = pos->pices[t_sq];
  while(pce != OFFBOARD) {
    if(pce != EMPTY) {
      if(IsBQ(pce) && PieceColour[pce] == side) {
        return TRUE;
      }
      break;
    }
    t_sq += dir;
    pce = pos->pices[t_sq];
  }
}
// same logic as rooks and queen




// for kings
for(index = 0; index < 8; ++index) {
  pce = pos->pices[sq + KiDir[index]];
  if(pce != OFFBOARD && IsKi(pce) && PieceColour[pce]==side) {
    return TRUE;
  }
}

return FALSE;


}
