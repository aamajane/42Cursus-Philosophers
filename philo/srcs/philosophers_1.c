/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:30:15 by aamajane          #+#    #+#             */
/*   Updated: 2022/05/07 17:16:44 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int ac, char **av)
{
	t_data	*data;
	int		count;

	if (ac < 5 || ac > 6)
	{
		printf("Error: Invalid number of arguments\n");
		return (E_NUMBER_ARG);
	}
	count = ft_atoi(av[1]);
	if (count <= 0)
	{
		printf("Error: Number of philosophers should be greater than 0\n");
		return (E_NUMBER_PHILO);
	}
	data = (t_data *)malloc(sizeof(t_data) * count);
	if (!data)
		return (E_MALLOC);
	if (!check_arg(data, count, ac, av))
		return (E_INVALID_ARG);
	return (start_simulation(data, count));
}

int	check_arg(t_data *data, int count, int ac, char **av)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		(data + i)->n_philo = count;
		(data + i)->t_die = ft_atoi(av[2]);
		(data + i)->t_eat = ft_atoi(av[3]);
		(data + i)->t_sleep = ft_atoi(av[4]);
		if (ac == 5)
			(data + i)->n_meals = -1;
		if (ac == 6)
			(data + i)->n_meals = ft_atoi(av[5]);
		if ((data + i)->t_die <= 0 || (data + i)->t_eat <= 0 || \
			(data + i)->t_sleep <= 0 || (ac == 6 && (data + i)->n_meals <= 0))
		{
			printf("Error: Invalid arguments\n");
			return (0);
		}
	}
	return (1);
}

int	start_simulation(t_data *data, int count)
{
	long	start;
	int		i;

	printf(BHGRN"********** Simulation started **********\n");
	i = -1;
	while (++i < count)
		if (pthread_mutex_init(&(data + i)->fork, NULL))
			return (E_MUTEX_INIT);
	i = -1;
	start = get_time();
	while (++i < count)
	{
		(data + i)->philo_id = i + 1;
		(data + i)->next = 1;
		if ((data + i)->philo_id == count)
			(data + i)->next = -count + 1;
		(data + i)->state = ALIVE;
		(data + i)->start_time = start;
		(data + i)->temp_time = start;
		if (pthread_create(&(data + i)->philo, NULL, &philosopher, data + i))
			return (E_PTHREAD_CREATE);
		usleep(50);
	}
	philosophers_manager(data, count);
	return (end_simulation(data, count));
}

int	end_simulation(t_data *data, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		if (pthread_join((data + i)->philo, NULL))
			return (E_PTHREAD_JOIN);
	i = -1;
	while (++i < count)
		if (pthread_mutex_destroy(&(data + i)->fork))
			return (E_MUTEX_DESTROY);
	free(data);
	printf(BHRED"********** Simulation ended **********\n");
	return (0);
}
