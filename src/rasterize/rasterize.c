/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize.c                                        :+:      :+:    :+:   */
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
		convert_points((t_point *)(points->content), mlx_data, matrix, row);
		points = points->next;
		row++;
	}
	draw_frame_buffer(image, mlx_data->pixels);
}
