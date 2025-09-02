
#ifndef MINIRT_H

# define MINIRT_H
# define HEIGTH 1080
# define WIDTH 1920
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

typedef enum s_boolean
{
	true,
	false,
}			t_boolean;

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

typedef struct	s_mini
{
	t_mlx	display;
	double	camera[2];

}				t_mini;

// WINDOW

t_boolean	open_window(t_mini *mini);
int			close_window(t_mini *mini);

#endif