/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:19:00 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/20 23:11:06 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# include "colors.h"

// Error Messages Macros
# define ERR_ARGNUM "Philo Error: invalid number of arguments"
# define ERR_ARGTYP	"Philo Error: arguments must be numeric"
# define ERR_NOPHIL	"Philo Error: number of philosophers must be one or greater"
# define ERR_NOMEAL	"Philo Error: number of meals must be one or greater"
# define ERR_NOTIME	"Philo Error: all timestamps must be positive and non-nulls"

// Final Messages
# define FINAL_DEAD	"What is the meaning of life?"
# define FINAL_FULL	"They all ate so much they can't barely think now..."

// Boolean Type Definition
typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

// Fork Enumerator
enum e_fork{
	RIGHT,
	LEFT
};

// Struct to populate with arguments passed by user 
typedef struct s_args
{
	long			start_time;	
	int				nb_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				nb_meals;
	t_bool			is_over;
}	t_args;

// Structure to represent a single philosopher
typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	int				meal_count;
	long			last_meal;
	t_bool			is_done;
	t_args			*args;
	pthread_mutex_t	*fork[2];
	pthread_mutex_t	*print_zone;
	void			(*ft[3])(struct s_philo *);
}	t_philo;

// Struct to store all data to table settings
typedef struct s_table
{
	pthread_mutex_t	print_zone;
	t_args			args;
	pthread_mutex_t	*forks;
	t_philo			**philos;
	pthread_t		watcher_id;
}	t_table;

// Program functions
t_bool	check_args(int argc, char **argv);
t_table	*set_table(int argc, char **argv);
void	*clean_table(t_table **table);
t_bool	create_philo(int i, t_table *table);
void	*dine(void	*philo_ptr);
void	*watch(void *table_ptr);
void	print_log(t_philo *philo, char *log_msg, char *color);
void	print_final_msg(t_philo *philo, char *log_msg, char *color);

// Function pointer array
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);

// Utilities
t_bool	ft_isnumeric(char *s);
int		ft_atoi(const char *str);
long	gettimems(void);

#endif