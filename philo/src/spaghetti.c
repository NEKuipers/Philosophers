/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   spaghetti.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/10 11:50:08 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/06/26 14:35:13 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
**		The function below is where every separate thread goes through the
**		process of taking forks, eating when they are able to grab two, and
**		releasing them and sleeping when they're done. 
*/

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

/*
**	This function below counts until every philosopher has
**	eaten N amount of times, if that argument was provided.
**
**	When they have eaten enough, the program ends.
*/

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
	pthread_join(inf->tid, NULL);
	return ((void *) 0);
}

/*
**	This function is for a separate thread per philosopher.
**	It monitors whether the time since their last meal has exceeded
**	the amount of time they can go without eating, locked by mutex.
**	If so, they die, and the program ends.
*/

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
			pthread_join(guy->tid, NULL);
			return ((void *)0);
		}
		pthread_mutex_unlock(&guy->mutex);
		usleep(1000);
	}
}

/*
**	Each philosopher gets a timestamp of their last meal, and
**	produces another thread that monitors whether or not they've
**	died. The while loop just keeps calling their daily routine
**	of eating, sleeping and thinking over and over again.
*/

static void	*eat_sleep_think_repeat(void *guy_ptr)
{
	t_guy		*guy;
	pthread_t	tid;

	guy = (t_guy *)guy_ptr;
	guy->last_eat = ft_time();
	guy->limit = guy->last_eat + guy->inf->time_to_die;
	if (pthread_create(&tid, NULL, &check_if_dead, guy_ptr) != 0)
		return ((void *)1);
	pthread_detach(tid);
	while (1)
	{
		eating_with_forks(guy);
		print_status(guy, THINKING);
	}
	return ((void *)0);
}

/*
**	Below is where the simulation is initialized in two steps. 
**	If a number of times each philosopher must eat argument was provided,
**	an additional thread is created to count towards this number.
**
**	The while loop creates threads for every individual philosopher and 
**	sends them into the function above.
*/

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
		inf->tid = tid;
		pthread_detach(tid);
	}
	i = 0;
	while (i < inf->amount)
	{
		guy = (void *)(&inf->guys[i]);
		if (pthread_create(&tid, NULL, &eat_sleep_think_repeat, guy))
			return (1);
		inf->guys[i].tid = tid;
		pthread_detach(tid);
		usleep(100);
		i++;
	}
	return (0);
}
