# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/04 15:10:36 by aamajane          #+#    #+#              #
#    Updated: 2022/08/23 18:19:40 by aamajane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_bonus

LIBPHIL	=	srcs/libphil.a

SRCS	=	srcs/philosophers_1.c \
			srcs/philosophers_2.c \
			srcs/ft_atoi.c

OBJS	=	$(SRCS:.c=.o)

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

LIB		=	ar -rcs

RM		=	rm -rf


all:		$(NAME)

$(NAME):	$(LIBPHIL)
			@$(CC) $(CFLAGS) $(LIBPHIL) -o $(NAME)

$(LIBPHIL):	$(OBJS)
			@$(LIB) $(LIBPHIL) $(OBJS)

.c.o:
			@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
			@$(RM) $(OBJS) $(LIBPHIL)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
