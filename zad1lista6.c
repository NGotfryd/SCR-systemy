#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<sys/types.h>



int main()
{
	char fname[64];
	int fd;
	struct stat statpl;
	char *map;
	int i = getchar();

	
	while(1)
	{
		printf("podaj nazwe pliku: ");
		scanf("%c", fname);
		fd = open(fname, O_RDONLY);
	
		if(fd < 0)
			return 1;
		
	   
		fstat(fd, &statpl);
		map = mmap(NULL, statpl.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
		ftruncate(fd, statpl.st_size);
		

		msync(fname, statpl.st_size , MS_SYNC);
			
	
	
	}
	

	
	return 0;
}

