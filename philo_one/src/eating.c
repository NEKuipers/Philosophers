/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eating.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/20 11:05:43 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/06/20 11:47:36 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

void	fork_management(t_guy *guy)
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