#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int read_line(char buf[512])
{
	char tmp;
	int i = 0;
	for(; i<511;i++)
	{
		if(read(0, &tmp, 1)!=0)
		{
			buf[i] = tmp;
			if(tmp == ' ')
			   break;	
		}
		else
			break;	
	}
	if(i == 511)
	{
		fprintf(2, "xargs: input line is too loog\n");
		exit(1);
	}
	buf[i] = '\0';
	return i;
}


int main(int argc, char* argv[])
{
	char buf[512];
	
	for(int i=1; i<argc; i++)
	    argv[i-1] = argv[i];
	
	while(read_line(buf)>0)
	{
		argv[argc-1] = buf;
		if(fork()==0)
		{
			exec(argv[0], argv);
			fprintf(2, "exec failed\n");
			exit(1);
		}
		else
		{
			wait((void*)0);
		}
	}
	exit(0);
}

