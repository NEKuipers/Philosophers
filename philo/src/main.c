/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/03 14:02:08 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/06/25 11:51:49 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	setup_mutex(t_inf *inf)
{
	int	i;

	pthread_mutex_init(&inf->write_mutex, NULL);
	pthread_mutex_init(&inf->dead_mutex, NULL);
	pthread_mutex_lock(&inf->dead_mutex);
	inf->forks_mutex = \
		(pthread_mutex_t *)malloc(sizeof(*(inf->forks_mutex)) * inf->amount);
	if (inf->forks_mutex == NULL)
		return (1);
	i = 0;
	while (i < inf->amount)
	{
		pthread_mutex_init(&inf->forks_mutex[i], NULL);
		i++;
	}
	return (0);
}

static void	setup_guys(t_inf *inf)
{
	int	i;

	i = 0;
	while (i < inf->amount)
	{
		inf->guys[i].pos = i;
		inf->guys[i].is_eating = 0;
		inf->guys[i].left_fork = i;
		inf->guys[i].right_fork = (i + 1) % inf->amount;
		inf->guys[i].eat_count = 0;
		inf->guys[i].inf = inf;
		pthread_mutex_init(&inf->guys[i].mutex, NULL);
		pthread_mutex_init(&inf->guys[i].eat_mutex, NULL);
		pthread_mutex_lock(&inf->guys[i].eat_mutex);
		i++;
	}
}

int	parser(t_inf *inf, int ac, char **av)
{
	inf->amount = ft_atoi(av[1]);
	inf->time_to_die = ft_atoi(av[2]);
	inf->time_to_eat = ft_atoi(av[3]);
	inf->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		inf->max_eats = ft_atoi(av[5]);
	else
		inf->max_eats = 0;
	if (inf->amount < 2 || inf->amount > 100 || inf->time_to_die < 60 || \
		inf->time_to_eat < 60 || inf->time_to_sleep < 60 || inf->max_eats < 0)
		return (1);
	inf->forks_mutex = NULL;
	inf->guys = (t_guy *)malloc(sizeof(*(inf->guys)) * inf->amount);
	if (inf->guys == NULL)
		return (1);
	setup_guys(inf);
	return (setup_mutex(inf));
}

int	main(int ac, char **av)
{
	t_inf	inf;

	if (ac != 5 && ac != 6)
		return (errormsg("Error: incorrect amount of arguments.\n"));
	if (parser(&inf, ac, av))
		return (clear_info(&inf) && errormsg("Error.\n"));
	if (start_sim(&inf))
		return (clear_info(&inf) && errormsg("Error.\n"));
	pthread_mutex_lock(&inf.dead_mutex);
	pthread_mutex_unlock(&inf.dead_mutex);
	clear_info(&inf);
	return (0);
}
