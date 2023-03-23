/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_semaphore_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:26:50 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/23 12:24:40 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_bool	create_semaphore(sem_t **sem, char *name, int value)
{
	sem_unlink(name);
	*sem = sem_open(name, O_CREAT, S_IRWXU, value);
	if (*sem == SEM_FAILED)
		return (FALSE);
	return (TRUE);
}
