/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reap_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:35:23 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/26 19:18:23 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*reap(void *table_ptr)
{
	t_table	*table;
	int		pid;
	int		i;

	table = (t_table *)table_ptr;
	sem_wait(table->death);
	i = -1;
	while (++i < table->args.nb_philo)
	{
		sem_wait(table->pid_array_lock);
		pid = table->pid_array[i];
		sem_post(table->pid_array_lock);
		if (pid != -1)
			kill(pid, SIGKILL);
	}
	i = -1;
	while (++i < table->args.nb_philo)
		sem_post(table->done);
	return (NULL);
}
