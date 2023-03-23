/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reap_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:35:23 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/23 19:36:18 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*reap(void *table_ptr)
{
	t_table	*table;
	int		i;

	table = (t_table *)table_ptr;
	sem_wait(table->args.death);
	i = -1;
	while (++i < table->args.nb_philo)
		if (table->args.pid_array[i] != -1)
			kill(table->args.pid_array[i], SIGKILL);
	return (NULL);
}
