/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_sim.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/10 11:50:08 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/06/11 14:51:46 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

static void	*monitor(void *a_guy)
{
	t_guy		*guy;

	guy = (t_guy*)a_guy;
	while (1)
	{
		pthread_mutex_lock(&guy->mutex);
		if (!guy->is_eating && get_time() > guy->limit)
		{
			display_message(guy, DIED);
			pthread_mutex_unlock(&guy->mutex);
			pthread_mutex_unlock(&guy->inf->dead_mutex);
			return ((void*)0);
		}
		pthread_mutex_unlock(&guy->mutex);
		usleep(1000);
	}
}

static void	*loop(void *a_guy)
{
	t_guy		*guy;
	pthread_t	tid;

	guy = (t_guy *)a_guy;
	guy->last_eat = ft_time();
	guy->limit = guy->last_eat + guy->inf->time_to_die;
	if (pthread_create(&tid, NULL, &monitor, a_guy) != 0)
		return (void *)1);
	while (1)
	{
		// take_forks(guy);
		// eat(guy);
		// clean_forks(guy);
		// print_status(guy);
	}
	return ((void *)0);
}

int	start_sim(t_inf *inf)
{
	pthread_t	tid;
	int			i;
	void		*guy;

	inf->start = ft_time();
	i = 0;
	while (i < inf->amount)
	{
		guy = (void *)(&inf->guys[i]);
		if (pthread_create(&tid, NULL, &loop, guy))
			return (1);
		pthread_detach(tid);
		usleep(100);
		i++;
	}
	return (0);
}
