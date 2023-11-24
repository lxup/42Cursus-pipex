# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/23 22:09:56 by lquehec           #+#    #+#              #
#    Updated: 2023/11/24 15:14:40 by lquehec          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# DIR
SRC_DIR	= ./src/
HEADER_DIR	= ./includes/
LIBFT_DIR	= ./libft/

SRC			= pipex.c \
				parsing.c \
				utils.c \
				free.c \
				exit.c \

SRCS		= $(addprefix $(SRC_DIR), $(SRC))

OBJS		= $(SRCS:.c=.o)

CC			= cc
RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

# LIBFT
MAKE_LIBFT	= make -s -C $(LIBFT_DIR)
LIBFT_A		= $(LIBFT_DIR)libft.a

NAME		= pipex

.c.o:
			$(CC) $(CFLAGS) -I $(HEADER_DIR) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			$(MAKE_LIBFT) all bonus
			$(CC) $(CFLAGS) -I $(HEADER_DIR) $(OBJS) $(LIBFT_A) -o $(NAME)

all: 		$(NAME)

clean:
			$(RM) $(OBJS)
			$(MAKE_LIBFT) clean

fclean:		clean
			$(RM) $(NAME)
			$(MAKE_LIBFT) fclean

re:			fclean all

bonus:		all

.PHONY: all clean fclean re bonus