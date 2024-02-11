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

static void	update_value(double *angle, double add, char reverse)
{
	if (reverse > 0)
		*angle += add;
	else
		*angle -= add;
}

static int	check_angles(int keys, t_ctrl_prgrm *data)
{
	t_shape	*shape;

	shape = (t_shape *)(data->space.shape);
	if (keys == XK_x)
		update_value(&(shape->angle_x), 0.1 * data->multiplier, data->reverse);
	else if (keys == XK_y)
		update_value(&(shape->angle_y), 0.1 * data->multiplier, data->reverse);
	else if (keys == XK_z)
		update_value(&(shape->angle_z), 0.1 * data->multiplier, data->reverse);
	else
		return (0);
	data->rasterize = 1;
	return (1);
}

static int	check_transformation(int keys, t_ctrl_prgrm *data)
{
	t_shape	*shape;

	shape = (t_shape *)(data->space.shape);
	if (keys == XK_w)
		shape->translate[0] -= data->multiplier;
	else if (keys == XK_s)
		shape->translate[0] += data->multiplier;
	else if (keys == XK_a)
		shape->translate[1] -= data->multiplier;
	else if (keys == XK_d)
		shape->translate[1] += data->multiplier;
	else if (keys == XK_q)
	{
		update_value(&(shape->scale[0]), data->multiplier, data->reverse);
		update_value(&(shape->scale[1]), data->multiplier, data->reverse);
	}
	else
		return (0);
	data->rasterize = 1;
	return (1);
}

/*
 *	Here we listen if a key that modifies output has been used.
 *	Or if we end the program.
 */
int	handle_keys(int keys, t_ctrl_prgrm *data)
{
    if (keys == XK_Escape)
		data->close = 1;
	else if (keys == XK_Tab)
		data->reverse = data->reverse * -1;
	else if (keys == XK_Up && data->multiplier < 10)
		data->multiplier++;
	else if (keys == XK_Down && data->multiplier > 1)
		data->multiplier--;
	else if (keys == XK_i)
		set_isometric_view(data);
	else if (keys == XK_c)
		set_cavalier_view(data);
	else if (check_angles(keys, data))
		return (0);
	else if (check_transformation(keys, data))
		return (0);
	return (0);
}
