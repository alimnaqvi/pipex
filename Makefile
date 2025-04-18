CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = pipex.c open_files.c get_cmds.c split.c fork_and_execute.c utils.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

NAME = pipex

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -I $(LIBFT_DIR)/includes -o $(<:.c=.o)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re