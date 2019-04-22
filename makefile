# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: kkamphor <kkamphor@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/04/12 12:16:49 by kkamphor       #+#    #+#                 #
#    Updated: 2019/04/22 18:23:13 by kkamphor      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = fillit

OBJECTS =	$(SRCS:.c=.o)

LIBFT =		Libft/libft.a

SRCS = 		fillit_main.c fillit_inputvalidation.c fillit_create_list.c \
			fillit_presolver.c fillit_solver.c

all :		$(NAME)

$(NAME) :	$(OBJECTS) $(LIBFT)
			gcc -Wall -Wextra -Werror $(OBJECTS) -L libft -lft -o $(NAME)

$(OBJECTS) : $(SRCS)
			gcc -c -Wall -Wextra -Werror $(SRCS)

$(LIBFT) :	
			cd Libft && make && cd ..

clean :
			cd Libft && make clean && cd .. && rm -f $(OBJECTS)

fclean :	clean
			cd Libft && make fclean && cd .. && rm -f $(NAME)

re :		fclean all
