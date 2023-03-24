/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:45:38 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/24 17:25:01 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

# define ESC_BOLD_RED "\001\033[1;31m\002"
# define ESC_BOLD_GREEN "\001\033[1;32m\002"
# define ESC_BOLD_YELLOW "\001\033[1;33m\002"
# define ESC_BOLD_BLUE "\001\033[1;34m\002"
# define ESC_BOLD_PURPLE "\001\033[1;35m\002"
# define ESC_BOLD_CYAN "\001\033[1;36m\002"
# define ESC_BOLD_WHITE "\001\033[1;37m\002"
# define ESC_WHITE "\001\033[0;37m\002"

// Error Messages Macros
# define ERR_ARGNUM "Philo Error: invalid number of arguments"
# define ERR_ARGTYP	"Philo Error: arguments must be numeric"
# define ERR_NOPHIL	"Philo Error: number of philosophers must be one or greater"
# define ERR_NOMEAL	"Philo Error: number of meals must be one or greater"
# define ERR_NOTIME	"Philo Error: all timestamps must be positive and non-nulls"

// Final Messages
# define FINAL_DEAD	"What is the meaning of life?"
# define FINAL_FULL	"They all ate so much they can't barely think now..."

// SEMAPHORE NAMES
# define PRINT	"/print"
# define FORKS	"/forks"
# define DEATH	"/death"

// Boolean Type Definition
typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

// Struct to populate with arguments passed by user 
typedef struct s_args
{
	long			start_time;	
	int				nb_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				nb_meals;
	sem_t			*death;
	int				*pid_array;
}	t_args;

// Structure to represent a single philosopher
typedef struct s_philo
{
	int				id;
	int				pid;
	int				meal_count;
	long			last_meal;
	t_bool			is_done;
	t_args			*args;
	sem_t			**forks;
	sem_t			**print_zone;
	void			(*ft[3])(struct s_philo *);

}	t_philo;

// Struct to store all data to table settings
typedef struct s_table
{
	sem_t			*print_zone;
	t_args			args;
	sem_t			*forks;
	t_philo			**philos;
	pthread_t		reaper_id;
}	t_table;

// Program functions
t_bool	check_args(int argc, char **argv);
t_table	*set_table(int argc, char **argv);
t_bool	create_philo(int i, t_table *table);
t_bool	start_dinner(t_table *table);
void	*clean_table(t_table **table);
void	*dine(t_philo *philo);
void	*reap(void *table_ptr);
void	print_log(t_philo *philo, char *log_msg, char *color);
void	print_log_death(t_philo *philo);
void	print_final_msg(t_philo *philo, char *log_msg, char *color);

// Function pointer array
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);

// Utilities
t_bool	create_semaphore(sem_t **sem, char *name, int value);
t_bool	ft_isnumeric(char *s);
int		ft_atoi(const char *str);
long	gettimems(void);
#endif
