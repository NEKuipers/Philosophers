/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/25 19:11:41 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/06/25 19:43:53 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static long int	ft_atoi_long_part_two(const char *str, int i, int pn)
{
	unsigned long int	result;

	result = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		if ((result > 922337203685477580 || (result == 922337203685477580 \
			 && (str[i] - '0') > 7)) && pn == 1)
			return (-1);
		else if ((result > 922337203685477580 || (result == 922337203685477580 \
			 && (str[i] - '0') > 8)) && pn == -1)
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * pn);
}

static long int	ft_atoi_long(const char *str)
{
	int			i;
	int			pn;
	long int	result;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13) || \
			(str[i] == '+' && str[i + 1] >= '0' && str[i + 1] <= '9'))
		i++;
	pn = 1;
	if (str[i] == '-')
	{
		pn = -1;
		i++;
	}
	result = ft_atoi_long_part_two(str, i, pn);
	return (result);
}

int	inputvalidator(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) == 0)
			return (0);
		j = 0;
		while (argv[i][j])
		{
			if (ft_strchr(" 0123456789/0", argv[i][j]) == NULL)
				return (0);
			j++;
		}
		if (ft_atoi_long(argv[i]) > 2147483647 || \
			ft_atoi_long(argv[i]) < -2147483648)
			return (0);
		i++;
	}
	return (1);
}

int	parser(t_inf *inf, int ac, char **av)
{
	inf->forks_mutex = NULL;
	inf->amount = ft_atoi(av[1]);
	inf->time_to_die = ft_atoi(av[2]);
	inf->time_to_eat = ft_atoi(av[3]);
	inf->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		inf->max_eats = ft_atoi(av[5]);
	else
	{
		inf->max_eats = 0;
		inf->meflag = 1;
	}
	if (inf->amount < 1 || inf->amount > 200 || inf->time_to_die < 60 || \
		inf->time_to_eat < 60 || inf->time_to_sleep < 60 || inf->max_eats < 0)
		return (1);
	inf->guys = (t_guy *)malloc(sizeof(*(inf->guys)) * inf->amount);
	if (inf->guys == NULL)
		return (1);
	setup_guys(inf);
	return (setup_mutex(inf));
}
