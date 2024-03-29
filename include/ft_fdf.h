/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:25:02 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 11:25:13 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H

//-----------------------------------------------------------------------------
//	LIBRARIES
//-----------------------------------------------------------------------------
# include "../ft_libft/include/libft.h"
# include "../minilibx_macos/mlx.h"
# include "key_definitions.h"
# include <fcntl.h>
# include <math.h>

//-----------------------------------------------------------------------------
//	CONSTANT VALUES
//-----------------------------------------------------------------------------
# define WIN_WIDTH 1980
# define WIN_HEIGHT 1024
# define WIN_NAME "FDF"

# ifndef MAX_ANGLE
#  define MAX_ANGLE 360
# endif

# ifndef USE_COLOR
#  define USE_COLOR 1
# endif

//-----------------------------------------------------------------------------
//	DEFINED STRUCTS
//-----------------------------------------------------------------------------

/*
 *	Struct used to store data of points.
 */
typedef struct s_point
{
	int	vector[3];
	int	color;
}	t_point;

typedef struct s_projected
{
	int	coord[2];
	int	color;
}	t_projected;

/*
 *	Used in the algorithm to calculate where to put pixels when drawing a line.
 */
typedef struct s_draw_line
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	error;
	int	error2;
	int	x0;
	int	y0;
	int	point[2];
}	t_draw_line;

/*
 *	Struct used to display pixels to the window through an image.
 */
typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

typedef struct s_view
{
	double	left;
	double	right;
	double	top;
	double	bottom;
	double	far;
	double	near;
}	t_view;

typedef double	(*t_proj)(t_view);

typedef struct s_camera
{
	t_view	view;
	t_proj	projection_matrix[4][4];
	char	homogeneous_coord;
	double	altitude;
}	t_camera;

/*
 *	This stores the information to print. A matrix of points (x, y)
 *	where a point should be printed.
 */
typedef struct s_buffer
{
	void	**points;
	int		n_col;
	int		n_row;
}	t_buffer;

typedef struct s_shape
{
	t_buffer	*buffer;
	t_list		*points;
	double		angle_x;
	double		angle_y;
	double		angle_z;
	double		scale[3];
	double		translate[3];
	double		transformation_matrix[4][4];
}	t_shape;

typedef double	(*t_mat_funct)(double);

typedef struct s_space
{
	t_shape		*shape;
	t_camera	camera;
	t_mat_funct	rotation_x[4][4];
	t_mat_funct	rotation_y[4][4];
	t_mat_funct	rotation_z[4][4];
	t_mat_funct	scalation[4][4];
	t_mat_funct	translation[4][4];
}	t_space;

typedef struct s_ctrl_prgrm
{
	t_space	space;
	t_image	image;
	void	*mlx;
	void	*mlx_win;
	char	rasterize;
	char	close;
	char	reverse;
	char	multiplier;
}	t_ctrl_prgrm;

//-----------------------------------------------------------------------------
//	FUNCTIONS TO READ INPUT FROM FILE
//-----------------------------------------------------------------------------
t_shape	*read_input(char *file);
t_list	*create_points(char **mat, int n_col, int n_row);

//-----------------------------------------------------------------------------
//	CLEAR STRUCT FUNCTIONS
//-----------------------------------------------------------------------------
void	clear_buffer(t_buffer *buffer);
void	clear_point(void *data);
void	clear_shape(t_shape *shape);

//-----------------------------------------------------------------------------
//	MAIN LOOP FUNCTIONS
//-----------------------------------------------------------------------------
void	main_loop(t_ctrl_prgrm *data);
int		handle_keys(int keys, t_ctrl_prgrm *data);

//-----------------------------------------------------------------------------
//	DATA INITIALIZATION FUNCTIONS 
//-----------------------------------------------------------------------------
t_shape	*init_shape(t_shape *shape, t_list *lst);
void	init_matrices(t_space *space);
void	set_rotation_x(t_mat_funct rotation_x[4][4]);
void	set_rotation_y(t_mat_funct rotation_y[4][4]);
void	set_rotation_z(t_mat_funct rotation_z[4][4]);
void	init_scalation(t_mat_funct scalation[4][4]);
void	init_translation(t_mat_funct translation[4][4]);
void	init_projection(t_proj projection_matrix[4][4]);
void	init_view(t_ctrl_prgrm *data);

//-----------------------------------------------------------------------------
//	RASTERIZE FUNCTIONS 
//-----------------------------------------------------------------------------
void	vblank_buffer(t_ctrl_prgrm *data);
void	rasterize(t_ctrl_prgrm *data);
void	buffer_points(t_point *points_3d, t_shape *shape, t_ctrl_prgrm *data,
			int row);
void	draw_line(t_image image, int p_0[2], int p_f[2], int color[2]);
void	draw_point(t_image image, int coord[2], int color);
void	draw_frame_buffer(t_image image, t_buffer *pixels);

//-----------------------------------------------------------------------------
//	MATRIX OPERATIONS FUNCTIONS 
//-----------------------------------------------------------------------------
void	calculate_matrix(t_ctrl_prgrm *data, t_shape *shape);

//-----------------------------------------------------------------------------
//	SET VIEWS
//-----------------------------------------------------------------------------
void	set_isometric_view(t_ctrl_prgrm *data);
void	set_cavalier_view(t_ctrl_prgrm *data);

void	clear_data(t_ctrl_prgrm **data);

char	mlx_reserve_image(t_ctrl_prgrm *data);

#endif
