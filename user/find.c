#include"kernel/types.h"
#include"kernel/stat.h"
#include"user/user.h"
#include"kernel/fs.h"

void find(char* dir, char* name)
{
	int fd, newfd;
	struct stat st, newst;
	char buf[512], *p;
	struct dirent de;
	
	if((fd = open(dir, 0))<0)
	{
		fprintf(2, "find: can't open %s", dir);
		exit(1);
	}

	if(fstat(fd, &st)<0)
	{
		fprintf(2, "find: can't stat %s", dir);
		exit(1);
	}

	switch(st.type)
	{
		case T_FILE:
			fprintf(2, "find: dir %s is a file", dir);
			exit(1);
		case T_DIR:
			strcpy(buf, dir);
			p = buf + strlen(buf);
			*p++ = '/';
			printf("cur dir is %s\n", buf);
			while(read(fd, &de, sizeof(de)) == sizeof(de))
			{
			if(de.inum == 0 )
				continue;
			memmove(p, de.name, strlen(de.name));
			p[strlen(de.name)] = 0;
			p[strlen(de.name)+1] = 0;
			if(strcmp(de.name, name) == 0)
			{
				printf("%s\n", buf);
			}
			if((newfd = open(buf, 0))<0)
			{
				fprintf(2, "find: can't open %s\n", buf);
				continue;
			}
			if(fstat(newfd, &newst) < 0)
			{		
				fprintf(2, "find: can't stat %s\n", buf);
				continue;
			}			
			if(newst.type == T_DIR)
			{
				if(strcmp(de.name, ".") !=0 && strcmp(de.name, "..")!=0)
					find(buf, name);
			}
			}
}
	
}


int
main(int argc, char* argv[])
{
	char* dir = ".";
	if(argc < 2)
	{
		fprintf(2,"too few argv for find");
		exit(1);
	}
	if(argc == 3)
	{
		find(argv[1], argv[2]);
	}
	else if(argc == 2)
	{
		find(dir, argv[1]);
	}
	exit(0);
}
