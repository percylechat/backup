#include "cub3d.h"

//Charachetr movement related to pressed touches.

//check if character position is in a wall or not (for bonus) and change map according to new charater position if it changes coordinates.
void	check_move(data_t *data_t, double temp, double tempbis)
{
	char spot;

	if ((int)data_t->position_x != (int)temp || (int)data_t->position_y != (int)tempbis)
	{
		data_t->maptab[(int)data_t->position_y][(int)data_t->position_x] = spot;
		data_t->maptab[(int)data_t->position_y][(int)data_t->position_x] = data_t->orientation;
		data_t->maptab[(int)tempbis][(int)temp] = spot;
	}
}

//characher goes backward or forward.
//ZERO is S, ONE is Z

//NOTE m == 0 doesnt work

void ft_move_updown(data_t *data_t, int m)
{
	double temp;
	double tempbis;

	temp = data_t->position_x;
	tempbis = data_t->position_y;
	if (m == 1)
	{
		data_t->position_x -= data_t->direction_x * (0.5);
		data_t->position_y -= data_t->direction_y * (0.5);
	}
	else if (m == 0)
	{
		data_t->position_x += data_t->direction_x * (0.5);
		data_t->position_y += data_t->direction_y * (0.5);
	}
	check_move(data_t, temp, tempbis);
}

//should makes character movre from left to right.
//ZERO is left and ONE is right
//does it work? the image of the walls says yes, the minimap says no.
void ft_move_leftright(data_t *data_t, int m)
{
	double temp;
	double tempbis;

	temp = data_t->position_x;
	tempbis = data_t->position_y;
	if (m == 1)
	{
		data_t->position_x += data_t->camera_x * (0.5);
		data_t->position_y += data_t->camera_y * (0.5);
	}
	else
	{
		data_t->position_x -= data_t->camera_x * (0.5);
		data_t->position_y -= data_t->camera_y * (0.5);
	}
	check_move(data_t, temp, tempbis);
}

//makes character rotate the head.
// ONE should be left and ZERO right.
void	ft_rotate(data_t *data_t, int m)
{
	double temp;

	if (m == 0)
	{
		temp = data_t->direction_x;
		data_t->direction_x = data_t->direction_x * cos(0.5) - data_t->direction_y * sin(0.5);
		data_t->direction_y = temp * sin(0.5) + data_t->direction_y * cos(0.5);
		temp = data_t->camera_x;
		data_t->camera_x = data_t->camera_x * cos(0.5) - data_t->camera_y * sin(0.5);
		data_t->camera_y = temp * sin(0.5) + data_t->camera_y * cos(0.5);
	}
	else
	{
		temp = data_t->direction_x;
		data_t->direction_x = data_t->direction_x * cos(-0.5) - data_t->direction_y * sin(-0.5);
		data_t->direction_y = temp * sin(-0.5) + data_t->direction_y * cos(-0.5);
		temp = data_t->camera_x;
		data_t->camera_x = data_t->camera_x * cos(-0.5) - data_t->camera_y * sin(-0.5);
		data_t->camera_y = temp * sin(-0.5) + data_t->camera_y * cos(-0.5);
	}
	if (data_t->direction_x > 1)
		data_t->direction_x = ((data_t->direction_x - 1) - 1) * -1;
	if (data_t->direction_y > 1)
		data_t->direction_y = ((data_t->direction_y - 1) - 1) * -1;
	if (data_t->direction_x < -1)
		data_t->direction_x = ((data_t->direction_x + 1) + 1) * -1;
	if (data_t->direction_y < -1)
		data_t->direction_y = ((data_t->direction_y + 1) + 1) * -1;
	printf("%f %f\n", data_t->direction_x, data_t->direction_y);
}

//kinda called by main
//assign movement depending of touch and displays new image.
void ft_keyboard_press(int key, data_t *data_t)
{

	if (key == KEY_S)
		ft_move_updown(data_t, 0);
	else if (key == KEY_Z)
		ft_move_updown(data_t, 1);
    else if (key == KEY_Q)
        ft_move_leftright(data_t, 0);
    else if (key == KEY_D)
        ft_move_leftright(data_t, 1);
	else if (key == KEY_A)
		ft_rotate(data_t, 1);
	else if (key == KEY_E)
		ft_rotate(data_t, 0);
	else if (key = KEY_ESC)
		ft_quit(data_t);
	else
	{	write(1, key, 3);
		printf("%d\n", key);
		write(1, "fail", 4);}
	// print_black(data_t);
	drawRays3d(data_t);
	print_minimap(data_t);
}

//is useless, since i work on tapped touch and won't take into account time pressed and frames.
void ft_keyboard_release(int key, data_t *data_t)
{
	if (key == KEY_S)
		return ;
	else
		return ;
}
