/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:18:41 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/23 09:49:22 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
