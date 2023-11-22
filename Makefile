# DIR
SRC_DIR	= ./src/
HEADER_DIR	= ./includes/
LIBFT_DIR	= ./libft/

SRC			= ft_error.c \
				main.c \

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

.PHONY: allclean fclean re