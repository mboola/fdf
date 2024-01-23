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

static void	multiply_matrix(double rotation_matrix[3][3],
				int point[3], double point_rotated[3])
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		point_rotated[i] = 0;
		j = 0;
		while (j < 3)
		{
			point_rotated[i] += rotation_matrix[i][j] * (double)point[j];
			j++;
		}
		i++;
	}
}

static void	rotate_and_project(int point[3], double rotation_matrix[3][3],
				t_mlx_data *mlx_data, int result[3])
{
	double	point_rotated[3];

	//here we multiply our point  
	multiply_matrix(rotation_matrix, point, point_rotated);
	result[0] = mlx_data->projection_matrix[0][0](point_rotated[0], mlx_data);
	result[1] = mlx_data->projection_matrix[1][1](point_rotated[1], mlx_data);
	result[2] = 0;
}

static void	map_points(t_point *points, t_mlx_data *mlx_data,
				double rotation_matrix[3][3], int row)
{
	t_vector2	*vector2;
	int			coord[3];
	int			i;

	i = 0;
	while (points[i].vector[0] != -1)	//while not end of array
	{
		rotate_and_project(points[i].vector, rotation_matrix, mlx_data, coord); //we get two coord
		vector2 = (t_vector2 *)mlx_data->pixels.points[row][i];
		vector2->vector2[0] = coord[0];
		vector2->vector2[1] = coord[1];
		vector2->color = points[i].color;
		//ft_printf(1, "X=%d, Y=%d\n", vector[0], vector[1]);
		i++;
	}
}

/*
 *	Calculates the matrix used to convert 3d points to 2d points.
 *	Once it has all points converted and stored in a matrix of points, we call
 *	an algorithm to draw the lines between them.
 */
void	rasterize(t_image image, t_mlx_data *mlx_data)
{
	t_list	*points;
	double	matrix[3][3];
	int		row;

	points = mlx_data->points;
	calculate_matrix(mlx_data, matrix);
	row = 0;
	while (points != NULL)
	{
		map_points((t_point *)(points->content), mlx_data, rot_matrix, row);
		points = points->next;
		row++;
	}
	draw_frame_buffer(image, mlx_data->pixels);
}
