NAME = miniRT
CC = cc
CFLAGS = -Wall -Werror -Wextra -Iinclude -Iminilibx-linux -g3
LFLAGS = -Imlx_linus -lXext -lX11 -lm -lz -lbsd
OBJ_DIR = obj
SRC_DIR = src
SRC =	main.c \
		window.c \
		free.c \
		parser.c \
		parser_buffer.c \
		parser_fill_mini.c \
		utils.c \
		debug.c \
		basic_draw.c \
		trace.c \
		set_up_camera.c \
		M_math.c
		
SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o))

all : $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
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