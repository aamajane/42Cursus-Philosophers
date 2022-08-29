/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 22:35:59 by aamajane          #+#    #+#             */
/*   Updated: 2022/05/07 17:18:48 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	philosopher(t_data *data)
{
	if (pthread_create(&data->thread[0], NULL, &routine, data))
		exit(E_PTHREAD_CREATE);
	if (pthread_create(&data->thread[1], NULL, &routine_manager, data))
		exit(E_PTHREAD_CREATE);
	if (pthread_join(data->thread[0], NULL))
		exit(E_PTHREAD_JOIN);
	if (pthread_join(data->thread[1], NULL))
		exit(E_PTHREAD_JOIN);
	exit(data->state);
}

void	*routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = data->philo_id - 1;
	while (data->n_meals && data->state == ALIVE)
	{
		sem_wait(data->forks);
		print_msg(data, "has taken the fisrt fork", 0, YEL);
		if (data->n_philo == 1)
			break ;
		sem_wait(data->forks);
		print_msg(data, "has taken the second fork", 0, YEL);
		data->temp_time = get_time();
		print_msg(data, "is eating", data->t_eat, GRN);
		sem_post(data->forks);
		sem_post(data->forks);
		print_msg(data, "is sleeping", data->t_sleep, MAG);
		print_msg(data, "is thinking", 0, BLU);
		data->n_meals--;
	}
	return (NULL);
}

void	*routine_manager(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (data->n_meals)
	{
		data->last_meal_time = get_time() - data->temp_time;
		if (data->last_meal_time >= data->t_die)
		{
			data->state = DIED;
			sem_wait(data->msg_lock);
			data->current_time = get_time();
			printf(CYN"%6ld ms: \e[0;31m[%d] died\n", \
			data->current_time - data->start_time, data->philo_id);
			return (NULL);
		}
	}
	return (NULL);
}

void	print_msg(t_data *data, char *str, int time, char *color)
{
	if (data->state == ALIVE)
	{
		data->current_time = get_time();
		sem_wait(data->msg_lock);
		printf(CYN"%6ld ms: %s[%d] %s\n", \
		data->current_time - data->start_time, color, data->philo_id, str);
		sem_post(data->msg_lock);
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
