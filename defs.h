#ifndef DEFS_H
#define DEFS_H

typedef unsigned long long U64;

#define NAME "Chess dot questionmark"
// name

#define BOARD_NUMBER 120
// array for square board



// enum: lists of constants
enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK };
// chess pieces w for white and b for black

enum { COLUMN_A, COLUMN_B, COLUMN_C, COLUMN_D, COLUMN_E, COLUMN_F, COLUMN_G, COLUMN_NONE };
// column name

enum { ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8, ROW_NONE };
// row name

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
    A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ

};
// grid of 8 x 8


enum {WK_castling =1 , WQ_castling=2, BK_castling=4, BQ_castling=8};
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
// rooks and queen

int minorPieces[3];
// bishops and knight

// all 3 bcoz of the color

Undo_struct history[2048];
// 2048 coz number of moves in a game is always less than 2048


} Board_struct;






#endif
