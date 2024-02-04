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
t_list	*read_input(int argc, char **argv)
{
	t_list	*node;
	t_shape	*shape;

	if (argc != 2)
		return (NULL);
	shape = convert_shape(argv[1]);
	if (shape == NULL)
		return (NULL);
	node = ft_lstnew(shape);
	if (node == NULL)
	{
		clear_shape((void *)shape);
		return (NULL);
	}
	return (node);
}
