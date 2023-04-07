/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/17 15:40:17 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/04/06 14:13:09 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	t_fdf	fdf;

	if (argc != 2)
		free_exit(NULL, NULL, NULL, ERR_ARGUMENT);
	init_fdf(&fdf, argv[1]);
	draw(&fdf);
	hooks(&fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
