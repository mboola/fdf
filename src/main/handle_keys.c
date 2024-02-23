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

static void	update_value(double *value, double add, char reverse)
{
	if (reverse > 0)
		*value += add;
	else
		*value -= add;
}

static int	check_angles(int keys, t_ctrl_prgrm *data)
{
	t_shape	*shape;

	shape = (t_shape *)(data->space.shape);
	if (keys == XK_X)
		update_value(&(shape->angle_x), 0.1 * data->multiplier, data->reverse);
	else if (keys == XK_Y)
		update_value(&(shape->angle_y), 0.1 * data->multiplier, data->reverse);
	else if (keys == XK_Z)
		update_value(&(shape->angle_z), 0.1 * data->multiplier, data->reverse);
	else
		return (0);
	data->rasterize = 1;
	return (1);
}

static void	update_altitude(double *altitude, char reverse)
{
	if (reverse > 0 && *altitude > 0.2)
		*altitude -= 0.1;
	else if (reverse <= 0 && *altitude < 2)
		*altitude += 0.1;
}

static int	check_transformation(int keys, t_ctrl_prgrm *data)
{
	t_shape	*shape;

	shape = (t_shape *)(data->space.shape);
	if (keys == XK_W)
		shape->translate[0] -= data->multiplier;
	else if (keys == XK_S)
		shape->translate[0] += data->multiplier;
	else if (keys == XK_A)
		shape->translate[1] -= data->multiplier;
	else if (keys == XK_D)
		shape->translate[1] += data->multiplier;
	else if (keys == XK_Q && ((data->reverse < 0 && shape->scale[0] > 0.2)
			|| data->reverse >= 0))
	{
		update_value(&(shape->scale[0]), data->multiplier, data->reverse);
		update_value(&(shape->scale[1]), data->multiplier, data->reverse);
	}
	else if (keys == XK_R)
		update_altitude(&(data->space.camera.altitude), data->reverse);
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
	if (keys == XK_ESCAPE)
		data->close = 1;
	else if (keys == XK_TAB)
		data->reverse = data->reverse * -1;
	else if (keys == XK_UP && data->multiplier < 10)
		data->multiplier++;
	else if (keys == XK_DOWN && data->multiplier > 1)
		data->multiplier--;
	else if (keys == XK_I)
		set_isometric_view(data);
	else if (check_angles(keys, data))
		return (0);
	else if (check_transformation(keys, data))
		return (0);
	return (0);
}
