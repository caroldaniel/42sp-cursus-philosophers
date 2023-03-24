/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:44:49 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/24 17:19:21 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	table = set_table(argc, argv);
	if (!table)
		return (1);
	if (!start_dinner(table))
		return (1);
	clean_table(&table);
	return (0);
}
