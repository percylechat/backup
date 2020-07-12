#include "cub3d.h"

//OBSOLETE FILE

//
// float		give_udlr(data_t *data_t, int i)
// {
// 	int		a;
// 	int		b;
//
// 	a = FOV / data_t->res_w * i;
// 	b = FOV - (30 - a);
// 	// if (b > 0 && b < 180)
// 		data_t->updown = 1;
// 	// else
// 	// 	data_t->updown = 0;
// 	// if (b > 90 && b < 270)
// 		data_t->leftright = 0;
// 	// else
// 		// data_t->leftright = 1;
// 	// if (b > data_t->res_w / 2)
// 	// 	b = data_t->direction - b;
// 	// else if (b < data_t->res_w / 2)
// 	// 	b = data_t->direction + b;
// 	// printf("%d", b);
// 	return (0.0);
// }
//
// void dist_finder(data_t *data_t, int inter_x, int inter_y, int i)
// {
// 	float exp_x;
// 	float exp_y;
// 	float res_exp;
//
// 	// printf("%d\n", ((data_t->position_x) * 64 + data_t->sub_position_x));
// 	// printf("%d\n", inter_x);
// 	// printf("%d\n", ((data_t->position_y) * 64 + data_t->sub_position_y));
// 	// printf("%d\n", inter_y);
// 	exp_x = (((data_t->position_x) * 64 + data_t->sub_position_x) - (inter_x)) * (((data_t->position_x) * 64 + data_t->sub_position_x) - (inter_x));
//
// 	exp_y = ((data_t->position_y * 64 + data_t->sub_position_y) - inter_y) * ((data_t->position_y * 64 + data_t->sub_position_y) - inter_y);
// 	// printf("%f\n", exp_x);
// 	// printf("%f\n", exp_y);
// 	res_exp =  exp_x + exp_y;
// 	// printf("%f\n", res_exp);
// 	if (i == 1)
// 		data_t->dist_vert = (int)sqrt(res_exp);
// 	else
// 		data_t->dist_hor = (int)sqrt(res_exp);
// 	printf("dist %d\n", (int)data_t->dist_hor);
// }
//
// // printf("pos y; %d\n", data_t->position_y);
// // printf("pos x; %d\n", data_t->position_x);
// // printf("inter y; %d\n", inter_y);
// // printf("coeff y; %d\n", coeff_y);
// // printf("inter x; %d\n", inter_x);
// // printf("coeff x; %d\n", coeff_x);
// // printf("wall found");
//
// void	find_vert_dist(data_t *data_t, float ray)
// {
// 	int		inter_x;
// 	int		inter_y;
// 	int		coeff_x;
// 	int		coeff_y;
// 	float	ray_rad;
//
// 	ray_rad = ray * M_PI / 180;
//
// 	// if up
// 	// 	e->r.v_xa = TW;
// 	// else down
// 	// 	e->r.b.x = floorl(RX / TW) * TW - 0.00001;
//
// 	// e->r.v_ya = fabsl(e->r.v_xa / tanl(e->r.rad));
// 	// e->r.b.y = RY + ((RX - e->r.b.x) / tanl(e->r.rad));
// 	// if ((e->r.deg > 270 && e->r.deg < 360) || (e->r.deg >= 0 && e->r.deg < 90)
// 	// 	|| e->r.deg == 0 || e->r.deg == 360)
// 	// 	e->r.v_ya *= -1;
//
// 	if (data_t->updown == 1)
// 	{
// 		inter_x = (((data_t->position_x) * 64 + data_t->sub_position_x) / BLOC_SIZE) * BLOC_SIZE + BLOC_SIZE;
// 		coeff_x = BLOC_SIZE;
// 	}
// 	else
// 	{
// 		inter_x = (((data_t->position_x) * 64 + data_t->sub_position_x) / BLOC_SIZE) * BLOC_SIZE - 1;
// 		coeff_x = BLOC_SIZE * -1;
// 	}
// 	inter_y = ((data_t->position_y) * 64 + data_t->sub_position_y) + (((data_t->position_x) * 64 + data_t->sub_position_x) - inter_x) / tan(M_PI_2 / ray_rad);
// 	coeff_y = fabsl(coeff_x / tan(M_PI_2 / ray_rad));
// 	if (data_t->leftright == 1)
// 		coeff_y *= -1;
// 	printf("inter y; %d\n", inter_y);
// 	printf("coeff y; %d\n", coeff_y);
// 	printf("inter x; %d\n", inter_x);
// 	printf("coeff x; %d\n", coeff_x);
// 	while (check_for_obstacle(inter_x, inter_y, data_t) != 1)
// 	{
// 		inter_x += coeff_x;
// 		inter_y += coeff_y;
// 	}
// 	dist_finder(data_t, inter_x, inter_y, 1);
// }
//
// // printf("%f\n", BLOC_SIZE);
// // printf("ray %d\n", ray);
// // printf("ray rad %f\n", ray_rad);
// // printf("tan ray %f\n", tan(ray_rad));
// // printf("pos y; %d\n", data_t->position_y);
// // printf("pos x; %d\n", data_t->position_x);
// // printf("inter y; %d\n", inter_y);
// // printf("coeff y; %d\n", coeff_y);
// // printf("inter x; %d\n", inter_x);
// // printf("coeff x; %d\n", coeff_x);
//
// void	find_hor_dist(data_t *data_t, float ray)
// {
// 	int		inter_x;
// 	int		inter_y;
// 	int		coeff_x;
// 	int		coeff_y;
// 	float	ray_rad;
//
// 	ray_rad = ray * M_PI / 180;
//
//
// 	// if ((e->r.deg right)
// 	// 		e->r.a.y =:!ù (floorl(RY / TH) * TH) - 0.00001;
// 	// 	else left
// 	// 		e->r.a.y = (floorl(RY / TH) * TH) + TH;
//
// 	// 	e->r.h_xa = fabsl(e->r.h_ya / tanl(M_PI_2 - e->r.rad));
// 	// 	e->r.a.x = RX + ((RY - e->r.a.y) / tanl(M_PI_2 - e->r.rad));
// 	// 	(e->r.deg > 180 ? e->r.h_xa *= -1. : 0);
//
//
// 	if (data_t->leftright == 1)
// 	{
// 		inter_y = (((data_t->position_y) * 64 + data_t->sub_position_y)/BLOC_SIZE) * (BLOC_SIZE) - 1;
// 		coeff_y = BLOC_SIZE * -1;
// 	}
// 	else
// 	{
// 		inter_y = (((data_t->position_y) * 64 + data_t->sub_position_y)/BLOC_SIZE) * (BLOC_SIZE) + BLOC_SIZE;
// 		coeff_y = BLOC_SIZE;
// 	}
//
// 	// e->r.a.y = (floorl(RY / TH) * TH) - 0.00001;
// 	//
// 	// e->r.a.x = RX + ((RY - e->r.a.y) / tanl(M_PI_2 - e->r.rad));
//
// 	inter_x = (data_t->position_x * 64 + data_t->sub_position_x) + (((data_t->position_y - 1) * 64 + data_t->sub_position_y) - inter_y) / tan(M_PI_2 / ray_rad);
// 	// e->r.h_xa = fabsl(e->r.h_ya / tanl(M_PI_2 - e->r.rad));
// 	coeff_x = fabsl(coeff_y / tan(M_PI_2 / ray_rad));
// 	if (data_t-> updown == 0)
// 		coeff_x *= -1;
// 	printf("inter y; %d\n", inter_y);
// 	printf("coeff y; %d\n", coeff_y);
// 	printf("inter x; %d\n", inter_x);
// 	printf("coeff x; %d\n", coeff_x);
// 	while (check_for_obstacle(inter_x, inter_y, data_t)
// 	!= 1)
// 	{
// 		inter_x += coeff_x;
// 		inter_y += coeff_y;
// 	}
// 	dist_finder(data_t, inter_x, inter_y, 0);
// }

// float get_res_f(data_t *data_t)
// {
// 	float i;
// 	int j;
// 	j = 0;
// 	i = 0.0;
// 	while (j != data_t->res_w)
// 	{
// 		j++;
// 		i += 1.0;
// 	}
// 	// printf("%f\n", i);
// 	return (i);
// }
//
// void	new_screen(data_t *data_t)
// {
// 	int		i;
// 	float	b;
// 	float	ray;
// 	float	ray_change;
// 	float res;
// 	int temp;
// 	i = 1;
// 	ray = 60.0;
// 	res = get_res_f(data_t);
// 	ray_change = FOV/res;
// 	// print_minimap(data_t);
// 	while (i <= data_t->res_w)
// 	{
// 		b = give_udlr(data_t, i);
// 		printf("ray%f\n", ray);
// 		// if (ray != 90.0)
// 		// find_vert_dist(data_t, ray);
// 		find_hor_dist(data_t, ray);
// 		// if (data_t->dist_hor > data_t->dist_vert)
// 			// data_t->wall_size = data_t->dist_vert;
// 		// else
// 			data_t->wall_size = data_t->dist_hor;
// 			// temp = data_t->dist_hor;
// 			// data_t->wall_size = temp * cos(data_t->direction - ray);
// 		// data_t->wall_size = BLOC_SIZE / data_t->wall_size * (data_t->res_w / 2 / tan(FOV/2 * M_PI / 180));
// 		print_column(data_t, i);
// 		i++;
// 		// printf("%.5f\n", ray_change);
// 		ray += ray_change;
// 	}
// }

// // printf("vert: %d", data_t->dist_vert);
// // printf("hor: %d", data_t->dist_hor);
// 	// if (data_t->dist_vert < data_t->dist_hor)
// 	// 	data_t->dist_hor =  data_t->dist_vert;
// 	// if (i < data_t->res_w / 2)
// 		// data_t->wall_size = (BLOC_SIZE / (data_t->dist_hor * cos((FOV/2) * M_PI / 180))) * ((data_t->res_w / 2) / tan((FOV/2) * M_PI / 180));
// 	// else
//   	// 	data_t->wall_size = (BLOC_SIZE / (data_t->dist_hor * cos((FOV / 2) * -1))) * ((data_t->res_w / 2) / tan((FOV/2) * M_PI / 180));



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
