/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:22:18 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/26 19:23:52 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	set_args(t_philo *philo, t_table *table);
static void	set_ptrs(t_philo *philo, t_table *table);
static void	set_fts(t_philo *philo);

t_bool	create_philo(int i, t_table *table)
{
	table->philos[i] = malloc(sizeof(t_philo));
	if (!table->philos[i])
		return (FALSE);
	table->philos[i]->id = i + 1;
	table->philos[i]->pid = -1;
	table->philos[i]->meal_count = 0;
	set_args(table->philos[i], table);
	set_ptrs(table->philos[i], table);
	set_fts(table->philos[i]);
	table->philos[i]->last_meal = gettimems();
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

static void	set_ptrs(t_philo *philo, t_table *table)
{
	philo->print_zone = &table->print_zone;
	philo->forks = &table->forks;
	philo->death = &table->death;
	philo->done = &table->done;
}

static void	set_fts(t_philo *philo)
{
	philo->ft[0] = ft_eat;
	philo->ft[1] = ft_sleep;
	philo->ft[2] = ft_think;
}
