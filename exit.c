/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/15 13:08:54 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/04/06 13:15:02 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_exit(mlx_t *mlx, mlx_image_t *img, t_point *map, char *errmsg)
{
	free_map(map);
	if (mlx && img)
		mlx_delete_image(mlx, img);
	if (mlx)
		mlx_terminate(mlx);
	if (!errmsg)
		exit(EXIT_SUCCESS);
	write(2, "Error: ", 7);
	write(2, errmsg, ft_strlen(errmsg));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	free_map(t_point *map)
{
	t_point	*temp;

	while (map)
	{
		temp = map;
		map = map->next;
		free(temp);
	}
}

void	free_split_line(char **split_line)
{
	int	i;

	i = 0;
	while (split_line[i])
		free(split_line[i++]);
	free(split_line);
}
