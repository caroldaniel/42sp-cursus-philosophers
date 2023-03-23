/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:22:18 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/23 19:07:23 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	set_ptrs(t_philo *philo, t_table *table);
static void	set_fts(t_philo *philo);

t_bool	create_philo(int i, t_table *table)
{
	table->philos[i] = malloc(sizeof(t_philo));
	if (!table->philos[i])
		return (FALSE);
	table->philos[i]->id = i + 1;
	table->philos[i]->pid = 0;
	table->philos[i]->meal_count = 0;
	table->philos[i]->last_meal = gettimems();
	table->philos[i]->is_done = FALSE;
	set_ptrs(table->philos[i], table);
	set_fts(table->philos[i]);
	return (TRUE);
}

static void	set_ptrs(t_philo *philo, t_table *table)
{
	philo->args = &table->args;
	philo->forks = &table->forks;
	philo->print_zone = &table->print_zone;
}

static void	set_fts(t_philo *philo)
{
	philo->ft[0] = ft_eat;
	philo->ft[1] = ft_sleep;
	philo->ft[2] = ft_think;
}
