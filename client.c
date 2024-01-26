/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri < cberneri@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2024/01/26 18:39:09 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal(int pid, unsigned char octet)
{
	int				i;
	unsigned char	bit;

	i = 7;
	while (i >= 0)
	{
		bit = (octet >> i) & 1;
		if (bit == 0)
		{
			kill(pid, SIGUSR1);
		}
		else
		{
			kill(pid, SIGUSR2);
		}
		usleep(100);
		i--;
	}
}

void	ft_error(int num, char *thing)
{
	if (num <= 2)
		ft_printf("ERROR | You sent an insufficient number of parameters.\n");
	else if (num >= 4)
		ft_printf("ERROR | Too many parameters!\n");
	if (!(thing[0] > 47 && thing[0] < 58))
		ft_printf("\n\nERROR | Bad format.\n");
}

int	main(int argc, char **argv)
{
	int		pid;
	int		i;
	char	*msg;

	if (argc != 3 || !(argv[1][0] > 47 && argv[1][0] < 58))
	{
		ft_error(argc, argv[1]);
		return (-1);
	}
	pid = ft_atoi(argv[1]);
	msg = argv[2];
	i = 0;
	while (msg[i])
	{
		send_signal(pid, (unsigned char) msg[i]);
		i++;
	}
	send_signal(pid, '\n');
	ft_printf("CLIENT | Sending %d symbols:\nCLIENT | %s", i, argv[2]);
	return (0);
}
