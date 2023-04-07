/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks1.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/04 13:01:26 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/04/06 13:30:12 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	hooks(t_fdf *fdf)
{
	mlx_key_hook(fdf->mlx, &key_hook, fdf);
	mlx_close_hook(fdf->mlx, &close_hook, fdf);
	mlx_resize_hook(fdf->mlx, &resize_hook, fdf);
	mlx_cursor_hook(fdf->mlx, &cursor_hook, fdf);
	mlx_mouse_hook(fdf->mlx, &mouse_hook, fdf);
	mlx_scroll_hook(fdf->mlx, &scroll_hook, fdf);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *) param;
	if (keydata.action != MLX_RELEASE && (keydata.key == MLX_KEY_A
			|| keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_D
			|| keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_Q
			|| keydata.key == MLX_KEY_E))
		rotate(fdf, keydata.key);
	else if (keydata.key == MLX_KEY_ESCAPE)
		free_exit(fdf->mlx, fdf->img, fdf->map, EXIT_SUCCESS);
	else if (keydata.key == MLX_KEY_EQUAL && keydata.modifier == MLX_SHIFT
		&& keydata.action != MLX_RELEASE)
		fdf->altitude *= 0.9;
	else if (keydata.key == MLX_KEY_MINUS && keydata.action != MLX_RELEASE)
		fdf->altitude *= 1.1;
	else if ((keydata.key == MLX_KEY_I || keydata.key == MLX_KEY_P)
		&& keydata.action != MLX_RELEASE)
		change_projection(fdf, keydata.key);
	mlx_delete_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, fdf->screen_width, fdf->screen_height);
	if (!fdf->img)
		free_exit(fdf->mlx, NULL, fdf->map, ERR_IMG);
	draw(fdf);
}

void	close_hook(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *) param;
	free_exit(fdf->mlx, fdf->img, fdf->map, EXIT_SUCCESS);
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *) param;
	fdf->screen_width = width;
	fdf->screen_height = height;
	mlx_delete_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, fdf->screen_width, fdf->screen_height);
	if (!fdf->img)
		free_exit(fdf->mlx, NULL, fdf->map, ERR_IMG);
	draw(fdf);
}

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_fdf	*fdf;

	(void) xdelta;
	fdf = (t_fdf *) param;
	mlx_delete_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, fdf->screen_width, fdf->screen_height);
	if (!fdf->img)
		free_exit(fdf->mlx, NULL, fdf->map, ERR_IMG);
	fdf->zoom -= ydelta * 10;
	if (fdf->zoom < 1)
		fdf->zoom = 1;
	draw(fdf);
}
