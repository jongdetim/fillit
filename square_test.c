/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   square_test.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkamphor <kkamphor@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/22 14:20:26 by kkamphor       #+#    #+#                */
/*   Updated: 2019/04/22 14:26:26 by kkamphor      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	print_square(char **square)
{
	int i;

	i = 0;
	while (square[i])
	{
		ft_putendl(square[i]);
		i++;
	}
}

static void	free_square(char **square)
{
	if (square[1] != NULL)
		free_square(&square[1]);
	ft_strdel(square);
	square = NULL;
}

static char	**make_square(size_t size)
{
	char		**square;
	size_t		i;

	square = (char**)malloc(sizeof(char*) * (size + 1));
	square[size] = NULL;
	i = 0;
	while (i < size)
	{
		square[i] = (char*)malloc(size + 1);
		ft_memset((void*)square[i], '.', size);
		i++;
	}
	return (square);
}

int		main(void)
{
	size_t size;
	char ** square;

	size = 7;
	square =  make_square(size);
	print_square(square);
	free_square(square);
	return (0);
}