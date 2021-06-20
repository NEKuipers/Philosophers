/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_one.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/03 14:03:25 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/06/20 12:22:13 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdint.h>
# include <pthread.h>
# include <sys/wait.h>
# include <sys/time.h>

# define EATING 	0
# define SLEEPING	1
# define TAKEN_FORK	2
# define THINKING	3
# define DIED	 	4
# define DONE	 	5


typedef struct s_guy
{
	int				position;
	int				is_eating;
	uint64_t		limit;
	uint64_t		last_eat;
	int				left_fork;
	int				right_fork;
	int				eat_count;
	struct s_inf	*inf;
	pthread_mutex_t	mutex;
	pthread_mutex_t	eat_mutex;
}					t_guy;

typedef struct s_inf
{
	int				amount;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				max_eats;
	uint64_t		start;
	t_guy			*guys;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	dead_mutex;
}					t_inf;

int					clear_info(t_inf *inf);
int					errormsg(char *msg);
void				eating_with_forks(t_guy *guy);
int					ft_atoi(const char *str);
size_t				ft_strlen(const char *s);
uint64_t			ft_time(void);
int					parser(t_inf *inf, int ac, char **av);
int					main(int ac, char **av);
void				print_status(t_guy *guy, int status);
int					setup_mutex(t_inf *inf);
int					start_sim(t_inf *inf);

#endif