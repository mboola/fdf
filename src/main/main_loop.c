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

static int	handle_no_event(t_mlx_data *mlx_data)
{
	t_image	image;

	mlx_data->angle_x += 0.1;
	mlx_data->rasterize = 1;
	if (mlx_data->close)
		mlx_loop_end(mlx_data->mlx);
	else if (mlx_data->rasterize)
	{
		image.img = mlx_new_image(mlx_data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
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
 */
static int	handle_input(int keys, t_mlx_data *mlx_data)
{
    if (keys == XK_Escape)
		mlx_data->close = 1;
		//if (mlx_data && mlx_data->mlx != NULL)
    	//mlx_loop_end(mlx_data->mlx);
	//here will be more ifs with rotating and escalating and whatever. when pressed, they will set
	//mlx_data->rasterize to 1
    return (0);
}

static void register_hooks(t_mlx_data *mlx_data)
{
    mlx_loop_hook(mlx_data->mlx, &handle_no_event, mlx_data);
    mlx_hook(mlx_data->mlx_win, KeyPress, KeyPressMask, &handle_input, mlx_data);
}

/*
 *	This method will initialize all the hooks needed and start the aplication
 */
int	main_loop(t_mlx_data *mlx_data)
{
	mlx_data->rasterize = 1;
	mlx_data->close = 0;
	mlx_data->offset[0] = WINDOW_WIDTH / 2;		//TODO: substract to this the num_col / 2
	mlx_data->offset[1] = WINDOW_HEIGHT / 2;
	mlx_data->scale = 10; 						//this has a limit. if it tries to put a pixel ouside the window it crashes
	set_projection(mlx_data);
	set_rotation_x(mlx_data);
	set_rotation_y(mlx_data);
	set_rotation_z(mlx_data);
	set_isometric_view(mlx_data);
	register_hooks(mlx_data);
	mlx_loop(mlx_data->mlx);
	return (1);
}
