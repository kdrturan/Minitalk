/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:21:23 by kdrturan          #+#    #+#             */
/*   Updated: 2024/12/06 16:54:49 by kdrturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	bit_count;

void	signal_handler(int sig, siginfo_t *info, void *num)
{
	static unsigned char	byte;

	if (sig == SIGUSR1)
		byte |= (1 << bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		write(1, &byte, 1);
		byte = 0;
		bit_count = 0;
	}
	kill(info->si_pid, SIGUSR1);
	num++;
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	bit_count = 0;
	pid = getpid();
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("%d\n", pid);
	while (1)
	{
		pause();
	}
	return (0);
}
