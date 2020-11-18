#ifndef DEFS_H
#define DEFS_H

#include <stdlib.h>


#define DEBUG

#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if(!(n)) { \
printf("%s - Failed",#n); \
printf("On %s ",__DATE__); \
printf("At %s ",__TIME__); \
printf("In File %s ",__FILE__); \
printf("At Line %d\n",__LINE__); \
exit(1);}
#endif

// for debugging no use



typedef unsigned long long U64;

#define NAME "Chess dot questionmark"
// name

#define BOARD_NUMBER 120
// array for square board

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/pppppppp/RNBQKBNR w KQkq - 0 1"



// enum: lists of constants
enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK };
// chess pieces w for white and b for black

enum { COLUMN_A, COLUMN_B, COLUMN_C, COLUMN_D, COLUMN_E, COLUMN_F, COLUMN_G, COLUMN_H, COLUMN_NONE };
// column name

enum { ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8, ROW_NONE };
// row name or rank

enum { WHITE, BLACK, BOTH };
// colors for board

enum {
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ, OFFBOARD

};
// grid of 8 x 8


enum {WKCA =1 , WQCA=2, BKCA=4, BQCA=8};
// 0000 4 bits represnets the castling permisons




enum { FALSE, TRUE };

typedef struct{

  int move;
  int castlingPermission;
  int enPas;
  int fiftyMove;
  U64 postionKey;

  // all these will be stored before the move is made


}Undo_struct;


typedef struct{

  int pices[BOARD_NUMBER];
  U64 pawns[3];
  // white black or both

  int kingSquare[2];

  int side;
  // which side to move

  int enPas;
  // for checking en passant rule

  int fiftyMove;
  // for checking 50 move rule

  int ply;
  int ply1;
  // ply1 is for history of player move

  // for checking half moves(50 move rule)

  int castlingPermission;

  U64 postionKey;
  // for each position


int picesNumber[13];
// 13 bcoz including empty

int bigPieces[3];
// all other than the pawns

int majorPieces[3];
// rooks and queen and king

int minorPieces[3];
// bishops and knight

int material[2];

// all 3 bcoz of the color

Undo_struct history[2048];
// 2048 coz number of moves in a game is always less than 2048

int pieceslist[13][10];
// piece list

} Board_struct;


#define FR2SQ(c,r) ( (21 + (c) ) + ( (r) * 10 ) )
// c for column and r for rows
// its use is to jab hum 64 array ke according indext denge to vo 120 ke according return kre
#define SQ64(sq120) Sq120ToSq64[sq120]
#define SQ120(sq64) (Sq64ToSq120[(sq64)])
#define POP(b) PopBit(b)
#define CNT(b) CountBits(b)
#define CLRBIT(bb,sq) ((bb) &= ClearMask[(sq)])
#define SETBIT(bb,sq) ((bb) |= SetMask[(sq)])



#define IsBQ(p) (PieceISBishopQueen[(p)])
#define IsRQ(p) (PieceISRookQueen[(p)])
#define IsKn(p) (PieceISKnight[(p)])
#define IsKi(p) (PieceISKing[(p)])

// to check type of pices


// macros



extern int Sq120ToSq64[BOARD_NUMBER];
extern int Sq64ToSq120[64];

extern U64 SetMask[64];
extern U64 ClearMask[64];
extern U64 PieceKeys[13][120];
extern U64 SideKeys;
extern U64 CastleKeys[16];

extern char PieceCharacter[];
extern char SideCharacter[];
extern char RowCharacter[];
extern char ColumnCharacter[];


extern int PieceBig[13];
extern int PieceMajor[13];
extern int PieceMinor[13];
extern int PieceValue[13];
extern int PieceColour[13];

// printing board characters



extern int ColumnBoard[BOARD_NUMBER];
extern int RowBoard[BOARD_NUMBER];
// column and row array


extern int PieceISKnight[13];
extern int PieceISKing[13];
extern int PieceISRookQueen[13];
extern int PieceISBishopQueen[13];
// to return which type of piece

// globals



extern void allInit();
// inside init.c

extern void printBitB(U64 bb);
extern int PopBit(U64 *bb);
extern int CountBits(U64 b);
// inside bitboard.c

// functions


extern U64 GeneratePosKey(const Board_struct *pos);
// hashkeys.c


extern void resetBoard(Board_struct *pos);
extern void parse_FEN(char *fen, Board_struct *pos);
extern void PrintingBoard(const Board_struct *pos);
extern void UpdateListsMaterial(Board_struct *pos);
extern int CheckBoard(const Board_struct *pos);
// c_board.c



extern int SqAttacked(const int sq, const int side, const Board_struct *pos);
// attack.c


#endif
