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
static void	draw_point(t_image image, int coord[2], int color)
{
	char	*dst;

	if (coord[1] > WIN_HEIGHT || coord[1] < 0 
		|| coord[0] > WIN_WIDTH || coord[0] < 0)
		return ;
	dst = image.addr + (coord[1] * image.line_len + coord[0] * (image.bpp / 8));
	*(unsigned int*)dst = color;
}

static void	calculate_values(int p_0[2], int p_f[2], t_draw_line *info)
{
	info->d[0] = abs(p_f[0] - p_0[0]);
	info->d[1] = abs(p_f[1] - p_0[1]);
	info->s[0] = (p_0[0] < p_f[0]) + (p_0[0] >= p_f[0]) * -1;
	info->s[1] = (p_0[1] < p_f[1]) + (p_0[1] >= p_f[1]) * -1;
}

/*
 *	
 */
static void	draw_line(t_image image, int p_0[2], int p_f[2], int color[2])
{
	t_draw_line	info;
	int	d[2];
	int	s[2];
	int	prec[2];
	int	x0;
	int	y0;

	calculate_values(p_0, p_f, &info);
	prec[0] = (d[0] > d[1]) * (d[0] / 2) + (d[0] <= d[1]) * (-d[1] / 2);
	while (x0 != p_f[0] && y0 != p_f[1])
	{
		draw_point(image, p_0, 0xFF0000);
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
