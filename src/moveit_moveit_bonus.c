/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moveit_moveit_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:59:50 by vharkush          #+#    #+#             */
/*   Updated: 2023/06/11 14:03:35 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/so_long_bonus.h"

void	ft_monke_moves(t_data *data, char *one, char *two)
{
	int	i;

	i = 0;
	ft_new_img(one, data);
	while (++i < 7000)
		ft_put_with_mlx(data, data->img->monki, data->x, data->y);
	i = 0;
	ft_new_img(two, data);
	while (++i < 5000)
		ft_put_with_mlx(data, data->img->monki, data->x, data->y);
}

void	move_monke(int keysym, t_data *data)
{
	if (keysym == XK_w || keysym == XK_d || keysym == XK_s || keysym == XK_a)
		data->moves += 1;
	if (keysym == LEFT_KEY || keysym == RIGHT_KEY || keysym == DOWN_KEY
		|| keysym == UP_KEY)
		data->moves += 1;
	if (data->moves == 1000000)
		data->moves = 0;
	ft_write_moves(data->moves, data);
	if_lrud(keysym, data);
	if (data->space[data->y][data->x] == 'C')
	{
		data->col += 1;
		data->space[data->y][data->x] = '0';
	}
	ft_put_with_mlx(data, data->img->monki, data->x, data->y);
	if (data->col == data->total_col)
	{
		mlx_destroy_image(data->mlx_ptr, data->img->exit);
		data->img->exit = assign_img_mlx("textures/exitop.xpm", data->mlx_ptr);
		ft_put_with_mlx(data, data->img->exit, data->ex, data->ey);
	}
	if (((data->col == data->total_col)
			&& (data->space[data->y][data->x] == 'E'))
		|| data->space[data->y][data->x] == 'V')
		handle_keypress(XK_Escape, data);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		ft_free_all(data, data->map);
	if (keysym == XK_q)
		return (ft_destroy_it_roarrr(data));
	mlx_destroy_image(data->mlx_ptr, data->img->monki);
	data->img->monki = assign_img_mlx("textures/mainchar.xpm", data->mlx_ptr);
	if (data->space[data->y][data->x] != 'E'
		&& data->space[data->y][data->x] != 'V')
		ft_put_with_mlx(data, data->img->right, data->x, data->y);
	else if (data->space[data->y][data->x] == 'E')
		ft_put_with_mlx(data, data->img->exit, data->x, data->y);
	else
		ft_put_with_mlx(data, data->img->villain, data->x, data->y);
	move_monke(keysym, data);
	return (0);
}
