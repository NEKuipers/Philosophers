/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_sim.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/10 11:50:08 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/06/10 12:55:55 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

static void	*loop(void *a_guy)
{
	t_guy		*guy;
	pthread_t	tid;

	guy = (t_guy *)a_guy;
	guy->last_eat = ft_time();
	guy->limit = guy->last_eat + guy->inf->time_to_die;
	
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
