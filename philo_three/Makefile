# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/27 17:02:17 by mspinnet          #+#    #+#              #
#    Updated: 2021/04/09 19:43:08 by mspinnet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ft_itoa.c main.c utils.c utils2.c utils3.c

OBJS	= ${SRCS:.c=.o}

NAME	= philo_three

GCC		= gcc

CFLAGS	= -Wall -Wextra -Werror -I.

RM		= rm -f

ARRC	= ar rc

FT_H	= header.h

all:	${NAME}

%.o: %.c ${FT_H}
		${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:${OBJS} ${FT_H}
		${GCC} ${CFLAGS} -o ${NAME} ${OBJS}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all
