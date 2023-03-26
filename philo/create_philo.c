/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 20:11:48 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/26 12:55:03 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_args(t_philo *philo, t_table *table);
static void	set_ptrs(int i, t_philo *philo, t_table *table);
static void	set_fts(t_philo *philo);

t_bool	create_philo(int i, t_table *table)
{
	table->philos[i] = malloc(sizeof(t_philo));
	if (!table->philos[i])
		return (FALSE);
	table->philos[i]->id = i + 1;
	table->philos[i]->thread_id = 0;
	table->philos[i]->meal_count = 0;
	table->philos[i]->is_done = FALSE;
	pthread_mutex_init(&table->philos[i]->is_done_lock, NULL);
	set_args(table->philos[i], table);
	set_ptrs(i, table->philos[i], table);
	set_fts(table->philos[i]);
	table->philos[i]->last_meal = gettimems();
	pthread_mutex_init(&table->philos[i]->last_meal_lock, NULL);
	print_log(table->philos[i], "has started the simulation", ESC_BOLD_WHITE);
	return (TRUE);
}

static void	set_args(t_philo *philo, t_table *table)
{
	philo->args.start_time = table->args.start_time;
	philo->args.nb_philo = table->args.nb_philo;
	philo->args.time_die = table->args.time_die;
	philo->args.time_eat = table->args.time_eat;
	philo->args.time_sleep = table->args.time_sleep;
	philo->args.nb_meals = table->args.nb_meals;
}

static void	set_ptrs(int i, t_philo *philo, t_table *table)
{
	philo->print_zone = &table->print_zone;
	philo->fork[LEFT] = &table->forks[i];
	philo->fork[RIGHT] = &table->forks[(i + 1) % table->args.nb_philo];
	philo->is_over = &table->is_over;
	philo->is_over_lock = &table->is_over_lock;
}

static void	set_fts(t_philo *philo)
{
	philo->ft[0] = ft_eat;
	philo->ft[1] = ft_sleep;
	philo->ft[2] = ft_think;
}
