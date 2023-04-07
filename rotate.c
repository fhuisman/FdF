/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 13:18:33 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/04/05 10:34:12 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	x_rotation(t_point *point, int degrees)
{
	double	new_y;
	double	new_z;
	double	radians;

	radians = degrees * M_PI / 180;
	new_y = point->y * cos(radians) + point->z * sin(radians);
	new_z = point->y * sin(radians) + point->z * cos (radians);
	point->y = new_y;
	point->z = new_z;
}

void	y_rotation(t_point *point, int degrees)
{
	double	new_x;
	double	new_z;
	double	radians;

	radians = degrees * M_PI / 180;
	new_x = point->x * cos(radians) + point->z * sin(radians);
	new_z = point->x * sin(radians) + point->z * cos(radians);
	point->x = new_x;
	point->z = new_z;
}

void	z_rotation(t_point *point, int degrees)
{
	double	new_x;
	double	new_y;
	double	radians;

	radians = degrees * M_PI / 180;
	new_x = point->x * cos(radians) - point->y * sin(radians);
	new_y = point->x * sin(radians) + point->y * cos(radians);
	point->x = new_x;
	point->y = new_y;
}

void	rotate(t_fdf *fdf, int key)
{
	if (key == MLX_KEY_A)
		fdf->y_rotation -= 2;
	if (key == MLX_KEY_S)
		fdf->x_rotation -= 2;
	if (key == MLX_KEY_D)
		fdf->y_rotation += 2;
	if (key == MLX_KEY_W)
		fdf->x_rotation += 2;
	if (key == MLX_KEY_Q)
		fdf->z_rotation -= 2;
	if (key == MLX_KEY_E)
		fdf->z_rotation += 2;
}
