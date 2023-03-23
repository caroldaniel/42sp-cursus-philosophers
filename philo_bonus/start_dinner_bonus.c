/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:19:37 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/23 19:06:50 by cado-car         ###   ########.fr       */
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

	i = -1;
	while (++i < table->args.nb_philo)
	{
		table->args.pid_array[i] = (int)fork();
		if (table->args.pid_array[i] == -1)
			return (FALSE);
		if (table->args.pid_array[i] == 0)
		{
			dine(table->philos[i]);
			clean_table(&table);
			exit(0);
		}
	}
	return (TRUE);
}

static t_bool	wait_all_philos(t_table *table)
{
	int		i;
	int		wstatus;
	t_bool	death;

	i = -1;
	death = FALSE;
	while (++i < table->args.nb_philo)
	{
		if (waitpid(table->args.pid_array[i], &wstatus, 0) == -1)
			return (FALSE);
		if (!WIFEXITED(wstatus))
			death = TRUE;
	}
	if (!death && table->args.nb_philo != 1)
		print_final_msg(table->philos[0], FINAL_FULL, ESC_BOLD_GREEN);
	else if (death && table->args.nb_philo != 1)
		print_final_msg(table->philos[0], FINAL_DEAD, ESC_BOLD_RED);
	sem_post(table->args.death);
	return (TRUE);
}
