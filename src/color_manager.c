/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:18:22 by lpollini          #+#    #+#             */
/*   Updated: 2023/07/14 13:48:00 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b); 
}

int	create_color_overflow(int b, t_a_c cl)
{
	return (create_trgb(0, b * cl.r, b * cl.g, b * cl.b));
}

int	j_c(t_vec_ld zed, t_ld x, t_ld y, t_a_c cl)
{
	t_vec_ld	t;
	int			count;

	count = -1;
	while (count++ < cl.iter)
	{
		t.x = x * x;
		t.y = y * y;
		if (t.x + t.y > SQR_RAD)
			return (create_color_overflow(count, cl));
		y = x * y * 2 + zed.y;
		x = t.x - t.y + zed.x;
	}
	return (create_trgb(0, 0, 0, 0));
}

int	m_c(t_vec_ld zed, t_ld x, t_ld y, t_a_c cl)
{
	t_vec_ld	t;
	int			count;

	count = -1;
	while (count++ < cl.iter)
	{
		t.x = zed.x * zed.x;
		t.y = zed.y * zed.y;
		if (t.x + t.y > SQR_RAD)
			return (create_color_overflow(count, cl));
		zed.y = zed.x * zed.y * 2 + y;
		zed.x = t.x - t.y + x;
	}
	return (create_trgb(0, 0, 0, 0));
}

int	bs_c(t_vec_ld zed, t_ld x, t_ld y, t_a_c cl) //
{
	t_vec_ld	t;
	int			count;

	count = -1;
	while (count++ < cl.iter)
	{
		t.x = zed.x * zed.x;
		t.y = zed.y * zed.y;
		if (t.x + t.y > SQR_RAD)
			return (create_color_overflow(count, cl));
		zed.y = mod(zed.x * zed.y) * 2 + y;
		zed.x = t.x - t.y + x;
	}
	return (create_trgb(0, 0, 0, 0));
}
