/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:48:54 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/26 13:09:16 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	get_args(int argc, char **argv, t_table *table);
static t_bool	get_forks(t_table *table);
static t_bool	get_philos(t_table *table);

t_table	*set_table(int argc, char **argv)
{
	t_table	*table;

	if (!check_args(argc, argv))
		return (NULL);
	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	pthread_mutex_init(&table->print_zone, NULL);
	pthread_mutex_init(&table->is_over_lock, NULL);
	if (!get_args(argc, argv, table) || !get_forks(table) || !get_philos(table))
		return (clean_table(&table));
	table->is_over = FALSE;
	if (table->args.nb_philo == 1)
		table->is_over = TRUE;
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
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->args.nb_philo);
	if (!table->forks)
		return (FALSE);
	i = -1;
	while (++i < table->args.nb_philo)
		pthread_mutex_init(&table->forks[i], NULL);
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
