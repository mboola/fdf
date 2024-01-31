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

/*
 *	Clears the struct created to run the application.
 */
static void	clear_data(t_ctrl_prgrm **data)
{
	clear_space((*data)->space);
	//ft_lstclear(&((*mlx_data)->points), clear_point);
	//mlx_destroy_window(mlx_data->mlx, mlx_data->mlx_win);
	//mlx_destroy_display((*mlx_data)->mlx);
	//free((*data)->mlx);
	free(*data);
	exit(0);
}

static void	print_info(t_shape *shape)
{
	t_list	*points;	//array of pointers
	t_point	*point;
	int		i;

	points = shape->points;
	while (points != NULL)
	{

		points = points->next;
	}
	i = 0;
	point = (t_point *)info;
	while (point[i].vector[0] != -1)
	{
		ft_printf(1, "X=%d, Y=%d, Z=%d\n", point[i].vector[0], point[i].vector[1], point[i].vector[2]);
		i++;
	}
	//ft_printf(1, "\n");
}

/*
 *	Main function. Reads the file into a matrix of points.
 *	Creates a struct that will hold all the information to create a window
 *	and put pixels to it. Clears the struct when ended.
 */
int main(int argc, char **argv)
{
	t_ctrl_prgrm	*data;

	data = ft_calloc(sizeof(t_ctrl_prgrm), 1);
	if (data == NULL)
		return (0);
	if (!read_input(argc, argv, data))
		clear_data(&data);
	ft_lstiter((t_shape)(data->space.shapes->content), print_info);
	//data->mlx = mlx_init();
	//if (data->mlx == NULL)
	//	clear_data(&data);
	//data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	//if (data->mlx_win == NULL)
	//	clear_data(&data);
	//main_loop(mlx_data);
	//mlx_destroy_window(mlx_data->mlx, mlx_data->mlx_win);
	//return (clear_data(&mlx_data));
	clear_data(&data);
	return (0);
}
