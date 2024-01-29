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
		printf("Rasterizing.\n");
		image.img = mlx_new_image(mlx_data->mlx, WIN_WIDTH, WIN_HEIGHT);
		image.addr = mlx_get_data_addr(image.img, &image.bpp, &image.line_len, &image.endian);
		rasterize(image, mlx_data);
		mlx_put_image_to_window(mlx_data->mlx, mlx_data->mlx_win, image.img, 0, 0);
		free(image.img);
		mlx_data->rasterize = 0;
	}
    return (0);
}

static void	check_traslation(int keys, t_mlx_data *mlx_data)
{
	if (keys == XK_w)
	{
		mlx_data->offset[0] -= mlx_data->scale[0];
		mlx_data->rasterize = 1;
	}
	if (keys == XK_s)
	{
		mlx_data->offset[0] += mlx_data->scale[0];
		mlx_data->rasterize = 1;
	}
	if (keys == XK_a)
	{
		mlx_data->offset[1] -= mlx_data->scale[0];
		mlx_data->rasterize = 1;
	}
	if (keys == XK_d)
	{
		mlx_data->offset[1] += mlx_data->scale[0];
		mlx_data->rasterize = 1;
	}
}

static void	check_rotation(int keys, t_mlx_data *mlx_data)
{
	if (keys == XK_z) //update x rotation
	{
		update_angle_x(mlx_data, 0.05);
		mlx_data->rasterize = 1;
	}
	if (keys == XK_x) //update x rotation
	{
		update_angle_x(mlx_data, -0.05);
		mlx_data->rasterize = 1;
	}
	if (keys == XK_c) //update x rotation
	{
		update_angle_y(mlx_data, 0.05);
		mlx_data->rasterize = 1;
	}
	if (keys == XK_v) //update x rotation
	{
		update_angle_y(mlx_data, -0.05);
		mlx_data->rasterize = 1;
	}
	if (keys == XK_b) //update x rotation
	{
		update_angle_z(mlx_data, 0.05);
		mlx_data->rasterize = 1;
	}
	if (keys == XK_n) //update x rotation
	{
		update_angle_z(mlx_data, -0.05);
		mlx_data->rasterize = 1;
	}
}

static void	check_scale(int keys, t_mlx_data *mlx_data)
{
	if (keys == XK_Up) //update z rotation
	{
		mlx_data->scale[0]++;
		mlx_data->scale[1]++;
		mlx_data->rasterize = 1;
	}
	if (keys == XK_Down) //update z rotation
	{
		mlx_data->scale[0]--;
		mlx_data->scale[1]--;
		mlx_data->rasterize = 1;
	}
	if (keys == XK_Left)
	{
		mlx_data->distorsion -= 0.1;
		mlx_data->rasterize = 1;
	}
	if (keys == XK_Right)
	{
		mlx_data->distorsion += 0.1;
		mlx_data->rasterize = 1;
	}
}

static void	check_view(int keys, t_mlx_data *mlx_data)
{
	if (keys == XK_p)
	{
		mlx_data->view_values.top += 0.1;
		mlx_data->rasterize = 1;
	}
	if (keys == XK_o)
	{
		mlx_data->view_values.top -= 0.1;
		mlx_data->rasterize = 1;
	}
	if (keys == XK_i)
	{
		mlx_data->view_values.down += 0.1;
		mlx_data->rasterize = 1;
	}
	if (keys == XK_u)
	{
		mlx_data->view_values.down -= 0.1;
		mlx_data->rasterize = 1;
	}
	if (keys == XK_l)
	{
		mlx_data->view_values.left += 0.1;
		mlx_data->rasterize = 1;
	}
	if (keys == XK_k)
	{
		mlx_data->view_values.left -= 0.1;
		mlx_data->rasterize = 1;
	}
	if (keys == XK_j)
	{
		mlx_data->view_values.right += 0.1;
		mlx_data->rasterize = 1;
	}
	if (keys == XK_h)
	{
		mlx_data->view_values.right -= 0.1;
		mlx_data->rasterize = 1;
	}
	if (keys == XK_g)
	{
		mlx_data->view_values.near += 0.1;
		mlx_data->rasterize = 1;
	}
	if (keys == XK_f)
	{
		mlx_data->view_values.near -= 0.1;
		mlx_data->rasterize = 1;
	}
	if (keys == XK_e)
	{
		mlx_data->view_values.far += 0.1;
		mlx_data->rasterize = 1;
	}
	if (keys == XK_r)
	{
		mlx_data->view_values.far -= 0.1;
		mlx_data->rasterize = 1;
	}
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
	else
	{
		check_traslation(keys, mlx_data);
		check_rotation(keys, mlx_data);
		check_scale(keys, mlx_data);
		check_view(keys, mlx_data);
	}
    return (0);
}

static void register_hooks(t_mlx_data *mlx_data)
{
    mlx_loop_hook(mlx_data->mlx, &handle_no_event, mlx_data);
    mlx_hook(mlx_data->mlx_win, KeyPress, KeyPressMask, &handle_input, mlx_data);
}

/*
 *	This method will initialize all the data needed to rasterize pixels.
 *	Then it will create a loop giving the end condition to the user.
 */
int	main_loop(t_mlx_data *mlx_data)
{
	initialize_matrices(mlx_data);
	mlx_data->rasterize = 1;
	mlx_data->close = 0;
	initialize_view(mlx_data);
	register_hooks(mlx_data);
	mlx_loop(mlx_data->mlx);
	return (1);
}
