/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors_and_messages.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/04 15:15:48 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/07/02 15:16:19 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <inttypes.h>
#define __STDC_FORMAT_MACROS

int	errormsg(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (1);
}

char	*statusmsgs(int status)
{
	if (status == EATING)
		return (" is eating.\n");
	if (status == SLEEPING)
		return (" is sleeping.\n");
	if (status == TAKEN_FORK)
		return (" has taken a fork.\n");
	if (status == THINKING)
		return (" is thinking.\n");
	if (status == DIED)
		return (" died.\n");
	return ("Everyone has eaten the specified number of times.\n");
}

void	print_status(t_guy *guy, int status)
{
	static int	end = 0;

	pthread_mutex_lock(&guy->inf->write_mutex);
	if (end == 0)
	{
		printf("%" PRIu64 "\t", ft_time() - guy->inf->start);
		if (status != DONE)
			printf("%d", guy->pos + 1);
		if (status >= DIED)
			end = 1;
		printf("%s", statusmsgs(status));
	}
	pthread_mutex_unlock(&guy->inf->write_mutex);
}

void	clear_info_two(t_inf *inf)
{
	int	i;

	if (inf->guys)
	{
		i = 0;
		while (i < inf->amount)
		{
			pthread_mutex_destroy(&inf->guys[i].mutex);
			pthread_mutex_destroy(&inf->guys[i].eat_mutex);
			i++;
		}
		free(inf->guys);
	}
	return ;
}

int	clear_info(t_inf *inf)
{
	int	i;

	if (inf->forks_mutex != NULL)
	{
		i = 0;
		while (i < inf->amount)
		{
			pthread_mutex_destroy(&inf->forks_mutex[i]);
			i++;
		}
		free(inf->forks_mutex);
	}
	clear_info_two(inf);
	pthread_mutex_destroy(&inf->write_mutex);
	pthread_mutex_destroy(&inf->dead_mutex);
	return (1);
}
