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

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
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
 *	Alias of a function that returns a function.
 */
typedef double	(*s_func)(double);

/*
 *	I just dont remember what is this.
 */
typedef struct	s_buffer {
	void	***points;
	int		n_col;
	int		n_row;
}	t_buffer;

/*
 *	I just dont remember what is this.
 */
typedef struct	s_vector2 {
	int	vector2[2];
	int	color;
}	t_vector2;

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
	int			offset[2];	//translation x and y of the points.
	s_func		rotation_x[3][3];	//matrix with functions to calculate rotation in x axis
	s_func		rotation_y[3][3];	//matrix with functions to calculate rotation in y axis
	s_func		rotation_z[3][3];	//matrix with functions to calculate rotation in z axis
	s_func		mat_scale[3][3];	//scalation of x, y and z matrix
	s_func		mat_translation[3][3];	//translation of x and y matrix
	int			mat_proj[3][3];		//projection matrix. used to convert 3d to 2d
	double		angle_x;
	double		angle_y;
	double		angle_z;
	t_buffer	pixels;	//information used to print pixels to the screen (I guess)
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
