#include <stdio.h>
#include<stdlib.h>
#include "defs.h"


int main()
{
  printf("\n");
  printf("\n");
  printf("-------------welcome to .? chess-----------------");
  printf("\n");
  printf("\n");
  allInit();




  for(int index=0; index< BOARD_NUMBER; ++index)
  {
    if(index%10==0)
    {
      printf("\n");
    }
    printf("%5d", Sq120ToSq64[index]);

  }
  printf("\n");
  printf("\n");

  for(int index=0; index< 64; ++index)
  {
    if(index%8==0)
    {
      printf("\n");
    }
    printf("%5d", Sq64ToSq120[index]);

  }










  U64 playBitBoard = 0ULL;

  printBitB(playBitBoard);


  playBitBoard |= (1ULL << SQ64(D2));
  playBitBoard |= (1ULL << SQ64(D3));
  playBitBoard |= (1ULL << SQ64(D4));
// adding a bit to D2 postion

  printBitB(playBitBoard);

  // playBitBoard |= (1ULL << SQ64(G2));
  // printBitB(playBitBoard);

  int count = CNT(playBitBoard);
  printf("Count: %d\n", count);
  printf("\n");

  // to print the number of X in bitboard

  int index = POP(&playBitBoard);
  printf("index %d", index);
  printf("\n");
  printBitB(playBitBoard);
  count = CNT(playBitBoard);
  printf("\n");
  printf("Count: %d\n", count);

  int a=0;

  while (playBitBoard){

    a=POP(&playBitBoard);
    printf("popped %d \n", a);
    printBitB(playBitBoard);


  }

// printing bits

  // int index= 0;


  // for(index=0 ; index<64; index++)
	// {
  //   printf("Index %d \n", index);
	// 	printBitB(ClearMask[index]);
	// 	printf("\n");
	// }

  SETBIT(playBitBoard, 61);
  printBitB(playBitBoard);

  CLRBIT(playBitBoard, 61);
  printBitB(playBitBoard);


  int pieceOne = rand();
  int pieceTwo = rand();
  int pieceThree = rand();
  int pieceFour = rand();

  printf("pieceOne: %X\n", pieceOne);
  printf("pieceTwo: %X\n", pieceTwo);
  printf("pieceThree: %X\n", pieceThree);
  printf("pieceFour: %X\n", pieceFour);

  int key =  pieceOne ^ pieceTwo ^ pieceThree ^ pieceFour;
  printf("key: %X", key);

  #define FEN1 "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"

  Board_struct board[1];

  parse_FEN(START_FEN, board);
  PrintingBoard(board);

  parse_FEN(FEN1, board);
  PrintingBoard(board);



    return 0;
}
