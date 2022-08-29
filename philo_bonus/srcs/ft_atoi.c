/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:27:50 by aamajane          #+#    #+#             */
/*   Updated: 2022/05/07 17:18:35 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_atoi(const char *str)
{
	unsigned int	res;
	int				sign;
	int				i;

	sign = 1;
	res = 0;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	if (str[i] == '0' && str[i + 1])
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i++] - '0';
		if ((res > INT_MAX && sign == 1) || (res - 1 > INT_MAX && sign == -1))
			return (0);
		if ((str[i] < '0' || str[i] > '9') && str[i])
			return (0);
	}
	return (sign * res);
}
