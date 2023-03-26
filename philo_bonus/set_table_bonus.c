/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:48:54 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/26 19:43:43 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_bool	get_args(int argc, char **argv, t_table *table);
static t_bool	get_forks(t_table *table);
static t_bool	get_philos(t_table *table);
static t_bool	start_pid_array(t_table *table);

t_table	*set_table(int argc, char **argv)
{
	t_table	*table;

	if (!check_args(argc, argv))
		return (NULL);
	table = malloc(sizeof(t_table));
	if (!table || !create_semaphore(&table->print_zone, PRINT, 1) || \
		!create_semaphore(&table->death, DEATH, 1) || \
		!create_semaphore(&table->done, DONE, 1))
		return (NULL);
	sem_wait(table->death);
	sem_wait(table->done);
	if (!get_args(argc, argv, table) || !get_forks(table) || !get_philos(table))
		return (clean_table(&table));
	start_pid_array(table);
	create_semaphore(&table->pid_array_lock, PID_LOCK, 1);
	return (table);
}

static t_bool	get_args(int argc, char **argv, t_table *table)
{
	table->args.start_time = gettimems();
	table->args.nb_philo = ft_atoi(argv[1]);
	table->args.time_die = ft_atoi(argv[2]);
	table->args.time_eat = ft_atoi(argv[3]);
	table->args.time_sleep = ft_atoi(argv[4]);
	table->args.nb_meals = -1;
	if (argc == 6)
		table->args.nb_meals = ft_atoi(argv[5]);
	return (TRUE);
}

static t_bool	get_forks(t_table *table)
{
	if (!create_semaphore(&table->forks, FORKS, table->args.nb_philo))
		return (FALSE);
	return (TRUE);
}

static t_bool	get_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->args.nb_philo);
	if (!table->philos)
		return (FALSE);
	i = -1;
	while (++i < table->args.nb_philo)
		if (!create_philo(i, table))
			return (FALSE);
	return (TRUE);
}

static t_bool	start_pid_array(t_table *table)
{
	int	i;

	table->pid_array = malloc(sizeof(size_t) * table->args.nb_philo);
	if (!table->pid_array)
		return (FALSE);
	i = -1;
	while (++i < table->args.nb_philo)
		table->pid_array[i] = -1;
	return (TRUE);
}
