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

/*
 *	Here I define 
 */
# ifndef XK_Escape
#  define XK_Escape 65307 // o 53
# endif

# ifndef XK_s
#  define XK_s 1 // o 115 abajo
# endif

# ifndef XK_w
#  define XK_w 13 // o 119 arriba
# endif

# ifndef XK_a
#  define XK_a 0 // o 97 arriba
# endif

# ifndef XK_d
#  define XK_d 2 // o 119 arriba
# endif

//izquierda 0 o 97
//derecha es 2 o 100

# include "libft.h"
# include "../minilibx/mlx.h"
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

/*
 *	Alias of a function that recieves a double and returns an int.
 *	Used by the projection matrix.
 */
typedef int	(*s_proj)(double);

/*
 *	Point to be printed and the color it will have.
 */
typedef struct	s_vector2 {
	int	point[2];
	int	color;
}	t_vector2;

/*
 *	This stores the information to print. A matrix of points (x, y)
 *	where a point should be printed.
 */
typedef struct	s_buffer {
	void	***points;
	int		n_col;
	int		n_row;
}	t_buffer;

/*
 *	Used in the algorithm to calculate where to put pixels when drawing a line.
 */
typedef struct	s_draw_line {
	int	d[2];
	int	s[2];
	int	prec[2];
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
	double		scale[3];	//scale x, y and z of the points.
	int			offset[3];	//translation x and y of the points.
	s_func		rotation_x[3][3];	//matrix with functions to calculate rotation in x axis
	s_func		rotation_y[3][3];	//matrix with functions to calculate rotation in y axis
	s_func		rotation_z[3][3];	//matrix with functions to calculate rotation in z axis
	s_func		mat_scale[3][3];	//scalation of x, y and z matrix
	s_func		mat_translation[3][3];	//translation of x and y matrix
	s_proj		mat_proj[3][3];		//projection matrix. used to convert 3d to 2d
	double		angle_x;
	double		angle_y;
	double		angle_z;
	t_buffer	pixels;	//information used to print pixels to the screen
}	t_mlx_data;

/*
 *	Struct used to store data of points.
 */
typedef struct  s_point {
	int	vector[3];
	int	color;
}	t_point;

/*
 *	Functions to run the program.
 */
int		read_input_file(int argc, char **argv, t_mlx_data *mlx_data);
int		main_loop(t_mlx_data *mlx_data);
t_list	*new_point(int row, int col, int num, char *err);
void	clear_point(void *point);

void	rasterize(t_image image, t_mlx_data *mlx_data);
void	obtain_rotation_matrix(t_mlx_data *mlx_data,
			double rotation_mat[3][3]);
void	draw_pixels(t_image image, t_mlx_data *mlx_data);

/*
 *	Matrices configuration. Used at start of the program.
 */
void	initialize_matrices(t_mlx_data *mlx_data);
void	initialize_projection(t_mlx_data *mlx_data);
void	initialize_scale(t_mlx_data *mlx_data);
void	initialize_translation(t_mlx_data *mlx_data);
void	set_rotation_x(t_mlx_data *mlx_data);
void	set_rotation_y(t_mlx_data *mlx_data);
void	set_rotation_z(t_mlx_data *mlx_data);

#endif
