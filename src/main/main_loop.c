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
		printf("a\n");
		rasterize(data);
		printf("z\n");
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->image.img, 0, 0);
		data->rasterize = 0;
	}
    return (0);
}

/*
 *	Here we listen if a key that modifies output has been used.
 *	Or if we end the program.
 */
static int	handle_keys(int keys, t_ctrl_prgrm *data)
{
    if (keys == XK_Escape)
		data->close = 1;
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
	init_matrices(data);
	init_camera(data->space.camera);
	data->rasterize = 1;
	data->close = 0;
	//initialize_view(mlx_data);
	register_hooks(data);
	mlx_loop(data->mlx);
}
