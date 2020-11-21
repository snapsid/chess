#include "stdio.h"
#include "defs.h"

#define MOVE(f,t,ca,pro,fl) ( (f) | ((t) << 7) | ( (ca) << 14 ) | ( (pro) << 20 ) | (fl))

#define SQOFFBOARD(sq) (ColumnBoard[(sq)]==OFFBOARD)



void AddQuiteMove(const Board_struct *pos, int move, MoveList_struct *list)
{
  list->moves[list->count].move=move;
  list->moves[list->count].score=0;
  list->count++;
}

void AddCaptureMove(const Board_struct *pos, int move, MoveList_struct *list)
{
  list->moves[list->count].move=move;
  list->moves[list->count].score=0;
  list->count++;
}


void AddEnPasMove(const Board_struct *pos, int move, MoveList_struct *list)
{
  list->moves[list->count].move=move;
  list->moves[list->count].score=0;
  list->count++;
}


void AddWhitePawnCapMove( const Board_struct *pos, const int from, const int to, const int cap, MoveList_struct *list ) {
	if(RowBoard[from] == ROW_7) {
		AddCaptureMove(pos, MOVE(from,to,cap,wQ,0), list);
		AddCaptureMove(pos, MOVE(from,to,cap,wR,0), list);
		AddCaptureMove(pos, MOVE(from,to,cap,wB,0), list);
		AddCaptureMove(pos, MOVE(from,to,cap,wN,0), list);
	} else {
		AddCaptureMove(pos, MOVE(from,to,cap,EMPTY,0), list);
	}
}
// jab pawn top par pauch jayega tab zinda karne ke liye



void AddWhitePawnMove( const Board_struct *pos, const int from, const int to, MoveList_struct *list ) {
	if(RowBoard[from] == ROW_7) {
		AddQuiteMove(pos, MOVE(from,to,EMPTY,wQ,0), list);
		AddQuiteMove(pos, MOVE(from,to,EMPTY,wR,0), list);
		AddQuiteMove(pos, MOVE(from,to,EMPTY,wB,0), list);
		AddQuiteMove(pos, MOVE(from,to,EMPTY,wN,0), list);
	} else {
		AddQuiteMove(pos, MOVE(from,to,EMPTY,EMPTY,0), list);
	}
}



// same for black
// direction ki vjah se row2 hogi air white ki jagh black

void AddBlackPawnCapMove( const Board_struct *pos, const int from, const int to, const int cap, MoveList_struct *list ) {
	if(RowBoard[from] == ROW_2) {
		AddCaptureMove(pos, MOVE(from,to,cap,bQ,0), list);
		AddCaptureMove(pos, MOVE(from,to,cap,bR,0), list);
		AddCaptureMove(pos, MOVE(from,to,cap,bB,0), list);
		AddCaptureMove(pos, MOVE(from,to,cap,bN,0), list);
	} else {
		AddCaptureMove(pos, MOVE(from,to,cap,EMPTY,0), list);
	}
}
// jab pawn top par pauch jayega tab zinda karne ke liye



void AddBlackPawnMove( const Board_struct *pos, const int from, const int to, MoveList_struct *list ) {
	if(RowBoard[from] == ROW_2) {
		AddQuiteMove(pos, MOVE(from,to,EMPTY,bQ,0), list);
		AddQuiteMove(pos, MOVE(from,to,EMPTY,bR,0), list);
		AddQuiteMove(pos, MOVE(from,to,EMPTY,bB,0), list);
		AddQuiteMove(pos, MOVE(from,to,EMPTY,bN,0), list);
	} else {
		AddQuiteMove(pos, MOVE(from,to,EMPTY,EMPTY,0), list);
	}
}









void GenerateAllMoves(const Board_struct *pos, MoveList_struct *list)
{
  list->count=0;

  ASSERT(CheckBoard(pos));


	int pce = EMPTY;
	int side = pos->side;
	int sq = 0; int t_sq = 0;
	int pceNum = 0;


  if(side == WHITE) {
		for(pceNum = 0; pceNum < pos->picesNumber[wP]; ++pceNum) {
			sq = pos->pieceslist[wP][pceNum];
			// ASSERT(SqOnBoard(sq));

			if(pos->pices[sq + 10] == EMPTY) {
				AddWhitePawnMove(pos, sq, sq+10, list);
				if(RowBoard[sq] == ROW_2 && pos->pices[sq + 20] == EMPTY) {
					AddQuiteMove(pos, MOVE(sq,(sq+20),EMPTY,EMPTY,MFLAGPS),list);
				}
			}
      // to move pawn therefore +10
       // and in first move of pawn +20 to move to square ahead

			if(!SQOFFBOARD(sq + 9) && PieceColour[pos->pices[sq + 9]] == BLACK) {
				AddWhitePawnCapMove(pos, sq, sq+9, pos->pices[sq + 9], list);
			}
			if(!SQOFFBOARD(sq + 11) && PieceColour[pos->pices[sq + 11]] == BLACK) {
				AddWhitePawnCapMove(pos, sq, sq+11, pos->pices[sq + 11], list);
			}
      // to attack 9 and 11 kyuki pawn attack vertically
      // it will also check color must be black

			if(sq + 9 == pos->enPas) {
				AddCaptureMove(pos, MOVE(sq,sq + 9,EMPTY,EMPTY,MFLAGEP), list);
			}
			if(sq + 11 == pos->enPas) {
				AddCaptureMove(pos, MOVE(sq,sq + 11,EMPTY,EMPTY,MFLAGEP), list);
			}
      // for enpassant

		}
	} else {
    // for black

    // same as white only change color
    for(pceNum = 0; pceNum < pos->picesNumber[bP]; ++pceNum) {
			sq = pos->pieceslist[bP][pceNum];

      // change direction from + to - bcoz black is in opp. direction
      if(pos->pices[sq-10] == EMPTY) {
				AddBlackPawnMove(pos, sq, sq-10, list);
				if(RowBoard[sq] == ROW_7 && pos->pices[sq-20] == EMPTY) {
					AddQuiteMove(pos, MOVE(sq,(sq-20),EMPTY,EMPTY,MFLAGPS),list);
				}
			}

      if(!SQOFFBOARD(sq-9) && PieceColour[pos->pices[sq-9]] == WHITE) {
				AddBlackPawnCapMove(pos, sq, sq-9, pos->pices[sq - 9], list);
			}
			if(!SQOFFBOARD(sq - 11) && PieceColour[pos->pices[sq - 11]] == WHITE) {
				AddBlackPawnCapMove(pos, sq, sq-11, pos->pices[sq - 11], list);
			}


      if(sq-9 == pos->enPas) {
				AddCaptureMove(pos, MOVE(sq,sq-9,EMPTY,EMPTY,MFLAGEP), list);
			}
			if(sq-11 == pos->enPas) {
				AddCaptureMove(pos, MOVE(sq,sq-11,EMPTY,EMPTY,MFLAGEP), list);
			}
      // for enpassant
    }

	}

}
