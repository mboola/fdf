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

/*
static void	print_points(void **points, int col)
{
	t_vector2	*arr;
	t_vector2	coord;
	int	i;
	int j;

	i = 0;
	while (points[i] != NULL)
	{
		arr = (t_vector2 *)points[i];
		j = 0;
		while (j < col)
		{
			coord = arr[j];
			ft_printf(1, "(%d,%d) ", coord.coord[0], coord.coord[1]);
			j++;
		}
		ft_printf(1, "\n");
		i++;
	}
}
*/

static void	rasterize_shape(t_ctrl_prgrm *data, t_shape *shape)
{
	t_list	*points;
	int		row;

	printf("c\n");
	calculate_matrix(data, shape);
	points = shape->points;
	row = 0;
	while (points != NULL)
	{
		buffer_points((t_point *)(points->content), shape, data, row);
		points = points->next;
		row++;
	}
	//print_points(mlx_data->pixels.points, mlx_data->pixels.n_col);
	//draw_frame_buffer(data->image, shape->buffer);
}

/*
 *	Calculates the matrix used to convert 3d points to 2d points.
 *	Once it has all points converted and stored in a matrix of points, we call
 *	an algorithm to draw the lines between them.
 */
void	rasterize(t_ctrl_prgrm *data)
{
	t_list	*shapes;
	t_shape	*shape;

	shapes = data->space.shapes;
	while (shapes != NULL)
	{
		printf("b\n");
		shape = (t_shape *)(shapes->content);
		if (shape != NULL)
			rasterize_shape(data, shape);
		shapes = shapes->next;
	}
}
