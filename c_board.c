#include <stdio.h>
#include "defs.h"

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
