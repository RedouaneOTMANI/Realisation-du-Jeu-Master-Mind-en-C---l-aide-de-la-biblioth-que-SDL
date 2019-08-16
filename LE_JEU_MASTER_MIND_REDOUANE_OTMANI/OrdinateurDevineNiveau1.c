#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include "JeuNiveau1.h"
#include"JeuNiveau2.h"
#include "OrdinateurDevineNiveau1.h"
#include "OrdinateurDevineNiveau2.h"
#include"DUP.h"
//la position des fléches < > on va les utilisér pour incrimenter ou decrementer combien de boules
//postion et combien de boule dans la mauvaise position
void init_pos_fleOrdinateurDevineNiveau1 (SDL_Rect pos[4], int n) {
	int i;
	pos[0].x = 445;
	pos[1].x = 480;
	pos[2].x = 515;
	pos[3].x = 550;

	for (i = 0; i < 4; i++) {
		pos[i].y = 378 - 35*n;
	}
}

//la position des : -Botton valider , et les 2 couleur blanche et rouge
void init_pos_evaOrdinateurDevineNiveau1 (SDL_Rect pos[3], int n) {
	int i;
	for (i = 0; i < 3; i++) {
		pos[i].x = 460 + 70 * i;
		pos[i].y = 378 - 35 * n;
	}
}

//la position des Fléche vers le Haut et Fléche vers le Bas
void init_pos_evoOrdinateurDevineNiveau1 (SDL_Rect pos[2], int n) {
	int i;
	for (i = 0; i < 2; i++) {
		pos[i].x = 140 + 40 * i;
		pos[i].y = 378 - 35 * n;
	}
}

//la position du Nombre combien de combinaison rest
void init_pos_nbOrdinateurDevineNiveau1 (SDL_Rect pos[4], int n) {
	int i;
	for (i = 0; i < 4; i++) {
		pos[i].x = 150 + 15 * i;
		pos[i].y = 378 - 35 * n;
	}
}

int ready_togoOrdinateurDevineNiveau1 (int code[4], int n_past[2], int n, int sens) { /* 0 = haut, 1 = bas */
	if (sens == 0) {
		if (all_fillJeuNiveau1(code) && n_past[0] + n_past[1] <= 4 && n < 9) {
			return 1;
		}
		return 0;
	}
	if (n > 0) {
		return 1;
	}
	return 0;
}

/* Nombre de possibilités */
int nb_remainOrdinateurDevineNiveau1 (int * tab[10][2], int n, int * poss) {
	int blank4[4];
	int blank2[2];
	int i, j;

	int s = 0;

	for (i = 0; i < pow(6, 4); i++) {
		poss[i] = 1;
		for (j = 0; j < n; j++) {
			decodeOrdinateurDevineNiveau1(i, blank4);
			eval_codeJeuNiveau1(blank4, tab[j][0], blank2);

			if (blank2[0] != tab[j][1][0] || blank2[1] != tab[j][1][1]) {
				poss[i] = 0;
				break;
			}
		}
		s += poss[i];
	}

	return s;
}

/* VALIDER */
void assistOrdinateurDevineNiveau1 (int * tab[10][2], int n, int * poss, int s, int conseil[4]) {
	if (s > 0) {
		srand(time(NULL));
		int i = 1+rand() % s;
		int j = 0;
		int k = -1;

		while (j < i) {
			if (poss[++k] == 1) {
				j++;
			}
		}
		decodeOrdinateurDevineNiveau1(k, conseil);
	} else {
		conseil[0] = -1;
	}
}

void decodeOrdinateurDevineNiveau1(int code, int a[4]) {
a[3] = code / pow(6, 3);
	code -= a[3] * pow(6, 3);
	a[2] = code / pow(6, 2);
	code -= a[2] * pow(6, 2);
	a[1] = code / pow(6, 1);
	code -= a[1] * 6;
	a[0] = code;
}

void nb_decompoOrdinateurDevineNiveau1(int nb, int a[4]) {
 a[0] = nb / 1000;
	nb -= 1000 * a[0];
	a[1] = nb / 100;
	nb -= 100 * a[1];
	a[2] = nb / 10;
	nb -= 10 * a[2];
	a[3] = nb;
}

int printOrdinateurDevineNiveau1(SDL_Surface *ecran) {

	/* Chargement des images */
	/* Préparation de l'écran de jeu */
	SDL_Surface *jeu = IMG_Load("img/fond.png");

	SDL_Surface *vert = IMG_Load("img/vert.png");
	SDL_Surface *violet = IMG_Load("img/violet.png");
	SDL_Surface *rouge = IMG_Load("img/rouge.png");
	SDL_Surface *orange = IMG_Load("img/orange.png");
	SDL_Surface *jaune = IMG_Load("img/jaune.png");
	SDL_Surface *bleu = IMG_Load("img/bleu.png");


	SDL_Surface *p_rouge0 = IMG_Load("img/p_rouge0.png");
	SDL_Surface *p_rouge1 = IMG_Load("img/p_rouge1.png");
	SDL_Surface *p_rouge2 = IMG_Load("img/p_rouge2.png");
	SDL_Surface *p_rouge3 = IMG_Load("img/p_rouge3.png");
	SDL_Surface *p_rouge4 = IMG_Load("img/p_rouge4.png");
	SDL_Surface *p_blanc0 = IMG_Load("img/p_blanc0.png");
	SDL_Surface *p_blanc1 = IMG_Load("img/p_blanc1.png");
	SDL_Surface *p_blanc2 = IMG_Load("img/p_blanc2.png");
	SDL_Surface *p_blanc3 = IMG_Load("img/p_blanc3.png");
	SDL_Surface *p_blanc4 = IMG_Load("img/p_blanc4.png");
	SDL_Surface *p_gauche = IMG_Load("img/p_gauche.png");
	SDL_Surface *p_droite = IMG_Load("img/p_droite.png");
	SDL_Surface *p_none = IMG_Load("img/p_none.png");

	SDL_Surface *vide = IMG_Load("img/vide.png");
	SDL_Surface *none = IMG_Load("img/none2.png");
	SDL_Surface *haut = IMG_Load("img/haut.png");
	SDL_Surface *bas = IMG_Load("img/bas.png");
	SDL_Surface *hauts = IMG_Load("img/hauts.png");
	SDL_Surface *bass = IMG_Load("img/bass.png");

	SDL_Surface *nb0 = IMG_Load("img/nb0.png");
	SDL_Surface *nb1 = IMG_Load("img/nb1.png");
	SDL_Surface *nb2 = IMG_Load("img/nb2.png");
	SDL_Surface *nb3 = IMG_Load("img/nb3.png");
	SDL_Surface *nb4 = IMG_Load("img/nb4.png");
	SDL_Surface *nb5 = IMG_Load("img/nb5.png");
	SDL_Surface *nb6 = IMG_Load("img/nb6.png");
	SDL_Surface *nb7 = IMG_Load("img/nb7.png");
	SDL_Surface *nb8 = IMG_Load("img/nb8.png");
	SDL_Surface *nb9 = IMG_Load("img/nb9.png");

	SDL_Surface *menu = IMG_Load("img/menu2.png");
	SDL_Surface *menus = IMG_Load("img/menu2s.png");


	SDL_Surface *aide = IMG_Load("img/aide.png");
	SDL_Surface *aides = IMG_Load("img/aides.png");
	SDL_Surface *help = IMG_Load("img/help.png");
	SDL_Surface *helps = IMG_Load("img/helps.png");

	SDL_Surface *aide_g = IMG_Load("img/assist_g.png");
	SDL_Surface *none_aide_g = IMG_Load("img/none_assist_g.png");

	SDL_Surface *sec_g = IMG_Load("img/sec_g.png");
	SDL_Surface *sec_d = IMG_Load("img/sec_d.png");
    SDL_Rect pos_sec[2] = {{180, 8}, {410, 8}}; // position de la combinaison qu'on va choisir
	SDL_BlitSurface(sec_g, NULL, ecran, &pos_sec[0]);
	SDL_BlitSurface(sec_d, NULL, ecran, &pos_sec[1]);


	SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 213));

	SDL_Surface *pions[6] = { vert, violet, rouge, orange,jaune, bleu};
	SDL_Surface *p_rouge[5] = { p_rouge0, p_rouge1, p_rouge2,
								p_rouge3, p_rouge4};
	SDL_Surface *p_blanc[5] = { p_blanc0, p_blanc1, p_blanc2,
								p_blanc3, p_blanc4};
	SDL_Surface *nb[10] = { nb0, nb1, nb2, nb3, nb4,
							nb5, nb6, nb7, nb8, nb9};

	SDL_Rect posp[6]; // position des pions
	SDL_Rect pos = {0, 0}; // position de l'écran de jeu
	SDL_Rect pos_men = {440, 440}; // position du bouton 'Menu'
	SDL_Rect pos_reg = {40, 440};
	SDL_Rect pos_reset = {240, 440};
	SDL_Rect pos_chx[4]; // position des réceptacles des pions
	SDL_Rect pos_eva[3]; // position des pastilles d'évaluation
	SDL_Rect pos_fle[4]; // position des fléchettes
	SDL_Rect pos_evo[2]; // position des flèches haut/bas
	SDL_Rect pos_nb[4]; // position du nombre de combinaisons restantes
	SDL_Rect pos_aide = {110, 4};

	SDL_BlitSurface(jeu, NULL, ecran, &pos);
//la position des 6 pions
	int i, j;
	for (i = 0; i < 2; i++) {
		posp[i].x = 40 + 60 * i;
		posp[i].y = 280;

		SDL_SetColorKey(pions[i], SDL_SRCCOLORKEY, SDL_MapRGB(pions[i]->format, 68, 116, 213));
		SDL_BlitSurface(pions[i], NULL, ecran, &posp[i]);
	}
for (i = 2; i < 4; i++) {
		posp[i].x = -79 + 60 * i;
		posp[i].y = 330;

		SDL_SetColorKey(pions[i], SDL_SRCCOLORKEY, SDL_MapRGB(pions[i]->format, 68, 116, 213));
		SDL_BlitSurface(pions[i], NULL, ecran, &posp[i]);
	}
	for (i = 4; i < 6; i++) {
		posp[i].x = -199 + 60 * i;
		posp[i].y = 380;
		SDL_SetColorKey(pions[i], SDL_SRCCOLORKEY, SDL_MapRGB(pions[i]->format, 68, 116, 213));
		SDL_BlitSurface(pions[i], NULL, ecran, &posp[i]);
	}

	for (j = 0; j < 10; j++) {
		init_pos_chxJeuNiveau1 (pos_chx, j);
		for (i = 0; i < 4; i++) {
			SDL_BlitSurface(vide, NULL, ecran, &pos_chx[i]);
		}
	}

	init_pos_chxJeuNiveau1(pos_chx, 0);
	init_pos_fleOrdinateurDevineNiveau1(pos_fle, 0);
	init_pos_evaOrdinateurDevineNiveau1(pos_eva, 0);
	init_pos_evoOrdinateurDevineNiveau1(pos_evo, 0);
	init_pos_nbOrdinateurDevineNiveau1(pos_nb, 0);

	SDL_BlitSurface(menu, NULL, ecran, &pos_men);
	SDL_BlitSurface(aide, NULL, ecran, &pos_reg);

	SDL_BlitSurface(p_rouge0, NULL, ecran, &pos_eva[0]);
	SDL_BlitSurface(p_blanc0, NULL, ecran, &pos_eva[1]);
	SDL_BlitSurface(p_droite, NULL, ecran, &pos_fle[1]);
	SDL_BlitSurface(p_droite, NULL, ecran, &pos_fle[3]);
	SDL_BlitSurface(help, NULL, ecran, &pos_eva[2]);

	/* Jeu à proprement parler */
	/* Variables utiles */
	SDL_Event event;

	int continuer = 1;
	int idx = -1;
	int pass = 0;
	int x_m, y_m;
	int n = 0;
	int chgt = 0;
	int blank4[4];

	int * poss = malloc(pow(6, 4) * sizeof(int));
	int s_possible = 1296;

	int *tab[10][2];
	for (j = 0; j < 10; j++) {
		tab[j][0] = malloc(4);
		for (i = 0; i < 4; i++) {
			tab[j][0][i] = -1;
		}
		tab[j][1] = malloc(2);
		for (i = 0; i < 2; i++) {
			tab[j][1][i] = 0;
		}
	}

	for (i = 0; i < s_possible; i++) {
		poss[i] = 1;
	}
	inc_score(1, 0, 1);

	SDL_Flip(ecran);

	while (continuer == 1) {
    	SDL_WaitEvent(&event);
        switch (event.type) {
           	case SDL_QUIT:
               	continuer = 0;
               	break;

            case SDL_MOUSEMOTION:
            	x_m = event.motion.x;
            	y_m = event.motion.y;

            	if (is_overJeuNiveau1(x_m, y_m, *menu, pos_men)) {
            		SDL_BlitSurface(menus, NULL, ecran, &pos_men);
            	}  else if (is_overJeuNiveau1(x_m, y_m, *aide, pos_reg)) {
            		SDL_BlitSurface(aides, NULL, ecran, &pos_reg);
            		SDL_BlitSurface(aide_g, NULL, ecran, &pos_aide);
            	} else if (ready_togoOrdinateurDevineNiveau1(tab[n][0], tab[n][1], n, 0) && is_overJeuNiveau1(x_m, y_m, *haut, pos_evo[0])) {
            		SDL_BlitSurface(hauts, NULL, ecran, &pos_evo[0]);
            	} else if (ready_togoOrdinateurDevineNiveau1(tab[n][0], tab[n][1], n, 1) && is_overJeuNiveau1(x_m, y_m, *haut, pos_evo[1])) {
            		SDL_BlitSurface(bass, NULL, ecran, &pos_evo[1]);
            	} else if (is_overJeuNiveau1(x_m, y_m, *help, pos_eva[2])) {
            		SDL_BlitSurface(helps, NULL, ecran, &pos_eva[2]);
            	} else {
            		SDL_BlitSurface(menu, NULL, ecran, &pos_men);
            		SDL_BlitSurface(aide, NULL, ecran, &pos_reg);
            		SDL_BlitSurface(none_aide_g, NULL, ecran, &pos_aide);
            		SDL_BlitSurface(help, NULL, ecran, &pos_eva[2]);

            		if (ready_togoOrdinateurDevineNiveau1(tab[n][0], tab[n][1], n, 0)) {
            			SDL_BlitSurface(haut, NULL, ecran, &pos_evo[0]);
            		}
            		if (ready_togoOrdinateurDevineNiveau1(tab[n][0], tab[n][1], n, 1)) {
            			SDL_BlitSurface(bas, NULL, ecran, &pos_evo[1]);
            		}
            	}
            	break;

            case SDL_MOUSEBUTTONUP:
		        x_m = event.button.x;
		       	y_m = event.button.y;

		       	/* Bouton menu */
		       	if (is_overJeuNiveau1(x_m, y_m, *menu, pos_men)) {
            		continuer = 2;
            		pass = 1;
            	} else {
            		SDL_BlitSurface(menu, NULL, ecran, &pos_men);
            	}

		       	/* Apposition d'une couleur */
		       	if (!pass) {
				   	for (i = 0; i < 4; i++) {
					   	if (is_overJeuNiveau1(x_m, y_m, *vide, pos_chx[i])) {
					   		if (idx > -1) {
					   			SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 212));
					   			SDL_BlitSurface(vide, NULL, ecran, &pos_chx[i]);
					   			SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 213));
					   			SDL_BlitSurface(pions[idx], NULL, ecran, &pos_chx[i]);
					   			tab[n][0][i] = idx;
					   			if (ready_togoOrdinateurDevineNiveau1(tab[n][0], tab[n][1], n, 0)) {
					   				SDL_BlitSurface(haut, NULL, ecran, &pos_evo[0]);
					   			}
					   		} else {
					   			SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 212));
					   			SDL_BlitSurface(vide, NULL, ecran, &pos_chx[i]);
					   			SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 213));
					   			SDL_BlitSurface(none, NULL, ecran, &pos_evo[0]);
					   			tab[n][0][i] = -1;
					   		}
					   		pass = 1;
					   		break;
					   	}
					}
				}

		       	/* Sélection d'une couleur */
		       	if (!pass) {
				   	for (i = 0; i < 6; i++) {
		        		if (is_overJeuNiveau1(x_m, y_m, *pions[i], posp[i])) {
		        			if (idx > -1) {
		        				SDL_SetColorKey(pions[idx], SDL_SRCCOLORKEY, SDL_MapRGB(pions[idx]->format, 68, 116, 212));
		        				SDL_BlitSurface(pions[idx], NULL, ecran, &posp[idx]);
		        				SDL_SetColorKey(pions[idx], SDL_SRCCOLORKEY, SDL_MapRGB(pions[idx]->format, 68, 116, 213));
		        			}
		        			if (i != idx) {
				    			SDL_BlitSurface(vide, NULL, ecran, &posp[i]);
				    			idx = i;
				    		} else {
				    			 idx = -1;
				    		}
				    		pass = 1;
		       				break;
		        		}
		        	}
		        }

		        /*

		        Conseil */
		        if (!pass) {
		        	if (is_overJeuNiveau1(x_m, y_m, *help, pos_eva[2])) {
		        		assistOrdinateurDevineNiveau1(tab, n, poss, s_possible, blank4);
						if (blank4[0] != -1) {
							for (i = 0; i < 4; i++) {
				    			SDL_BlitSurface(pions[blank4[i]], NULL, ecran, &pos_chx[i]);
				    			tab[n][0][i] = blank4[i];
				    		}
				    	}
		        	}
		        }

		        /* Flèches des pastilles */
		        if (!pass) {
		        	if (is_overJeuNiveau1(x_m, y_m, *p_droite, pos_fle[1]) && tab[n][1][0] < 4) {
		        		SDL_BlitSurface(p_rouge[++tab[n][1][0]], NULL, ecran, &pos_eva[0]);
		        		SDL_BlitSurface(p_gauche, NULL, ecran, &pos_fle[0]);
		        		if (tab[n][1][0] == 4) {
		        			SDL_BlitSurface(p_none, NULL, ecran, &pos_fle[1]);
		        		}
		        		pass = 1;
		        	} else if (is_overJeuNiveau1(x_m, y_m, *p_gauche, pos_fle[0]) && tab[n][1][0] > 0) {
		        		SDL_BlitSurface(p_rouge[--tab[n][1][0]], NULL, ecran, &pos_eva[0]);
		        		SDL_BlitSurface(p_droite, NULL, ecran, &pos_fle[1]);
		        		if (tab[n][1][0] == 0) {
		        			SDL_BlitSurface(p_none, NULL, ecran, &pos_fle[0]);
		        		}
		        		pass = 1;
		        	} else if (is_overJeuNiveau1(x_m, y_m, *p_droite, pos_fle[3]) && tab[n][1][1] < 4) {
		        		SDL_BlitSurface(p_blanc[++tab[n][1][1]], NULL, ecran, &pos_eva[1]);
		        		SDL_BlitSurface(p_gauche, NULL, ecran, &pos_fle[2]);
		        		if (tab[n][1][1] == 4) {
		        			SDL_BlitSurface(p_none, NULL, ecran, &pos_fle[3]);
		        		}
		        		pass = 1;
		        	} else if (is_overJeuNiveau1(x_m, y_m, *p_gauche, pos_fle[2]) && tab[n][1][1] > 0) {
		        		SDL_BlitSurface(p_blanc[--tab[n][1][1]], NULL, ecran, &pos_eva[1]);
		        		SDL_BlitSurface(p_droite, NULL, ecran, &pos_fle[3]);
		        		if (tab[n][1][1] == 0) {
		        			SDL_BlitSurface(p_none, NULL, ecran, &pos_fle[2]);
		        		}
		        	}

		        	if (ready_togoOrdinateurDevineNiveau1(tab[n][0], tab[n][1], n, 0)) {
						SDL_BlitSurface(haut, NULL, ecran, &pos_evo[0]);
					} else {
						SDL_BlitSurface(none, NULL, ecran, &pos_evo[0]);
					}
					if (ready_togoOrdinateurDevineNiveau1(tab[n][0], tab[n][1], n, 1)) {
						SDL_BlitSurface(bas, NULL, ecran, &pos_evo[1]);
					} else {
						SDL_BlitSurface(none, NULL, ecran, &pos_evo[1]);
					}
		        }

		        /* Flèches d'évolution */
			    if (!pass) {
			    	if (ready_togoOrdinateurDevineNiveau1(tab[n][0], tab[n][1], n, 0) && is_overJeuNiveau1(x_m, y_m, *haut, pos_evo[0])) {
			    		chgt = 1;
			    	} else if (ready_togoOrdinateurDevineNiveau1(tab[n][0], tab[n][1], n, 1) && is_overJeuNiveau1(x_m, y_m, *bas, pos_evo[1])) {
			    		chgt = -1;
			    	}

			    	if (chgt != 0) {
						for (i = 0; i < 4; i++) {
							SDL_BlitSurface(p_none, NULL, ecran, &pos_fle[i]);
						}
						for (i = 0; i < 2; i++) {
							SDL_BlitSurface(none, NULL, ecran, &pos_evo[i]);
						}

						SDL_BlitSurface(none, NULL, ecran, &pos_eva[2]);

						n += chgt;
						s_possible = nb_remainOrdinateurDevineNiveau1 (tab, n, poss);

						if (chgt > 0) {
							nb_decompoOrdinateurDevineNiveau1(s_possible, blank4);

							j = 0;
							for (i = 0; i < 4; i++) {
								if (j == 0) {
									if (blank4[i] > 0 || i == 3) {
										SDL_BlitSurface(nb[blank4[i]], NULL, ecran, &pos_nb[i]);
										j = 1;
									}
								} else {
									SDL_BlitSurface(nb[blank4[i]], NULL, ecran, &pos_nb[i]);
								}
							}
							init_pos_nbOrdinateurDevineNiveau1(pos_nb, n);

						} else {
							init_pos_nbOrdinateurDevineNiveau1(pos_nb, n);
							SDL_BlitSurface(none, NULL, ecran, &pos_nb[0]);
							SDL_BlitSurface(none, NULL, ecran, &pos_nb[2]);
						}

						chgt = 0;

			    		init_pos_chxJeuNiveau1(pos_chx, n);
						init_pos_fleOrdinateurDevineNiveau1(pos_fle, n);
						init_pos_evaOrdinateurDevineNiveau1(pos_eva, n);
						init_pos_evoOrdinateurDevineNiveau1(pos_evo, n);

						SDL_BlitSurface(help, NULL, ecran, &pos_eva[2]);

						if (tab[n][1][0] == 0 && tab[n][1][1] == 0) {
							SDL_BlitSurface(p_rouge0, NULL, ecran, &pos_eva[0]);
							SDL_BlitSurface(p_blanc0, NULL, ecran, &pos_eva[1]);
						}
						if (tab[n][1][0] > 0) {
							SDL_BlitSurface(p_gauche, NULL, ecran, &pos_fle[0]);
						}
						if (tab[n][1][0] < 4) {
							SDL_BlitSurface(p_droite, NULL, ecran, &pos_fle[1]);
						}
						if (tab[n][1][1] > 0) {
							SDL_BlitSurface(p_gauche, NULL, ecran, &pos_fle[2]);
						}
						if (tab[n][1][1] < 4) {
							SDL_BlitSurface(p_droite, NULL, ecran, &pos_fle[3]);
						}
						if (ready_togoOrdinateurDevineNiveau1(tab[n][0], tab[n][1], n, 0)) {
							SDL_BlitSurface(haut, NULL, ecran, &pos_evo[0]);
						}
						if (ready_togoOrdinateurDevineNiveau1(tab[n][0], tab[n][1], n, 1)) {
							SDL_BlitSurface(bas, NULL, ecran, &pos_evo[1]);
						}

						pass = 1;
					}
	        	}

		        pass = 0;

           	default:
           		break;
       	}
       	SDL_Flip(ecran);
    }

	return continuer;
}
