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

void	clear_buffer(t_buffer *buffer)
{
	ft_matclear(&(buffer->points));
	free(buffer);
}

void	clear_point(void *data)
{
	t_point	*point;

	point = (t_point *)data;
	free(point);
}

void	clear_shape(t_shape *shape)
{
	ft_lstclear(&(shape->points), clear_point);
	clear_buffer(shape->buffer);
	free(shape);
}

/*
 *	Clears the struct created to run the application.
 */
void	clear_data(t_ctrl_prgrm **data)
{
	if ((*data)->mlx != NULL)
		free((*data)->mlx);
	if ((*data)->space.shape != NULL)
		clear_shape((*data)->space.shape);
	free(*data);
	exit(0);
}
