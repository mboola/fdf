/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:25:02 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 11:25:13 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"

# define WINDOW_WIDTH 600
# define WINDOW_HEIGHT 300
# define WINDOW_NAME "FDF"

typedef struct	s_image {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

typedef struct	s_mlx_data {
	void	*mlx;
	void	*mlx_win;
	t_list	*points;
	char	rasterize;
}	t_mlx_data;

typedef struct  s_point {
	int	matrix[4][4];
	int	color;
}	t_point;

t_list	*read_data_file(int argc, char **argv);
int		main_loop(t_mlx_data *mlx_data);
t_list	*new_point(int row, int col, int num, char *err);
void	clear_point(void *point);
void	rasterize(t_image image, t_list *points);

#endif
