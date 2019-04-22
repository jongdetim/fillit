/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fillit_presolver.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkamphor <kkamphor@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/22 15:53:47 by kkamphor       #+#    #+#                */
/*   Updated: 2019/04/22 17:09:23 by kkamphor      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Telt het aantal pointers in een 2d array. de 2d array moet eindiging met een
** NULL pointer. Deze functie kan in c library.
*/

static	int		count_pointers(void **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

/*
** bepaalt de starting size van het kleinste vierkant waar tetriminos in
** kunnen passen
*/

static int		square_startsize(int n)
{
	int size;

	size = 2;
	while ((size * size) < n)
		size++;
	return (size);
}

/*
** free_square deletes all strings in a given 2D array, frees the allocated
** memory, and sets all pointers to NULL.
*/

static void		free_square(char **square)
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

static char		**make_square(size_t size)
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
** roept de solver aan voor grotere squares als er geen oplossing is voor een
** kleinere square
*/

void			pre_solver(t_tetrimino **arr)
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
