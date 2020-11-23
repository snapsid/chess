#include <stdio.h>
#include<stdlib.h>
#include "defs.h"





#define FEN11 "8/3q1p2/8/5P2/4Q3/8/8/8 w - - 0 2 "

// to check the attacking position available
void ShowSqAtBySide(const int side, const Board_struct *pos) {

	int row = 0;
	int column = 0;
	int sq = 0;

	printf("\n\nSquares attacked by:%c\n",SideCharacter[side]);
	for(row = ROW_8; row >= ROW_1; --row) {
		for(column = COLUMN_A; column <= COLUMN_H; ++column) {
			sq = FR2SQ(column,row);
			if(SqAttacked(sq,side,pos)==TRUE) {
				printf("X");
			} else {
				printf("-");
			}

		}
		printf("\n");
	}
    printf("\n\n");

}












int main()
{
  printf("\n");
  printf("\n");
  printf("-------------welcome to .? chess-----------------");
  printf("\n");
  printf("\n");
  allInit();





//   for(int index=0; index< BOARD_NUMBER; ++index)
//   {
//     if(index%10==0)
//     {
//       printf("\n");
//     }
//     printf("%5d", Sq120ToSq64[index]);
//
//   }
//   printf("\n");
//   printf("\n");
//
//   for(int index=0; index< 64; ++index)
//   {
//     if(index%8==0)
//     {
//       printf("\n");
//     }
//     printf("%5d", Sq64ToSq120[index]);
//
//   }
//
//
//
//
//
//
//
//
//
//
//   U64 playBitBoard = 0ULL;
//
//   printBitB(playBitBoard);
//
//
//   playBitBoard |= (1ULL << SQ64(D2));
//   playBitBoard |= (1ULL << SQ64(D3));
//   playBitBoard |= (1ULL << SQ64(D4));
// // adding a bit to D2 postion
//
//   printBitB(playBitBoard);
//
//   // playBitBoard |= (1ULL << SQ64(G2));
//   // printBitB(playBitBoard);
//
//   int count = CNT(playBitBoard);
//   printf("Count: %d\n", count);
//   printf("\n");
//
//   // to print the number of X in bitboard
//
//   int index = POP(&playBitBoard);
//   printf("index %d", index);
//   printf("\n");
//   printBitB(playBitBoard);
//   count = CNT(playBitBoard);
//   printf("\n");
//   printf("Count: %d\n", count);
//
//   int a=0;
//
//   while (playBitBoard){
//
//     a=POP(&playBitBoard);
//     printf("popped %d \n", a);
//     printBitB(playBitBoard);
//
//
//   }
//
// // printing bits
//
//   // int index= 0;
//
//
//   // for(index=0 ; index<64; index++)
// 	// {
//   //   printf("Index %d \n", index);
// 	// 	printBitB(ClearMask[index]);
// 	// 	printf("\n");
// 	// }
//
//   SETBIT(playBitBoard, 61);
//   printBitB(playBitBoard);
//
//   CLRBIT(playBitBoard, 61);
//   printBitB(playBitBoard);
//
//
//   int pieceOne = rand();
//   int pieceTwo = rand();
//   int pieceThree = rand();
//   int pieceFour = rand();
//
//   printf("pieceOne: %X\n", pieceOne);
//   printf("pieceTwo: %X\n", pieceTwo);
//   printf("pieceThree: %X\n", pieceThree);
//   printf("pieceFour: %X\n", pieceFour);
//
//   int key =  pieceOne ^ pieceTwo ^ pieceThree ^ pieceFour;
//   printf("key: %X", key);

  #define FEN1 "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"

  Board_struct board[1];

  // parse_FEN(START_FEN, board);
  // PrintingBoard(board);
	//
  // parse_FEN(FEN1, board);
  // PrintingBoard(board);
	//
	//
	//
  // #define FEN4 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
  // parse_FEN(FEN4, board);
  // PrintingBoard(board);
  // printf("\nAll white pawns\n");
  // printBitB(board->pawns[WHITE]);
  // printf("\nAll black pawns\n");
  // printBitB(board->pawns[BLACK]);
  // printf("\nAll ALL pawns\n");
  // printBitB(board->pawns[BOTH]);


  // ASSERT(CheckBoard(board));
	// printf("\nForced asserts...\n");
	// board->postionKey ^= SideKeys;
	// ASSERT(CheckBoard(board));


// to check attack function

// S_BOARD board[1];

// parse_FEN(FEN11, board);
// PrintingBoard(board);
// //ASSERT(CheckBoard(board));
//
// printf("\n\nWhite Attacking:\n");
// ShowSqAtBySide(WHITE,board);
//
// printf("\n\nBlack Attacking:\n");
// ShowSqAtBySide(BLACK,board);


// int move = 0;
// int from = A2; int to = H7;
// int cap = wR; int prom = wR;
//
// move = ( ( from ) | ( to << 7 ) | ( cap << 14 ) | ( prom << 20) );
//
//   printf("from:%d to:%d cap:%d prom:%d\n",
// 	FROMSQ(move),TOSQ(move),CAPTURED(move),
// 	PROMOTED(move));
//
// printf("Algebraic from:%s\n",PrSq(from));
// printf("Algebraic to:%s\n",PrSq(to));
// printf("Algebraic move:%s\n",PrMove(move));




  #define PAWNMOVES "rnbqkbnr/p1p1p3/3p3p/1p1p4/2P1Pp2/8/PP1P1PpP/RNBQKB1R b KQkq e3 0 1"

	#define KNIGHTSKINGS "5k2/1n6/4n3/6N1/8/3N4/8/5K2 w - - 0 1"

	#define ROOKS "6k1/8/5r2/8/1nR5/5N2/8/6K1 b - - 0 1"
	#define QUEENS "6k1/8/4nq2/8/1nQ5/5N2/1N6/6K1 b - - 0 1 "
	#define BISHOPS "6k1/1b6/4n3/8/1n4B1/1B3N2/1N6/2b3K1 b - - 0 1 "

	parse_FEN(QUEENS,board);
	PrintingBoard(board);

	MoveList_struct list[1];

	GenerateAllMoves(board, list);

	PrintMoveList(list);


    return 0;
}
