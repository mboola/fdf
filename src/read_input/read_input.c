/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 10:45:14 by mpovill-          #+#    #+#             */
/*   Updated: 2023/12/26 11:42:52 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static char	**separate_digits(char **line)
{
	char	**mat;
	char	*trimmed_line;

	trimmed_line = ft_strtrim(*line, " \n");
	free(*line);
	if (trimmed_line == NULL)
		return (NULL);
	mat = ft_split(trimmed_line, ' ');
	free(trimmed_line);
	return (mat);
}

static t_list	*process_line(char **line, int *n_col, int n_row)
{
	char	**mat;
	t_list	*arr_points;

	mat = separate_digits(line);
	if (mat == NULL)
	{
		*n_col = 0;
		return (NULL);
	}
	*n_col = ft_matlen((void **)mat);
	arr_points = NULL;
	if (*n_col > 0)
		arr_points = create_points(mat, *n_col, n_row);
	ft_matclear((void ***)&mat);
	return (arr_points);
}

static t_list	*end_converting(int fd, t_list **lst, int ref_col, int n_col)
{
	int		n_row;
	char	*line;
	t_list	*node;

	n_row = 1;
	line = get_next_line(fd, 0);
	while (line != NULL)
	{
		node = process_line(&line, &n_col, n_row);
		if (n_col != ref_col && node != NULL)
		{
			clear_point((node->content));
			free(node);
			node = NULL;
		}
		if (node == NULL)
		{
			ft_lstclear(lst, clear_point);
			return (NULL);
		}
		ft_lstadd_back(lst, node);
		n_row++;
		line = get_next_line(fd, 0);
	}
	return (*lst);
}

/*
 *	Creates a linked list with an array of points as a node.
 */
static	t_list	*convert_points(int fd)
{
	t_list	*lst;
	t_list	*node;
	char	*line;
	int		n_col;

	lst = NULL;
	line = get_next_line(fd, 0);
	if (line == NULL)
		return (NULL);
	node = process_line(&line, &n_col, 0);
	if (node == NULL)
		return (NULL);
	ft_lstadd_back(&lst, node);
	return (end_converting(fd, &lst, n_col, n_col));
}

/*
 *	Read the file and return a t_shape if valid.
 */
t_shape	*read_input(char *file)
{
	t_shape	*shape;
	int		fd;
	t_list	*lst;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	shape = ft_calloc(sizeof(t_shape), 1);
	if (shape != NULL)
	{
		lst = convert_points(fd);
		if (lst == NULL)
		{
			free(shape);
			get_next_line(fd, 1);
			shape = NULL;
		}
		else
			shape = init_shape(shape, lst);
	}
	close(fd);
	return (shape);
}
