/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_sim.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/10 11:50:08 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/06/10 12:41:23 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

static void	*loop(void *a_guy)
{

}

int	start_sim(t_inf *inf)
{
	pthread_t	tid;
	int			i;
	void		*guy;

	inf->start = get_time();
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
