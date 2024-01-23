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
static int	handle_no_event(t_mlx_data *mlx_data)
{
	t_image	image;

	if (mlx_data->close)
		mlx_loop_end(mlx_data->mlx);
	else if (mlx_data->rasterize)
	{
		image.img = mlx_new_image(mlx_data->mlx, WIN_WIDTH, WIN_HEIGHT);
		image.addr = mlx_get_data_addr(image.img, &image.bpp, &image.line_len, &image.endian);
		rasterize(image, mlx_data);
		mlx_put_image_to_window(mlx_data->mlx, mlx_data->mlx_win, image.img, 0, 0);
		free(image.img);
		mlx_data->rasterize = 0;
	}
    return (0);
}

/*
 *  Using mlx_loop_end creates a leak. Not my problem, caused by mlx lib.
 *	Here we listen if a key that modifies output has been used.
 *	Or if we end the program.
 */
static int	handle_input(int keys, t_mlx_data *mlx_data)
{
    if (keys == XK_Escape) // or closed clicking X in the windows
		mlx_data->close = 1;
	if (keys == XK_a) //update x rotation
	{
		mlx_data->angle_x += 0.1;
		mlx_data->rasterize = 1;
	}
	if (keys == XK_b) //update y rotation
	{
		mlx_data->angle_y += 0.1;
		mlx_data->rasterize = 1;
	}
	if (keys == XK_c) //update z rotation
	{
		mlx_data->angle_z += 0.1;
		mlx_data->rasterize = 1;
	}
	if (keys == XK_d) //update x scale
	{
		//mlx_data->angle_z += 0.1;
		mlx_data->rasterize = 1;
	}
	if (keys == XK_e) //update y scale
	{
		//mlx_data->angle_z += 0.1;
		mlx_data->rasterize = 1;
	}
	if (keys == XK_f) //update z scale
	{
		//mlx_data->angle_z += 0.1;
		mlx_data->rasterize = 1;
	}
	if (keys == XK_g) //update x translation positive
	{
		//mlx_data->angle_z += 0.1;
		mlx_data->rasterize = 1;
	}
	if (keys == XK_h) //update x translation negative
	{
		//mlx_data->angle_z += 0.1;
		mlx_data->rasterize = 1;
	}
	if (keys == XK_i) //update y translation positive
	{
		//mlx_data->angle_z += 0.1;
		mlx_data->rasterize = 1;
	}
	if (keys == XK_j) //update y translation negative
	{
		//mlx_data->angle_z += 0.1;
		mlx_data->rasterize = 1;
	}
    return (0);
}

static void register_hooks(t_mlx_data *mlx_data)
{
    mlx_loop_hook(mlx_data->mlx, &handle_no_event, mlx_data);
    mlx_hook(mlx_data->mlx_win, KeyPress, KeyPressMask, &handle_input, mlx_data);
}

/*
 *	This initializes the scale, the translation (offset)
 *	and sets the flag to be rasterized.
 *	TODO: calculate offset to it is centered
 */
static void	initialize_data(t_mlx_data *mlx_data)
{
	mlx_data->scale[0] = 1;
	mlx_data->scale[1] = 1;
	mlx_data->scale[2] = 1;
	mlx_data->offset[0] = WIN_WIDTH / 2;
	mlx_data->offset[1] = WIN_HEIGHT / 2;
	mlx_data->offset[2] = 0;
	mlx_data->rasterize = 1;
	mlx_data->close = 0;
}

/*
 *	This method will initialize all the data needed to rasterize pixels.
 *	Then it will create a loop giving the end condition to the user.
 */
int	main_loop(t_mlx_data *mlx_data)
{
	initialize_matrices(mlx_data);
	initialize_view(mlx_data);
	initialize_data(mlx_data);
	register_hooks(mlx_data);
	mlx_loop(mlx_data->mlx);
	return (1);
}
