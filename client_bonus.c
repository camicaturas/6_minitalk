/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri < cberneri@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2024/03/27 17:05:59 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ucontext.h>
#include <signal.h>
#include "libft/libft.h"

void	error_controller(int error_index)
{
	if (error_index == 1)
		ft_printf("\n Error: You didn't provide any parameter.\n\n");
	if (error_index == 2)
		ft_printf("\n Error: Not enough parameters supplied.\n\n");
	if (error_index == 3)
		ft_printf("\n Error: The format provided is not correct.\n\n");
	if (error_index >= 4)
		ft_printf("\n Error: Too many parameters supplied. \n\n");
}

void	message_confirmation(int sig)
{
	if (sig == SIGUSR2)
		ft_printf("Message recieved!!\n");
}

void	signal_data(char character, int pid)
{
	int	octet;

	octet = 0;
	while (octet < 8)
	{
		if ((character & (0x01 << octet)))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
		octet++;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		while (argv[2][i])
		{
			signal_data(argv[2][i], pid);
			i++;
		}
		signal(SIGUSR2, message_confirmation);
		signal_data(pid, '\0');
	}
	else
	{
		error_controller(argc);
		return (1);
	}
	return (0);
}
