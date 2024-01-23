/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame_buffer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 10:45:14 by mpovill-          #+#    #+#             */
/*   Updated: 2023/12/26 11:42:52 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static void	convert_vector2(void **vector2, int vector[2], int *color)
{
	t_vector2	*vector;

	vector = (t_vector2 *)vector2;
	vector[0] = vector->vector2[0];
	vector[1] = vector->vector2[1];
	*color = vector->color;
}

/*
 *	Draws all pixels between the right point and current point AND
 *	the lower point and current point. Connects points. It also creates
 *	a color degradate between points.
 */
static void	draw_segments(t_image image, t_buffer pixels, int i, int j)
{
	int	current_point[2];
	int	point_right[2];
	int	point_down[2];
	int	colors[2];

	convert_vector2(pixels.points[i][j], current_point, &colors[0]);
	draw_point(image, current_point, current_color);
	if (i < pixels.n_row - 1)
	{
		get_vector2(pixels.points[i + 1][j], point_down, &colors[1]);
		draw_line(image, current_point, point_down, colors);
	}
	if (j < pixels.n_col - 1)
	{
		get_vector2(pixels.points[i][j + 1], point_right, &colors[1]);
		draw_line(image, current_point, point_right, colors);
	}
}

/*
 *	Draws the lines between points for each coord (x, y) in points.
 */
void	draw_frame_buffer(t_image image, t_buffer pixels)
{
	int	i;
	int	j;

	i = 0;
	while (i < pixels.n_row)
	{
		j = 0;
		while (j < pixels.n_col)
		{
			draw_segments(image, pixels, i, j);
			j++;
		}
		i++;
	}
}
