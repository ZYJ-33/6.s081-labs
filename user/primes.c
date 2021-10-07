#include "kernel/types.h"
#include "user/user.h"

void new_process(int fd[2])
{
	close(fd[1]);
	int num;
	int term;
	read(fd[0], &num, 4);
	int new_fd[2];
	printf("%d\n", num);
	int create_process = 0;
	while(read(fd[0], &term, 4)!=0)
	{
		if(term%num!=0)
		{
			if(create_process)
				write(new_fd[1], &term, 4);
			else
			{
				pipe(new_fd);
				create_process = 1;
				if(fork()==0)
				{
					new_process(new_fd);
				}
				else
				{
					close(new_fd[0]);
					write(new_fd[1], &term, 4);	
				}
			}
		}
	}
	close(fd[0]);
	close(new_fd[1]);
	wait((void*)0);
	exit(0);

}
int main(int argc, char* argv[])
{
	int fd[2];
	pipe(fd);
	if(fork() == 0)
	{
		new_process(fd);	
		exit(0);
	}
	else
	{
		close(fd[0]);
		for(int i=2; i<=35; i++)
		{
			write(fd[1], &i, 4);
		}
		close(fd[1]);
		wait((void*)0);
		exit(0);
	}

	
}
