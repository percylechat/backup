#include "cub3d.h"

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
	m_w = (data_t->res_w / 2) / data_t->column;
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
					// printf("i; %d j; %d\n", i + (m_h_c * m_h), j + (m_w_c * m_w));
					i++;
				}
				// mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, j + 1, i + (m_h_c * m_h), 1+(255<<16)+(1<<8));
				m_h_c++;
				i = 0;
			}
		    j++;
			m_h_c = 0;
			// printf("j: %d\n", j);
			// printf("mw; %d\n", m_w);
		}
		m_w_c++;
		// printf("wcompt %d\n", m_w_c);
		j = 0;
	}
}

int	check_for_obstacle_m(int x, int y, data_t *data_t)
{
	int res;

	res = (y * (data_t->column + 1) + x);
	// printf("res: %d map:%c \n", res, data_t->map[res]);
	if (data_t->map[res] == '1')
		return (1+(1<<16)+(255<<8));
	else if (data_t->map[res] == '2')
		return (1+(255<<16)+(1<<8));
	else if (data_t->map[res] == '0')
		return (255+(1<<16)+(1<<8));
	else if (data_t->map[res] != ' ')
		return (1+(255<<8)+(255<<16));
	else
		return (1+(1<<16)+(1<<8));
}
