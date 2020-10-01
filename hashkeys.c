#include <stdio.h>
#include "defs.h"

U64 GeneratePosKey(const Board_struct *pos) {

	int sq = 0;
	U64 finalKey = 0;
	int piece = EMPTY;

	// pieces
	for(sq = 0; sq < BOARD_NUMBER; ++sq) {
		piece = pos->pices[sq];
		if(piece!=NO_SQ && piece!=EMPTY) {
			ASSERT(piece>=wP && piece<=bK);
			finalKey ^= PieceKeys[piece][sq];
		}
	}

	if(pos->side == WHITE) {
		finalKey ^= SideKeys;
	}

	if(pos->enPas != NO_SQ) {
		ASSERT(pos->enPas>=0 && pos->enPas<BOARD_NUMBER);
		finalKey ^= PieceKeys[EMPTY][pos->enPas];
	}

	ASSERT(pos->castlingPermission>=0 && pos->castlingPermission<=15);

	finalKey ^= CastleKeys[pos->castlingPermission];

	return finalKey;
}
