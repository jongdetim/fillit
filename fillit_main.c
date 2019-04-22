/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fillit_main.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkamphor <kkamphor@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/12 16:35:17 by tide-jon       #+#    #+#                */
/*   Updated: 2019/04/22 18:04:03 by kkamphor      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** free_tetrilist takes the list of tetriminos created in this program, and
** frees all of its allocated memory.
*/

static void	free_tetrilist(t_tetrimino **tetrilist)
{
	if (tetrilist[1] != NULL)
		free_tetrilist(&tetrilist[1]);
	free(*tetrilist);
	tetrilist = NULL;
}

int			main(int argc, char **argv)
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
			free_tetrilist(tetrilist);
		}
		else
			ft_putendl("error");
	}
	else
		ft_putendl("usage: ./fillit target_file");
	return (0);
}
