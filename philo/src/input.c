/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/25 19:11:41 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/07/28 14:29:21 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static long int	ft_atoi_long_part_two(const char *str, int i, int pn)
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

static long int	ft_atoi_long(const char *str)
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
	result = ft_atoi_long_part_two(str, i, pn);
	return (result);
}

/*
**	The function below validates the input, using atoi_long above to 
**	make sure no number greater than MAX_INT is parsed. Only positive 
**	numbers are passed on to regular atoi to parse into the structure.
*/

int	inputvalidator(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) == 0)
			return (0);
		j = 0;
		while (argv[i][j])
		{
			if (ft_strchr(" 0123456789/0", argv[i][j]) == NULL)
				return (0);
			j++;
		}
		if (ft_atoi_long(argv[i]) > 2147483647 || \
			ft_atoi_long(argv[i]) < -2147483648)
			return (0);
		i++;
	}
	return (1);
}
