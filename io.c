#include "stdio.h"
#include "defs.h"

char *PrSq(const int sq) {

	static char SqStr[3];

	int col = ColumnBoard[sq];
	int row = RowBoard[sq];

	sprintf(SqStr, "%c%c", ('a'+col), ('1'+row));

	return SqStr;

}

char *PrMove(const int move) {

	static char MvStr[6];

	int ff = ColumnBoard[FROMSQ(move)];
	int rf = RowBoard[FROMSQ(move)];
	int ft = ColumnBoard[TOSQ(move)];
	int rt = RowBoard[TOSQ(move)];

	int promoted = PROMOTED(move);

	if(promoted) {
		char pchar = 'q';
		if(IsKn(promoted)) {
			pchar = 'n';
		} else if(IsRQ(promoted) && !IsBQ(promoted))  {
			pchar = 'r';
		} else if(!IsRQ(promoted) && IsBQ(promoted))  {
			pchar = 'b';
		}
		sprintf(MvStr, "%c%c%c%c%c", ('a'+ff), ('1'+rf), ('a'+ft), ('1'+rt), pchar);
	} else {
		sprintf(MvStr, "%c%c%c%c", ('a'+ff), ('1'+rf), ('a'+ft), ('1'+rt));
	}

	return MvStr;
}

int ParseMove(char *ptrChar, Board_struct *pos)
{
	  if(ptrChar[1] > '8' || ptrChar[1] < '1') return NOMOVE;
    if(ptrChar[3] > '8' || ptrChar[3] < '1') return NOMOVE;
    if(ptrChar[0] > 'h' || ptrChar[0] < 'a') return NOMOVE;
    if(ptrChar[2] > 'h' || ptrChar[2] < 'a') return NOMOVE;

		// positon in letter if greater or less than

    int from = FR2SQ(ptrChar[0] - 'a', ptrChar[1] - '1');
    int to = FR2SQ(ptrChar[2] - 'a', ptrChar[3] - '1');

		printf("prtchar: %s from %d to %d\n", ptrChar, from, to);

		MoveList_struct list[1];
	  GenerateAllMoves(pos,list);
	  int MoveNum = 0;
		int Move = 0;
		int PromPce = EMPTY;


		for(MoveNum = 0; MoveNum < list->count; ++MoveNum) {
			Move = list->moves[MoveNum].move;
			if(FROMSQ(Move)==from && TOSQ(Move)==to) {
				PromPce = PROMOTED(Move);
				if(PromPce!=EMPTY) {
					if(IsRQ(PromPce) && !IsBQ(PromPce) && ptrChar[4]=='r') {
						return Move;
					} else if(!IsRQ(PromPce) && IsBQ(PromPce) && ptrChar[4]=='b') {
						return Move;
					} else if(IsRQ(PromPce) && IsBQ(PromPce) && ptrChar[4]=='q') {
						return Move;
					} else if(IsKn(PromPce)&& ptrChar[4]=='n') {
						return Move;
					}
					continue;
				}
				return Move;
			}
	    }

	    return NOMOVE;	
}
// for GUI


void PrintMoveList(const MoveList_struct *list) {
	int index = 0;
	int score = 0;
	int move = 0;
	printf("MoveList:\n",list->count);

	for(index = 0; index < list->count; ++index) {

		move = list->moves[index].move;
		score = list->moves[index].score;

		printf("Move:%d > %s (score:%d)\n",index+1,PrMove(move),score);
	}
	printf("MoveList Total %d Moves:\n\n",list->count);
}
