/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dine_fts_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:34:22 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/26 19:40:17 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void		get_forks(t_philo *philo);
static t_bool	check_life(t_philo	*philo);

void	ft_eat(t_philo *philo)
{		
	get_forks(philo);
	philo->last_meal = gettimems();
	print_log(philo, "is eating", ESC_BOLD_GREEN);
	philo->meal_count++;
	while ((gettimems() - philo->last_meal) < philo->args.time_eat)
		if (!check_life(philo))
			return ;
	sem_post(*(philo->forks));
	sem_post(*(philo->forks));
}

static void	get_forks(t_philo *philo)
{
	int	forks;

	forks = 0;
	while (forks < 2)
	{
		sem_wait(*(philo->forks));
		if (!check_life(philo))
			return ;
		print_log(philo, "has taken a fork", ESC_BOLD_YELLOW);
		forks++;
	}
}

void	ft_sleep(t_philo *philo)
{
	long	start_time;

	start_time = gettimems();
	print_log(philo, "is sleeping", ESC_BOLD_CYAN);
	while ((gettimems() - start_time) < philo->args.time_sleep)
		if (!check_life(philo))
			return ;
}

void	ft_think(t_philo *philo)
{
	print_log(philo, "is thinking", ESC_BOLD_PURPLE);
	while (*(int *)(*(philo->forks)) < 2)
		if (!check_life(philo))
			return ;
}

static t_bool	check_life(t_philo	*philo)
{
	long	since_last_meal;

	since_last_meal = gettimems() - philo->last_meal;
	if (since_last_meal >= philo->args.time_die)
	{
		sem_post(*(philo->death));
		print_final_death(philo);
		return (FALSE);
	}
	usleep(500);
	return (TRUE);
}
