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
	if (mlx_data->rasterize)
	{
		//create a new image and rasterize it
		mlx_data->rasterize = 0;
	}
    /* This function needs to exist, but it is useless for the moment */
    //mlx_put_image_to_window(mlx_data->mlx, mlx_data->mlx_img.win, img.img, 0, 0);
    return (0);
}

/*
 *  Using mlx_loop_end creates a leak. Not my problem, caused by mlx lib.
 */
static int	handle_input(int keys, t_mlx_data *mlx_data)
{
    if (keys == XK_Escape)
		//if (mlx_data && mlx_data->mlx != NULL)
    	mlx_loop_end(mlx_data->mlx);
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
	register_hooks(mlx_data);
	mlx_loop(mlx_data->mlx);
	return (1);
}

//image.img = mlx_new_image(mlx_data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	//image.addr = mlx_get_data_addr(image.img, &image.bpp, &image.line_len,
	//							&image.endian);
	//mlx_destroy_image(mlx_data.mlx, image.img);
