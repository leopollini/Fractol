/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_renderer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:16:36 by lpollini          #+#    #+#             */
/*   Updated: 2023/07/01 16:19:34 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	stuff_doer(t_window *win, t_vec_i_ld *cen, t_a_c *cl, t_vec_i winsize)
{
	if (win->col.z != 1 + E_N2)
	{
		mlx_mouse_get_pos(win->mlx, win->win, &cen->i.x, &cen->i.y);
		cen->d.x = (win->cen.x - cen->i.x) * (win->col.z / win->z) + cen->i.x;
		cen->d.y = (win->cen.y - cen->i.y) * (win->col.z / win->z) + cen->i.y;
	}
	else
	{
		win->col.z -= E_N2;
		cen->d.x = winsize.x / 2;
		cen->d.y = winsize.y / 2;
	}
	win->cen.x = cen->d.x;
	win->cen.y = cen->d.y;
	win->z = win->col.z;
	cl->iter = win->iters;
	cen->d.x /= win->s;
	cen->d.y /= win->s;
}

void	j_s(t_window *win, t_vec_i winsize)
{
	t_vec_i_ld		cen;
	t_vec_ld		z;
	t_a_c			cl;
	t_vec_i			c;
	int				t;

	c.x = -1;
	cl = win->col;
	z.x = win->firstp.x;
	z.y = win->firstp.y;
	stuff_doer(win, &cen, &cl, winsize);
	while (++c.x < winsize.x)
	{
		c.y = -1;
		while (++c.y < winsize.y)
		{
			t = j_c(z, c.x / win->s - cen.d.x, c.y / win->s - cen.d.y, cl);
			my_mlx_pixel_put(&win->img, c.x, c.y, t);
		}
	}
}

void	mandelbrot_set(t_window *win, t_vec_i winsize)
{
	t_vec_i_ld		cen;
	t_vec_ld		z;
	t_a_c			cl;
	t_vec_i			c;
	int				t;

	c.x = 0;
	cl = win->col;
	z.x = 0;
	z.y = 0;
	stuff_doer(win, &cen, &cl, winsize);
	while (++c.x < winsize.x)
	{
		c.y = -1;
		while (++c.y < winsize.y)
		{
			t = m_c(z, c.x / win->s - cen.d.x, c.y / win->s - cen.d.y, cl);
			my_mlx_pixel_put(&win->img, c.x, c.y, t);
		}
	}
}

void	burning_ship_set(t_window *win, t_vec_i winsize)
{
	t_vec_i_ld		cen;
	t_vec_ld		z;
	t_a_c			cl;
	t_vec_i			c;
	int				t;

	c.x = 0;
	cl = win->col;
	z.x = 0;
	z.y = 0;
	stuff_doer(win, &cen, &cl, winsize);
	while (++c.x < winsize.x)
	{
		c.y = -1;
		while (++c.y < winsize.y)
		{
			t = bs_c(z, c.x / win->s - cen.d.x, c.y / win->s - cen.d.y, cl);
			my_mlx_pixel_put(&win->img, c.x, c.y, t);
		}
	}
}

void	my_image_creator(t_window *win, t_vec_i winsize)
{
	win->s = winsize.x / 10 * win->col.z;
	if (win->type == JULIA)
	{
		j_s(win, winsize);
	}
	if (win->type == MANDELBROT)
	{
		mandelbrot_set(win, winsize);
	}
	if (win->type == B_SHIP)
	{
		burning_ship_set(win, winsize);
	}
}
