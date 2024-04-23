/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:57:52 by lpollini          #+#    #+#             */
/*   Updated: 2023/01/29 21:45:40 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H

# define FRACTOL_H

# define LN_ACCURACY 50
# define MAX_ITER 500
# define SQR_RAD 4
# define CHANGE_VAL 0.25f
# define E_0 0.2f
# define E_N1 0.02f
# define E_N2 0.002f
# define SCALE_S 1.2f
# define SCALE_L 2.2f

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "fractol.h"

enum	e_fractype
{
	MANDELBROT,
	JULIA,
	B_SHIP,
	TYPE_END
};

typedef long double	t_ld;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vector_int {
	int	x;
	int	y;
}				t_vector_int;

typedef struct s_vector_ld {
	t_ld	x;
	t_ld	y;
}				t_vector_ld;

typedef struct s_vector_int_ld {
	t_vector_int	intg;
	t_vector_ld		doub;
}				t_vector_int_ld;

typedef struct s_color {
	int	t;
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_another_cont {
	t_ld	z;
	int		iter;
	t_ld	r;
	t_ld	g;
	t_ld	b;
}				t_another_cont;

typedef struct s_window {
	void			*mlx;
	void			*win;
	t_data			img;
	t_vector_int	size;
	t_another_cont	coloration;
	t_ld			p_zoom;
	t_ld			scale;
	t_ld			invscale;
	enum e_fractype	type;
	t_vector_ld		firstp;
	t_vector_ld		cen;
	int				using;
	int				lkey;
	int				iters;
	int				mdown;
}				t_window;

#endif
