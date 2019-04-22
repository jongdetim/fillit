/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fillit.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkamphor <kkamphor@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/12 10:31:47 by kkamphor       #+#    #+#                */
/*   Updated: 2019/04/22 16:33:46 by kkamphor      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include "Libft/libft.h"

typedef	struct		s_tetrimino
{
	char			sign;
	int				x_coord[4];
	int				y_coord[4];
}					t_tetrimino;

t_tetrimino			**create_tetrilist(char *buff);
void				pre_solver(t_tetrimino **arr);
int					solver(char **sqr, t_tetrimino **arr, int square_size);
int					inputvalidator(char *buf);

#endif
