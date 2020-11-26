#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){

	int potok_fd[2];
	pid_t PID;
	int deskryptor;
	char bufor[128];
	char nazwa_pliku[64];
	int licznik;

	pipe(potok_fd);
	PID = fork();

	if(PID>0)
	{
		printf("proces rodzica\n");
		close(potok_fd[0]);
		printf("wpisz nazwe pliku: ");
		scanf("%s", nazwa_pliku);

		deskryptor = open(nazwa_pliku, O_RDONLY);


		while((licznik = read(deskryptor,bufor,128)) > 0)
		{
			write(potok_fd[1],bufor,licznik);
			
		}	
	
		close(potok_fd[1]);
	}
			
	else if(PID == 0)
	{
		printf("proces dziecka");
		close(0);
		dup(potok_fd[0]);
		close(potok_fd[0]);
		close(potok_fd[1]);
	       	close(1);
		execlp("display","",NULL);
	}
	else 
	{ printf("blad");
	  return -1;
	}
		
	return 0;
}
