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
