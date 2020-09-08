#include <stdio.h>
#include "defs.h"


int main()
{
  printf("\n");
  printf("\n");
  printf("-------------welcome to .? chess-----------------");
  printf("\n");
  printf("\n");
  allInit();


  int index;

  for(index=0; index< BOARD_NUMBER; ++index)
  {
    if(index%10==0)
    {
      printf("\n");
    }
    printf("%5d", Sq120ToSq64[index]);

  }
  printf("\n");
  printf("\n");

  for(index=0; index< 64; ++index)
  {
    if(index%8==0)
    {
      printf("\n");
    }
    printf("%5d", Sq64ToSq120[index]);

  }



    return 0;
}
