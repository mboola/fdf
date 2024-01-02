/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 10:45:14 by mpovill-          #+#    #+#             */
/*   Updated: 2023/12/26 11:42:52 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"


static void	print_matrix(int mat[3][3])
{
	int	i;
	int j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			ft_printf(1, "%d", mat[i][j]);
			j++;
		}
		ft_printf(1, "\n");
		i++;
	}
}

/*
 *	This function puts a pixel on screen. The coordinates of the point are
 *	already calculated, this justs put it.
 */
static void	put_pixel(t_image image, int x, int y, int color)
{
	char	*dst;

	if (y > WINDOW_HEIGHT || x > WINDOW_WIDTH)
		return ;
	dst = image.addr + (y * image.line_len + x * (image.bpp / 8));
	*(unsigned int*)dst = color;
}

static void	mult(int mat[3][3], int point[3], int res[3])
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		res[i] = 0;
		j = 0;
		while (j < 3)
		{
			res[i] += mat[i][j] * point[j];
			j++;
		}
		i++;
	}
}

static void	project(int vec[3], int rot[3][3], t_mlx_data *mlx, int res[3])
{
	int	res_rot[3];

	mult(rot, vec, res_rot);
	res[0] = mlx->projection_matrix[0][0](res_rot[0], mlx);
	res[1] = mlx->projection_matrix[1][1](res_rot[1], mlx);
	res[2] = 0;
}

void	rasterize_row(t_point *points_col, t_mlx_data *mlx_data, int rotation_mat[3][3], int row)
{
	int			i;
	int			vector[3];
	t_vector2	*vector2;

	i = 0;
	while (points_col[i].vector[0] != -1)	//while not end of array
	{
		project(points_col[i].vector, rotation_mat, mlx_data, vector); //we get two points
		vector2 = (t_vector2 *)mlx_data->data_to_print.screen_points[row][i];
		vector2->vector2[0] = vector[0];
		vector2->vector2[1] = vector[1];
		ft_printf(1, "X=%d, Y=%d\n", vector[0], vector[1]);
		i++;
	}
}

static void	put_row_pixels(t_image image, void **pixels, int n_col)
{
	int			i;
	t_vector2	*vector;

	i = 0;
	while (i < n_col)
	{
		vector = (t_vector2 *)pixels[i];
		ft_printf(1, "X=%d, Y=%d\n", vector->vector2[0], vector->vector2[1]);
		put_pixel(image, vector->vector2[0], vector->vector2[1], 0xFF0000);
		i++;
	}
}

void	rasterize(t_image image, t_mlx_data *mlx_data)
{
	t_point	*points_col;
	t_list	*points_row;
	int		row;
	int		rotation_mat[3][3];
	int		result[3];

	points_row = mlx_data->points;
	get_mat_rotation(mlx_data, rotation_mat);
	row = 0;
	while (points_row != NULL)
	{
		rasterize_row((t_point *)(points_row->content), mlx_data, rotation_mat, row);
		points_row = points_row->next;
		row++;
	}
	row = 0;
	while (row < mlx_data->data_to_print.n_row)
	{
		put_row_pixels(image, mlx_data->data_to_print.screen_points[row], mlx_data->data_to_print.n_col);
		row++;
	}
}