
#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char* argv[])
{
   if(argc < 2)
  {
     fprintf(2, "need a number");
     exit(1);	
  }
   int time = atoi(argv[1]);
   fprintf(1, "sleep %d", time);
   sleep(time);
   exit(0);
}
