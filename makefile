# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: kkamphor <kkamphor@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/04/12 12:16:49 by kkamphor       #+#    #+#                 #
#    Updated: 2019/04/22 13:05:03 by kkamphor      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = fillit

OBJECTS =	$(SRCS:.c=.o)

SRCS = 		fillit_main.c fillit_create_list.c

all :		$(NAME)

$(NAME) :	$(OBJECTS)
			gcc -Wall -Wextra -Werror $(OBJECTS) -L libft -lft -o $(NAME)

$(OBJECTS) : $(SRCS) $(INCL)
			gcc -c -Wall -Wextra -Werror $(SRCS)

clean :
			rm -f $(OBJECTS)

fclean :	clean
			rm -f $(NAME)

re :		fclean all