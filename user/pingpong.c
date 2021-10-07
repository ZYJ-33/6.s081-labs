#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
   int p_fd[2];
   int c_fd[2];
   pipe(p_fd);
   pipe(c_fd);

   if(fork() == 0)
   {
	int pid = getpid();
	char tmp = 'a';
	read(p_fd[0], &tmp, 1);
	printf("<%d>: receive ping", pid);
	write(c_fd[1], &tmp, 1);
	exit(0);
   }
   else
   {
	char tmp = 'a';
	int pid = getpid();
	write(p_fd[1], &tmp, 1);
	read(c_fd[0], &tmp, 1);
	printf("<%d>: receive pong", pid);
	exit(0);
   } 
}
