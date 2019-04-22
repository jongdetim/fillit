/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fillit_main.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkamphor <kkamphor@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/12 16:35:17 by tide-jon       #+#    #+#                */
/*   Updated: 2019/04/22 15:27:53 by kkamphor      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
/*
static void	free_tetrilist(t_tetrimino **tetrilist)
{
	if (tetrilist[1] != NULL)
		free_tetrilist(&tetrilist[1]);
	free(*tetrilist);
	tetrilist = NULL;
}
*/
/*
** checks for correct tetrimino shapes inside the 4x4 blocks
*/

int			correctshape(int subindex, int i, char *buf)
{
	if (5 < subindex && subindex < 15)
	{
		if (buf[i - 1] != '#' && buf[i + 1] != '#' &&
				buf[i - 5] != '#' && buf[i + 5] != '#')
			return (0);
	}
	else if (subindex < 5)
	{
		if (subindex == 0 && buf[i + 1] != '#' && buf[i + 5] != '#')
			return (0);
		else if (buf[i - 1] != '#' && buf[i + 1] != '#' && buf[i + 5] != '#')
			return (0);
	}
	else if (15 < subindex)
	{
		if (subindex == 20 && buf[i - 1] != '#' && buf[i - 5] != '#')
			return (0);
		else if (buf[i - 1] != '#' && buf[i + 1] != '#' && buf[i - 5] != '#')
			return (0);
	}
	return (1);
}

/*
** checks for the correct amount of blocks within a 4x4 block
*/

int		blockcount(char *buf)
{
	int		i;
	int		countblocks;
	int		subindex;

	i = 0;
	while (buf[i] != '\0')
	{
		countblocks = 0;
		subindex = 1;
		while ((i == 0 || (i + 1) % 21 != 0) && buf[i + 1] != '\0')
		{
			if (buf[i] == '#')
			{
				countblocks++;
				if (correctshape(subindex, i, buf) == 0)
					return (0);
			}
			i++;
			subindex++;
		}
		i++;
		if (countblocks != 4)
			return (0);
	}
	return (1);
}

/*
** checks for blocks of 4 by 4 with the correct characters,
** and seperated by 1 newline
*/

int		inputvalidator(char *buf)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buf[i] != '\0')
	{
		j++;
		if ((i + 1) % 21 == 0)
		{
			if (buf[i] != '\n')
				return (0);
			i++;
			j = 1;
		}
		if (buf[i] == '\0')
			break ;
		if ((j % 5 != 0 && (buf[i] != '#' && buf[i] != '.')) ||
								(j % 5 == 0 && buf[i] != '\n'))
			return (0);
		i++;
	}
	if (j != 20 || blockcount(buf) == 0)
		return (0);
	return (1);
}

int		main(int argc, char **argv)
{
	int			chars_read;
	char		buf[BUFF_SIZE + 1];
	t_tetrimino	**tetrilist;

	if (argc == 2)
	{
		chars_read = read(open(argv[1], O_RDONLY), buf, BUFF_SIZE);
		buf[chars_read] = '\0';
		if (inputvalidator(buf))
		{
			tetrilist = create_tetrilist(buf);
			pre_solver(tetrilist);
		}
	}
	return (0);
}
