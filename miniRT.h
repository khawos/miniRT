
#ifndef MINIRT_H

# define MINIRT_H
# define HEIGHT 500
# define WIDTH 500
# define OBJ_MAX 20
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "libft/include/get_next_line.h"
# include "libft/include/libft.h"
# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

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
	t_type			type;
	char			*name;
	t_vec3			pos;
	t_vec3			vec_dir;
	unsigned char	color[3];
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

typedef struct	s_scene
{
	t_cam			*cam;
	unsigned char	nb_cam;
	t_objet			*objet;
	unsigned char	nb_objet;

}				t_scene;

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
	t_scene scene;
	int		cam_lock;
	int		n_cam;
	int		n_cy;
	int		n_pl;
	int		n_sp;
	int		n_a;
	int		n_l;
	int		N_OBJ;
	
}				t_mini;

// MLX

int	my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color);


// WINDOW

t_boolean	open_window(t_mini *mini);
int			close_window(t_mini *mini);

// UTILS

double		atoi_double(char *str);
double		__atoi_double(char **str);

// FREE

void free_mini(t_mini *mini);


// -------- PARSING -------- 

t_boolean	parser(t_mini *mini, char **av);
t_boolean	count_line(t_mini *mini, char *file);

// PARSE BUFFER

void	parse_cam(t_mini *mini, char *buffer);

// PARSE FILL MINI

t_boolean	fill_mini(t_mini *mini, char *file_name);
void		parse_cy(t_mini *mini, char *buffer);
void		parse_sp(t_mini *mini, char *buffer);
void		parse_pl(t_mini *mini, char *buffer);
void		parse_a(t_mini *mini, char *buffer);
void		parse_l(t_mini *mini, char *buffer);
void		parse_cam(t_mini *mini, char *buffer);

// DEBUG
void	printAllCam(t_mini *mini);
void	printAllObject(t_mini *mini);

//RAY 

void	set_up_cam(t_mini *mini);
t_boolean	trace(t_mini *mini);

// MATRIX MATH

t_vec3 		vec_cross(t_vec3 i, t_vec3 j);
double		vec_cross_x(t_vec3 i, t_vec3 j);
double		vec_cross_y(t_vec3 i, t_vec3 j);
double		vec_cross_z(t_vec3 i, t_vec3 j);
double 		vec_normalize(t_vec3 i);
#endif