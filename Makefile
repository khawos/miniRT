NAME = minirt
CC = cc
CFLAGS = -Wall -Wextra -Iinclude -Iminilibx-linux -O3 -flto
LFLAGS = -lXext -lX11 -lm -lz -lbsd -flto
OBJ_DIR = obj
SRC_DIR = src
SRC =	main.c \
		graphic_lib/window.c \
		graphic_lib/handle_input.c \
		free.c \
		parsing/parser.c \
		parsing/parser_buffer.c \
		parsing/parser_fill_mini.c \
		utils.c \
		debug.c \
		graphic_lib/basic_draw.c \
		cast.c \
		light_ray.c \
		set_up_camera.c \
		maths/M_math.c \
		maths/M_math2.c \
		maths/C_math.c \
		intersect.c \
		geometry.c \
		horloge.c \
		geometry2.c \
		specular.c \
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
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a minilibx-linux/libmlx.a minilibx-linux/libmlx_Linux.a $(LFLAGS) -o $(NAME)

clean :
	rm -f -r $(OBJ_DIR)
	$(MAKE) clean -C libft/

fclean : clean
	$(MAKE) fclean -C libft/
	$(MAKE) clean minilibx-linux/
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
