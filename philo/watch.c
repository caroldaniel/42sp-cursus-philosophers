/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watch.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 08:03:45 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/20 19:03:51 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	are_all_done(t_args *args, t_philo **philos);
static t_bool	is_any_dead(t_args *args, t_philo **philos);

void	*watch(void *table_ptr)
{
	t_table	*table;

	table = (t_table *)table_ptr;
	if (table->args.is_over)
		return (NULL);
	while (!are_all_done(&table->args, table->philos))
	{
		if (is_any_dead(&table->args, table->philos))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

static t_bool	are_all_done(t_args *args, t_philo **philos)
{
	int	i;

	i = -1;
	if (args->nb_meals == -1)
		return (FALSE);
	while (++i < args->nb_philo)
		if (!philos[i]->is_done)
			return (FALSE);
	args->is_over = TRUE;
	return (TRUE);
}

static t_bool	is_any_dead(t_args *args, t_philo **philos)
{
	int		i;
	long	since_last_meal;

	i = -1;
	while (++i < args->nb_philo)
	{
		since_last_meal = gettimems() - philos[i]->last_meal;
		if (!philos[i]->is_done && since_last_meal >= args->time_die)
		{
			philos[i]->args->is_over = TRUE;
			print_log(philos[i], "has died", ESC_BOLD_RED);
			return (TRUE);
		}
	}
	return (FALSE);
}
