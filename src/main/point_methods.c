/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 10:45:14 by mpovill-          #+#    #+#             */
/*   Updated: 2023/12/26 11:42:52 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

//not currently used
t_list	*new_point(int row, int col, int num, char *err)
{
	t_point	*point;
	t_list	*node;

	if (*err)
		return (NULL);
	point = malloc(sizeof(t_point));
	if (point == NULL)
	{
		*err = 1;
		return (NULL);
	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//here I set the X,Y,Z coord, but for the moment I dont know how
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	point->vector[0] = row;
	point->vector[1] = col;
	point->vector[2] = num;
	node = ft_lstnew(point);
	if (node == NULL)
	{
		free(point);
		*err = 1;
	}
	return (node);
}

void	clear_point(void *point)
{
	free(point);
}
