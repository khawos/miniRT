
#ifndef MINIRT_H

# define MINIRT_H
# define HEIGHT 1080
# define WIDTH 1920
# define OBJ_MAX 20
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include "libft/include/get_next_line.h"
# include "libft/include/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <float.h>
# include <limits.h>

typedef enum s_type
{
	A,
	L,
	pl,
	sp,
	cy,
}				t_type;				

typedef struct	s_data {
	
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

}				t_data;

typedef struct	s_mlx
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

}				t_mlx;


// OBJECT AND CAMERA PROPERTIES

typedef struct	s_objet
{
	t_type			type;
	char			*name;
	double			pos[2];
	double			vec_dir[2];
	char			color[2];
	double			ratio;
	double			diameter;
	double			height;
	unsigned char	id;
}				t_objet;


typedef struct	s_camera
{
	char			*name;
	double			pos[2];
	double			vec_dir[2];
	unsigned char	id;
	unsigned char	fov;
}				t_cam;


typedef struct	s_scene
{
	t_cam			*cam;
	unsigned char	nb_cam;
	t_objet			*objet;
	unsigned char	nb_objet;

}				t_scene;


typedef struct	s_mini
{
	t_mlx	display;
	t_scene scene;
}				t_mini;




// WINDOW

t_boolean	open_window(t_mini *mini);
int			close_window(t_mini *mini);

// UTILS
double		atoi_double(char *str);
void		free_double_array(char **dest);


// PARSER

t_boolean	parser(t_mini *mini, char **av);

// PARSER_CHECKER

t_boolean	checker(char *file);
t_boolean	count_line(t_mini *mini, char *file);

// PARSER CHECKER UTILS

int			count_double_array(char **str);
t_boolean	is_a_rgb_value(char *word);
t_boolean	is_a_ratio(char	*word);
t_boolean	is_a_xyz_normalize_value(char *word);
t_boolean	is_a_xyz_value(char	*word);
t_boolean	is_a_fov_value(char	*word);
t_boolean	is_a_strictly_positive_number(char *word);
int			count_coma(char *line);
t_boolean	alpha_problem(char *line);
t_boolean	nb_data_problem(char *line , char *type);

// ARGS CHECKER

t_boolean	args_checker_pl(char *line);
t_boolean	args_checker_sp(char *line);
t_boolean	args_checker_cy(char *line);
t_boolean	args_checker_c(char *line);
t_boolean	args_checker_a(char *line);
t_boolean	args_checker_l(char *line);
t_boolean	args_type_checker(char *type, char *line);

#endif