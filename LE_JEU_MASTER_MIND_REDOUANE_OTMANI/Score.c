#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Score.h"
#include "JeuNiveau1.h"
#include"JeuNiveau2.h"
#include "OrdinateurDevineNiveau1.h"
#include "OrdinateurDevineNiveau2.h"

/// Renvoie 'a' le nombres de parties.
   /// 'b' le nombre de victoires.
 int is_over (int x, int y, SDL_Surface s, SDL_Rect p) {
	if (x > p.x && x < p.x+(&s)->w && y > p.y && y < p.y+(&s)->h) {
		return 1;
	}
	return 0;
}


void ecrire_score (char data[3][6]) {
	FILE *f_stats = fopen("DATA", "w");//notre fichier en mode ecriture
	if (f_stats == NULL) {
		exit(EXIT_FAILURE);
	}
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; data[i][j] != '\0'; j++) {
			fputc((int)data[i][j], f_stats);
		}
		if (i != 2) {
			fputc(' ', f_stats);
		}
	}
	fclose(f_stats);
}
void lire_score (char data[3][6] /*dans un tableau de caractére */) {
	FILE *f_stats = fopen("DATA", "r");//on decalre notre fichier en mode lecture
	if (f_stats == NULL) {
		strcpy(data[0], "0");
		strcpy(data[1], "0");
		strcpy(data[2], "0");
		reset_score();
		return;
	}

	int i = 0;
	int l = 0;
	char c = (char)fgetc(f_stats);

	while (!feof(f_stats)) {
		if (l < 5 && strchr("0123456789", (int)c)) {
			data[i][l] = c;
			data[i][l+1] = '\0';
			l++;
		} else if (i < 2 && c == ' ') {
			i++;
			l = 0;
		} else if (!(i == 2 && c == '\n')) {
			fclose(f_stats);
			reset_score();
			strcpy(data[0], "0");
			strcpy(data[1], "0");
			strcpy(data[2], "0");
			return;
		}

		c = (char)fgetc(f_stats);
	}
	fclose(f_stats);
}

void inc_score (int a, int b, int c) {
	char data[3][6];
	lire_score(data);
	sprintf(data[0], "%i", atoi(data[0])+a);
	sprintf(data[1], "%i", atoi(data[1])+b);
	sprintf(data[2], "%i", atoi(data[2])+c);
	ecrire_score(data);
}
 ///la fonction qui initialise les SCORES
void reset_score () {
	FILE *f_stats = fopen("DATA", "w");
	if (f_stats == NULL) {
		exit(EXIT_FAILURE);
	}
	fwrite("0 0 0", 5, sizeof(char), f_stats);
	fclose(f_stats);
}

///la position du (nombre de partiés jouées,victoire contre l'ordinateur et victoire de l'ordinateur
void init_pos_s (SDL_Rect pos[3][5]) {
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 5; j++) {
			pos[i][j].x = 360 + j*20;
			pos[i][j].y = 140 + i*63;
		}
	}
}

///la fonction principale du SCORES
int printStats (SDL_Surface *ecran) {
    /** on declare toutes les images (pariels pour les nombres (ce sont des images)***/
	SDL_Surface *jeu = IMG_Load("img/fond.png");
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
	SDL_Surface *none = IMG_Load("img/none.png");

	SDL_Surface *stats = IMG_Load("img/stats.png");
	SDL_Surface *menu = IMG_Load("img/menu2.png");
	SDL_Surface *menus = IMG_Load("img/menu2s.png");
	SDL_Surface *reset = IMG_Load("img/reset.png");
	SDL_Surface *resets = IMG_Load("img/resets.png");

	SDL_Surface *nb[10] = { nb0, nb1, nb2, nb3, nb4,
							nb5, nb6, nb7, nb8, nb9};

	SDL_Rect pos = {0, 0};
	SDL_Rect pos_reset = {240, 440};
	SDL_Rect pos_men = {440, 440};
	SDL_Rect pos_stats = {100, 150};
	SDL_Rect pos_s[3][5];

	SDL_BlitSurface(jeu, NULL, ecran, &pos);
	SDL_BlitSurface(menu, NULL, ecran, &pos_men);
	SDL_BlitSurface(reset, NULL, ecran, &pos_reset);
	SDL_BlitSurface(stats, NULL, ecran, &pos_stats);

	int continuer = 1;
	SDL_Event event;
	int x_m, y_m;
	int i, j;
	char data[3][6];

	init_pos_s (pos_s);

	lire_score(data);
	for (i = 0; i < 3; i++) {
		for (j = 0; data[i][j] != '\0'; j++) {
			SDL_BlitSurface(nb[data[i][j] - '0'], NULL, ecran, &pos_s[i][j]);
		}
	}

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

           		if (is_over(x_m, y_m, *menu, pos_men)) {
           			SDL_BlitSurface(menus, NULL, ecran, &pos_men);
           		} else if (is_over(x_m, y_m, *reset, pos_reset)) {
           			SDL_BlitSurface(resets, NULL, ecran, &pos_reset);
           		} else {
           			SDL_BlitSurface(menu, NULL, ecran, &pos_men);
           			SDL_BlitSurface(reset, NULL, ecran, &pos_reset);
           		}
           		break;
           	case SDL_MOUSEBUTTONUP:
            	x_m = event.button.x;
	           	y_m = event.button.y;

            	if (is_over(x_m, y_m, *menu, pos_men)) {
            		continuer = 2;
            	} else if (is_over(x_m, y_m, *reset, pos_reset)) {
            		reset_score(data);
					for (i = 0; i < 3; i++) {
						for (j = 0; data[i][j] != '\0'; j++) {
							SDL_BlitSurface(none, NULL, ecran, &pos_s[i][j]);
						}
						SDL_BlitSurface(nb[0], NULL, ecran, &pos_s[i][0]);
					}
            	}
            	break;
            default:
            	break;
    	}
    	SDL_Flip(ecran);
    }

	return continuer;
}

