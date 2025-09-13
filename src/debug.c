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

void	printVec(t_vec3	Ray)
{
	printf(" x: %f, y: %f, z: %f\n", Ray.x, Ray.y, Ray.z);
}