/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 10:45:14 by mpovill-          #+#    #+#             */
/*   Updated: 2023/12/26 11:42:52 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static void	calculate_values(int p_0[2], int p_f[2], t_draw_line *info)
{
	t_draw_line	b;

	b.x0 = p_0[0];
	b.y0 = p_0[1];
	b.dx = abs(p_f[0] - b.x0);
	b.sx = (b.x0 < p_f[0]) + (b.x0 >= p_f[0]) * -1;
	b.dy = -abs(p_f[1] - b.y0);
	b.sy = (b.y0 < p_f[1]) + (b.y0 >= p_f[1]) * -1;
	b.error = b.dx + b.dy;
	b.point[0] = b.x0;
	b.point[1] = b.y0;
	info[0] = b;
}

static int	ini_degrad(double col_var[3], int color[2], t_draw_line info)
{
	int		red_variation;
	int		green_variation;
	int		blue_variation;
	double	h;
	
	red_variation = (color[1] & 0xFF0000) - (color[0] & 0xFF0000);
	green_variation = (color[1] & 0x00FF00) - (color[0] & 0x00FF00);
	blue_variation = (color[1] & 0x0000FF) - (color[0] & 0x0000FF);
	h = sqrt(info.dx * info.dx + info.dy * info.dy);
	if (h = 0)
		h = 1;
	col_var[0] = 0 + red_variation / h;
	col_var[1] = 0 + green_variation / h;
	col_var[2] = 0 + blue_variation / h;
	return (color[0]);
}

static int	convert_rgb(unsigned char red, unsigned char green, unsigned blue)
{
	return (red << 16 | green << 8 | blue);
}

static int	update_color(int *curr_color, double col_var[3])
{
}

/*
 *	Algorithm that puts pixels between points.
 *	TODO: Need to calculate gradient of color.
 */
void	draw_line(t_image image, int p_0[2], int p_f[2], int color[2])
{
	t_draw_line		b;
	double			color_var[3];
	int				current_color;

	calculate_values(p_0, p_f, &b);
	current_color = ini_degrad(color_var, color, p_0, p_f);
	while (1)
	{
		draw_point(image, b.point, update_color(&current_color, color_var));
		if (b.x0 == p_f[0] && b.y0 == p_f[1])
			break;
		b.error2 = 2 * b.error;
		if (b.error2 >= b.dy && b.x0 != p_f[0])
		{
			b.error += b.dy;
			b.x0 += b.sx;
		}
		if (b.error2 <= b.dx && b.y0 != p_f[1])
		{
			b.error += b.dx;
			b.y0 += b.sy;
		}
		b.point[0] = b.x0;
		b.point[1] = b.y0;	
	}
}

/*
 *	This function puts a pixel on screen. The coordinates of the point are
 *	already calculated, this justs put it.
 */
void	draw_point(t_image image, int coord[2], int color)
{
	char	*dst;

	if (coord[1] >= WIN_WIDTH || coord[1] < 0 
		|| coord[0] >= WIN_HEIGHT || coord[0] < 0)
		return ;
	dst = image.addr + (coord[0] * image.line_len + coord[1] * (image.bpp / 8));
	*(unsigned int*)dst = color;
}
