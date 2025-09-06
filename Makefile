NAME = miniRT
CC = cc
CFLAGS = -Wall -Werror -Wextra -Iinclude -Iminilibx-linux -g3 #-fsanitize=address
LFLAGS = -Imlx_linus -lXext -lX11 -lm -lz -lbsd
OBJ_DIR = obj
SRC_DIR = src
SRC =	main.c \
		window.c \
		parser.c \
		utils.c \
		checker/arg_checker.c \
		checker/arg_checker2.c \
		checker/parser_checker.c \
		checker/parser_checker_utils.c \
		checker/parser_checker_utils2.c \

SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o))

all : $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(NAME) : $(OBJS)
	$(MAKE) -C minilibx-linux/
	$(MAKE) -C libft/
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) libft/libft.a minilibx-linux/libmlx.a minilibx-linux/libmlx_Linux.a -o $(NAME)

clean :
	rm -f -r $(OBJ_DIR)
	$(MAKE) clean -C libft/

fclean : clean
	$(MAKE) fclean -C libft/
	$(MAKE) clean minilibx-linux/
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re