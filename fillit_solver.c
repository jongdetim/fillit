/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fillit_solver.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkamphor <kkamphor@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/19 13:35:49 by tide-jon       #+#    #+#                */
/*   Updated: 2019/04/22 16:59:26 by kkamphor      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

static void	print_solution(char **sqr, int square_size)
{
	int	i;

	i = 0;
	while (i < square_size)
	{
		ft_putendl(*sqr);
		sqr++;
		i++;
	}
}

static int	tetri_filler(char **sqr, t_tetrimino **arr, int y_sqr, int x_sqr)
{
	int	part;

	part = 0;
	while (part < 4)
	{
		sqr[y_sqr + (**arr).y_coord[part]][x_sqr + (**arr).x_coord[part]] =
																(**arr).sign;
		part++;
	}
	if (solver(sqr, arr + 1, ft_strlen(sqr[0])) == 1)
		return (1);
	else
	{
		while (part > 0)
		{
			sqr[y_sqr + (**arr).y_coord[part - 1]][x_sqr +
						(**arr).x_coord[part - 1]] = '.';
			part--;
		}
		return (0);
	}	
}

static int	tetri_fit_check(char **sqr, t_tetrimino **arr, int y_sqr, int x_sqr)
{
	int	part;

	part = 0;
	while (part < 4)
	{
		if (sqr[y_sqr + (**arr).y_coord[part]][x_sqr +
						(**arr).x_coord[part]] == '.')
			part++;
		else
			break ;
	}
	if (part == 4)
	{
		if (tetri_filler(sqr, arr, y_sqr, x_sqr) == 1)
			return (1);
	}
	return (0);
}

/*
** dit is de solver die met recursive backtracking de puzzel bruteforced
** en de functie aanroept die het antwoord uitprint.
*/

int			solver(char **sqr, t_tetrimino **arr, int square_size)
{
	int x_sqr;
	int y_sqr;

	while (*arr != NULL)
	{
		y_sqr = 0;
		while (y_sqr < square_size)
		{
			x_sqr = 0;
			while (x_sqr < square_size)
			{
				if (tetri_fit_check(sqr, arr, y_sqr, x_sqr) == 1)
					return (1);
				x_sqr++;
			}
			y_sqr++;
		}
		return (0);
	}
	print_solution(sqr, square_size);
	return (1);
}
