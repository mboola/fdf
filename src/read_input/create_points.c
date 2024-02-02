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

static unsigned char	transform_color(char **str, char *err)
{
	char	value[3];

	if (**str == '\0')
		return (0xFF);
	value[0] = **str;
	(*str)++;
	if (**str == '\0')
	{
		*err = 1;
		return (0);
	}
	value[1] = **str;
	(*str)++;
	value[2] = '\0';
	if (ft_strchr(HEXHIGHBASE, value[0]) && ft_strchr(HEXHIGHBASE, value[1]))
		return (ft_atoi_base(value, HEXHIGHBASE));
	if (ft_strchr(HEXLOWBASE, value[0]) && ft_strchr(HEXLOWBASE, value[1]))
		return (ft_atoi_base(value, HEXLOWBASE));
	*err = 1;
	return (0);
}

static int	convert_rgb(unsigned char red, unsigned char green, unsigned blue)
{
	return (red << 16 | green << 8 | blue);
}

static int	convert_color(char *str)
{
	char			*color;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	char			err;

	color = ft_strchr(str, ',');
	if (color == NULL)
		return (0xFFFFFF);
	color++;
	if (!ft_strncmp(color, "0x", 2))
		return (0xFFFFFF);
	color += 2;
	red = transform_color(&color, &err);
	if (err)
		return (0);
	green = transform_color(&color, &err);
	if (err)
		return (0);
	blue = transform_color(&color, &err);
	if (err)
		return (0);
	return (convert_rgb(red, green, blue));
}

static t_point	new_point(int col, int row, char *z)
{
	t_point	point;

	point.vector[0] = row;
	point.vector[1] = col;
	point.vector[2] = ft_atoi(z);
	point.color = convert_color(z);
	//printf("Vector: %d, %d, %d; Color: %d\n", point.vector[0], point.vector[1], point.vector[2], point.color);
	return (point);
}

t_list	*create_points(char **mat, int n_col, int n_row)
{
	t_point	*points;
	t_list	*node;
	int		i;

	points = ft_calloc(sizeof(t_point), n_col + 1);
	if (points == NULL)
		return (NULL);
	i = 0;
	while (i < n_col)
	{
		points[i] = new_point(i, n_row, *(mat + i));
		i++;
	}
	points[n_col].vector[0] = -1;
	points[n_col].vector[1] = -1;
	points[n_col].vector[2] = -1;
	points[n_col].color = -1;
	node = ft_lstnew(points);
	if (node == NULL)
		free(points);
	return (node);
}
