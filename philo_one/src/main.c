/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/03 14:02:08 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/06/03 14:25:45 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

int		main(int ac, char **av)
{
	(void)av;
	if (ac != 5 && ac != 6)
	{
		printf("Error\n");
		return (1);
	}
	return (0);
}