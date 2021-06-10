/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errorhandling.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/04 15:15:48 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/06/04 20:49:53 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

int		errormsg(char *msg)
{
	printf("%s", msg);
	return (1);
}

void	clear_info_two(t_inf *inf)
{
	int i;

	if (inf->philos)
	{
		i = 0;
		while (i < inf->amount)
		{
			pthread_mutex_destroy(&inf->philos[i].mutex);
			pthread_mutex_destroy(&inf->philos[i].eat_mutex);
			i++;
		}
		free(inf->philos);
	}
	return;
}

int		clear_info(t_inf *inf)
{
	int	i;

	if (inf->forks_mutex)
	{
		i = 0;
		while (i < inf->amount)
		{
			pthread_mutex_destroy(&inf->forks_mutex[i]);
			i++;
		}
		free(inf->forks_mutex);
	}
	pthread_mutex_destroy(&inf->write_mutex);
	pthread_mutex_destroy(&inf->dead_mutex);
	return (1);
}
