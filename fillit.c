/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <beborch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 19:46:44 by beborch           #+#    #+#             */
/*   Updated: 2018/05/26 01:27:42 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void		print_map(char map[MAX][MAX], size_t map_size)
{
	t_size_t2	i;

	i.y = 0;
	while (i.y < map_size)
	{
		i.x = 0;
		while (i.x < map_size)
		{
			write(1, &map[i.y][i.x], 1);
			i.x++;
		}
		write(1, "\n", 1);
		i.y++;
	}
}

static int		error(void)
{
	write(1, "error\n", 6);
	return (-1);
}

int				not_again(t_fill *fill)
{
	int i;

	i = 0;
	fill->i = 0;
	fill->j = 0;
	while (fill->buff[fill->i] != '\0')
	{
		if (fill->buff[fill->i] != '\n')
			fill->j++;
		if (fill->j == 4 && (fill->buff[fill->i] == '\n'))
		{
			i++;
			fill->j = 0;
		}
		fill->i++;
	}
	if (i + fill->piece == (fill->piece * 5) - 1)
		return (0);
	return (-1);
}

int				main(int argc, char *argv[])
{
	t_fill		fill;

	if (argc != 2)
		return (error());
	fill.file = open(argv[1], O_RDONLY);
	fill.ret = read(fill.file, fill.buff, BUFF_SIZE);
	fill.buff[fill.ret] = '\0';
	if (parse(&fill) == -1)
		return (error());
	if (check_parse(&fill) == -1)
		return (error());
	solver(&fill);
	if (not_again(&fill) == -1)
		return (error());
	print_map(fill.map, fill.map_size);
}
