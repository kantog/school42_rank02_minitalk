/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:33:31 by bclaeys           #+#    #+#             */
/*   Updated: 2024/09/13 18:35:33 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <signal.h>

void	bin_from_dec(int ascii_char, char binary[9])
{
	int	binary_counter;
	int	index;

	binary_counter = 64;
	index = 1;
	binary[0] = '0';
	while (index <= 7)
	{
		if (ascii_char >= binary_counter)
		{
			binary[index] = '1';
			ascii_char -= binary_counter;
		}
		else
			binary[index] = '0';
		binary_counter = binary_counter / 2;
		index++;
	}
	if (binary_counter == 1 && ascii_char % 2 == 0)
		binary[index] = '1';
}

int	main(int ac, char **av)
{
	int		j;
	int		k;
	char	binary[9];

	j = 0;
	k = 0;
	binary[8] = '\0';
	if (ac != 3)
		return (1);
	while (av[2][j])
	{
		bin_from_dec(av[2][j], binary);
		while (binary[k])
		{
			if (binary[k] == '0')
				kill(ft_atoi(av[1]), SIGUSR1);
			if (binary[k] == '1')
				kill(ft_atoi(av[1]), SIGUSR2);
			k++;
			usleep(150);
		}
		k = 0;
		j++;
	}
}
