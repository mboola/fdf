/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 10:45:14 by mpovill-          #+#    #+#             */
/*   Updated: 2023/12/26 11:42:52 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

/*
 *	This gets executed each frame. It finishes the application if it is
 *	requested by the user. If not, it checks if points need to be
 *	rasterized.
 */
static int	handle_no_event(t_ctrl_prgrm *data)
{
	if (data->close)
		mlx_loop_end(data->mlx);
	else if (data->rasterize)
	{
		printf("Rasterizing.\n");
		vblank_buffer(data);
		rasterize(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->image.img, 0, 0);
		data->rasterize = 0;
	}
    return (0);
}

static void	check_shape(int keys, t_ctrl_prgrm *data)
{
	if (keys == XK_z)
	{
		((t_shape *)(data->space.shape))->angle_x += 0.1;
		data->rasterize = 1;
	}
	else if (keys == XK_x)
	{
		((t_shape *)(data->space.shape))->angle_x -= 0.1;
		data->rasterize = 1;
	}
	else if (keys == XK_w)
	{
		((t_shape *)(data->space.shape))->translate[0]--;
		data->rasterize = 1;
	}
	else if (keys == XK_s)
	{
		((t_shape *)(data->space.shape))->translate[0]++;
		data->rasterize = 1;
	}
	else if (keys == XK_a)
	{
		((t_shape *)(data->space.shape))->translate[1]--;
		data->rasterize = 1;
	}
	else if (keys == XK_d)
	{
		((t_shape *)(data->space.shape))->translate[1]++;
		data->rasterize = 1;
	}
	else if (keys == XK_q)
	{
		((t_shape *)(data->space.shape))->scale[0]++;
		((t_shape *)(data->space.shape))->scale[1]++;
		data->rasterize = 1;
	}
	else if (keys == XK_e)
	{
		((t_shape *)(data->space.shape))->scale[0]--;
		((t_shape *)(data->space.shape))->scale[1]--;
		data->rasterize = 1;
	}
}

/*
 *	Here we listen if a key that modifies output has been used.
 *	Or if we end the program.
 */
static int	handle_keys(int keys, t_ctrl_prgrm *data)
{
    if (keys == XK_Escape)
		data->close = 1;
	else if (keys == XK_r)
		data->reverse = data->reverse * -1;
	else
	{
		check_shape(keys, data);
	}
	return (0);
}

static void register_hooks(t_ctrl_prgrm *data)
{
    mlx_loop_hook(data->mlx, &handle_no_event, data);
    mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &handle_keys, data);
}

/*
 *	This method will initialize all the data needed to rasterize pixels.
 *	Then it will create a loop giving the end condition to the user.
 */
void	main_loop(t_ctrl_prgrm *data)
{
	init_matrices(&(data->space));
	init_view(data);
	//init_camera(&(data->space.camera));	//set projection
	data->rasterize = 1;
	data->close = 0;
	data->reverse = 0;
	register_hooks(data);
	mlx_loop(data->mlx);
}
