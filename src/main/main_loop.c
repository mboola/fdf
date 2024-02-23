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
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		clear_data(&data);
	}
	else if (data->rasterize)
	{
		rasterize(data);
		mlx_put_image_to_window(data->mlx,
			data->mlx_win, data->image.img, 0, 0);
		data->rasterize = 0;
	}
	return (0);
}

static int	close_program(t_ctrl_prgrm *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	clear_data(&data);
	return (0);
}

static void	register_hooks(t_ctrl_prgrm *data)
{
	mlx_loop_hook(data->mlx, &handle_no_event, data);
	mlx_hook(data->mlx_win, 17, 0, &close_program, data);
	mlx_hook(data->mlx_win, 2, 0, &handle_keys, data);
}

/*
 *	This method will initialize all the data needed to rasterize pixels.
 *	Then it will create a loop giving the end condition to the user.
 */
void	main_loop(t_ctrl_prgrm *data)
{
	init_matrices(&(data->space));
	init_view(data);
	data->close = 0;
	data->reverse = 1;
	data->multiplier = 1;
	register_hooks(data);
	mlx_loop(data->mlx);
}
