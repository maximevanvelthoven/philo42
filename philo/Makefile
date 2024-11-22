# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/07 15:01:52 by mvan-vel          #+#    #+#              #
#    Updated: 2024/11/09 18:12:25 by mvan-vel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#---------------------------------------------------------#
CC	= cc

CFLAGS	= -Wall -Wextra -Werror

GFLAGS	= -g

DFLAGS	= -fsanitize=address -fsanitize=undefined

SRC	= main.c parcing.c init_struct.c start_thread.c utils.c routine.c

OBJ	= $(SRC:.c=.o) 

NAME	= philo

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(GFLAGS) $(OBJ) -o $(NAME)
	
%.o: %.c
	$(CC) $(CFLAGS) $(GFLAGS) -c $< -o $@

#---------------------------------------------------------#
clean:
	rm -rf $(OBJ)

fclean:		clean
	rm -rf $(NAME) 

re: fclean all

#---------------------------------------------------------#