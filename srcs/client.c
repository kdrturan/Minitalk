/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:14:00 by kdrturan          #+#    #+#             */
/*   Updated: 2024/12/06 20:00:52 by kdrturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_flag;

void	signal_handler(int sig)
{
	if (sig == SIGUSR1)
		g_flag = 1;
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
	int	cntrl;

	cntrl = 0;
	i = 0;
	while (i < 8)
	{
		g_flag = 0;
		if (c & (1 << i))
			cntrl = kill(s_pid, SIGUSR1);
		else
			cntrl = kill(s_pid, SIGUSR2);
		i++;
		if (cntrl == -1)
		{
			ft_printf("Signal Error");
			exit(1);
		}
		if (!g_flag)
			pause();
	}
	return (cntrl);
}

int	main(int argc, char *argv[])
{
	int	s_pid;
	int	i;

	g_flag = 0;
	i = 0;
	if (argc != 3)
		return (ft_printf("Invalid input!"), -1);
	signal(SIGUSR1, signal_handler);
	s_pid = ft_atoi_mini(argv[1]);
	while (argv[2][i])
	{
		send_bits(s_pid, argv[2][i]);
		i++;
	}
	return (0);
}
