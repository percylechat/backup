#include "cub3d.h"

//bonus
//print a minimap in the upper left corner.

//called by ft_keyboard_press in move.c
//print the minimap.
void    print_minimap(data_t *data_t)
{
	int m_w;
	int m_h;
	int m_w_c = 0;
	int m_h_c = 0;
	int i;
	int j;

	i = 0;
	j = 0;
	m_h = (data_t->res_h / 3) / data_t->line;
	m_w = (data_t->res_w / 2) / data_t->column ;
	if (m_h > m_w)
		m_h = m_w;
	else
		m_w = m_h;
	while (m_w_c < data_t->column)
	{
	    while (j < m_w)
	    {
			while (m_h_c < data_t->line)
			{
				while (i < m_h)
				{
					mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, j + (m_w_c * m_w), i + (m_h_c * m_h), check_for_obstacle_m(m_w_c, m_h_c, data_t));
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
int	check_for_obstacle_m(int x, int y, data_t *data_t)
{
	if (data_t->maptab[y][x] == '1')
		return (1+(1<<16)+(255<<8));
	else if (data_t->maptab[y][x] == '2')
		return (1+(255<<16)+(1<<8));
	else if (data_t->maptab[y][x] == '0')
		return (255+(1<<16)+(1<<8));
	else if (data_t->maptab[y][x] != ' ')
		return (1+(255<<8)+(255<<16));
	else
		return (1+(1<<16)+(1<<8));
}
