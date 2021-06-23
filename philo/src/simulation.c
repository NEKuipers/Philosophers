/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/10 11:50:08 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/06/23 10:36:23 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eating_with_forks(t_guy *guy)
{
	pthread_mutex_lock(&guy->inf->forks_mutex[guy->left_fork]);
	print_status(guy, TAKEN_FORK);
	pthread_mutex_lock(&guy->inf->forks_mutex[guy->right_fork]);
	print_status(guy, TAKEN_FORK);
	pthread_mutex_lock(&guy->mutex);
	guy->is_eating = 1;
	guy->last_eat = ft_time();
	guy->limit = guy->last_eat + guy->inf->time_to_die;
	print_status(guy, EATING);
	usleep(guy->inf->time_to_eat * 1000);
	guy->eat_count += 1;
	guy->is_eating = 0;
	pthread_mutex_unlock(&guy->mutex);
	pthread_mutex_unlock(&guy->eat_mutex);
	print_status(guy, SLEEPING);
	pthread_mutex_unlock(&guy->inf->forks_mutex[guy->left_fork]);
	pthread_mutex_unlock(&guy->inf->forks_mutex[guy->right_fork]);
	usleep(guy->inf->time_to_sleep * 1000);
}

static void	*count_until_limit(void *inf_ptr)
{
	t_inf	*inf;
	int		i;
	int		counter;

	inf = (t_inf *)inf_ptr;
	counter = 0;
	while (counter < inf->max_eats)
	{
		i = 0;
		while (i < inf->amount)
		{
			pthread_mutex_lock(&inf->guys[i].eat_mutex);
			i++;
		}
		counter++;
	}
	print_status(&inf->guys[0], DONE);
	pthread_mutex_unlock(&inf->dead_mutex);
	return ((void *) 0);
}

static void	*check_if_dead(void *guy_ptr)
{
	t_guy	*guy;

	guy = (t_guy *)guy_ptr;
	while (1)
	{
		pthread_mutex_lock(&guy->mutex);
		if (!guy->is_eating && ft_time() > guy->limit)
		{
			print_status(guy, DIED);
			pthread_mutex_unlock(&guy->mutex);
			pthread_mutex_unlock(&guy->inf->dead_mutex);
			return ((void *)0);
		}
		pthread_mutex_unlock(&guy->mutex);
		usleep(1000);
	}
}

static void	*eat_sleep_think_repeat(void *guy_ptr)
{
	t_guy		*guy;
	pthread_t	tid;

	guy = (t_guy *)guy_ptr;
	guy->last_eat = ft_time();
	guy->limit = guy->last_eat + guy->inf->time_to_die;
	if (pthread_create(&tid, NULL, &check_if_dead, guy_ptr) != 0)
		return ((void *)1);
	while (1)
	{
		eating_with_forks(guy);
		print_status(guy, THINKING);
	}
	return ((void *)0);
}

int	start_sim(t_inf *inf)
{
	pthread_t	tid;
	int			i;
	void		*guy;

	inf->start = ft_time();
	if (inf->max_eats > 0)
	{
		if (pthread_create(&tid, NULL, &count_until_limit, (void *)inf) != 0)
			return (1);
		pthread_detach(tid);
	}
	i = 0;
	while (i < inf->amount)
	{
		guy = (void *)(&inf->guys[i]);
		if (pthread_create(&tid, NULL, &eat_sleep_think_repeat, guy))
			return (1);
		pthread_detach(tid);
		usleep(100);
		i++;
	}
	return (0);
}
