/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fillit_main.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkamphor <kkamphor@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/11 11:19:49 by kkamphor       #+#    #+#                */
/*   Updated: 2019/04/22 13:12:51 by kkamphor      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	free_tetrilist(t_tetrimino **tetrilist)
{
	if (tetrilist[1] != NULL)
		free_tetrilist(&tetrilist[1]);
	free(*tetrilist);
	tetrilist = NULL;

}
/*
void	print_coor(t_tetrimino **tetrilist)
{
	int i;
	int count = 0;

	while (tetrilist[count] != NULL)
	{
		ft_putstr("TEST ");
		ft_putchar(tetrilist[count]->sign);
		ft_putchar('\n');
		i = 0;
		while (i < 4)
		{
			ft_putnbr(tetrilist[count]->x_coord[i]);
			ft_putchar(',');
			ft_putnbr(tetrilist[count]->y_coord[i]);
			ft_putchar(' ');
			i++;
		}
		ft_putchar('\n');
		count++;
	}
	ft_putendl("TEST COMPLETE, COMMENCE PARTY");
}
*/
int     main(int argc, char **argv)
{
    int			chars_read;
    char		buf[BUFF_SIZE + 1];
	t_tetrimino	**tetrilist;

    if (argc == 2)
    {
        chars_read = read(open(argv[1], O_RDONLY), buf, BUFF_SIZE);
        buf[chars_read] = '\0';
		tetrilist = create_tetrilist(buf);
		print_coor(tetrilist);
		free_tetrilist(tetrilist);
	}
    return (0);
}
