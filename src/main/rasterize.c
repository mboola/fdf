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

void	rasterize(t_image image, t_mlx_data *mlx_data)
{
	t_point	*point;
	t_list	*points;
	int		rotation_mat[3][3];
	int		result[3];

	points = mlx_data->points;
	get_mat_rotation(mlx_data, rotation_mat);	//this gets me the rotation matrix
	//first I should draw the points and then store the coord of each point.
	//then I should draw a line for each point to connect them.
	//TODO: change the t_list of points to a t_list of an array of points, and each node is a row
	//print_matrix(rotation_mat);
	while (points != NULL)
	{
		point = (t_point *)(points->content);
		project(point->vector, rotation_mat, mlx_data, result);
		put_pixel(image, result[1], result[0], 0x00FF0000);
		points = points->next;
	}
}