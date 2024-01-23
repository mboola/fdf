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
	info->d[0] = abs(p_f[0] - p_0[0]);
	info->d[1] = abs(p_f[1] - p_0[1]);
	info->s[0] = (p_0[0] < p_f[0]) + (p_0[0] >= p_f[0]) * -1;
	info->s[1] = (p_0[1] < p_f[1]) + (p_0[1] >= p_f[1]) * -1;
	info->prec[0] = (d[0] > d[1]) * (d[0] / 2) + (d[0] <= d[1]) * (-d[1] / 2);
	info->point[0] = p_0[0];
	info->point[1] = p_0[1];
}

/*
 *	Algorithm that puts pixels between points.
 *	TODO: Need to calculate gradient of color.
 */
void	draw_line(t_image image, int p_0[2], int p_f[2], int color[2])
{
	t_draw_line	info;

	calculate_values(p_0, p_f, &info);
	while (info.point[0] != p_f[0] && info.point[1] != p_f[1])
	{
		draw_point(image, info.point, 0xFF0000);
		info.prec[1] = info.prec[0];
		if (info.prec[1] > -info.d[0])
		{
			info.prec[0] -= info.d[1];
			info.point[0] += info.s[0];
		}
		if (info.prec[1] < info.d[1])
		{
			info.prec[0] += info.d[0];
			info.point[1] += info.s[1];
		}
	}
}

/*
 *	This function puts a pixel on screen. The coordinates of the point are
 *	already calculated, this justs put it.
 */
void	draw_point(t_image image, int coord[2], int color)
{
	char	*dst;

	if (coord[1] > WIN_HEIGHT || coord[1] < 0 
		|| coord[0] > WIN_WIDTH || coord[0] < 0)
		return ;
	dst = image.addr + (coord[1] * image.line_len + coord[0] * (image.bpp / 8));
	*(unsigned int*)dst = color;
}
