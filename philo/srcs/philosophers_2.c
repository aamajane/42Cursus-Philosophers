/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 22:35:59 by aamajane          #+#    #+#             */
/*   Updated: 2022/05/07 17:16:51 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*philosopher(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (data->n_meals && data->state == ALIVE)
	{
		pthread_mutex_lock(&data->fork);
		print_msg(data, "has taken the fisrt fork", 0, YEL);
		if (data->n_philo == 1)
			break ;
		pthread_mutex_lock(&(data + data->next)->fork);
		print_msg(data, "has taken the second fork", 0, YEL);
		data->temp_time = get_time();
		print_msg(data, "is eating", data->t_eat, GRN);
		pthread_mutex_unlock(&(data + data->next)->fork);
		pthread_mutex_unlock(&data->fork);
		print_msg(data, "is sleeping", data->t_sleep, MAG);
		print_msg(data, "is thinking", 0, BLU);
		data->n_meals--;
	}
	return (NULL);
}

void	philosophers_manager(t_data *data, int count)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while ((data + i)->n_meals)
	{
		(data + i)->last_meal_time = get_time() - (data + i)->temp_time;
		if ((data + i)->last_meal_time >= (data + i)->t_die)
		{
			while (++j < count)
				(data + j)->state = DIED;
			(data + i)->current_time = get_time();
			printf(CYN"%6ld ms: \e[0;31m[%d] deid\n", \
			(data + i)->current_time - (data + i)->start_time, \
			(data + i)->philo_id);
			return ;
		}
		i++;
		if (i == count)
			i = 0;
	}
}

void	print_msg(t_data *data, char *str, int time, char *color)
{
	if (data->state == ALIVE)
	{
		data->current_time = get_time();
		printf(CYN"%6ld ms: %s[%d] %s\n", \
		data->current_time - data->start_time, color, data->philo_id, str);
		if (time)
		{
			data->current_time = get_time();
			while (data->state == ALIVE && \
					get_time() - data->current_time < time)
				usleep(100);
		}
	}
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
