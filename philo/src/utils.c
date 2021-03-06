/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/03 14:53:31 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/06/25 19:14:11 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/* 
** ft_time returns the current time in a uint64 variable.
*/

uint64_t	ft_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000));
}

static long int	ft_atoi_part_two(const char *str, int i, int pn)
{
	unsigned long int	result;

	result = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		if ((result > 922337203685477580 || (result == 922337203685477580 \
			 && (str[i] - '0') > 7)) && pn == 1)
			return (-1);
		else if ((result > 922337203685477580 || (result == 922337203685477580 \
			 && (str[i] - '0') > 8)) && pn == -1)
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * pn);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			pn;
	long int	result;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13) || \
			(str[i] == '+' && str[i + 1] >= '0' && str[i + 1] <= '9'))
		i++;
	pn = 1;
	if (str[i] == '-')
	{
		pn = -1;
		i++;
	}
	result = ft_atoi_part_two(str, i, pn);
	return (result);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	*string;
	int		i;
	char	d;

	d = (char)c;
	i = 0;
	string = (char *)s;
	while (string[i] != '\0')
	{
		if (string[i] == d)
			return (&string[i]);
		i++;
	}
	if (d == '\0')
		return (&string[i]);
	else
		return (NULL);
}
