/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/04 15:31:07 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/04/06 13:38:41 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	cursor_hook(double xpos, double ypos, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *) param;
	if (mlx_is_mouse_down(fdf->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if (fdf->mouse_x == -1 || fdf->mouse_y == -1)
		{
			fdf->mouse_x = xpos;
			fdf->mouse_y = ypos;
		}
		else
		{
			mlx_delete_image(fdf->mlx, fdf->img);
			fdf->img = mlx_new_image(fdf->mlx, fdf->screen_width,
					fdf->screen_height);
			if (!fdf->img)
				free_exit(fdf->mlx, NULL, fdf->map, ERR_IMG);
			fdf->x_shift += xpos - fdf->mouse_x;
			fdf->y_shift += ypos - fdf->mouse_y;
			fdf->mouse_x = xpos;
			fdf->mouse_y = ypos;
			draw(fdf);
		}
	}
}

void	mouse_hook(mouse_key_t button, action_t action,
			modifier_key_t mods, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *) param;
	(void) mods;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
	{
		fdf->mouse_x = -1;
		fdf->mouse_y = -1;
	}
}
