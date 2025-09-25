#include "miniRT.h"

void	printAllCam(t_mini *mini){

	for (int i = 0; i < mini->sc.nb_cam; i++){

		printf("Camera ID : %d\n", mini->sc.cam[i].id);
		printf("position : x = %f, y = %f, z = %f\n",
			mini->sc.cam[i].pos.x,
			mini->sc.cam[i].pos.y,
			mini->sc.cam[i].pos.z);
		printf("vecteur directon : x = %f, y = %f, z = %f\n",
			mini->sc.cam[i].vec_dir.x,
			mini->sc.cam[i].vec_dir.y,
			mini->sc.cam[i].vec_dir.z);
		printf("fov : %d\n", mini->sc.cam[i].fov);
		printf("\n");
	}
}

void	printAllObject(t_mini *mini){

	for (int i = 0; i < mini->sc.nb_cam; i++){

		printf("Camera ID : %d\n", mini->sc.cam[i].id);
		printf("position : x = %f, y = %f, z = %f\n",
			mini->sc.cam[i].pos.x,
			mini->sc.cam[i].pos.y,
			mini->sc.cam[i].pos.z);
		printf("vecteur directon : x = %f, y = %f, z = %f\n",
			mini->sc.cam[i].vec_dir.x,
			mini->sc.cam[i].vec_dir.y,
			mini->sc.cam[i].vec_dir.z);
		printf("fov : %d\n", mini->sc.cam[i].fov);
		printf("\n");
	}

	printf("          ----- Object -----\n");
	printf("A = 0, L = 2 , pl = 3, cy = 5, sp = 4\n          ----------------- \n\n");

	for (int i = 0;  i < mini->sc.nb_objet; i++){
		
		printf("Type : %d\n", mini->sc.objet[i].type);
		printf("ID : %d\n", mini->sc.objet[i].id);
		if (mini->sc.objet[i].type != A)
		{
			printf("position : x = %f, y = %f, z = %f\n",
				mini->sc.objet[i].pos.x,
				mini->sc.objet[i].pos.y,
				mini->sc.objet[i].pos.z);
		}
		if (mini->sc.objet[i].type == cy || mini->sc.objet[i].type == pl)
		{
			printf("vecteur directon : x = %f, y = %f, z = %f\n",
				mini->sc.objet[i].vec_dir.x,
				mini->sc.objet[i].vec_dir.y,
				mini->sc.objet[i].vec_dir.z);
		}
		if (mini->sc.objet[i].type == A || mini->sc.objet[i].type == L)
			printf("ratio [0.0;1.0] : %f\n", mini->sc.objet[i].ratio);
		printf("color : r = %u, g = %u, b = %u\n",
			mini->sc.objet[i].color.r,
			mini->sc.objet[i].color.g,
			mini->sc.objet[i].color.b);
		if (mini->sc.objet[i].type == cy || mini->sc.objet[i].type == sp)
		{
			printf("diameter : %f\n", mini->sc.objet[i].diameter);
			if (mini->sc.objet[i].type == cy)
				printf("height : %f\n", mini->sc.objet[i].height);
		}
		printf("\n");

	}
}

// void	testcolor(t_mini *mini)
// {
// 	t_color	red = (t_color){255,0,0,0};
// 	t_color	blue = (t_color){0,0,255,0};
// 	t_color	green = (t_color){0,255,0,0};
// 	t_color	white = (t_color){255,255,255,0};

// 	for (int i = 0; i < HEIGHT ; i++){
// 		for (int j = 0; j < WIDTH; j++){
// 			my_mlx_pixel_put(mini, j, i, color_shift(color_multiplie(blue, green)));
// 		}
// 	}
// }

void	printVec(t_vec3	Ray)
{
	printf(" x: %f, y: %f, z: %f\n", Ray.x, Ray.y, Ray.z);
}

void	printObject(t_objet obj)
{
		printf("Type : %d\n",obj.type);
		printf("ID : %d\n",obj.id);
		if (obj.type != A)
		{
			printf("position : x = %f, y = %f, z = %f\n",
				obj.pos.x,
				obj.pos.y,
				obj.pos.z);
		}
		if (obj.type == cy ||obj.type == pl)
		{
			printf("vecteur directon : x = %f, y = %f, z = %f\n",
				obj.vec_dir.x,
				obj.vec_dir.y,
				obj.vec_dir.z);
		}
		if (obj.type == A ||obj.type == L)
			printf("ratio [0.0;1.0] : %f\n",obj.ratio);
		printf("color : r = %u, g = %u, b = %u\n",
			obj.color.r,
			obj.color.g,
			obj.color.b);
		if (obj.type == cy ||obj.type == sp)
		{
			printf("diameter : %f\n",obj.diameter);
			if (obj.type == cy)
				printf("height : %f\n",obj.height);
		}
		printf("\n");
}

void	printColor(t_color color)
{
	printf("r:%u ", color.r);
	printf("g:%u ", color.g);
	printf("b:%u\n", color.b);
}