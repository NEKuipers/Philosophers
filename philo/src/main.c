/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/03 14:02:08 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/06/25 19:44:10 by nkuipers      ########   odam.nl         */
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

void	setup_guys(t_inf *inf)
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

int	main(int ac, char **av)
{
	t_inf	inf;

	inf.meflag = 0;
	if ((ac != 5 && ac != 6) || !inputvalidator(av))
		return (errormsg("Error: bad arguments.\n"));
	if (parser(&inf, ac, av) == 1)
		return (clear_info(&inf) && errormsg("Error: bad arguments.\n"));
	if (inf.max_eats == 0 && inf.meflag == 0)
		return (clear_info(&inf) && printf("0\t%s", statusmsgs(DONE)));
	if (start_sim(&inf) == 1)
		return (clear_info(&inf) && errormsg("Error.\n"));
	pthread_mutex_lock(&inf.dead_mutex);
	pthread_mutex_unlock(&inf.dead_mutex);
	clear_info(&inf);
	return (0);
}
