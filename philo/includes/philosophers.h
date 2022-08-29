/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:29:40 by aamajane          #+#    #+#             */
/*   Updated: 2022/05/08 17:04:07 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <pthread.h>
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
# define E_NUMBER_PHILO		2
# define E_MALLOC			3
# define E_INVALID_ARG		4
# define E_MUTEX_INIT		5
# define E_PTHREAD_CREATE	6
# define E_PTHREAD_JOIN		7
# define E_MUTEX_DESTROY	8

# define ALIVE	1
# define DIED	0

typedef struct s_data
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_meals;
	int				philo_id;
	int				next;
	int				state;
	pthread_t		philo;
	pthread_mutex_t	fork;
	long			start_time;
	long			current_time;
	long			last_meal_time;
	long			temp_time;
}				t_data;

// philosopher_1.c
int		check_arg(t_data *data, int count, int ac, char **av);
int		start_simulation(t_data *data, int count);
int		end_simulation(t_data *data, int count);

// philosopher_2.c
void	*philosopher(void *arg);
void	philosophers_manager(t_data *data, int count);
void	print_msg(t_data *data, char *str, int time, char *color);
long	get_time(void);

// ft_atoi.c
int		ft_atoi(const char *str);

#endif
