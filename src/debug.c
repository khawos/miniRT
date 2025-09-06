#include "miniRT.h"

void	printAllCam(t_mini *mini){

	for (int i = 0; i < mini->scene.nb_cam; i++){

		printf("Camera ID : %d\n", mini->scene.cam[i].id);
		printf("position : x = %f, y = %f, z = %f\n",
			mini->scene.cam[i].pos[0],
			mini->scene.cam[i].pos[1],
			mini->scene.cam[i].pos[2]);
		printf("vecteur directon : x = %f, y = %f, z = %f\n",
			mini->scene.cam[i].vec_dir[0],
			mini->scene.cam[i].vec_dir[1],
			mini->scene.cam[i].vec_dir[2]);
		printf("fov : %d\n", mini->scene.cam[i].fov);
		printf("\n");
	}
}

void	printAllObject(t_mini *mini){

	for (int i = 0; i < mini->scene.nb_cam; i++){

		printf("Camera ID : %d\n", mini->scene.cam[i].id);
		printf("position : x = %f, y = %f, z = %f\n",
			mini->scene.cam[i].pos[0],
			mini->scene.cam[i].pos[1],
			mini->scene.cam[i].pos[2]);
		printf("vecteur directon : x = %f, y = %f, z = %f\n",
			mini->scene.cam[i].vec_dir[0],
			mini->scene.cam[i].vec_dir[1],
			mini->scene.cam[i].vec_dir[2]);
		printf("fov : %d\n", mini->scene.cam[i].fov);
		printf("\n");
	}

	printf("          ----- Object -----\n");
	printf("A = 0, L = 2 , pl = 3, cy = 5, sp = 4\n          ----------------- \n\n");

	for (int i = 0;  i < mini->scene.nb_objet; i++){
		
		printf("Type : %d\n", mini->scene.objet[i].type);
		printf("ID : %d\n", mini->scene.objet[i].id);
		if (mini->scene.objet[i].type != A)
		{
			printf("position : x = %f, y = %f, z = %f\n",
				mini->scene.objet[i].pos[0],
				mini->scene.objet[i].pos[1],
				mini->scene.objet[i].pos[2]);
		}
		if (mini->scene.objet[i].type == cy || mini->scene.objet[i].type == pl)
		{
			printf("vecteur directon : x = %f, y = %f, z = %f\n",
				mini->scene.objet[i].vec_dir[0],
				mini->scene.objet[i].vec_dir[1],
				mini->scene.objet[i].vec_dir[2]);
		}
		if (mini->scene.objet[i].type == A || mini->scene.objet[i].type == L)
			printf("ratio [0.0;1.0] : %f\n", mini->scene.objet[i].ratio);
		printf("color : r = %u, g = %u, b = %u\n",
			mini->scene.objet[i].color[0],
			mini->scene.objet[i].color[1],
			mini->scene.objet[i].color[2]);
		if (mini->scene.objet[i].type == cy || mini->scene.objet[i].type == sp)
		{
			printf("diameter : %f\n", mini->scene.objet[i].diameter);
			if (mini->scene.objet[i].type == cy)
				printf("height : %f\n", mini->scene.objet[i].height);
		}
		printf("\n");

	}
}