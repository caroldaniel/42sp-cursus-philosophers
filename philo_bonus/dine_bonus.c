/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dine_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:32:23 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/23 19:39:30 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*dine_alone(t_philo *philo);
static void	*check_life(void *philo_ptr);

void	*dine(t_philo *philo)
{
	pthread_t	watch_id;
	int 		i;
	
	if (philo->args->nb_philo == 1)
		return (dine_alone(philo));
	pthread_create(&watch_id, NULL, check_life, philo);
	i = 0;
	while (!philo->is_done)
		philo->ft[i++ % 3](philo);
	pthread_join(watch_id, NULL);
	return (NULL);
}

static void	*dine_alone(t_philo *philo)
{
	sem_wait(*(philo->forks));
	print_log(philo, "has taken a fork", ESC_BOLD_YELLOW);
	print_log(philo, "can't eat alone", ESC_BOLD_RED);
	return (NULL);
}

static void	*check_life(void *philo_ptr)
{
	t_philo	*philo;
	long	since_last_meal;

	philo = (t_philo *)philo_ptr;
	since_last_meal = gettimems() - philo->last_meal;
	while (!philo->is_done && since_last_meal < philo->args->time_die)
	{
		since_last_meal = gettimems() - philo->last_meal;
		usleep(1000);
	}
	if (!philo->is_done)
	{
		sem_post(philo->args->death);
		print_log_death(philo);
	}
	return (NULL);	
}
