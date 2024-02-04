/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 10:45:14 by mpovill-          #+#    #+#             */
/*   Updated: 2023/12/26 11:42:52 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	clear_buffer(void *data)
{
	t_buffer	*buffer;

	buffer = (t_buffer *)buffer;
	if (buffer->points != NULL)
		ft_matclear((void ***)&(buffer->points));
}

//works
void	clear_point(void *data)
{
	t_point	*point;

	point = (t_point *)data;
	free(point);
}

//works. buffer needs testing
void	clear_shape(void *data)
{
	t_shape	*shape;

	shape = (t_shape *)data;
	ft_lstclear(&(shape->points), clear_point);
	//clear_buffer(shape->buffer);
	free(shape);
}

void	clear_space(t_space space)
{
	ft_lstclear(&(space.shapes), clear_shape);
}
