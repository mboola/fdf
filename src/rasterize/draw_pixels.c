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
static void	draw_point(t_image image, int x, int y, int color)
{
	char	*dst;

	if (y > WINDOW_HEIGHT || x > WINDOW_WIDTH)
		return ;
	dst = image.addr + (y * image.line_len + x * (image.bpp / 8));
	*(unsigned int*)dst = color;
}

static void	draw_line(t_image image, int x0, int y0, int final_p[2])
{
	int	d[2];
	int	s[2];
	int	prec[2];

	d[0] = abs(final_p[0] - x0);
	d[1] = abs(final_p[1] - y0);
	s[0] = (x0 < final_p[0]) + (x0 >= final_p[0]) * -1;
	s[1] = (y0 < final_p[1]) + (y0 >= final_p[1]) * -1;
	prec[0] = (d[0] > d[1]) * (d[0] / 2) + (d[0] <= d[1]) * (-d[1] / 2);
	while (x0 != final_p[0] && y0 != final_p[1])
	{
		draw_point(image, x0, y0, 0xFF0000);
		prec[1] = prec[0];
		if (prec[1] > -d[0])
		{
			prec[0] -= d[1];
			x0 += s[0];
		}
		if (prec[1] < d[1])
		{
			prec[0] += d[0];
			y0 += s[1];
		}
	}
}

static void	get_vector2(void **vector2, int vector[2])
{
	t_vector2	*mat_vector;

	mat_vector = (t_vector2 *)vector2;
	vector[0] = mat_vector->vector2[0];
	vector[1] = mat_vector->vector2[1];
}

static void	draw_segment(t_image image, t_mlx_data *mlx_data, int i, int j)
{
	int	current_point[2];
	int	point_right[2];
	int	point_down[2];

	get_vector2(mlx_data->pixels.points[i][j], current_point);
	draw_point(image, current_point[0], current_point[1], 0xFF0000); //TODO hmm
	if (i < mlx_data->pixels.n_row - 1)
	{
		get_vector2(mlx_data->pixels.points[i + 1][j], point_down);
		draw_line(image, current_point[0], current_point[1], point_down);
	}
	if (j < mlx_data->pixels.n_col - 1)
	{
		get_vector2(mlx_data->pixels.points[i][j + 1], point_right);
		draw_line(image, current_point[0], current_point[1], point_right);
	}
}

void	draw_pixels(t_image image, t_mlx_data *mlx_data)
{
	int	i;
	int	j;

	i = 0;
	while (i < mlx_data->pixels.n_row)
	{
		j = 0;
		while (j < mlx_data->pixels.n_col)
		{
			draw_segment(image, mlx_data, i, j);
			j++;
		}
		i++;
	}
}
