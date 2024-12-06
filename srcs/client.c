/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:14:00 by kdrturan          #+#    #+#             */
/*   Updated: 2024/12/06 16:45:25 by kdrturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	flag;

void	signal_handler(int sig)
{
	if (sig == SIGUSR1)
		flag = 1;
}

int	ft_atoi_mini(const char *str)
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

int	send_bits(int s_pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		flag = 0;
		if (c & (1 << i))
			kill(s_pid, SIGUSR1);
		else
			kill(s_pid, SIGUSR2);
		i++;
		if (!flag)
			pause();
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int	s_pid;
	int	i;

	flag = 0;
	i = 0;
	flag = 0;
	if (argc > 2)
	{
		signal(SIGUSR1, signal_handler);
		s_pid = ft_atoi_mini(argv[1]);
		while (argv[2][i])
		{
			send_bits(s_pid, argv[2][i]);
			i++;
		}
	}
	return (0);
}
