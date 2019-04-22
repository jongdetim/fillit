/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fillit_create_list.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkamphor <kkamphor@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 15:47:00 by kkamphor       #+#    #+#                */
/*   Updated: 2019/04/22 16:31:48 by kkamphor      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** takes a tetrimino that has been filled out, assigns a alphabetical character
** to said tetrimino corresponding to its position within the list, and "moves"
** the coordinates to the lowest possible values.
*/

static void	finish_tetrimino(t_tetrimino *tetri, int count)
{
	int		i;
	int		lowx;
	int		lowy;

	tetri->sign = 'A' + count;
	i = 0;
	lowx = 4;
	lowy = 4;
	while (i < 4)
	{
		if (lowx > tetri->x_coord[i])
			lowx = tetri->x_coord[i];
		if (lowy > tetri->y_coord[i])
			lowy = tetri->y_coord[i];
		i++;
	}
	i = 0;
	while (i < 4)
	{
		tetri->x_coord[i] = tetri->x_coord[i] - lowx;
		tetri->y_coord[i] = tetri->y_coord[i] - lowy;
		i++;
	}
}

/*
** Fills in the coordinates of a '#' character of a given tetrimino
*/

static void	fill_block(int i, int y, t_tetrimino *tetri, int count)
{
	static int	hash;

	tetri->x_coord[hash] = (i - count) % 5;
	tetri->y_coord[hash] = y;
	hash++;
	if (hash == 4)
		hash = 0;
}

/*
** Creates a list of tetriminos out of the character buffer read from the
** input file.
*/

t_tetrimino	**create_tetrilist(char *buff)
{
	t_tetrimino	**tetrilist;
	int			y;
	int			i;
	int			count;

	tetrilist = (t_tetrimino**)ft_memalloc(sizeof(t_tetrimino*) * 27);
	i = 0;
	count = 0;
	while (buff[i] != '\0')
	{
		y = 0;
		tetrilist[count] = (t_tetrimino*)ft_memalloc(sizeof(t_tetrimino));
		while (y < 5 && buff[i] != '\0')
		{
			if (buff[i] == '#')
				fill_block(i, y, tetrilist[count], count);
			if (buff[i] == '\n')
				y++;
			i++;
		}
		finish_tetrimino(tetrilist[count], count);
		count++;
	}
	tetrilist[count] = NULL;
	return (tetrilist);
}
