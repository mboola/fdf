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

static void	put_pixel(t_image image, int x, int y, int color)
{
	char	*dst;

	dst = image.addr + (y * image.line_len + x * (image.bpp / 8));
	*(unsigned int*)dst = color;
}

void	rasterize(t_image image, t_list *points)
{
	t_point	*point;
	//for all the pixels in points, put them on the screen
	while (points != NULL)
	{
		//put pixel
		point = (t_point *)(points->content);
		put_pixel(image, point->matrix[0][0], point->matrix[1][1], 0x00FF0000);
		points = points->next;
	}
}