/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:14:44 by lpollini          #+#    #+#             */
/*   Updated: 2023/07/17 18:38:47 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	win_close(t_window *win)
{
	mlx_destroy_image(win->mlx, win->img.img);
	mlx_destroy_window(win->mlx, win->win);
	mlx_destroy_display(win->mlx);
	free(win->mlx);
	exit(0);
}

static int	keys_manager_1(t_window *win, int keypressed)
{
	if (keypressed == 117)
		win->col.r += CHANGE_VAL;
	else if (keypressed == 106)
		win->col.r -= CHANGE_VAL;
	else if (keypressed == 105)
		win->col.g += CHANGE_VAL;
	else if (keypressed == 107)
		win->col.g -= CHANGE_VAL;
	else if (keypressed == 111)
		win->col.b += CHANGE_VAL;
	else if (keypressed == 108)
		win->col.b -= CHANGE_VAL;
	else if (keypressed == 118)
		win->col.z /= SCALE_L;
	else if (keypressed == 98)
		win->col.z /= SCALE_S;
	else if (keypressed == 110)
		win->col.z *= SCALE_S;
	else if (keypressed == 109)
		win->col.z *= SCALE_L;
	else if (keypressed == 113)
		win->firstp.x += E_0;
	else
		return (0);
	return (1);
}

static int	keys_manager_2(t_window *win, int keypressed)
{
	if (keypressed == 119)
		win->firstp.x += E_N1;
	else if (keypressed == 101)
		win->firstp.x += E_N2;
	else if (keypressed == 114)
		win->firstp.x -= E_N2;
	else if (keypressed == 116)
		win->firstp.x -= E_N1;
	else if (keypressed == 121)
		win->firstp.x -= E_0;
	else if (keypressed == 97)
		win->firstp.y += E_0;
	else if (keypressed == 115)
		win->firstp.y += E_N1;
	else if (keypressed == 100)
		win->firstp.y += E_N2;
	else if (keypressed == 102)
		win->firstp.y -= E_N2;
	else if (keypressed == 103)
		win->firstp.y -= E_N1;
	else if (keypressed == 104)
		win->firstp.y -= E_0;
	else
		return (0);
	return (1);
}

int	manage_keys(int keypressed, t_window *win)
{
	if (keys_manager_1(win, keypressed))
		(void)win;
	else if (keys_manager_2(win, keypressed))
		(void)win;
	else if (keypressed == 65361)
		win->cen.x += 30;
	else if (keypressed == 65363)
		win->cen.x -= 30;
	else if (keypressed == 65362)
		win->cen.y += 30;
	else if (keypressed == 65364)
		win->cen.y -= 30;
	else if (keypressed == 112)
		initw(win);
	else if (keypressed == 65307)
		win_close(win);
	else if (keypressed == 44)
		win->col.z /= SCALE_LL;
	else if (keypressed == 46)
		win->col.z *= SCALE_LL;
	win->iters = MAX_ITER * log(win->col.z / 2 + 25) / 3;
	reimage(win);
	return (0);
}

int	manage_mouse(int button, int x, int y, t_window *win)
{
	t_vec_i	t;

	if (button == 5)
		manage_keys(98, win);
	if (button == 4)
		manage_keys(110, win);
	if (button == 1 && win->type == JULIA)
	{
		t.x = x;
		t.y = y;
		win->firstp.x = (t_ld)t.x / win->size.x * 4 - 2;
		win->firstp.y = -(t_ld)t.y / win->size.y * 4 + 2;
		reimage(win);
	}
	return (0);
}
