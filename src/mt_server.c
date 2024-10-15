/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:19:22 by bclaeys           #+#    #+#             */
/*   Updated: 2024/09/13 18:16:08 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <signal.h>

void	mt_handler_server(int sig)
{
	static int	index;
	int			i;
	int			ascii_char;
	int			binary_counter;
	char		binary[8];

	binary_counter = 128;
	ascii_char = 0;
	i = 0;
	if (sig == SIGUSR1)
		binary[index] = '0';
	if (sig == SIGUSR2)
		binary[index] = '1';
	index++;
	if (index != 8)
		return ;
	while (i <= 9)
	{
		if (binary[i] == '1')
			ascii_char += binary_counter;
		binary_counter = binary_counter / 2;
		i++;
	}
	write(1, &ascii_char, 1);
	index = 0;
}

int	main(void)
{
	struct sigaction	mt_sa;
	int					pid_server;

	mt_sa.sa_flags = SA_RESTART;
	sigemptyset(&mt_sa.sa_mask);
	mt_sa.sa_handler = &mt_handler_server;
	pid_server = getpid();
	if (pid_server == -1)
		return (1);
	ft_printf("%d\n", pid_server);
	if (sigaction(SIGUSR1, &mt_sa, NULL) < 0)
		ft_printf("sigaction failed");
	if (sigaction(SIGUSR2, &mt_sa, NULL) < 0)
		ft_printf("sigaction failed");
	while (1)
		;
}
