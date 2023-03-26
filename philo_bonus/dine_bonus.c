/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dine_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:32:23 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/26 19:28:05 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void		*dine_alone(t_philo *philo);
static t_bool	is_meal_over(t_philo *philo);

void	*dine(t_philo *philo)
{
	int			i;

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
	sem_wait(*(philo->forks));
	print_log(philo, "has taken a fork", ESC_BOLD_YELLOW);
	print_log(philo, "can't eat alone", ESC_BOLD_RED);
	sem_post(*(philo->forks));
	sem_post(*(philo->death));
	return (NULL);
}

static t_bool	is_meal_over(t_philo *philo)
{
	if (philo->meal_count == philo->args.nb_meals)
	{		
		print_log(philo, "has finished eating", ESC_BOLD_WHITE);
		sem_post(*(philo->done));
		return (TRUE);
	}
	return (FALSE);
}
