/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                            :+:      :+:    :+:   */
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
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "key_definitions.h"
# include <math.h>

//-----------------------------------------------------------------------------
//	CONSTANT VALUES
//-----------------------------------------------------------------------------
# define WIN_WIDTH 900
# define WIN_HEIGHT 600
# define WIN_NAME "FDF"

/*
 *	Constant used to choose the view. 0 means isometric. Other means conic.
 */
# ifndef VIEW
#  define VIEW 0
# endif

# ifndef MAX_ANGLE
#  define MAX_ANGLE 360
# endif

//-----------------------------------------------------------------------------
//	DEFINED STRUCTS
//-----------------------------------------------------------------------------

/*
 *	Struct used to store data of points.
 */
typedef struct  s_point {
	int	vector[3];
	int	color;
}	t_point;

typedef struct	s_projected {
	int	coord[2];
	int	color;
}	t_projected;

/*
 *	Used in the algorithm to calculate where to put pixels when drawing a line.
 */
typedef struct	s_draw_line {
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
typedef struct	s_image {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

typedef struct	s_view {
	double	left;
	double	right;
	double	top;
	double	bottom;
	double	far;
	double	near;
}	t_view;

typedef double	(*t_proj)(t_view);

typedef struct	s_camera {
	t_view	view;
	t_proj	projection_matrix[4][4];
	float	angle_x;
	float	angle_y;
	float	angle_z;
	double	translate[3];
	double	transformation_matrix[4][4];
}	t_camera;

/*
 *	This stores the information to print. A matrix of points (x, y)
 *	where a point should be printed.
 */
typedef struct	s_buffer {
	void	**points;
	int		n_col;
	int		n_row;
}	t_buffer;

typedef struct	s_shape {
	t_buffer	*buffer;
	t_list		*points;
	float		angle_x;
	float		angle_y;
	float		angle_z;
	double		scale[3];
	double		translate[3];
	double		transformation_matrix[4][4];
}	t_shape;

typedef double	(*t_mat_funct)(double);

typedef struct	s_space {
	t_list		*shapes;
	t_camera	camera;
	t_mat_funct	rotation_x[4][4];
	t_mat_funct	rotation_y[4][4];
	t_mat_funct	rotation_z[4][4];
	t_mat_funct	scalation[4][4];
	t_mat_funct	translation[4][4];
}	t_space;

typedef struct	s_ctrl_prgrm {
	t_space		space;
	void		*mlx;
	void		*mlx_win;
	char		rasterize;
	char		close;
}	t_ctrl_prgrm;

//-----------------------------------------------------------------------------
//	FUNCTIONS
//-----------------------------------------------------------------------------
t_list	*read_input(int argc, char **argv);
t_shape	*convert_shape(char *file);
t_list	*create_points(char **mat, int n_col, int n_row);

//-----------------------------------------------------------------------------
//	CLEAR STRUCT FUNCTIONS
//-----------------------------------------------------------------------------
void	clear_buffer(t_buffer *buffer);
void	clear_point(void *data);
void	clear_shape(void *data);
void	clear_space(t_space space);

//-----------------------------------------------------------------------------
//	MAIN LOOP FUNCTIONS
//-----------------------------------------------------------------------------
void	main_loop(t_ctrl_prgrm *data);

//-----------------------------------------------------------------------------
//	INITIALIZE DATA FUNCTIONS 
//-----------------------------------------------------------------------------
t_shape	*init_shape(t_shape *shape, t_list *lst);
void	init_matrices(t_space space);
void	set_rotation_x(t_mat_funct rotation_x[4][4]);
void	set_rotation_y(t_mat_funct rotation_y[4][4]);
void	set_rotation_z(t_mat_funct rotation_z[4][4]);
void	init_scalation(t_mat_funct scalation[4][4]);
void	init_translation(t_mat_funct translation[4][4]);
void	init_camera(t_camera camera);

/*
int		read_input_file(int argc, char **argv, t_mlx_data *mlx_data);


int		read_input_file(int argc, char **argv, t_mlx_data *mlx_data);
int		main_loop(t_mlx_data *mlx_data);
t_list	*new_point(int row, int col, int num, char *err);
void	clear_point(void *point);

void	initialize_matrices(t_mlx_data *mlx_data);
void	initialize_projection(t_mlx_data *mlx_data);
void	initialize_scale(t_mlx_data *mlx_data);
void	initialize_translation(t_mlx_data *mlx_data);
void	initialize_translation_correction(t_mlx_data *mlx_data);
void	set_rotation_x(t_mlx_data *mlx_data);
void	set_rotation_y(t_mlx_data *mlx_data);
void	set_rotation_z(t_mlx_data *mlx_data);


void	initialize_view(t_mlx_data *mlx_data);

void	rasterize(t_image image, t_mlx_data *mlx_data);
void	calculate_matrix(t_mlx_data *mlx_data, double result_mat[4][4]);
void	convert_points(t_point *points, t_mlx_data *mlx_data,
    double mat[4][4], int row);
void	draw_frame_buffer(t_image image, t_buffer pixels);
void	draw_line(t_image image, int p_0[2], int p_f[2], int color[2]);
void	draw_point(t_image image, int coord[2], int color);

void	update_angle_x(t_mlx_data *mlx_data, double increment);
void	update_angle_y(t_mlx_data *mlx_data, double increment);
void	update_angle_z(t_mlx_data *mlx_data, double increment);

void	initialize_conic_projection(t_mlx_data *mlx_data);
*/

#endif
