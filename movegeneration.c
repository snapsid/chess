#include "stdio.h"
#include "defs.h"

#define MOVE(f,t,ca,pro,fl) ( (f) | ((t) << 7) | ( (ca) << 14 ) | ( (pro) << 20 ) | (fl))

#define SQOFFBOARD(sq) (ColumnBoard[(sq)]==OFFBOARD)



// for sliding
int LoopSlidePce[8] = {
 wB, wR, wQ, 0, bB, bR, bQ, 0
};
// keep moving in loop until it comes 0 for white and black both


int LoopSlideIndex[2] = { 0, 4 };
// which side to move for that (white=0... black=4)


int LoopNonSlidePce[6] = {
 wN, wK, 0, bN, bK, 0
};
int LoopNonSlideIndex[2] = { 0, 3 };
// same logic as slide pices


int PceDir[13][8] = {
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ -8, -19,	-21, -12, 8, 19, 21, 12 },
	{ -9, -11, 11, 9, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ -8, -19,	-21, -12, 8, 19, 21, 12 },
	{ -9, -11, 11, 9, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 }
};

int NumDir[13] = {
 0, 0, 8, 4, 4, 8, 8, 0, 8, 4, 4, 8, 8
};


// for move generation
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


  int dir = 0;
	int index = 0;
	int pceIndex = 0;


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



      if(pos->castlingPermission & WKCA) {
  			if(pos->pices[F1] == EMPTY && pos->pices[G1] == EMPTY) {
  				if(!SqAttacked(E1,BLACK,pos) && !SqAttacked(F1,BLACK,pos) ) {
  					printf("WKCA MoveGen\n");
  				}
  			}
  		}

  		if(pos->castlingPermission & WQCA) {
  			if(pos->pices[D1] == EMPTY && pos->pices[C1] == EMPTY && pos->pices[B1] == EMPTY) {
  				if(!SqAttacked(E1,BLACK,pos) && !SqAttacked(D1,BLACK,pos) ) {
  					printf("WQCA MoveGen\n");
  				}
  			}
  		}
      // for casteling

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




      if(pos->castlingPermission &  BKCA) {
  			if(pos->pices[F8] == EMPTY && pos->pices[G8] == EMPTY) {
  				if(!SqAttacked(E8,WHITE,pos) && !SqAttacked(F8,WHITE,pos) ) {
  					printf("BKCA MoveGen\n");
  				}
  			}
  		}

  		if(pos->castlingPermission &  BQCA) {
  			if(pos->pices[D8] == EMPTY && pos->pices[C8] == EMPTY && pos->pices[B8] == EMPTY) {
  				if(!SqAttacked(E8,WHITE,pos) && !SqAttacked(D8,WHITE,pos) ) {
  					printf("BQCA MoveGen\n");
  				}
  			}
  		}
      // for castling





    }

	}




  // Loop for slide pieces
	pceIndex = LoopSlideIndex[side];
	pce = LoopSlidePce[pceIndex++];
	while( pce != 0) {

		printf("sliders pceIndex:%d pce:%d\n",pceIndex,pce);


    for(pceNum = 0; pceNum < pos->picesNumber[pce]; ++pceNum) {
			sq = pos->pieceslist[pce][pceNum];

			printf("Piece:%c on %s\n",PieceCharacter[pce],PrSq(sq));

			for(index = 0; index < NumDir[pce]; ++index) {
				dir = PceDir[pce][index];
				t_sq = sq + dir;

				while(!SQOFFBOARD(t_sq)) {
					// BLACK ^ 1 == WHITE       WHITE ^ 1 == BLACK
					if(pos->pices[t_sq] != EMPTY) {
						if( PieceColour[pos->pices[t_sq]] == side ^ 1) {
							printf("\t\tCapture on %s\n",PrSq(t_sq));
						}
						break;
					}
					printf("\t\tNormal on %s\n",PrSq(t_sq));
					t_sq += dir;
				}
			}
		}


		pce = LoopSlidePce[pceIndex++];
	}

	// Loop for non slide
	pceIndex = LoopNonSlideIndex[side];
	pce = LoopNonSlidePce[pceIndex++];

  while( pce != 0) {

		printf("non sliders pceIndex:%d pce:%d\n",pceIndex,pce);

		for(pceNum = 0; pceNum < pos->picesNumber[pce]; ++pceNum) {
			sq = pos->pieceslist[pce][pceNum];

			printf("Piece:%c on %s\n",PieceCharacter[pce],PrSq(sq));

			for(index = 0; index < NumDir[pce]; ++index) {
				dir = PceDir[pce][index];
				t_sq = sq + dir;

				if(SQOFFBOARD(t_sq)) {
					continue;
				}

				// BLACK ^ 1 == WHITE       WHITE ^ 1 == BLACK
				if(pos->pices[t_sq] != EMPTY) {
					if( PieceColour[pos->pices[t_sq]] == side ^ 1) {
						printf("\t\tCapture on %s\n",PrSq(t_sq));
					}
					continue;
				}
				printf("\t\tNormal on %s\n",PrSq(t_sq));
			}
		}

		pce = LoopNonSlidePce[pceIndex++];
	}

}
