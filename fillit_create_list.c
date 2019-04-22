/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fillit_create_list.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkamphor <kkamphor@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 15:47:00 by kkamphor       #+#    #+#                */
/*   Updated: 2019/04/18 19:29:59 by kkamphor      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	finish_tetrimino(t_tetrimino *tetri, int count)
{
	int		i;
	int		lowX;
	int		lowY;

	tetri->sign = 'A' + count;
	i = 0;
	lowX = 4;
	lowY = 4;
	while (i < 4)
	{
		if (lowX > tetri->x_coord[i])
			lowX = tetri->x_coord[i];
		if (lowY > tetri->y_coord[i])
			lowY = tetri->y_coord[i];
		i++;
	}
	i = 0;
	while (i < 4)
	{
		tetri->x_coord[i] = tetri->x_coord[i] - lowX;
		tetri->y_coord[i] = tetri->y_coord[i] - lowY;
		i++;
	}
}

static void	fill_block(int i, int y, t_tetrimino *tetri, int count)
{
	static int	hash;
	
	tetri->x_coord[hash] = (i - count) % 5;
	tetri->y_coord[hash] = y;
	hash++;
	if (hash == 4)
		hash = 0;
}

t_tetrimino	**create_tetrilist(char* buff)
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
