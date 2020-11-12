#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <ucontext.h>



int flag=0; //flaga potrzebna do wstrzymania odbierania sygnalow

//Funkcja obslugujaca przychodzace sygnaly
void sig_handler(int sig, siginfo_t *sip, ucontext_t *uap)
{

  if(sig==14)
  {
    printf("sygnal SIGALRM\n");
    printf("Program zostanie wylaczony\n");
    exit(1);
  }
  if(sig==15)
  {
    printf("sygnal SIGTERM\n");
    printf("Program bedzie kontynuowany\n");
  }
  if(sig==10)
  {
    printf("Otrzymalem sygnal SIGUSR1\n");
    printf("Odbieranie sygnalow zostanie wstrzymane na 100 iteracji petli\n");
    flag=1;
  }

}


void main(){


struct sigaction act;
act.sa_handler =sig_handler;
sigemptyset(&act.sa_mask);
act.sa_flags=SA_SIGINFO;



struct timespec ts;
ts.tv_sec=(time_t) 0;
ts.tv_nsec=100000000L;  //100ms

signal(SIGUSR2,SIG_IGN);

int i = 0, tmp = 0;

for(;;)
{

  i++;
  
  if(flag == 0)
  {
  act.sa_handler=sig_handler;
  sigaction(SIGTERM, &act, 0);
  sigaction(SIGALRM, &act, 0);
  sigaction(SIGUSR1, &act, 0);
  }
  if(flag == 1)
  {
    act.sa_handler =SIG_IGN;
    sigaction(SIGTERM, &act, 0);
    sigaction(SIGALRM, &act, 0);
    sigaction(SIGUSR1, &act, 0);
  
  
    if(tmp == 0)
    {
	    tmp = i + 100;
    }
    if(tmp == i)
    {
	    printf("juz mozna wysylac sygnaly \n");
	    flag = 0;
	    tmp = 0;
    }

  }
//  printf("Hello World!\n");
  nanosleep(&ts,NULL);
}




}
