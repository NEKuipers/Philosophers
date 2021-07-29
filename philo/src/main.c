/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/03 14:02:08 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/07/29 10:20:31 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/* 
** 	The function below initializes the mutexes: one to protect the statusprints,
**	one to protect the death check, and one for every fork in an array.
**	The fork array is set up for (fork_mutex * amount of philosophers).
*/

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

/*
**	This function prepares all the required information for the individual
**	philosopher threads. They're all assigned a seat at the table and their
**	own left and right forks, as well as their own mutex which locks when
**	they eat.
*/

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

/*
**	The function below parses the arguments and saves them in the inf
**	main structure. The program mustn't run when any of the ms values
**	are below 60. Finally, an array of philosophers is created, to 
**	be initialized in setup_guys().
*/

int	parser(t_inf *inf, int ac, char **av)
{
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
	inf->forks_mutex = NULL;
	inf->guys = NULL;
	inf->guys = (t_guy *)malloc(sizeof(*(inf->guys)) * inf->amount);
	if (inf->guys == NULL)
		return (1);
	setup_guys(inf);
	return (setup_mutex(inf));
}

/*
** 	The main is fairly simple, it splits the initialization process into
**	separate stages and returns to main in between.
**	The meflag variable is used so that when 0 is specified as the
**	number of times each philosopher must eat it immediately prints
**	that the eating is done without accessing any other function.
**	Without it, this would always happen if that argument was not
**	provided since I set it to 0.
*/

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
