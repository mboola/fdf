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

char	mlx_reserve_image(t_ctrl_prgrm *data)
{
	t_image	image;

	image.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (image.img == NULL)
		return (0);
	image.addr = mlx_get_data_addr(image.img, &image.bpp, &image.line_len,
			&image.endian);
	data->image = image;
	return (1);
}

/*
 *	Calculates the matrix used to convert 3d points to 2d points.
 *	Once it has all points converted and stored in a matrix of points, we call
 *	an algorithm to draw the lines between them.
 */
void	rasterize(t_ctrl_prgrm *data)
{
	t_shape	*shape;
	t_list	*points;
	int		row;

	if (data->image.img != NULL)
		mlx_destroy_image(data->mlx, data->image.img);
	if (!mlx_reserve_image(data))
		clear_data(&data);
	shape = data->space.shape;
	calculate_matrix(data, shape);
	points = shape->points;
	row = 0;
	while (points != NULL)
	{
		buffer_points((t_point *)(points->content), shape, data, row);
		points = points->next;
		row++;
	}
	draw_frame_buffer(data->image, shape->buffer);
}
