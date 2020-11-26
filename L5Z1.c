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
	FILE *Plik;
	pipe(potok_fd);
	PID = fork();

	if(PID > 0)
	{
		printf("proces rodzica");
		close(potok_fd[0]);
		printf("wpisz nazwe pliku: ");
		scanf("%s", nazwa_pliku);
		Plik = fopen(nazwa_pliku, "r");
		if(Plik == NULL)
		{
			printf("nie ma takiego pliku");
			return 1;
		}
	
		

		deskryptor = open(nazwa_pliku, O_RDONLY);


		while((licznik = read(deskryptor, bufor,128)) > 0)
		{
			write(potok_fd[1],bufor,licznik);
		}
		
		close(potok_fd[1]);
	
		fclose(Plik);
	}

	else if(PID == 0)
	{
		printf("proces dziecka\n");
		close(potok_fd[1]);
		while (licznik = read(potok_fd[0], bufor, 128))
		{
			write(1, bufor, licznik);
		}

		printf("koniec czytania\n");

				
	}

	else 
	{
		return -1;
	}

	return 0;
}
