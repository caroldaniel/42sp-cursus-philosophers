/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_table_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:50:41 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/24 12:06:27 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	close_semaphore(sem_t *sem, char *name);
static void	destroy_philos(t_table *table);

void	*clean_table(t_table **table)
{
	if (*table)
	{
		if ((*table)->print_zone)
			close_semaphore((*table)->print_zone, PRINT);
		if ((*table)->args.death)
			close_semaphore((*table)->args.death, DEATH);
		free((*table)->args.pid_array);
		if ((*table)->forks)
			close_semaphore((*table)->forks, FORKS);
		destroy_philos(*table);
		free(*table);
	}
	return (NULL);
}

static void	close_semaphore(sem_t *sem, char *name)
{
	sem_close(sem);
	sem_unlink(name);
}

static void	destroy_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->args.nb_philo)
		free(table->philos[i]);
	free(table->philos);
}
