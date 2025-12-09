NAME = miniRT
CC = cc
CFLAGS = -Iminilibx-linux -Iinclude -O3 -flto
LFLAGS = -lXext -lX11 -lm -lz -lbsd -lpthread -lrt -Wall -Wextra -Wpedantic  -flto
OBJ_DIR = obj
SRC_DIR = src
SRC =	main.c \
		graphic_lib/window.c \
		graphic_lib/basic_draw.c \
		graphic_lib/handle_input.c \
		light/specular.c \
		light/light_ray.c \
		light/light_geometry.c \
		light/light_geometry2.c \
		renderer/cast.c \
		renderer/render.c \
		renderer/set_up_camera.c \
		renderer/ray_direction_setup.c \
		maths/M_math.c \
		maths/M_math2.c \
		maths/C_math0.c \
		maths/C_math1.c \
		maths/C_math3.c \
		intersect/intersect.c \
		intersect/loop.c \
		intersect/get_triangle_array.c \
		geometry_intersect/geometry0.c \
		geometry_intersect/geometry1.c \
		geometry_intersect/geometry2.c \
		geometry_intersect/geometry3.c \
		geometry_intersect/normal.c \
		utils/horloge.c \
		utils/cast_utils.c \
		utils/free.c \
		utils/thread_utils.c \
		utils/utils.c \
		utils/mini_initialisation.c \
		utils/realloc_tab.c \
		utils/parser_texture_utils.c \
		utils/atoi_base.c \
		checker/arg_checker.c \
		checker/arg_checker2.c \
		checker/parser_checker.c \
		checker/parser_checker_utils.c \
		checker/parser_checker_utils2.c \
		parsing/parser.c \
		parsing/parser_texture0.c \
		parsing/parser_texture1.c \
		parsing/parser_buffer.c \
		parsing/parser_buffer2.c \
		parsing/parser_get_material.c \
		parsing/parser_fill_mini.c \
		parsing/parser_utils.c \
		parsing/parser_utils2.c \
		bvh/bounds_utils.c \
		bvh/init_bounds.c \
		bvh/search_bounds.c \
		bvh/bvh.c \
		bvh/bvh_utils.c \
		texture/uv_mapping.c \
		texture/get_from_map.c \
		refraction_reflection/reflection.c \
		graphic_lib/mouse_controls.c \
		graphic_lib/mouse_controls_bis.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o))

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C minilibx-linux/
	$(MAKE) -C libft/
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a minilibx-linux/libmlx.a minilibx-linux/libmlx_Linux.a $(LFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C libft/

fclean: clean
	$(MAKE) fclean -C libft/
	$(MAKE) clean -C minilibx-linux/
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
