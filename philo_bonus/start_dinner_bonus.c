/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:19:37 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/26 19:16:01 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_bool	start_philos(t_table *table);
static t_bool	wait_all_philos(t_table *table);

t_bool	start_dinner(t_table *table)
{
	if (pthread_create(&table->reaper_id, NULL, &reap, table))
		return (FALSE);
	if (!start_philos(table))
		return (FALSE);
	if (!wait_all_philos(table))
		return (FALSE);
	if (pthread_join(table->reaper_id, NULL))
		return (FALSE);
	return (TRUE);
}

static t_bool	start_philos(t_table *table)
{
	int	i;
	int	pid;

	i = -1;
	while (++i < table->args.nb_philo)
	{
		pid = (int)fork();
		if (pid == -1)
			return (FALSE);
		if (pid == 0)
		{
			dine(table->philos[i]);
			clean_table(&table);
			return (0);
		}
		sem_wait(table->pid_array_lock);
		table->pid_array[i] = pid;
		sem_post(table->pid_array_lock);
	}
	return (TRUE);
}

static t_bool	wait_all_philos(t_table *table)
{
	int		i;
	int		wstatus;
	t_bool	death;

	i = -1;
	while (++i < table->args.nb_philo)
		sem_wait(table->done);
	death = FALSE;
	i = -1;
	while (++i < table->args.nb_philo)
	{
		sem_wait(table->pid_array_lock);
		table->philos[i]->pid = table->pid_array[i];
		table->pid_array[i] = -1;
		sem_post(table->pid_array_lock);
		if (waitpid(table->philos[i]->pid, &wstatus, 0) == -1)
			return (FALSE);
		if (!WIFEXITED(wstatus))
			death = TRUE;
	}
	if (!death && table->args.nb_philo != 1)
		print_final_full(table->philos[0]);
	sem_post(table->death);
	return (TRUE);
}
