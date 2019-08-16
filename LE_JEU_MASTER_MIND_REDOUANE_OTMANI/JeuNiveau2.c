#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include <math.h>
#include "JeuNiveau1.h"
#include"JeuNiveau2.h"
#include "OrdinateurDevineNiveau1.h"
#include "OrdinateurDevineNiveau2.h"
#include "Score.h"

void chx_codeJeuNiveau2 (int code[4]) {
	srand(time(NULL));
	int i;
	for (i = 0; i < 4; i++) {
		code[i] = rand() % 8;
	}
}

void eval_codeJeuNiveau2 (int code[4], int prop[4], int res[2]) {
	res[0] = 0; res[1] = 0;
	int st_prop[4] = {0, 0, 0, 0};
	int st_code[4] = {0, 0, 0, 0};
	int i, j;

	for (i = 0; i < 4; i++) {
		if (prop[i] == code[i]) {
			res[0]++;
			st_prop[i] = 1;
			st_code[i] = 1;
		}
	}
	for (i = 0; i < 4; i++) {
		if (!st_prop[i]) {
			for (j = 0; j < 4; j++) {
				if (!st_code[j] && prop[i] == code[j]) {
					res[1]++;
					st_code[j] = 1;
					st_prop[i] = 1;
					break;
				}
			}
		}
	}
}

int all_fillJeuNiveau2 (int code[4]) {
	if (code[0] == -1 || code[1] == -1 || code[2] == -1 || code[3] == -1) {
		return 0;
	}
	return 1;
}

void init_pos_resJeuNiveau2 (SDL_Rect pos[2], int n) {
	int i;
	for (i = 0; i < 2; i++) {
		pos[i].x = 450 + 40 * i;
		pos[i].y = 380 - 35 * n;
	}
}

void init_pos_chxJeuNiveau2 (SDL_Rect pos[4], int n) {
	int i;
	for (i = 0; i < 4; i++) {
		pos[i].x = 230 + 50 * i;
		pos[i].y = 378 - 35 * n;
	}
}

void init_pos_optJeuNiveau2 (SDL_Rect pos[3], int n) {
	int i;
	for (i = 0; i < 3; i++) {
		pos[i].x = 450 + 40 * i;
		pos[i].y = 378 - 35 * n;
	}
}

int is_overJeuNiveau2 (int x, int y, SDL_Surface s, SDL_Rect p) {
	if (x > p.x && x < p.x+(&s)->w && y > p.y && y < p.y+(&s)->h) {
		return 1;
	}
	return 0;
}

int printJeuNiveau2 (SDL_Surface *ecran) {

	/* Chargement des images */
	/* Préparation de l'écran de jeu */
	SDL_Surface *jeu = IMG_Load("img/fond.png");

	SDL_Surface *vert = IMG_Load("img/vert.png");
	SDL_Surface *violet = IMG_Load("img/violet.png");
	SDL_Surface *rouge = IMG_Load("img/rouge.png");
	SDL_Surface *orange = IMG_Load("img/orange.png");
	SDL_Surface *noir = IMG_Load("img/noir.png");
	SDL_Surface *jaune = IMG_Load("img/jaune.png");
	SDL_Surface *bleu = IMG_Load("img/bleu.png");
	SDL_Surface *blanc = IMG_Load("img/blanc.png");

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

	SDL_Surface *vide = IMG_Load("img/vide.png");
	SDL_Surface *none = IMG_Load("img/none2.png");
	SDL_Surface *annul = IMG_Load("img/annul.png");
	SDL_Surface *valid = IMG_Load("img/valid.png");
	SDL_Surface *sec_g = IMG_Load("img/sec_g.png");
	SDL_Surface *sec_d = IMG_Load("img/sec_d.png");

	SDL_Surface *good = IMG_Load("img/good.png");
	SDL_Surface *bad = IMG_Load("img/bad.png");
	SDL_Surface *meh = IMG_Load("img/meh.png");
	SDL_Surface *abandon = IMG_Load("img/abandon.png");
	SDL_Surface *abandons = IMG_Load("img/abandons.png");
	SDL_Surface *jouer = IMG_Load("img/partie.png");
	SDL_Surface *jouers = IMG_Load("img/parties.png");
	SDL_Surface *menu = IMG_Load("img/menu2.png");
	SDL_Surface *menus = IMG_Load("img/menu2s.png");
	SDL_Surface *aide = IMG_Load("img/aide.png");
	SDL_Surface *aides = IMG_Load("img/aides.png");

	SDL_Surface *aide_g = IMG_Load("img/aide_g.png");
	SDL_Surface *none_aide_g = IMG_Load("img/none_assist_g.png");

	SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 213));

	SDL_Surface *pions[8] = { vert, violet, rouge, orange,
							  noir, jaune, bleu, blanc };
	SDL_Surface *p_rouge[5] = { p_rouge0, p_rouge1, p_rouge2,
								p_rouge3, p_rouge4};
	SDL_Surface *p_blanc[5] = { p_blanc0, p_blanc1, p_blanc2,
								p_blanc3, p_blanc4};

	SDL_Rect posp[8]; // position des pions
	SDL_Rect pos = {0, 0}; // position de l'écran de jeu
	SDL_Rect pos_sec[2] = {{180, 8}, {410, 8}}; // position de 'secret'
	SDL_Rect pos_reg = {40, 440}; // position du bouton 'Règles'
	SDL_Rect pos_jou = {240, 440}; // position du bouton 'Nouvelle partie'
	SDL_Rect pos_men = {440, 440}; // position du bouton 'Menu'
	SDL_Rect pos_chx[4]; // position des réceptacles des pions
	SDL_Rect pos_opt[3]; // position des boutons
	SDL_Rect pos_res[2]; // position des pastilles d'évaluation
	SDL_Rect pos_smiley = {470, 10};
	SDL_Rect pos_aide = {70, 4};

	SDL_BlitSurface(jeu, NULL, ecran, &pos);
//la position des 8 pions
int i, j;
	for (i = 0; i < 2; i++) {
		posp[i].x = 40 + 60 * i;
		posp[i].y = 230;

		SDL_SetColorKey(pions[i], SDL_SRCCOLORKEY, SDL_MapRGB(pions[i]->format, 68, 116, 213));
		SDL_BlitSurface(pions[i], NULL, ecran, &posp[i]);
	}
    for (i = 2; i < 4; i++) {
		posp[i].x = -79 + 60 * i;
		posp[i].y = 280;

		SDL_SetColorKey(pions[i], SDL_SRCCOLORKEY, SDL_MapRGB(pions[i]->format, 68, 116, 213));
		SDL_BlitSurface(pions[i], NULL, ecran, &posp[i]);
	}
	for (i = 4; i < 6; i++) {
		posp[i].x = -199 + 60 * i;
		posp[i].y = 330;
		SDL_SetColorKey(pions[i], SDL_SRCCOLORKEY, SDL_MapRGB(pions[i]->format, 68, 116, 213));
		SDL_BlitSurface(pions[i], NULL, ecran, &posp[i]);
	}
    for(i = 6; i < 8; i++) {
		posp[i].x = -319 + 60 * i;
		posp[i].y = 380;
		SDL_SetColorKey(pions[i], SDL_SRCCOLORKEY, SDL_MapRGB(pions[i]->format, 68, 116, 213));
		SDL_BlitSurface(pions[i], NULL, ecran, &posp[i]);
	}

	for (j = 0; j < 10; j++) {
		init_pos_chxJeuNiveau2 (pos_chx, j);
		for (i = 0; i < 4; i++) {
			SDL_BlitSurface(vide, NULL, ecran, &pos_chx[i]);
		}
	}

	init_pos_chxJeuNiveau2(pos_chx, 0);
	init_pos_optJeuNiveau2(pos_opt, 0);
	init_pos_resJeuNiveau2(pos_res, 0);

	SDL_BlitSurface(annul, NULL, ecran, &pos_opt[0]);
	SDL_BlitSurface(abandon, NULL, ecran, &pos_jou);
	SDL_BlitSurface(aide, NULL, ecran, &pos_reg);
	SDL_BlitSurface(menu, NULL, ecran, &pos_men);


	/* Jeu à proprement parler */
	/* Variables utiles */
	int continuer = 1;
	int idx = -1;
	int pass = 0;
	int x_m, y_m;
	SDL_Event event;
	int n = 0;
	int over = 0;

	int * poss = malloc(pow(8, 4) * sizeof(int));
	int s_possible = 4096;
	int au = 0; // aide utilisée

	int *tab[10][2];
	for (j = 0; j < 10; j++) {
		tab[j][0] = malloc(4 * sizeof(int));
		for (i = 0; i < 4; i++) {
			tab[j][0][i] = -1;
		}
		tab[j][1] = malloc(2 * sizeof(int));
		for (i = 0; i < 2; i++) {
			tab[j][1][i] = 0;
		}
	}

	for (i = 0; i < s_possible; i++) {
		poss[i] = 1;
	}

	/* Choix du code */
	int code[4];
	chx_codeJeuNiveau2(code);
	SDL_BlitSurface(sec_g, NULL, ecran, &pos_sec[0]);
	SDL_BlitSurface(sec_d, NULL, ecran, &pos_sec[1]);

	inc_score(1, 0, 0);

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

            	if (!over) {
            		if (is_overJeuNiveau2(x_m, y_m, *annul, pos_opt[0])) {
            			SDL_BlitSurface(vide, NULL, ecran, &pos_opt[0]);
            		} else if (all_fillJeuNiveau2(tab[n][0]) && is_overJeuNiveau2(x_m, y_m, *valid, pos_opt[1])) {
            			SDL_BlitSurface(vide, NULL, ecran, &pos_opt[1]);
            		} else if (all_fillJeuNiveau2(tab[n][0])) {
            			SDL_BlitSurface(valid, NULL, ecran, &pos_opt[1]);
            			SDL_BlitSurface(annul, NULL, ecran, &pos_opt[0]);
            		} else {
            			SDL_BlitSurface(annul, NULL, ecran, &pos_opt[0]);
            		}
            	}

            	if (is_overJeuNiveau2(x_m, y_m, *jouer, pos_jou)) {
            		if (!over) {
            			SDL_BlitSurface(abandons, NULL, ecran, &pos_jou);
            		} else {
            			SDL_BlitSurface(jouers, NULL, ecran, &pos_jou);
            		}
            	} else if (is_overJeuNiveau2(x_m, y_m, *menu, pos_men)) {
            		SDL_BlitSurface(menus, NULL, ecran, &pos_men);
            	} else if (!over && is_overJeuNiveau2(x_m, y_m, *aide, pos_reg)) {
            		SDL_BlitSurface(aides, NULL, ecran, &pos_reg);
            		SDL_BlitSurface(aide_g, NULL, ecran, &pos_aide);
            	}
            	 else if (!over) {
            		SDL_BlitSurface(abandon, NULL, ecran, &pos_jou);
            		SDL_BlitSurface(menu, NULL, ecran, &pos_men);
            		SDL_BlitSurface(aide, NULL, ecran, &pos_reg);

            		SDL_BlitSurface(none_aide_g, NULL, ecran, &pos_aide);
            		SDL_BlitSurface(sec_g, NULL, ecran, &pos_sec[0]);
					SDL_BlitSurface(sec_d, NULL, ecran, &pos_sec[1]);
            	} else {
            		SDL_BlitSurface(jouer, NULL, ecran, &pos_jou);
            		SDL_BlitSurface(menu, NULL, ecran, &pos_men);
            		SDL_BlitSurface(aide, NULL, ecran, &pos_reg);
            	}
            	break;

            case SDL_MOUSEBUTTONUP:
		        x_m = event.button.x;
		       	y_m = event.button.y;

		       	if (over && is_overJeuNiveau2(x_m, y_m, *jouer, pos_jou)) {
            		continuer = 3;
            		pass = 1;
            	} else if (is_overJeuNiveau2(x_m, y_m, *menu, pos_men)) {
            		continuer = 2;
            		pass = 1;
            	}

            	/* Bouton 'abandon' */
            	if (!pass && !over) {
            		if (is_overJeuNiveau2(x_m, y_m, *jouer, pos_jou)) {
		    			for (i = 0; i < 4; i++) {
							pos_chx[i].x = 230 + 50 * i;
							pos_chx[i].y = 17;

							SDL_BlitSurface(vide, NULL, ecran, &pos_chx[i]);
							SDL_BlitSurface(pions[code[i]], NULL, ecran, &pos_chx[i]);
							SDL_BlitSurface(meh, NULL, ecran, &pos_smiley);
							SDL_BlitSurface(jouers, NULL, ecran, &pos_jou);
							over = 1;
						}
					}
            	}

		       	/* Bouton 'effacer' */
		       	if (!pass && !over) {
		        	if (is_overJeuNiveau2(x_m, y_m, *annul, pos_opt[0])) {
		        		SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 212));
		        		for (i = 0; i < 4; i++) {
		        			tab[n][0][i] = -1;
		        			SDL_BlitSurface(vide, NULL, ecran, &pos_chx[i]);
		        		}
		        		SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 213));
		        		SDL_BlitSurface(none, NULL, ecran, &pos_opt[1]);
		        		pass = 1;
		        	}
		        }



		        /* Bouton 'valider' */
		        if (!pass && !over) {
		        	if (all_fillJeuNiveau2(tab[n][0]) && is_overJeuNiveau2(x_m, y_m, *valid, pos_opt[1])) {
		        		SDL_BlitSurface(none, NULL, ecran, &pos_opt[0]);
		        		SDL_BlitSurface(none, NULL, ecran, &pos_opt[1]);
		        		SDL_BlitSurface(none, NULL, ecran, &pos_opt[2]);
		        		eval_codeJeuNiveau2(code, tab[n][0], tab[n][1]);
						if (n == 9 || tab[n][1][0] == 4) {
		        			for (i = 0; i < 4; i++) {
								pos_chx[i].x = 230 + 50 * i;
								pos_chx[i].y = 17;

								SDL_BlitSurface(vide, NULL, ecran, &pos_chx[i]);
								SDL_BlitSurface(pions[code[i]], NULL, ecran, &pos_chx[i]);
							}
							if (tab[n][1][0] == 4) {
								inc_score(0, 1, 1-au);
								SDL_BlitSurface(good, NULL, ecran, &pos_smiley);
							} else {
								SDL_BlitSurface(bad, NULL, ecran, &pos_smiley);
							}
							SDL_BlitSurface(jouer, NULL, ecran, &pos_jou);
							over = 1;
		        		} else {
				    		SDL_BlitSurface(p_rouge[tab[n][1][0]], NULL, ecran, &pos_res[0]);
				    		SDL_BlitSurface(p_blanc[tab[n][1][1]], NULL, ecran, &pos_res[1]);
		        			n++;
		        			init_pos_chxJeuNiveau2(pos_chx, n);
							init_pos_resJeuNiveau2(pos_res, n);
							init_pos_optJeuNiveau2(pos_opt, n);
							s_possible = nb_remainOrdinateurDevineNiveau1 (tab, n, poss);
							SDL_BlitSurface(annul, NULL, ecran, &pos_opt[0]);

							for (i = 0; i < 4; i++) { tab[n][0][i] = -1; }
		        		}
		        		pass = 1;
		        	}
		        }

		       	/* Apposition d'une couleur */
		       	if (!pass && !over) {
				   	for (i = 0; i < 4; i++) {
					   	if (is_overJeuNiveau2(x_m, y_m, *vide, pos_chx[i])) {
					   		if (idx > -1) {
					   			SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 212));
					   			SDL_BlitSurface(vide, NULL, ecran, &pos_chx[i]);
					   			SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 213));
					   			SDL_BlitSurface(pions[idx], NULL, ecran, &pos_chx[i]);
					   			tab[n][0][i] = idx;

					   			if (all_fillJeuNiveau2(tab[n][0])) {
					   				SDL_BlitSurface(valid, NULL, ecran, &pos_opt[1]);
					   			}

					   		} else {
					   			SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 212));
					   			SDL_BlitSurface(vide, NULL, ecran, &pos_chx[i]);
					   			SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 213));
					   			tab[n][0][i] = -1;
					   			SDL_BlitSurface(none, NULL, ecran, &pos_opt[1]);
					   		}
					   		pass = 1;
					   		break;
					   	}
					}
				}

		       	/* Sélection d'une couleur */
		       	if (!pass && !over) {
				   	for (i = 0; i < 8; i++) {
		        		if (is_overJeuNiveau2(x_m, y_m, *pions[i], posp[i])) {
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

		        pass = 0;
            	break;

           	default:
           		break;
       	}
       	SDL_Flip(ecran);
    }

	return continuer;
}
