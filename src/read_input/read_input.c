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
	t_list	*node;
	t_shape	*shape;
	t_space	*space;

	if (argc != 2)
		return (0);
	space = ft_calloc(sizeof(t_space), 1);
	if (space == NULL)
		return (0);
	shape = convert_shape(argv[1]);
	if (shape == NULL)
	{
		free(space);
		return (0);
	}
	node = ft_lstnew(&shape);
	if (node == NULL)
	{
		free(space);
		clear_shape((void *)&shape);
		return (0);
	}
	ft_lstadd_back(&(space->shapes), node);
	data->space = space;
	clear_space(data->space);
	free(space);
	return (1);
}
