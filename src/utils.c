/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:19:05 by lpollini          #+#    #+#             */
/*   Updated: 2023/07/17 18:38:46 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	clear_image(t_window *win, t_vec_i size)
{
	t_ld	i;
	t_ld	j;

	i = 0;
	j = 0;
	while (i < size.x)
		while (j < size.y)
			my_mlx_pixel_put(&win->img, i++, j++, 0);
}

t_ld	square_of(t_ld a)
{
	return (a * a);
}

t_ld	sqr_mod_of(t_vec_ld vec)
{
	return (square_of(vec.x) + square_of(vec.y));
}

t_ld	mod(t_ld a)
{
	if (a > 0)
		return (a);
	return (-a);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int cl)
{
	char	*dst;

	dst = data->addr + (y * data->ll + x * (data->bps / 8)); //hlep
	*(unsigned int *)dst = cl;
}
