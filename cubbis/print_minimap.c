#include "cub3d.h"

//bonus
//print a minimap in the upper left corner.

//called by ft_keyboard_press in move.c
//print the minimap.
void    print_minimap(t_main *t_m)
{
	int m_w;
	int m_h;
	int m_w_c = 0;
	int m_h_c = 0;
	int i;
	int j;

	i = 0;
	j = 0;
	m_h = (t_m->res_h / 3) / t_m->line;
	m_w = (t_m->res_w / 2) / t_m->column ;
	if (m_h > m_w)
		m_h = m_w;
	else
		m_w = m_h;
	while (m_w_c < t_m->column)
	{
	    while (j < m_w)
	    {
			while (m_h_c < t_m->line)
			{
				while (i < m_h)
				{
					mlx_pixel_put(t_m->mlx_prog, t_m->mlx_win, j + (m_w_c * m_w), i + (m_h_c * m_h), check_for_obstacle_m(m_w_c, m_h_c, t_m));
					i++;
				}
				m_h_c++;
				i = 0;
			}
		    j++;
			m_h_c = 0;
		}
		m_w_c++;
		j = 0;
	}
}

//check for content of coordinates and returns appropriate colors.
int	check_for_obstacle_m(int x, int y, t_main *t_m)
{
	if (t_m->maptab[y][x] == '1')
		return (1+(1<<16)+(255<<8));
	else if (t_m->maptab[y][x] == '2')
		return (1+(255<<16)+(1<<8));
	else if (t_m->maptab[y][x] == '0')
		return (255+(1<<16)+(1<<8));
	else if (t_m->maptab[y][x] != ' ')
		return (1+(255<<8)+(255<<16));
	else
		return (1+(1<<16)+(1<<8));
}
