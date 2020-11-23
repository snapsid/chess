#include "defs.h"
#include "stdio.h"



#define HASH_PCE(pce,sq) (pos->postionKey ^= (PieceKeys[(pce)][(sq)]))
#define HASH_CA (pos->postionKey ^= (CastleKeys[(pos->castlingPermission)]))
#define HASH_SIDE (pos->postionKey ^= (SideKeys))
#define HASH_EP (pos->postionKey ^= (PieceKeys[EMPTY][(pos->enPas)]))

const int CastlePerm[120] = {
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 13, 15, 15, 15, 12, 15, 15, 14, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15,  7, 15, 15, 15,  3, 15, 15, 11, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};
// except 6 position all are set to 15
// 15 bcoz casteling permission require 4 CountBit
// 1111 = 15


static void ClearPiece(const int sq, Board_struct *pos) {



    int pce = pos->pices[sq];



	int col = PieceColour[pce];
	int index = 0;
	int t_pceNum = -1;

    HASH_PCE(pce,sq);

	pos->pices[sq] = EMPTY;
    pos->material[col] -= PieceValue[pce];

	if(PieceBig[pce]) {
			pos->bigPieces[col]--;
		if(PieceMajor[pce]) {
			pos->majorPieces[col]--;
		} else {
			pos->minorPieces[col]--;
		}
	} else {
		CLRBIT(pos->pawns[col],SQ64(sq));
		CLRBIT(pos->pawns[BOTH],SQ64(sq));
	}
  //
	// /*
	// 	pos->pceNum[wP] == 5 Looping from 0 to 4
	// 	pos->pList[pce][0] == sq0
	// 	pos->pList[pce][1] == sq1
	// 	pos->pList[pce][2] == sq2
	// 	pos->pList[pce][3] == sq3
	// 	pos->pList[pce][4] == sq4
  //
	// 	sq==sq3 so t_pceNum = 3;
	// */
  //
	for(index = 0; index < pos->picesNumber[pce]; ++index) {
		if(pos->pieceslist[pce][index] == sq) {
			t_pceNum = index;
			break;
		}
	}


	 pos->picesNumber[pce]--;
	// // pos->pceNum[wP] == 4
  //
	 pos->pieceslist[pce][t_pceNum] = pos->pieceslist[pce][pos->picesNumber[pce]];
  // //pos->pList[wP][3]	= pos->pList[wP][4] = sq4
  // /*
	// 	pos->pceNum[wP] == 4 Looping from 0 to 3
	// 	pos->pList[pce][0] == sq0
	// 	pos->pList[pce][1] == sq1
	// 	pos->pList[pce][2] == sq2
	// 	pos->pList[pce][3] == sq4
	// */

}

static void AddPiece(const int sq, Board_struct *pos, const int pce) {



	int col = PieceColour[pce];

    HASH_PCE(pce,sq);

	pos->pices[sq] = pce;

    if(PieceBig[pce]) {
			pos->bigPieces[col]++;
		if(PieceMajor[pce]) {
			pos->majorPieces[col]++;
		} else {
			pos->minorPieces[col]++;
		}
	} else {
		SETBIT(pos->pawns[col],SQ64(sq));
		SETBIT(pos->pawns[BOTH],SQ64(sq));
	}

	pos->material[col] += PieceValue[pce];
	pos->pieceslist[pce][pos->picesNumber[pce]++] = sq;

}


static void MovePiece(const int from, const int to, Board_struct *pos) {


	int index = 0;
	int pce = pos->pices[from];
	int col = PieceColour[pce];

#ifdef DEBUG
	int t_PieceNum = FALSE;
#endif

	HASH_PCE(pce,from);
	pos->pices[from] = EMPTY;

	HASH_PCE(pce,to);
	pos->pices[to] = pce;

	if(!PieceBig[pce]) {
		CLRBIT(pos->pawns[col],SQ64(from));
		CLRBIT(pos->pawns[BOTH],SQ64(from));
		SETBIT(pos->pawns[col],SQ64(to));
		SETBIT(pos->pawns[BOTH],SQ64(to));
	}

	for(index = 0; index < pos->picesNumber[pce]; ++index) {
		if(pos->pieceslist[pce][index] == from) {
			pos->pieceslist[pce][index] = to;
#ifdef DEBUG
			t_PieceNum = TRUE;
#endif
			break;
		}
	}
	ASSERT(t_PieceNum);
}




int MakeMove(Board_struct *pos, int move) {



	int from = FROMSQ(move);
    int to = TOSQ(move);
    int side = pos->side;



	pos->history[pos->ply1].postionKey = pos->postionKey;

	if(move & MFLAGEP) {
        if(side == WHITE) {
            ClearPiece(to-10,pos);
        } else {
            ClearPiece(to+10,pos);
        }
        // enpassant capture
    } else if (move & MFLAGCA) {
        switch(to) {
            case C1:
                MovePiece(A1, D1, pos);
			break;
            case C8:
                MovePiece(A8, D8, pos);
			break;
            case G1:
                MovePiece(H1, F1, pos);
			break;
            case G8:
                MovePiece(H8, F8, pos);
			break;
            default:  break;
        }
        // if castling
    }

	if(pos->enPas != NO_SQ) HASH_EP;
    HASH_CA;
    // hash enpassand and castling


	pos->history[pos->ply1].move = move;
    pos->history[pos->ply1].fiftyMove = pos->fiftyMove;
    pos->history[pos->ply1].enPas = pos->enPas;
    pos->history[pos->ply1].castlingPermission = pos->castlingPermission;

    pos->castlingPermission &= CastlePerm[from];
    pos->castlingPermission &= CastlePerm[to];
    pos->enPas = NO_SQ;

	HASH_CA;

	int captured = CAPTURED(move);
    pos->fiftyMove++;

	if(captured != EMPTY) {

        ClearPiece(to, pos);
        pos->fiftyMove = 0;
    }

	pos->ply1++;
	pos->ply++;
// to increment total and half move

	if(PieceISPawn[pos->pices[from]]) {
        pos->fiftyMove = 0;
        if(move & MFLAGPS) {
          // if pawn start move
            if(side==WHITE) {
                pos->enPas=from+10;

            } else {
                pos->enPas=from-10;

            }
            HASH_EP;
        }
    }

	MovePiece(from, to, pos);
// moving piece

	int prPce = PROMOTED(move);
    if(prPce != EMPTY)   {

        ClearPiece(to, pos);
        AddPiece(to, pos, prPce);
    }

	if(PieceISKing[pos->pices[to]]) {
        pos->kingSquare[pos->side] = to;
    }

	pos->side ^= 1;
    HASH_SIDE;

    // ASSERT(CheckBoard(pos));


	if(SqAttacked(pos->kingSquare[side],pos->side,pos))  {
        TakeMove(pos);
        return FALSE;
    }
    // if check

	return TRUE;

}



void TakeMove(Board_struct *pos) {

// for undo


	pos->ply1--;
    pos->ply--;

    int move = pos->history[pos->ply1].move;
    int from = FROMSQ(move);
    int to = TOSQ(move);



	if(pos->enPas != NO_SQ) HASH_EP;
    HASH_CA;

    pos->castlingPermission = pos->history[pos->ply1].castlingPermission;
    pos->fiftyMove = pos->history[pos->ply1].fiftyMove;
    pos->enPas = pos->history[pos->ply1].enPas;

    if(pos->enPas != NO_SQ) HASH_EP;
    HASH_CA;

    pos->side ^= 1;
    HASH_SIDE;

	if(MFLAGEP & move) {
        if(pos->side == WHITE) {
            AddPiece(to-10, pos, bP);
        } else {
            AddPiece(to+10, pos, wP);
        }
    } else if(MFLAGCA & move) {
        switch(to) {
            case C1: MovePiece(D1, A1, pos); break;
            case C8: MovePiece(D8, A8, pos); break;
            case G1: MovePiece(F1, H1, pos); break;
            case G8: MovePiece(F8, H8, pos); break;
            default:  break;
        }
    }

	MovePiece(to, from, pos);

	if(PieceISKing[pos->pices[from]]) {
        pos->kingSquare[pos->side] = from;
    }

	int captured = CAPTURED(move);
    if(captured != EMPTY) {

        AddPiece(to, pos, captured);
    }

	if(PROMOTED(move) != EMPTY)   {

        ClearPiece(from, pos);
        AddPiece(from, pos, (PieceColour[PROMOTED(move)] == WHITE ? wP : bP));
    }

    ASSERT(CheckBoard(pos));

}
