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

typedef struct	s_mlx_data {
    void    *mlx;
    void    *mlx_win;
}	t_mlx_data;

typedef struct  s_data {
    int i;  //No idea what struct will be inside
}   t_data;

t_data	read_data_file(int argc, char **argv);
int	    main_loop(t_mlx_data mlx_data, t_data data);

#endif
