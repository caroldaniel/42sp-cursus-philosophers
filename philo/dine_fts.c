/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dine_fts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:30:36 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/24 12:46:40 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	get_a_fork(t_philo *philo, int type);

void	ft_eat(t_philo *philo)
{		
	if (!get_a_fork(philo, RIGHT))
		return ;
	if (!get_a_fork(philo, LEFT))
	{
		pthread_mutex_unlock(philo->fork[RIGHT]);
		return ;
	}
	print_log(philo, "is eating", ESC_BOLD_GREEN);
	philo->last_meal = gettimems();
	philo->meal_count++;
	usleep(philo->args->time_eat * 1000);
	pthread_mutex_unlock(philo->fork[RIGHT]);
	pthread_mutex_unlock(philo->fork[LEFT]);
	if (philo->meal_count == philo->args->nb_meals)
	{		
		print_log(philo, "has finished eating", ESC_BOLD_WHITE);
		philo->is_done = TRUE;
	}
}

static t_bool	get_a_fork(t_philo *philo, int type)
{
	pthread_mutex_lock(philo->fork[type]);
	if (philo->args->is_over)
	{
		pthread_mutex_unlock(philo->fork[type]);
		return (FALSE);
	}
	print_log(philo, "has taken a fork", ESC_BOLD_YELLOW);
	return (TRUE);
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
