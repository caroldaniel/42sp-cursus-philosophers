/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dine.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 09:19:09 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/26 13:13:44 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		*dine_alone(t_philo *philo);
static t_bool	is_meal_over(t_philo *philo);

void	*dine(void	*philo_ptr)
{
	t_philo			*philo;
	unsigned long	i;

	philo = (t_philo *)philo_ptr;
	if (philo->id % 2 == 0)
		usleep(1000);
	if (philo->args.nb_philo == 1)
		return (dine_alone(philo));
	i = 0;
	while (!is_meal_over(philo))
		philo->ft[i++ % 3](philo);
	return (NULL);
}

static void	*dine_alone(t_philo *philo)
{
	pthread_mutex_lock(philo->fork[RIGHT]);
	print_log(philo, "has taken a fork", ESC_BOLD_YELLOW);
	print_log(philo, "can't eat alone", ESC_BOLD_RED);
	pthread_mutex_unlock(philo->fork[RIGHT]);
	return (NULL);
}

static t_bool	is_meal_over(t_philo *philo)
{
	t_bool	is_over;
	t_bool	is_done;

	pthread_mutex_lock(philo->is_over_lock);
	is_over = *philo->is_over;
	pthread_mutex_unlock(philo->is_over_lock);
	if (is_over)
		return (TRUE);
	pthread_mutex_lock(&philo->is_done_lock);
	is_done = philo->is_done;
	pthread_mutex_unlock(&philo->is_done_lock);
	if (is_done)
		return (TRUE);
	return (FALSE);
}
