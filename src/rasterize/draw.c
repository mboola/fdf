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

static int	calculate_values(int p_0[2], int p_f[2], t_draw_line *info, int *c)
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
	*c = 0;
	return (sqrt((p_f[0] - p_0[0]) * (p_f[0] - p_0[0])
			+ (p_f[1] - p_0[1]) * (p_f[1] - p_0[1])));
}

static int	calc_color(int color[2], double total_steps, int curr_step)
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;

	red = ((color[1] & 0xFF0000) - (color[0] & 0xFF0000)) >> 16;
	green = ((color[1] & 0x00FF00) - (color[0] & 0x00FF00)) >> 8;
	blue = (color[1] & 0x0000FF) - (color[0] & 0x0000FF);
	if (total_steps == 0)
		total_steps = 1;
	return (color[0] + (((int)((double)(red * curr_step) / total_steps) << 16)
		| ((int)((double)(green * curr_step) / total_steps) << 8)
		| ((int)((double)(blue * curr_step) / total_steps))));
}

/*
 *	Algorithm that puts pixels between points. (Bresenham)
 *	TODO: Need to calculate gradient of color.
 */
void	draw_line(t_image image, int p_0[2], int p_f[2], int color[2])
{
	t_draw_line	b;
	double		total_steps;
	int			curr_step;

	total_steps = calculate_values(p_0, p_f, &b, &curr_step);
	while (1)
	{
		draw_point(image, b.point, calc_color(color, total_steps, curr_step));
		curr_step++;
		if (b.x0 == p_f[0] && b.y0 == p_f[1])
			break ;
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
	*(unsigned int *)dst = color;
}

void	vblank_buffer(t_ctrl_prgrm *data)
{
	t_image	image;

	image = data->image;
	ft_bzero((void *)image.addr, WIN_HEIGHT * data->image.line_len
		+ WIN_WIDTH * (data->image.bpp / 8));
}
