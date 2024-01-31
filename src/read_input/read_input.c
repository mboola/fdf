/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 10:45:14 by mpovill-          #+#    #+#             */
/*   Updated: 2023/12/26 11:42:52 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

/*
 *	Read the file.
 */
int	read_input(int argc, char **argv, t_ctrl_prgrm *data)
{
	t_list	*lst;
	t_list	*node;
	t_shape	*shape;

	if (argc != 2)
		return (0);
	shape = convert_shape(argv[1]);
	if (shape == NULL)
		return (0);
	node = ft_lstnew(shape);
	if (node == NULL)
	{
		ft_lstclear(&(shape->points), clear_point);
		free(shape);
		return (0);
	}
	lst = NULL;
	ft_lstadd_back(&lst, node);
	data->space.shapes = lst;
	return (1);
}
