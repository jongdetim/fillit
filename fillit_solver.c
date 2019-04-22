/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fillit_solver.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/19 13:35:49 by tide-jon       #+#    #+#                */
/*   Updated: 2019/04/22 16:34:43 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

/*
** deze functie kan in c library
*/

static int	count_pointers(void **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

/*
** bepaalt de starting size van het kleinste vierkant waar
** tetriminos in kunnen passen
*/

static int	square_startsize(int n)
{
	int size;

	size = 2;
	while ((size * size) < n)
		size++;
	return (size);
}

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
			part++;
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

static int	solver(char **sqr, t_tetrimino **arr, int square_size)
{
	int x_sqr;
	int y_sqr;
	int part;

	while (*arr != NULL)
	{
		y_sqr = 0;
		while (y_sqr < square_size)
		{
			x_sqr = 0;
			while (x_sqr < square_size)
			{
				tetri_fit_check(sqr, arr, y_sqr, x_sqr);
				x_sqr++;
			}
			y_sqr++;
		}
		return (0);
	}
	print_solution(sqr, square_size);
	return (1);
}

static void	free_square(char **square)
{
	if (square[1] != NULL)
		free_square(&square[1]);
	ft_strdel(square);
	square = NULL;
}

/*
** make_square takes a size_t size, and creates a square 2d array of that size.
** It also fills all characters in said square with "."
*/

static char	**make_square(size_t size)
{
	char		**square;
	size_t		i;

	square = (char**)malloc(sizeof(char*) * (size + 4));
	square[size + 3] = NULL;
	i = 0;
	while (i < size)
	{
		square[i] = (char*)malloc(size + 1);
		ft_memset((void*)square[i], '.', size);
		square[i][size] = '\0';
		i++;
	}
	while (i < size + 3)
	{
		square[i] = (char*)malloc(size + 1);
		ft_memset((void*)square[i], '*', size);
		square[i][size] = '\0';
		i++;
	}
	return (square);
}

/*
** roept de solver aan voor grotere squares als er
** geen oplossing is voor een kleinere square
*/

void		pre_solver(t_tetrimino **arr)
{
	int		i;
	size_t	square_size;
	char	**sqr;

	i = 0;
	square_size = square_startsize(count_pointers((void**)arr) * 4);
	sqr = make_square(square_size);
	while (solver(sqr, arr, square_size) == 0)
	{
		free_square(sqr);
		square_size++;
		sqr = make_square(square_size);
	}
	free_square(sqr);
}
