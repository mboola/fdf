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

static void	initialize_mat(double mat[4][4])
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mat[i][j] = 0;
			j++;
		}
		i++;
	}
}

static void	initialize_arr(double arr[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		arr[i] = 0;
		i++;
	}
}

void	initialize_shape(t_shape *shape, t_list *lst)
{
	shape->points = lst;
	shape->buffer = NULL;
	shape->angle_x = 0;
	shape->angle_y = 0;
	shape->angle_z = 0;
	initialize_arr(shape->scale);
	initialize_arr(shape->translate);
	initialize_mat(shape->transformation_matrix);
}