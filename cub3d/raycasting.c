#include "cub3d.h"

void drawRays3d(data_t *data_t)
{
	int j = 0;
	float dirx = 0, diry = -1; //initial direction vector
	float planex = 0.66, planey = 0; //the 2d raycaster version of camera plane
	float posx = data_t->position_x;// + data_t->sub_position_x
	float posy = data_t->position_y;// + data_t->sub_position_y
	int mapX = (int)posx;
	int mapY = (int)posy;
	float sideDistX;
	float sideDistY;
	float deltaDistX;
	float deltaDistY;
	float perpWallDist;
	int stepX;
	int stepY;
	int hit = 0; //was there a wall hit?
	int side; //was a NS or a EW wall hit?
	int i = 1;
	while (i <= data_t->res_w)
	{
		mapX = (int)posx;
		mapY = (int)posy;
		float camerax = 2 * i / data_t->res_w - 1;
		float raydirx = dirx + planex * camerax;
		float raydiry = diry + planey * camerax;
		if (raydirx != 0)
			deltaDistX = abs(1 / raydirx);
		else
			deltaDistX = 1;
		if (raydiry != 0)
			deltaDistY = abs(1 / raydiry);
		else
			deltaDistY = 1;
		if (raydirx < 0)
		{
			stepX = -1;
			sideDistX = (posx - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posx) * deltaDistX;
		}
		if (raydiry < 0)
		{
			stepY = -1;
			sideDistY = (posy - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posy) * deltaDistY;
		}
		// printf("mapx: %d mapy %d\n", mapX, mapY);
		while (hit == 0 && j < 8)
		{
//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
	  //Check if ray has hit a wall
			// printf("mapxbis: %d mapybis: %d\n", mapX, mapY);
			if (check_for_obstacle(mapX, mapY, data_t) > 0)
				hit = 1;
			j++;
		}
		j = 0;
		hit = 0;
		if (side == 0)
			perpWallDist = (mapX - posx + (1 - stepX) / 2) / raydirx;
		else
			perpWallDist = (mapY - posy + (1 - stepY) / 2) / raydiry;
		data_t->wall_size = (int)(data_t->res_h / perpWallDist);
		printf("wall: %d\n", data_t->wall_size);
		print_column(data_t, i, side);
		i += 1;
	}
}



// ******************************************

// float dist(float ax, float ay, float bx, float by, float ang)
// {
//	 return (sqrt((bx-ax) * (bx-ax) + (by -ay) * (by-ay)));
// }
//
// void drawRays3d(data_t *data_t)
// {
//	 int py =  data_t->position_y * BLOC_SIZE + data_t->sub_position_y;
//	 int px = data_t->position_x * BLOC_SIZE + data_t->sub_position_x;
//	 int r, mx, my, mp, dof, disT, vy, vx, hy, hx, i;
//	 float rx, ry, ra, xo, yo;
//	 i = 1;
//		 int j =  data_t->res_w;
//	 ra = data_t->direction * M_PI/180;
//	 ra =  ra - DR * 30;
//	 if (ra < 0){ra+=2*M_PI;} if (ra > 2*M_PI){ra -= 2*M_PI;}
//	 for (r = 0; r<1;r++)
//	 {
//	   //horizontal
//	   dof = 0;
//	   float disH = 10000000, hp= px, hy = py;
//	   float aTan = -1/atan(ra * M_PI / 180);
//	   if (ra > M_PI)
//	   {
//		 ry = (((int)py>>6)<<6)-0.0001;
//		 rx = (py - ry) * aTan+px;
//		 yo = -64;
//		 xo = yo*aTan;
//	   }
//	   else if (ra == 0 || ra == M_PI)
//	   {
//		 rx = px;
//		 ry = py;
//		 dof = 8;
//	   }
//	   else
//	   {
//		 ry = (((int)py>>6)<<6)+64;
//		 rx = (py - ry) * aTan+px;
//		 yo = 64;
//		 xo = yo*aTan;
//	   }
//	   while (dof < 8)
//	   {
//		 mx = (int) (rx)>>6;
//		 my = (int)(ry)>>6;
//		 mp = check_for_obstacle(mx, my, data_t);
//		 if (mp != 1)
//		 {
//			 rx += xo;
//			 ry += yo;
//			 dof++;
//			 mp = check_for_obstacle(mx, my, data_t);
//		 }
//		 hx = rx;
//		 hy = ry;
//		 disH = dist(px, py, hx, hy, ra);
//		 dof++;
//	   }
//	   //vertical
//	   dof = 0;
//	   float disV = 10000000, vp = px, vy = py;
//	   float nTan = -tan(ra * M_PI / 180);
//	   if (ra > M_PI_2 && ra < (M_PI + M_PI_2))
//	   {
//		 rx = (((int)px>>6)<<6)-0.0001;
//		 ry = (px - rx) * nTan+py;
//		 xo = -64;
//		 yo = xo*nTan;
//	   }
//	   else if (ra == M_PI_2 || ra == (M_PI + M_PI_2))
//	   {
//		 ry = py;
//		 rx = px;
//		 dof = 8;
//	   }
//	   else
//	   {
//		 rx = (((int)px>>6)<<6)+64;
//		 ry = (px - rx) * nTan+py;
//		 xo = 64;
//		 yo = xo*nTan;
//	   }
//	   while (dof < 8)
//	   {
//		 mx = (int) (rx)>>6;
//		 my = (int)(ry)>>6;
//		 mp = check_for_obstacle(mx, my, data_t);
//		 if (mp != 1)
//		 {
//			 rx += xo;
//			 ry += yo;
//			 dof++;
//			 mp = check_for_obstacle(mx, my, data_t);
//		 }
//		 vx = rx;
//		 vy = ry;
//		 disV = dist(px, py, vx, vy, ra);
//		 dof++;
//	   }
//	   if (disV < disH)
//	   {
//		 rx = vx;
//		 ry = vy;
//		 disT = disV;
//	   }
//	   else
//	   {
//		 rx = hx;
//		 ry = hy;
//		 disT = disH;
//	   }
//	   float lineH = BLOC_SIZE * data_t->res_h / disT;
//	   // printf("%f", disH);
//	   // printf("|%f\n", disV);
//	   data_t->wall_size = (int)lineH;
//	   while (i <= data_t->res_w / FOV)
//	   {
//		 print_column(data_t, (int)j);
//		 i++;
//		 j--;
//	   }
//	   i = 1;
//	   ra += DR;
//	 }
// }
//
// // void	new_screen(data_t *data_t)
// // {
// //	 data_t t_raycast[16];
// //
// //	 t_raycast->p_absolut_y = data_t->position_y * BLOC_SIZE + data_t->sub_position_y;
// //	 t_raycast->p_absolut_x = data_t->position_x * BLOC_SIZE + data_t->sub_position_x;
// //	 t_raycast->direction = data_t->direction;
// //	 t_raycast->column = 1;
// //	 t_raycast->ray_change = FOV / data_t->res_w;
// //	 t_raycast->ray = t_raycast->direction - 30;
// //
// //	 // mesurer ditance referente avec angle
// //	 // creer liste chainee pour plus grand/plus petit et orientation murs?
// //	 //
// //
// //	 while (column != data_t->res_w)
// //	 {
// //	   if (t_raycast->ray > 45 && t_raycast->ray <= 135)
// //		 t_raycast->ref = 90;
// //	   else if (t_raycast->ray > 135 && t_raycast->ray <= 225)
// //		 t_raycast->ref = 180;
// //	   else if (t_raycast->ray > 225 && t_raycast->ray <= 315)
// //		 t_raycast->ref = 270;
// //	   else if (t_raycast->ray > 315 || t_raycast->ray <= 45)
// //		 t_raycast->ref = 0;
// //
// //	   column++;
// //	   t_raycast->ray += t_raycast->ray_change;
// //	 }
// // }
