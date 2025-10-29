
#ifndef MINIRT_H

# define MINIRT_H
# define HEIGHT 720
# define WIDTH 1280
# define M_PI       3.14159265358979323846
# define RENDER_DISTANCE 10000
# define N_THREAD 24
# define BLOCK_SIZE_MAX 20
# define BLOCK_SIZE_MIN 1
# define DEEPTH	8
# define LIGHT_MAX 10
# define BOUNCE_MAX 10
# define SAMPLE_MAX 5
# include <unistd.h>
# include <semaphore.h>
# include <pthread.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/time.h>
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


typedef struct s_vec2
{
	int u;
	int v;
}				t_vec2;

typedef struct s_t_map
{
	unsigned int	**map;
	t_vec2			size;
}				t_t_map;

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct s_material
{
	double	reflection;   //0 = mat  1 = miroir
	double	refraction;   //0 = opaque 1 = complètement transparent  a voir si on garde mais c le plus logique
	double	ior;
	t_t_map	albedo;
	t_t_map	normal;
	t_t_map roughness;
}	t_material;

typedef struct s_bounds
{
	t_vec3	max;
	t_vec3	min;
	int		deepth;

}		t_bounds;

typedef struct s_offset_bounds
{
	double	delta_u_max;
	double	delta_u_min;	
	double	delta_v_max;
	double	delta_v_min;

}				t_delta_offset;

typedef	struct s_bvh
{
	t_bounds	bounds;
	int			*idx_tr_hbv;
	int			n_obj;
	struct s_bvh *zone_1;
	struct s_bvh *zone_2; 
	struct s_bvh *previous; 
	
}	t_bvh;


typedef struct	s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	t_boolean		hit;
}				t_color;

typedef struct s_var_texture{
	
	t_vec2	uv;
	t_color color;
	t_vec3	normal_texture;
	t_vec3	normal;
}				t_var_texture;

typedef enum s_type
{
	A,
	C,
	L,
	pl,
	sp,
	cy,
	tr,
}				t_type;				

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
	unsigned int	i;
	unsigned int	j;
	double	delta_u;
	double	delta_v;
	unsigned int		max;
	unsigned int		block_size;
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
	t_material		mat;
	double			ratio;
	double			diameter;
	double			height;
	unsigned char	id;
	double			spec;
	t_vec3			p0;
	t_vec3			p1;
	t_vec3			p2;
	t_vec3			normal;
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
	t_objet			*objet_tr;
	unsigned char	nb_objet;
	t_light			*light;
	unsigned char	nb_light;
	t_light			ambiant;
}				t_sc;

// GENERAL AND MLX	bvh_free(mini->bvh);


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
	t_vec3	left_corner;
	sem_t	*m_cast;
	sem_t	*s_img;
	t_bvh	*bvh;
	t_bvh	*tmp;
	int		max;
	int		min;
	int		cam_lock;
	int		n_cam;
	int		n_cy;
	int		n_pl;
	int		n_sp;
	int		n_a;
	int		n_tr;
	int		n_l;
	int		N_OBJ;
	int		N_LIGHT;
	int		block_size;
	t_vec3	up_world;
	unsigned long	last_input;
}				t_mini;

typedef	struct s_ray
{
	double		t_min;
	double		t_current;
	t_vec3		*dir_tab;
	t_vec3		current_dir;
	t_vec3		origin;
	t_color		color;
	int			bounce;
}			t_ray;


typedef struct s_normal
{
	t_vec3 geometric;
	t_vec3 texture;
	
}			t_normal;

typedef struct s_light_utils
{
	t_normal	normal;
	int			i;
	
}				t_light_utils;

// DRAW BASIC

int				my_mlx_pixel_put(t_mini *mini, int x, int y, unsigned int color);
unsigned int	color_shift(t_color rgb);
t_color			color_shift_revert(unsigned int color);


// WINDOW

t_boolean	open_window(t_mini *mini);
int			close_window(t_mini *mini);
int			handle_key_input(int keysym, t_mini *mini);
int			handle_mouse_input(int keysym, int x, int y, t_mini *mini);

// UTILS

t_boolean	is_space(char c);
double		atoi_double(char *str);
double		__atoi_double(char **str);
t_boolean	is_null_vector(t_vec3 normal);

// FREE

void 		free_mini(t_mini *mini);
void		free_double_array_error(void **array, int n);


// -------- PARSING -------- 

t_boolean	parser(t_mini *mini, char **av);
t_boolean	count_line(t_mini *mini, char *file);
t_vec3		get_point(char **buffer);
t_color		get_color(char **buffer);
double		get_spec(char *buffer);

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
void		parse_tr(t_mini *mini, char *buffer);

// DEBUG

void		printAllCam(t_mini *mini);
void		printVec2(t_vec2 vec);
void		printAllObject(t_mini *mini);
void		printVec(t_vec3	Ray);
void		printObject(t_objet obj);
void		printColor(t_color color);
void		printBounds(t_bvh *bvh);
void 		printColorMap(unsigned int **map, t_vec2 size);
void 		printCharTab(char **tab);

//RAY 

void		set_up_cam(t_mini *mini);
void		*cast(void *arg);

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
t_color	mix_layer(t_color c1, t_color c2);
t_color	mix_colors_ratio(t_color c1, t_color c2, double ratio);

// INTERSECT

double	intersect_cy(t_vec3 origin, t_vec3 ray_direction, t_objet object);
double	intersect_sp(t_vec3 origin, t_vec3 ray_direction, t_objet object);
double	intersect_pl(t_vec3 origin, t_vec3 ray_direction, t_objet object);
double  intersect_cap(t_vec3 origin, t_vec3 ray_direction, t_objet object);
t_boolean is_intersect(t_mini *mini, t_vec3 ray_direction, t_vec3 origin, int index_light);
void		set_normal_tr(t_mini *mini);


// LIGHT_RAY

t_color	light_ray(t_mini *mini, t_ray *ray, t_objet obj);
t_var_texture	find_ray_texture(t_objet obj, t_vec3 p);
// INTERSEC

t_color		intersect_loop(t_mini *mini, t_ray *ray);
void		free_double_array(void **dest);


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


t_vec3	get_left_corner_viewport(t_mini mini);

// SPECULAR

t_boolean	shadow_ray(t_mini *mini, t_ray ray, double t, int light_index);
t_color		specular(t_mini *mini, t_objet obj, t_ray *ray, t_light_utils utils);


//THREAD

t_boolean	run_thread(t_mini *mini);
double	compute_tr_area(t_vec3 a, t_vec3 b, t_vec3 c);
double	intersect_tr(t_vec3 origin, t_vec3 ray_direction, t_objet object);


t_boolean		run_thread(t_mini *mini);
unsigned long	chrono(void);

// render 

t_color	multiple_ray(t_mini *mini, t_ray *ray);
int render_loop(t_mini *mini);

// Cast utils

t_vec3	get_left_corner_viewport(t_mini mini);
double	get_delta_u(t_cam cam, int min);

// init

t_boolean	init(t_mini *mini, char **av);

// LIGHT

t_color	light_sp(t_mini *mini, t_objet obj, t_ray *ray, t_light_utils utils);
t_color	light_pl(t_mini *mini, t_objet obj, t_ray *ray, t_light_utils utils);
t_color	light_cy(t_mini *mini, t_objet obj, t_ray *ray, t_light_utils utils);
t_color	light_tr(t_mini *mini, t_objet obj, t_ray *ray, t_light_utils utils);

// BOUNDS

typedef struct s_var_bounds
{
	double	mid_x;
	double	mid_y;
	double	mid_z;
	double	dx; 
	double	dy; 
	double	dz; 
} 			t_var_bounds;

t_bounds	found_first_bound(t_mini *mini);
t_boolean	tr_is_in_bounds(t_objet	tr, t_bounds bounds);
t_bounds	find_bounds(t_bounds old_bounds, int direction);
void		find_bounds_utils(t_var_bounds *var, t_bounds old_bounds);
t_vec3		try_max_bound(t_objet obj, t_vec3 max);
t_vec3		try_min_bound(t_objet obj, t_vec3 max);



// BVH
t_bvh	*bvh_fill(t_mini *mini, int dir, t_bvh *old);
int		*in_view_realloc(int *old, int add, int nb);
void	bvh_free(t_bvh *bvh);
int		*search_tr_in_tree(t_bvh *bvh, t_vec3 origin, t_vec3 ray_direction, int *size, int *tr_in_view);


// GET_UV

t_vec2	get_uv_sp(t_vec3 p, t_vec2 size);

// PARSER TXT

unsigned int	**get_texture(char *file, t_t_map *map);
t_boolean		is_digit_or_space_str(char *str);
t_boolean		is_on_xpm_pixel_info(char *str);
char			**realloc_add_to_tab(char **tab, char *new);
t_boolean		is_digit_or_space_str(char *str);
t_boolean		is_on_xpm_pixel_info(char *str);
t_vec2			get_texture_dimension(int fd);
char			*go_to_pixel_info(int fd);
char			**get_color_tab(int fd);
t_boolean		get_material(t_objet *obj, char *buffer);
char			*get_texture_path(char *str);

// GET FROM MAP

t_color			get_color_from_map(t_objet obj, t_vec3 p, t_vec3 up_world);
t_vec3			transform_normal_from_map(unsigned int color, t_vec3 n, t_vec3 up_world);
t_normal		get_normal_sp_from_map(t_mini *mini, t_objet obj, t_ray *ray);
double			get_roughness_from_map(t_objet obj, double spec, t_vec3 geometric_normal);
// reflection

t_color			 reflection(t_mini *mini, t_ray *old_ray, t_objet obj, t_normal normal);

// ray direction setup

t_vec3			*ray_direction_allocation(void);
t_vec3			*ray_offset(t_vec3	*ray_direction, t_delta_offset bounds, t_mini *mini);
t_delta_offset	get_first_offset_ray_bounds(t_mini *mini, t_var_trace var);



#endif