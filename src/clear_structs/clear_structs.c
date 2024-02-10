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

//works
void	clear_buffer(t_buffer *buffer)
{
	ft_matclear(&(buffer->points));
	free(buffer);
}

//works
void	clear_point(void *data)
{
	t_point	*point;

	point = (t_point *)data;
	free(point);
}

//works
void	clear_shape(void *data)
{
	t_shape	*shape;

	shape = (t_shape *)data;
	ft_lstclear(&(shape->points), clear_point);
	clear_buffer(shape->buffer);
	free(shape);
}

//works
void	clear_space(t_space space)
{
	clear_shape(space.shape);
}
