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


/*
 *	Algorithm that puts pixels between points.
 *	TODO: Need to calculate gradient of color.
 */
void	draw_line(t_image image, int p_0[2], int p_f[2], int color[2])
{
	t_draw_line		b;

	calculate_values(p_0, p_f, &b);
	while (1)
	{
		draw_point(image, b.point, color[0]);
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
