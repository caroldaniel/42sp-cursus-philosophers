/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:50:41 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/20 20:30:21 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_forks(t_table *table);
static void	destroy_philos(t_table *table);

void	*clean_table(t_table **table)
{
	if (*table)
	{
		pthread_mutex_destroy(&(*table)->print_zone);
		if ((*table)->forks)
			destroy_forks(*table);
		if ((*table)->philos)
			destroy_philos(*table);
		free(*table);
	}
	return (NULL);
}

static void	destroy_forks(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->args.nb_philo)
		pthread_mutex_destroy(&table->forks[i]);
	free(table->forks);
}

static void	destroy_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->args.nb_philo)
		free(table->philos[i]);
	free(table->philos);
}
