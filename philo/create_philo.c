/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 20:11:48 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/20 22:42:30 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	set_ptrs(i, table->philos[i], table);
	set_fts(table->philos[i]);
	table->philos[i]->last_meal = gettimems();
	print_log(table->philos[i], "has started the simulation", ESC_BOLD_WHITE);
	return (TRUE);
}

static void	set_ptrs(int i, t_philo *philo, t_table *table)
{
	philo->args = &table->args;
	philo->fork[LEFT] = &table->forks[i];
	philo->fork[RIGHT] = &table->forks[(i + 1) % table->args.nb_philo];
	philo->print_zone = &table->print_zone;
}

static void	set_fts(t_philo *philo)
{
	philo->ft[0] = ft_eat;
	philo->ft[1] = ft_sleep;
	philo->ft[2] = ft_think;
}
