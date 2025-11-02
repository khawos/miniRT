
#ifndef MINIRT_H

# define MINIRT_H
# define HEIGHT 1080
# define WIDTH 1920
# define OBJ_MAX 20
# define M_PI       3.14159265358979323846
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <stdio.h>
# include "libft/include/get_next_line.h"
# include "libft/include/libft.h"
# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <float.h>
# include <limits.h>

typedef	enum	s_inter
{
	in,
	out,
	edge,
}				t_inter;

typedef struct	s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	t_boolean		hit;
}				t_color;


typedef enum s_type
{
	A,
	C,
	L,
	pl,
	sp,
	cy,
}				t_type;				


typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef	struct s_equation
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	s1;
	double	s2;
	double  t;
	t_vec3	intersect;
	t_vec3	H;
	t_vec3	B;
	t_vec3	H_chapeau;
	t_vec3	W;
	t_vec3	cap_center_top;
	t_vec3	cap_center_bottom;

}				t_equation;

typedef struct s_var_trace
{
	double	i;
	double	j;
	double	delta_u;
	double	delta_v;
	
}				t_var_trace;

typedef struct	s_data {
	
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

}				t_data;

// OBJECT AND CAMERA PROPERTIES

typedef struct	s_objet
{
	t_boolean		cap;
	t_type			type;
	char			*name;
	t_vec3			pos;
	t_vec3			vec_dir;
	t_color			color;
	double			ratio;
	double			diameter;
	double			height;
	unsigned char	id;
}				t_objet;

typedef struct	s_camera
{
	char			*name;
	t_vec3			pos;
	t_vec3			vec_dir;
	t_vec3			up;
	t_vec3			right;
	int				aspect_ratio;	
	int				id;
	int				fov;
	double			h;
	double			w;
}				t_cam;

typedef	struct	s_light
{
	char			*name;
	int				id;
	double			ratio;
	t_vec3			pos;
	t_vec3			vec_dir;
	t_color			color;
	t_type			type;

}				t_light;


typedef struct	s_sc
{
	t_cam			*cam;
	unsigned char	nb_cam;
	t_objet			*objet;
	unsigned char	nb_objet;
	t_light			*light;
	unsigned char	nb_light;
	t_light			ambiant;
}				t_sc;

// GENERAL AND MLX

typedef struct	s_mlx
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

}				t_mlx;

typedef struct	s_mini
{
	t_mlx	display;
	t_sc 	sc;
	int		cam_lock;
	int		n_cam;
	int		n_cy;
	int		n_pl;
	int		n_sp;
	int		n_a;
	int		n_l;
	int		N_OBJ;
	int		N_LIGHT;
	
}				t_mini;

// DRAW BASIC

int				my_mlx_pixel_put(t_mini *mini, int x, int y, unsigned int color);
unsigned int	color_shift(t_color rgb);


// WINDOW

t_boolean	open_window(t_mini *mini);
int			close_window(t_mini *mini);
int			handle_key_input(int keysym, t_mini *mini);

// UTILS

t_boolean	is_space(char c);
double		atoi_double(char *str);
double		__atoi_double(char **str);

// FREE

void 		free_mini(t_mini *mini);


// -------- PARSING -------- 

t_boolean	parser(t_mini *mini, char **av);
t_boolean	count_line(t_mini *mini, char *file);

// PARSE BUFFER

void		parse_cam(t_mini *mini, char *buffer);

// PARSE FILL MINI

t_boolean	fill_mini(t_mini *mini, char *file_name);
void		parse_cy(t_mini *mini, char *buffer);
void		parse_sp(t_mini *mini, char *buffer);
void		parse_pl(t_mini *mini, char *buffer);
void		parse_a(t_mini *mini, char *buffer);
void		parse_l(t_mini *mini, char *buffer);
void		parse_cam(t_mini *mini, char *buffer);

// DEBUG
void		printAllCam(t_mini *mini);
void		printAllObject(t_mini *mini);
void		printVec(t_vec3	Ray);
void		printObject(t_objet obj);
void	printColor(t_color color);

//RAY 

void		set_up_cam(t_mini *mini);
t_boolean	cast(t_mini *mini);

// MATRIX MATH

t_vec3		vec_cross(t_vec3 i, t_vec3 j);
t_vec3		vec_create(double x, double y, double z);
double		vec_get_norme(t_vec3 i);
double		convert_range(double v, double max_src, double min_dst, double max_dst);

// MATRIX MATH2

double		vec_dot(t_vec3 i, t_vec3 j);
t_vec3		vec_substact(t_vec3 i, t_vec3 j);
t_vec3		vec_normalize(t_vec3 i);
t_vec3		vec_add(t_vec3 i, t_vec3 j);
t_vec3		vec_scale(t_vec3 i, double n);
void		vec_add_ptr(t_vec3 *result, t_vec3 add);
void		vec_sub_ptr(t_vec3 *result, t_vec3 sub);
t_vec3		vec_div(t_vec3 i, double n);

// COLOR MATH

t_color	apply_ambiant(t_mini *mini, t_color color);
t_color color_multiplie(t_color i, t_color j);
t_color	color_substract(t_color i, t_color j);
t_color	color_add(t_color i, t_color j);
t_color	color_scalar(t_color i, double ratio);
t_color mix_colors(t_color c1, t_color c2);

// INTERSECT

double	intersect_cy(t_vec3 origin, t_vec3 ray_direction, t_objet *object);
double	intersect_sp(t_vec3 origin, t_vec3 ray_direction, t_objet *object);
double	intersect_pl(t_vec3 origin, t_vec3 ray_direction, t_objet *object);
double  intersect_cap(t_vec3 origin, t_vec3 ray_direction, t_objet *object);
t_boolean is_intersect(t_mini *mini, t_vec3 ray_direction, t_vec3 origin);

// LIGHT_RAY

t_color	light_ray(t_mini *mini, t_vec3 ray_dir, double t, t_objet obj);
t_color	light_cy(t_mini *mini, t_objet obj, t_vec3 ray_dir, double t);
t_color	light_pl(t_mini *mini, t_objet obj, t_vec3 ray_dir, double t);
t_color	light_sp(t_mini *mini, t_objet obj, t_vec3 ray_dir, double t);

// CAST

/**
 * @brief get ray direction
 * 
 * Donne a ray_D un vecteur norme dans la direction de la cam vers P
 * 
 * @param ray_d directon du ray cast par la cam
 * @param P point dans l'espace 3D d'un pixel projete sur le plan de taille w * h 
 * @param mini mini tu connais y a tout e qui faut dedans
 * 
 */
void	get_ray_direction(t_vec3 *ray_D, t_vec3 *P, t_mini *mini);

void	clash_of_clan(t_mini *mini, t_vec3 ray_direction, int x, int y);
// INTERSEC

t_color	intersect(t_mini *mini, t_vec3 ray_direction);
double	intersect_sp(t_vec3 origin, t_vec3 ray_direction, t_objet *object);
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