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

/*
 *	This function puts a pixel on screen. The coordinates of the point are
 *	already calculated, this justs put it.
 */
static void	put_pixel(t_image image, int x, int y, int color)
{
	char	*dst;

	//TODO: check if it is inside the windows
	if (y > WINDOW_HEIGHT || x > WINDOW_WIDTH)
		return ;
	dst = image.addr + (y * image.line_len + x * (image.bpp / 8));
	*(unsigned int*)dst = color;
}

static void	apply_and_draw_projection(t_image image, t_point *point, t_mlx_data *mlx_data)
{
	//here we should first apply the rotation to the points and store the result
	//... in a 3x3 matrix of doubles
	int	final_point[3];

	final_point[0] = mlx_data->projection_matrix[0][0](point->vector[0], mlx_data);
	final_point[1] = mlx_data->projection_matrix[1][1](point->vector[1], mlx_data);
	final_point[2] = 0;

	put_pixel(image, final_point[1], final_point[0], 0x00FF0000);	
}

void	rasterize(t_image image, t_mlx_data *mlx_data)
{
	t_point	*point;
	t_list	*points;

	points = mlx_data->points;
	while (points != NULL)
	{
		point = (t_point *)(points->content);
		apply_and_draw_projection(image, point, mlx_data);
		points = points->next;
	}
}