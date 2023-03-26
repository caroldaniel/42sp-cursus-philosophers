/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dine_fts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:30:36 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/26 13:07:50 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	get_two_forks(t_philo *philo);
static t_bool	get_a_fork(t_philo *philo, int type);

void	ft_eat(t_philo *philo)
{		
	if (!get_two_forks(philo))
		return ;
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = gettimems();
	pthread_mutex_unlock(&philo->last_meal_lock);
	print_log(philo, "is eating", ESC_BOLD_GREEN);
	philo->meal_count++;
	usleep(philo->args.time_eat * 1000);
	pthread_mutex_unlock(philo->fork[RIGHT]);
	pthread_mutex_unlock(philo->fork[LEFT]);
	if (philo->meal_count == philo->args.nb_meals)
	{		
		print_log(philo, "has finished eating", ESC_BOLD_WHITE);
		pthread_mutex_lock(&philo->is_done_lock);
		philo->is_done = TRUE;
		pthread_mutex_unlock(&philo->is_done_lock);
	}
}

static t_bool	get_two_forks(t_philo *philo)
{
	int	first;
	int	second;

	if (philo->id % 2 == 0)
	{
		first = RIGHT;
		second = LEFT;
	}
	else
	{
		first = LEFT;
		second = RIGHT;
	}
	if (!get_a_fork(philo, first))
		return (FALSE);
	if (!get_a_fork(philo, second))
	{
		pthread_mutex_unlock(philo->fork[first]);
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	get_a_fork(t_philo *philo, int type)
{
	t_bool	is_over;

	pthread_mutex_lock(philo->fork[type]);
	pthread_mutex_lock(philo->is_over_lock);
	is_over = *philo->is_over;
	pthread_mutex_unlock(philo->is_over_lock);
	if (is_over)
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
	usleep(philo->args.time_sleep * 1000);
}

void	ft_think(t_philo *philo)
{
	print_log(philo, "is thinking", ESC_BOLD_PURPLE);
}
