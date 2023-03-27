/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:17:05 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/26 21:08:57 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_log(t_philo *philo, char *log_msg, char *color)
{
	long	timestmp;

	sem_wait(*(philo->print_zone));
	timestmp = gettimems() - philo->args.start_time;
	printf("%s%8ld %2d %s%s\n", color, timestmp, philo->id, log_msg, ESC_WHITE);
	sem_post(*(philo->print_zone));
}

void	print_final_death(t_philo *philo)
{
	long	timestmp;

	sem_wait(*(philo->print_zone));
	timestmp = gettimems() - philo->args.start_time;
	printf("%s%8ld %2d has died%s\n", ESC_BOLD_RED, timestmp, philo->id, \
		ESC_WHITE);
	printf("\n%s%s%s\n\n", ESC_BOLD_RED, FINAL_DEAD, ESC_WHITE);
}

void	print_final_full(t_philo *philo)
{
	sem_wait(*(philo->print_zone));
	printf("\n%s%s%s\n\n", ESC_BOLD_GREEN, FINAL_FULL, ESC_WHITE);
	sem_post(*(philo->print_zone));
}
