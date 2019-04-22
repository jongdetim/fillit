/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solver.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/19 13:35:49 by tide-jon       #+#    #+#                */
/*   Updated: 2019/04/19 15:06:17 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** deze functie kan in c library
*/

int				count_pointers(void **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

/*
** bepaalt de starting size van het kleinste vierkant waar tetriminos in kunnen passen
*/

static int		square_startsize(int n)
{
	int size;

	size = 2;
	while ((size * size) < n)
		size++;
	return (size);
}

void			print_solution(char **sqr)
{
	while (*sqr != NULL)
	{
		ft_putstr(*sqr);
		ft_putchar('\n');
		sqr++;
	}
}

/*
** dit is de solver die met recursive backtracking de puzzel bruteforced en de functie aanroept die het antwoord uitprint.
*/

int				solver(char **sqr, t_tetrimino **arr, int square_size)
{
	int x_sqr;
	int y_sqr;
	int part;

	y_sqr = 0;
	while (*arr != NULL)
	{
		while (y_sqr < square_size)
		{
			x_sqr = 0;
			while (x_sqr < square_size)
			{
				part = 0;																			// {function
				while (part < 4)
				{
					if (sqr[y_sqr + (**arr).y_coord[part]][x_sqr + (**arr).x_coord[part]] == '.')
						part++;
					else
					{
						part = 0;
						break ;
					}
				}
				if (part == 4)																		// (2e functie in functie){
				{
					while (part > 0)
					{
						sqr[y_sqr + (**arr).y_coord[part]][x_sqr + (**arr).x_coord[part]] = (**arr).sign;
						part--;
					}
					if (solver(sqr, arr + 1, square_size) == 1)
						return (1);
					else
					{
						while (part < 4)
						{
							sqr[y_sqr + (**arr).y_coord[part]][x_sqr + (**arr).x_coord[part]] = '.';
							part++;
						}
					}																				// }}
				}
				x_sqr++;
			}
			y_sqr++;
		}
		return (0);
	}
	print_solution(sqr);
	return (1);
}

/*
** vult het vierkant met '.' en eindigt strings met '\0' en eindigt het array sqr met een NULL;
*/

void			fillsqr(char **sqr, int square_size)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < square_size)
	{
		while (i < square_size)
		{
			sqr[j][i] = '.';
			i++;
		}
		sqr[j][i] = '\0';
		i = 0;
		j++;
	}
	sqr[j] = NULL;
}

/*
** roept de solver aan voor grotere squares als er geen oplossing is voor een kleinere square
*/

void			pre_solver(t_tetrimino **arr)
{
	int		i;
	int		square_size;
	char	**sqr;

	i = 0;
	square_size = square_startsize(count_pointers(arr) * 4);
	sqr[square_size + 1][square_size + 1];
	fillsqr(&sqr, square_size);
	while (solver(sqr, arr, square_size) != 1)
	{
		square_size++;
		sqr[square_size + 1][square_size + 1];
		fillsqr(sqr, square_size);
	}
	print_result(sqr);
}
