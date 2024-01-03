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

# define WINDOW_WIDTH 900
# define WINDOW_HEIGHT 600
# define WINDOW_NAME "FDF"

# define PRECISION 10

typedef struct	s_image {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

typedef double	(*s_rot_function)(double);

struct s_mlx_data;

typedef int (*s_proj_function)(double, struct s_mlx_data *);

typedef struct	s_data_to_print {
	void	***points;
	int		n_col;
	int		n_row;
}	t_data_to_print;

typedef struct	s_vector2 {
	int	vector2[2];
	int	color;
}	t_vector2;

typedef struct	s_mlx_data {
	void			*mlx;
	void			*mlx_win;
	t_list			*points;
	char			rasterize;
	char			close;
	int				scale;
	int				offset[2];
	s_proj_function projection_matrix[3][3];	//this will offset and scale our points
	s_rot_function	rotation_x[3][3];			//this will rotate our points in the x axis
	s_rot_function	rotation_y[3][3];			//this will rotate our points in the y axis
	s_rot_function	rotation_z[3][3];			//this will rotate our points in the z axis
	double			angle_x;
	double			angle_y;
	double			angle_z;
	t_data_to_print	pixels;
}	t_mlx_data;

typedef struct  s_point {
	int	vector[3];
	int	color;
}	t_point;

int		read_input_file(int argc, char **argv, t_mlx_data *mlx_data);
int		main_loop(t_mlx_data *mlx_data);
t_list	*new_point(int row, int col, int num, char *err);
void	clear_point(void *point);

void	rasterize(t_image image, t_mlx_data *mlx_data);
void	obtain_rotation_matrix(t_mlx_data *mlx_data,
			double rotation_mat[3][3]);
void	draw_pixels(t_image image, t_mlx_data *mlx_data);

//matrix_configuration
void	set_projection(t_mlx_data *mlx_data);
void	set_rotation_x(t_mlx_data *mlx_data);
void	set_rotation_y(t_mlx_data *mlx_data);
void	set_rotation_z(t_mlx_data *mlx_data);
void    set_isometric_view(t_mlx_data *mlx_data);


#endif
