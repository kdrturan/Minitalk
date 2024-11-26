
#include "minitalk.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	int		result;

	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * sign);
}


int	send_bits(int s_pid,char c)
{
	int i = 0;

	while (i < 8)
	{
		if (c & (1 << i))
			kill(s_pid,SIGUSR1);
		else
			kill(s_pid,SIGUSR2);
		i++;
		usleep(1000);
	}
	return(0);
}



int main(int argc,char *argv[])
{
	int s_pid;
	int i = 0;

	s_pid = ft_atoi(argv[1]);

	printf("%d\n",s_pid);
	while (argv[2][i])
	{
		send_bits(s_pid,argv[2][i]);
		i++;
	}
	return (0);
}