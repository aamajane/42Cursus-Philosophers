/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:30:15 by aamajane          #+#    #+#             */
/*   Updated: 2022/05/07 17:18:41 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 5 || ac > 6)
	{
		printf("Error: Invalid number of arguments\n");
		return (E_NUMBER_ARG);
	}
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (E_MALLOC);
	check_arg(data, ac, av);
	start_simulation(data);
	end_simulation(data);
	free(data->pid);
	free(data);
	return (0);
}

void	check_arg(t_data *data, int ac, char **av)
{
	data->n_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (ac == 5)
		data->n_meals = -1;
	if (ac == 6)
		data->n_meals = ft_atoi(av[5]);
	if (data->n_philo <= 0 || data->t_die <= 0 || data->t_eat <= 0 || \
		data->t_sleep <= 0 || (ac == 6 && data->n_meals <= 0))
	{
		printf("Error: Invalid arguments\n");
		exit(E_INVALID_ARG);
	}
}

void	start_simulation(t_data *data)
{
	int	i;

	printf(BHGRN"********** Simulation started **********\n");
	creat_forks(data);
	data->pid = (pid_t *)malloc(sizeof(pid_t) * data->n_philo);
	if (!data->pid)
		exit(E_MALLOC);
	i = -1;
	data->state = ALIVE;
	data->start_time = get_time();
	data->temp_time = data->start_time;
	while (++i < data->n_philo)
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			exit(E_FORK);
		data->philo_id = i + 1;
		if (data->pid[i] == 0)
			philosopher(data);
	}
}

void	creat_forks(t_data *data)
{
	sem_unlink("/forks");
	data->forks = sem_open("/forks", O_CREAT, 0644, data->n_philo);
	if (data->forks == SEM_FAILED)
		exit(E_SEM_OPEN);
	sem_unlink("/msg_lock");
	data->msg_lock = sem_open("/msg_lock", O_CREAT, 0644, 1);
	if (data->msg_lock == SEM_FAILED)
		exit(E_SEM_OPEN);
}

void	end_simulation(t_data *data)
{
	int	i;
	int	status;

	i = -1;
	while (++i < data->n_philo)
	{
		if (waitpid(-1, &status, 0) == -1)
			exit(E_WAITPID);
		if (status == DIED)
		{
			i = -1;
			while (++i < data->n_philo)
				kill(data->pid[i], SIGKILL);
		}
	}
	if (sem_close(data->forks) == -1)
		exit(E_SEM_CLOSE);
	if (sem_close(data->msg_lock) == -1)
		exit(E_SEM_CLOSE);
	if (sem_unlink("/forks") == -1)
		exit(E_SEM_UNLINK);
	if (sem_unlink("/msg_lock") == -1)
		exit(E_SEM_UNLINK);
	printf(BHRED"********** Simulation ended **********\n");
}
