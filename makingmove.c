#include "defs.h"
#include "stdio.h"



#define HASH_PCE(pce,sq) (pos->postionKey ^= (PieceKeys[(pce)][(sq)]))
#define HASH_CA (pos->postionKey ^= (CastleKeys[(pos->castlingPermission)]))
#define HASH_SIDE (pos->postionKey ^= (SideKey))
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
