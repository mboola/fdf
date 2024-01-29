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

# include "../ft_libft/include/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "key_definitions.h"
# include <math.h>

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

/*
 *	Alias of a function that recieves a double and returns a double.
 */
typedef double	(*s_func)(double);

typedef struct	s_view {
	double	right;
	double	left;
	double	top;
	double	down;
	double	far;
	double	near;
}	t_view;

/*
 *	Alias of a function that recieves a view and returns a double.
 *	Used by the projection matrix.
 */
typedef double	(*s_proj)(t_view);

/*
 *	Point to be printed and the color it will have.
 */
typedef struct	s_vector2 {
	int	coord[2];
	int	color;
}	t_vector2;

/*
 *	This stores the information to print. A matrix of points (x, y)
 *	where a point should be printed.
 */
typedef struct	s_buffer {
	void	**points;
	int		n_col;
	int		n_row;
}	t_buffer;

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
 *	Struct with all the information of the program.
 */
typedef struct	s_mlx_data {
	void		*mlx;
	void		*mlx_win;
	t_list		*points;
	char		rasterize;	//flag to know if we need to resterize the image.
	char		close;		//flag to know if we need to close the program.
	char		conic;
	double		scale[3];	//scale x, y and z of the points.
	double		offset[3];	//translation x and y of the points.
	s_func		rotation_x[4][4];	//matrix with functions to calculate rotation in x axis
	s_func		rotation_y[4][4];	//matrix with functions to calculate rotation in y axis
	s_func		rotation_z[4][4];	//matrix with functions to calculate rotation in z axis
	s_func		mat_scale[4][4];	//scalation of x, y and z matrix
	s_func		mat_translation[4][4];	//translation of x and y matrix
	s_func		mat_translation_correction[4][4];	//translation of x and y matrix
	s_proj		mat_proj[4][4];		//projection matrix. used to convert 3d to 2d
	double		angle_x;
	double		angle_y;
	double		angle_z;
	t_buffer	pixels;	//information used to print pixels to the screen
	t_view		view_values;
	double		distorsion;
}	t_mlx_data;

/*
 *	Struct used to store data of points.
 */
typedef struct  s_point {
	int	vector[3];
	int	color;
}	t_point;

/*
 *	Read data from file functions.
 */
int		read_input_file(int argc, char **argv, t_mlx_data *mlx_data);


int		read_input_file(int argc, char **argv, t_mlx_data *mlx_data);
int		main_loop(t_mlx_data *mlx_data);
t_list	*new_point(int row, int col, int num, char *err);
void	clear_point(void *point);

/*
 *	Matrices configuration. Used at start of the program.
 */
void	initialize_matrices(t_mlx_data *mlx_data);
void	initialize_projection(t_mlx_data *mlx_data);
void	initialize_scale(t_mlx_data *mlx_data);
void	initialize_translation(t_mlx_data *mlx_data);
void	initialize_translation_correction(t_mlx_data *mlx_data);
void	set_rotation_x(t_mlx_data *mlx_data);
void	set_rotation_y(t_mlx_data *mlx_data);
void	set_rotation_z(t_mlx_data *mlx_data);

/*
 *	Initializes the angles to rasterize from.
 */
void	initialize_view(t_mlx_data *mlx_data);

/*
 *	Rasterization functions.
 */
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

#endif
