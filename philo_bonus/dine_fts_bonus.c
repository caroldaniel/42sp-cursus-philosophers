/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dine_fts_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:34:22 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/23 18:13:27 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	get_forks(t_philo *philo);

void	ft_eat(t_philo *philo)
{		
	if (philo->meal_count == philo->args->nb_meals)
	{		
		print_log(philo, "has finished eating", ESC_BOLD_WHITE);
		philo->is_done = TRUE;
		return ;
	}
	get_forks(philo);
	print_log(philo, "is eating", ESC_BOLD_GREEN);
	philo->last_meal = gettimems();
	philo->meal_count++;
	usleep(philo->args->time_eat * 1000);
	sem_post(*(philo->forks));
	sem_post(*(philo->forks));
}

static void	get_forks(t_philo *philo)
{
	int forks;

	forks = 0;
	while (forks < 2)
	{
		sem_wait(*(philo->forks));
		print_log(philo, "has taken a fork", ESC_BOLD_YELLOW);
		forks ++;
	}
}

void	ft_sleep(t_philo *philo)
{
	print_log(philo, "is sleeping", ESC_BOLD_CYAN);
	usleep(philo->args->time_sleep * 1000);
}

void	ft_think(t_philo *philo)
{
	print_log(philo, "is thinking", ESC_BOLD_PURPLE);
}
