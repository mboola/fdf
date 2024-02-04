/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_shape.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 10:45:14 by mpovill-          #+#    #+#             */
/*   Updated: 2023/12/26 11:42:52 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static t_buffer	*initialize_buffer(t_list *lst)
{
	t_buffer	*buffer;
	t_list		*node;
	t_point		*arr;
	int			i;

	buffer = malloc(sizeof(t_buffer));
	if (buffer == NULL)
		return (NULL);
	node = lst;
	i = 0;
	while (node != NULL)
	{
		i++;
		node = node->next;
	}
	buffer->n_row = i;
	arr = (t_point *)lst->content;
	i = 0;
	while (arr[i].vector[0] != -1)
		i++;
	buffer->n_col = i;
	buffer->points = ft_calloc_matstruct(sizeof(t_projected), buffer->n_row, buffer->n_col);
	if (buffer->points == NULL)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

t_shape	*initialize_shape(t_shape *shape, t_list *lst)
{
	t_buffer	*buffer;

	buffer = initialize_buffer(lst);
	if (buffer == NULL)
	{
		ft_lstclear(&lst, clear_point);
		free(shape);
		return (NULL);
	}
	shape->points = lst;
	shape->buffer = buffer;
	shape->angle_x = 0;
	shape->angle_y = 0;
	shape->angle_z = 0;
	return (shape);
}