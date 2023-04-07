/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   projection.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 10:34:18 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/04/05 13:21:52 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_projection(t_fdf *fdf, int key)
{
	fdf->x_rotation = 0;
	fdf->y_rotation = 0;
	fdf->z_rotation = 0;
	if (key == MLX_KEY_I)
		fdf->projection = ISOMETRIC;
	if (key == MLX_KEY_P)
		fdf->projection = PARALLEL;
}

void	isometric(t_point *point)
{
	double	new_x;
	double	new_y;

	new_x = (point->x - point->y) * cos(0.523599);
	new_y = (point->x + point->y) * sin(0.523599) - point->z;
	point->x = new_x;
	point->y = new_y;
}
