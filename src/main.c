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

static int	clear_data(t_list **points, void *mlx)
{
	ft_lstclear(points, clear_point);
	mlx_destroy_display(mlx);
	free(mlx);
	return (0);
}

//
static void	print_info(void *info)
{
	t_point	*point;
	int		test;

	point = (t_point *)info;
	ft_printf(1, "X=%d, Y=%d, Z=%d\n", point->matrix[0][0], point->matrix[1][1], point->matrix[2][2]);
}

int main(int argc, char **argv)
{
	t_list		*points;
	t_mlx_data	mlx_data;
	t_image		image;

	points = read_data_file(argc, argv);
	if (points == NULL)
		return (0);
	ft_lstiter(points, print_info);
	mlx_data.mlx = mlx_init();
	if (mlx_data.mlx == NULL)
		return (clear_data(&points, NULL));
	mlx_data.mlx_win = mlx_new_window(mlx_data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
	if (mlx_data.mlx_win == NULL)
		return (clear_data(&points, mlx_data.mlx));
	//image.img = mlx_new_image(mlx_data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	//image.addr = mlx_get_data_addr(image.img, &image.bpp, &image.line_len,
	//							&image.endian);
	//mlx_destroy_image(mlx_data.mlx, image.img);
	//ft_lstiter(points, print_info);
	main_loop(mlx_data, points);
	mlx_destroy_window(mlx_data.mlx, mlx_data.mlx_win);
	return (clear_data(&points, mlx_data.mlx));
}
