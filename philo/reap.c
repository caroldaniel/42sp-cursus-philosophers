/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 21:06:43 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/20 23:10:48 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	are_all_done(t_table *table);
static t_bool	is_any_dead(t_table *table);

void	*reap(void *table_ptr)
{
	t_table	*table;
	t_bool	is_over;

	table = (t_table *)table_ptr;
	pthread_mutex_lock(&table->is_over_lock);
	is_over = table->is_over;
	pthread_mutex_unlock(&table->is_over_lock);
	if (is_over)
		return (NULL);
	while (!are_all_done(table))
	{
		if (is_any_dead(table))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

static t_bool	are_all_done(t_table *table)
{
	int		i;
	t_bool	is_done;

	i = -1;
	if (table->args.nb_meals == -1)
		return (FALSE);
	while (++i < table->args.nb_philo)
	{
		pthread_mutex_lock(&table->philos[i]->is_done_lock);
		is_done = table->philos[i]->is_done;
		pthread_mutex_unlock(&table->philos[i]->is_done_lock);
		if (!is_done)
			return (FALSE);
	}
	pthread_mutex_lock(&table->is_over_lock);
	table->is_over = TRUE;
	pthread_mutex_unlock(&table->is_over_lock);
	print_final_full(&table->print_zone);
	return (TRUE);
}

static t_bool	is_any_dead(t_table *table)
{
	int		i;
	long	since_last_meal;
	t_bool	is_done;

	i = -1;
	while (++i < table->args.nb_philo)
	{
		pthread_mutex_lock(&table->philos[i]->last_meal_lock);
		pthread_mutex_lock(&table->philos[i]->is_done_lock);
		since_last_meal = gettimems() - table->philos[i]->last_meal;
		is_done = table->philos[i]->is_done;
		pthread_mutex_unlock(&table->philos[i]->last_meal_lock);
		pthread_mutex_unlock(&table->philos[i]->is_done_lock);
		if (!is_done && since_last_meal >= table->args.time_die)
		{
			pthread_mutex_lock(&table->is_over_lock);
			table->is_over = TRUE;
			pthread_mutex_unlock(&table->is_over_lock);
			print_final_death(table->philos[i]);
			return (TRUE);
		}
	}
	return (FALSE);
}
