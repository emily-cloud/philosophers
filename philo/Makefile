# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hai <hai@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/01 10:33:32 by hai               #+#    #+#              #
#    Updated: 2024/07/01 11:05:27 by hai              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

SRCS = main.c parse_input.c init_philo.c valid_check.c process.c  \
	actions.c monitor.c philo_utils.c philo_utils2.c philo_utils3.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)
fclean : clean
	$(RM) $(NAME)

re: fclean all

.PHONY : all clean fclean re
