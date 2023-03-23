/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:17:05 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/23 18:12:54 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_log(t_philo *philo, char *log_msg, char *color)
{
	long	timestmp;

	sem_wait(*(philo->print_zone));
	timestmp = gettimems() - philo->args->start_time;
	printf("%s%-5ld %2d %s\n", color, timestmp, philo->id, log_msg);
	sem_post(*(philo->print_zone));
}

void	print_final_msg(t_philo *philo, char *log_msg, char *color)
{
	sem_wait(*(philo->print_zone));
	printf("\n%s%s%s\n\n", color, log_msg, ESC_WHITE);
	sem_post(*(philo->print_zone));
}
