
#include "minitalk.h"
#define POSIX_C_SOURCE 208009L


unsigned char byte = 0;  
int bit_count = 0;

void signal_handler(int sig,siginfo_t *info, void *num)
{
	if (sig == SIGUSR1)
		byte |= (1 << bit_count);
	bit_count++;

    if (bit_count == 8) 
	{
        write(1, &byte, 1);
        byte = 0;
        bit_count = 0;
    }
	kill(info->si_pid,SIGUSR1);
	num++;
}


int main(void)
{
	int pid;
	struct sigaction sa;
	
	pid = getpid();
	bit_count = 0;
   	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	printf("%d\n",pid);
	while (1)
	{
		pause();
	}
	return (0);
}