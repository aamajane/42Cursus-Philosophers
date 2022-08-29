/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:29:40 by aamajane          #+#    #+#             */
/*   Updated: 2022/05/08 17:04:22 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <stdio.h>

# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"

# define BHRED "\e[1;91m"
# define BHGRN "\e[1;92m"

# define E_NUMBER_ARG		1
# define E_MALLOC			2
# define E_NUMBER_PHILO		3
# define E_INVALID_ARG		4
# define E_SEM_OPEN			5
# define E_FORK				6
# define E_SEM_CLOSE		7
# define E_SEM_UNLINK		8
# define E_WAITPID			9
# define E_PTHREAD_CREATE	10
# define E_PTHREAD_JOIN		11

# define ALIVE	1
# define DIED 	0

typedef struct s_data
{
	int			n_philo;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			n_meals;
	int			philo_id;
	int			state;
	pid_t		*pid;
	sem_t		*forks;
	sem_t		*msg_lock;
	pthread_t	thread[2];
	long		start_time;
	long		current_time;
	long		last_meal_time;
	long		temp_time;
}				t_data;

// philosopher_1.c
void	check_arg(t_data *data, int ac, char **av);
void	start_simulation(t_data *data);
void	creat_forks(t_data *data);
void	end_simulation(t_data *data);

// philosopher_2.c
void	philosopher(t_data *data);
void	*routine(void *arg);
void	*routine_manager(void *arg);
void	print_msg(t_data *data, char *str, int time, char *color);
long	get_time(void);

// ft_atoi.c
int		ft_atoi(const char *str);

#endif
