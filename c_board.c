#include <stdio.h>
#include "defs.h"



int CheckBoard(const Board_struct *pos) {

	int t_pceNum[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int t_bigPce[2] = { 0, 0};
	int t_majPce[2] = { 0, 0};
	int t_minPce[2] = { 0, 0};
	int t_material[2] = { 0, 0};

	int sq64,t_piece,t_pce_num,sq120,colour,pcount;

	U64 t_pawns[3] = {0ULL, 0ULL, 0ULL};

	t_pawns[WHITE] = pos->pawns[WHITE];
	t_pawns[BLACK] = pos->pawns[BLACK];
	t_pawns[BOTH] = pos->pawns[BOTH];

	// check piece lists
	for(t_piece = wP; t_piece <= bK; ++t_piece) {
		for(t_pce_num = 0; t_pce_num < pos->picesNumber[t_piece]; ++t_pce_num) {
			sq120 = pos->pieceslist[t_piece][t_pce_num];
			ASSERT(pos->pices[sq120]==t_piece);
		}
	}

	// check piece count and other counters
	for(sq64 = 0; sq64 < 64; ++sq64) {
		sq120 = SQ120(sq64);
		t_piece = pos->pices[sq120];
		t_pceNum[t_piece]++;
		colour = PieceColour[t_piece];
		if( PieceBig[t_piece] == TRUE) t_bigPce[colour]++;
		if( PieceMinor[t_piece] == TRUE) t_minPce[colour]++;
		if( PieceMajor[t_piece] == TRUE) t_majPce[colour]++;

		t_material[colour] += PieceValue[t_piece];
	}

	for(t_piece = wP; t_piece <= bK; ++t_piece) {
		ASSERT(t_pceNum[t_piece]==pos->picesNumber[t_piece]);
	}

	// check bitboards count
	pcount = CNT(t_pawns[WHITE]);
	ASSERT(pcount == pos->picesNumber[wP]);
	pcount = CNT(t_pawns[BLACK]);
	ASSERT(pcount == pos->picesNumber[bP]);
	pcount = CNT(t_pawns[BOTH]);
	ASSERT(pcount == (pos->picesNumber[bP] + pos->picesNumber[wP]));

	// check bitboards squares
	while(t_pawns[WHITE]) {
		sq64 = POP(&t_pawns[WHITE]);
		ASSERT(pos->pices[SQ120(sq64)] == wP);
	}

	while(t_pawns[BLACK]) {
		sq64 = POP(&t_pawns[BLACK]);
		ASSERT(pos->pices[SQ120(sq64)] == bP);
	}

	while(t_pawns[BOTH]) {
		sq64 = POP(&t_pawns[BOTH]);
		ASSERT( (pos->pices[SQ120(sq64)] == bP) || (pos->pices[SQ120(sq64)] == wP) );
	}

	ASSERT(t_material[WHITE]==pos->material[WHITE] && t_material[BLACK]==pos->material[BLACK]);
	ASSERT(t_minPce[WHITE]==pos->minorPieces[WHITE] && t_minPce[BLACK]==pos->minorPieces[BLACK]);
	ASSERT(t_majPce[WHITE]==pos->majorPieces[WHITE] && t_majPce[BLACK]==pos->majorPieces[BLACK]);
	ASSERT(t_bigPce[WHITE]==pos->bigPieces[WHITE] && t_bigPce[BLACK]==pos->bigPieces[BLACK]);

	ASSERT(pos->side==WHITE || pos->side==BLACK);
	ASSERT(GeneratePosKey(pos)==pos->postionKey);

	ASSERT(pos->enPas==NO_SQ || ( RowBoard[pos->enPas]==ROW_6 && pos->side == WHITE)
		 || ( RowBoard[pos->enPas]==ROW_3 && pos->side == BLACK));

	ASSERT(pos->pices[pos->kingSquare[WHITE]] == wK);
	ASSERT(pos->pices[pos->kingSquare[BLACK]] == bK);

	return TRUE;
}







void UpdateListsMaterial(Board_struct *pos) {

	int piece,sq,index,colour;

	for(index = 0; index < BOARD_NUMBER; ++index) {
		sq = index;
		piece = pos->pices[index];
		if(piece!=OFFBOARD && piece!= EMPTY) {
			colour = PieceColour[piece];

		    if( PieceBig[piece] == TRUE) pos->bigPieces[colour]++;
		    if( PieceMinor[piece] == TRUE) pos->minorPieces[colour]++;
		    if( PieceMajor[piece] == TRUE) pos->majorPieces[colour]++;

			pos->material[colour] += PieceValue[piece];

			// piece list
			// pList[wP][0] = a1;
			// pList[wP][1] = a2;

			pos->pieceslist[piece][pos->picesNumber[piece]] = sq;
			pos->picesNumber[piece]++;

			if(piece==wK) pos->kingSquare[WHITE] = sq;
			if(piece==bK) pos->kingSquare[BLACK] = sq;

			if(piece==wP) {

				SETBIT(pos->pawns[WHITE],SQ64(sq));
				SETBIT(pos->pawns[BOTH],SQ64(sq));
			}
      else if(piece==bP) {
				SETBIT(pos->pawns[BLACK],SQ64(sq));
				SETBIT(pos->pawns[BOTH],SQ64(sq));
			}

		}
	}

}




void parse_FEN(char *fen, Board_struct *pos)
{

  ASSERT(fen!=NULL);
  ASSERT(pos!=NULL);

  // rnbqkbnr/pppppppp/8/8/8/8/pppppppp/RNBQKBNR w KQkq - 0 1

  int row= ROW_8;
  // starting with row 8
  int column = COLUMN_A;
  int piece=0;
  int count=0;
  // number of empty square
  int i =0;
  int sq64=0;
  int sq120=0;

  resetBoard(pos);

  while((row>=ROW_1) && *fen){
    count=1;

    switch(*fen)
    {
      case 'p': piece = bP; break;
      case 'r': piece = bR; break;
      case 'n': piece = bN; break;
      case 'b': piece = bB; break;
      case 'k': piece = bK; break;
      case 'q': piece = bQ; break;
      case 'P': piece = wP; break;
      case 'R': piece = wR; break;
      case 'N': piece = wN; break;
      case 'B': piece = wB; break;
      case 'K': piece = wK; break;
      case 'Q': piece = wQ; break;

      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
        piece = EMPTY;
        count = *fen - '0';
        break;

      case '/':
      case ' ':
        row--;
        column = COLUMN_A;
        fen++;
        continue;

      default:
        printf("FEN error \n");



    }

    for (i = 0; i < count; i++)
    {
      sq64 = row * 8 + column;
			sq120 = SQ120(sq64);
      if (piece != EMPTY) {
        pos->pices[sq120] = piece;
      }
			column++;
    }
		fen++;

}

ASSERT(*fen == 'w' || *fen == 'b');

if(*fen == 'w')
{
  pos->side=WHITE;
}
else{
  pos->side=BLACK;
}
fen=fen+2;

for(i = 0; i<4; i ++)
{
  if(*fen == ' ')
  {
    break;
  }

  switch(*fen)
  {
    case 'K': pos->castlingPermission |= WKCA; break;
    case 'Q': pos->castlingPermission |= WQCA; break;
    case 'k': pos->castlingPermission |= BKCA; break;
    case 'q': pos->castlingPermission |= BQCA; break;
    default: break;
  }
  fen++;

}
fen++;

ASSERT(pos->castlingPermission>=0 && pos->castlingPermission <= 15);

if (*fen != '-') {
		column = fen[0] - 'a';
		row = fen[1] - '1';

		ASSERT(column>=COLUMN_A && column <= COLUMN_H);
		ASSERT(row>=ROW_1 && row <= ROW_8);

		pos->enPas = FR2SQ(column,row);
    }

    pos->postionKey = GeneratePosKey(pos);
		UpdateListsMaterial(pos);

}



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

		pos->material[i]=0;

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

void PrintingBoard(const Board_struct *pos){

  int sq, column, row, piece;

  printf("\n OUR GAME BOARD:\n\n");

  for(row=ROW_8; row>=ROW_1; row--){

    printf("%d", row+1);

    for(column= COLUMN_A; column<=COLUMN_H; column++)
    {
      sq=FR2SQ(column, row);
      piece= pos->pices[sq];
      printf("%3c", PieceCharacter[piece]);


    }
    printf("\n");

  }

  printf("\n ");
  for(column= COLUMN_A; column<=COLUMN_H; column++)
  {
    printf("%3c", 'a'+column);
  }
  printf("\n\n\n");
  printf("side: %c\n", SideCharacter[pos->side]);
  // whose turn

  printf("enPas: %d\n", pos->enPas);
  // enpassent rule

  printf("Position Key: %11X\n", pos->postionKey);

  printf("castlling: %c%c%c%c\n",
			pos->castlingPermission & WKCA ? 'K' : '-',
			pos->castlingPermission & WQCA ? 'Q' : '-',
			pos->castlingPermission & BKCA ? 'k' : '-',
			pos->castlingPermission & BQCA ? 'q' : '-'
			);



}
