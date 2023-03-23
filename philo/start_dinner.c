/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:44:56 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/23 19:11:46 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	start_philos(t_table *table);
static t_bool	join_all_threads(t_table *table);

t_bool	start_dinner(t_table *table)
{
	if (!start_philos(table))
		return (FALSE);
	if (pthread_create(&table->reaper_id, NULL, reap, table))
		return (FALSE);
	if (!join_all_threads(table))
		return (FALSE);
	return (TRUE);
}

static t_bool	start_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->args.nb_philo)
		if (pthread_create(&table->philos[i]->thread_id, NULL, dine, \
			table->philos[i]))
			return (FALSE);
	return (TRUE);
}

static t_bool	join_all_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->args.nb_philo)
		if (pthread_join(table->philos[i]->thread_id, NULL))
			return (FALSE);
	if (pthread_join(table->reaper_id, NULL))
		return (FALSE);
	return (TRUE);
}
