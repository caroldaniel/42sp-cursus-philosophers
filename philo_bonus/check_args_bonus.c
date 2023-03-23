/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:54:30 by cado-car          #+#    #+#             */
/*   Updated: 2023/03/21 21:54:45 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_bool	check_numeric(char **argv);
static t_bool	check_philo_nb(char **argv);
static t_bool	check_meals_nb(int argc, char **argv);
static t_bool	check_time(char **argv);

t_bool	check_args(int argc, char **argv)
{
	t_bool	ret;

	ret = FALSE;
	if (argc != 5 && argc != 6)
		printf("%s\n", ERR_ARGNUM);
	else if (!check_numeric(argv))
		printf("%s\n", ERR_ARGTYP);
	else if (!check_philo_nb(argv))
		printf("%s\n", ERR_NOPHIL);
	else if (!check_meals_nb(argc, argv))
		printf("%s\n", ERR_NOMEAL);
	else if (!check_time(argv))
		printf("%s\n", ERR_NOTIME);
	else
		ret = TRUE;
	return (ret);
}

static t_bool	check_numeric(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
		if (!ft_isnumeric(argv[i]))
			return (FALSE);
	return (TRUE);
}

static t_bool	check_philo_nb(char **argv)
{
	int	nb_philo;

	nb_philo = ft_atoi(argv[1]);
	if (!nb_philo)
		return (FALSE);
	return (TRUE);
}

static t_bool	check_meals_nb(int argc, char **argv)
{
	int	nb_meals;

	nb_meals = -1;
	if (argc == 6)
		nb_meals = ft_atoi(argv[5]);
	if (!nb_meals)
		return (FALSE);
	return (TRUE);
}

static t_bool	check_time(char **argv)
{
	int	timestmp;
	int	i;

	i = 1;
	while (++i < 5)
	{
		timestmp = ft_atoi(argv[i]);
		if (timestmp == 0)
			return (FALSE);
	}
	return (TRUE);
}
