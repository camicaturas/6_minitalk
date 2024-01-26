/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri < cberneri@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2024/01/26 18:37:41 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_bit_count = 0;

int	ft_convert(volatile char *binaryString)
{
	int	result;

	result = 0;
	while (*binaryString)
	{
		result = (result << 1) + (*binaryString - '0');
		binaryString++;
	}
	return (result);
}

void	handler(int signal, siginfo_t *info, void *context)
{
	static volatile char			bit_stash[7];

	(void)info;
	(void)context;
	if (signal == SIGUSR1)
	{
		bit_stash[g_bit_count] = '0';
	}
	else if (signal == SIGUSR2)
	{
		bit_stash[g_bit_count] = '1';
	}
	g_bit_count++;
	if (g_bit_count == 8)
	{
		ft_printf("%c", ft_convert(bit_stash));
		ft_bzero((char *)bit_stash, 8);
		g_bit_count = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handler;
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_printf("Error setting up SIGUSR1 handler");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Error setting up SIGUSR2 handler");
		exit(EXIT_FAILURE);
	}
	ft_printf("SERVER || %i || ONLINE .\n\n", getpid());
	while (1)
		pause();
	return (0);
}
