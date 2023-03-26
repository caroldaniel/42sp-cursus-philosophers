/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:17:05 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/26 12:45:37 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(t_philo *philo, char *log_msg, char *color)
{
	long	timestmp;

	pthread_mutex_lock(philo->print_zone);
	timestmp = gettimems() - philo->args.start_time;
	printf("%s%8ld %2d %s%s\n", color, timestmp, philo->id, log_msg, ESC_WHITE);
	pthread_mutex_unlock(philo->print_zone);
}

void	print_final_death(t_philo *philo)
{
	long	timestmp;

	pthread_mutex_lock(philo->print_zone);
	timestmp = gettimems() - philo->args.start_time;
	printf("%s%8ld %2d has died\n", ESC_BOLD_RED, timestmp, philo->id);
	printf("\n%s%s%s\n\n", ESC_BOLD_RED, FINAL_DEAD, ESC_WHITE);
	pthread_mutex_unlock(philo->print_zone);
}

void	print_final_full(pthread_mutex_t *print_zone)
{
	pthread_mutex_lock(print_zone);
	printf("\n%s%s%s\n\n", ESC_BOLD_GREEN, FINAL_FULL, ESC_WHITE);
	pthread_mutex_unlock(print_zone);
}
