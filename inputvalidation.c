/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   inputvalidation.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/12 16:35:17 by tide-jon       #+#    #+#                */
/*   Updated: 2019/04/18 16:18:17 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFF_SIZE 546

/*
** checks for correct tetrimino shapes inside the 4x4 blocks
*/

int		correctshape(int subindex, int i, char *buf)
{
	if (5 < subindex && subindex < 15)
	{
		if (buf[i - 1] != '#' && buf[i + 1] != '#' &&
				buf[i - 5] != '#' && buf[i + 5] != '#')
			return (-1);
	}
	else if (subindex < 5)
	{
		if (subindex == 0 && buf[i + 1] != '#' && buf[i + 5] != '#')
			return (-1);
		else if (buf[i - 1] != '#' && buf[i + 1] != '#' && buf[i + 5] != '#')
			return (-1);
	}
	else if (15 < subindex)
	{
		if (subindex == 20 && buf[i - 1] != '#' && buf[i - 5] != '#')
			return (-1);
		else if (buf[i - 1] != '#' && buf[i + 1] != '#' && buf[i - 5] != '#')
			return (-1);
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
				if (correctshape(subindex, i, buf) == -1)
					return (-1);
			}
			i++;
			subindex++;
		}
		i++;
		if (countblocks != 4)
			return (-1);
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
				return (-1);
			i++;
			j = 1;
		}
		if (buf[i] == '\0')
			break ;
		if ((j % 5 != 0 && (buf[i] != '#' && buf[i] != '.')) ||
								(j % 5 == 0 && buf[i] != '\n'))
			return (-1);
		i++;
	}
	if (j != 20 || blockcount(buf) == -1)
		return (-1);
	return (1);
}
