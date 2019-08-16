#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Score.h"
#include "JeuNiveau1.h"
#include"JeuNiveau2.h"
#include "OrdinateurDevineNiveau1.h"
#include "OrdinateurDevineNiveau2.h"
#include"DUP.h"
int main (int argc, char **argv) {
    SDL_Init(SDL_INIT_VIDEO);

	SDL_WM_SetIcon(IMG_Load("img/mastermind_icone.png"), NULL);//l'iconne qui apparait dans la fenetre du jeu
	SDL_WM_SetCaption("MASTERMIND", NULL);//le Titre de la fenétre
    SDL_Surface *ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);//l'ecran

	SDL_Surface *JeuNiveau1=IMG_Load("img/JeuNiveau1.png");
	SDL_Surface *JeuNiveau1s=IMG_Load("img/JeuNiveau1s.png");
	SDL_Surface *JeuNiveau2=IMG_Load("img/JeuNiveau2.png");
	SDL_Surface *JeuNiveau2s=IMG_Load("img/JeuNiveau2s.png");
	SDL_Surface *OrdinateurDevineNiveau1=IMG_Load("img/OrdinateurDevineNiveau1.png");
	SDL_Surface *OrdinateurDevineNiveau1s=IMG_Load("img/OrdinateurDevineNiveau1s.png");
	SDL_Surface *OrdinateurDevineNiveau2=IMG_Load("img/OrdinateurDevineNiveau2.png");
	SDL_Surface *OrdinateurDevineNiveau2s=IMG_Load("img/OrdinateurDevineNiveau2s.png");

	SDL_Surface *fond = IMG_Load("img/fond.png");//l'image de fond
	SDL_Surface *mastermind=IMG_Load("img/mastermind.png");//l'image master mind

	SDL_Surface *m_jouer = IMG_Load("img/m_jouer.png");//le botton jouer contre l'ordinateur
	SDL_Surface *m_jouers = IMG_Load("img/m_jouers.png");
	SDL_Surface *m_ordinateur = IMG_Load("img/m_ordinateur.png");//le botton Ordinateur va deviner
	SDL_Surface *m_ordinateurs = IMG_Load("img/m_ordinateurs.png");
	SDL_Surface *m_dupliquer=IMG_Load("img/m_dupliquer.png");//le botton dupliquer
    SDL_Surface *m_dupliquers=IMG_Load("img/m_dupliquers.png");
	SDL_Surface *m_stat = IMG_Load("img/m_stat.png");//le botton stats
	SDL_Surface *m_stats = IMG_Load("img/m_stats.png");
    SDL_Surface *Quitter=IMG_Load("img/Quitter.png");
    SDL_Surface *Quitters=IMG_Load("img/Quitters.png");

	SDL_Rect posFond = {0, 0};//position du fond
	SDL_Rect pos0={200,0};//position d'image MASTER MIND
	SDL_Rect pos1 = {80, 40};//position du botton jouer contre l'ordinateur
	SDL_Rect pos2 = {80, 130};//position du botton ordinateur va deviner
	SDL_Rect pos3={100,250};//position du botton dupliquer
	SDL_Rect pos4 = {100, 350};//position du botton Stats

    SDL_Rect posJeuNiveau1={457,53};
    SDL_Rect posJeuNiveau2={553,53};
    SDL_Rect posOrdinateurDevineNiveau1={457,147};
    SDL_Rect posOrdinateurDevineNiveau2={553,147};

    SDL_Rect posQuitter={545,435};
    SDL_Rect posQuitters={545,435};
/// on va blitter les surfaces


	SDL_BlitSurface(fond, NULL, ecran, &posFond);
	SDL_BlitSurface(mastermind,NULL,ecran,&pos0);

	SDL_BlitSurface(m_jouer, NULL, ecran, &pos1);
	SDL_BlitSurface(m_ordinateur, NULL, ecran, &pos2);

	SDL_BlitSurface(JeuNiveau1,NULL,ecran,&posJeuNiveau1);
	SDL_BlitSurface(JeuNiveau2,NULL,ecran,&posJeuNiveau2);

	SDL_BlitSurface(OrdinateurDevineNiveau1,NULL,ecran,&posOrdinateurDevineNiveau1);
	SDL_BlitSurface(OrdinateurDevineNiveau2,NULL,ecran,&posOrdinateurDevineNiveau2);

	SDL_BlitSurface(m_dupliquer,NULL,ecran,&pos3);
	SDL_BlitSurface(m_stat, NULL, ecran, &pos4);

    SDL_BlitSurface(Quitter,NULL,ecran,&posQuitter);

	SDL_Flip(ecran);

    int continuer = 1;
    int x_m, y_m;
    SDL_Event event;
    int is_over (int x, int y, SDL_Surface s, SDL_Rect p) {
	if (x > p.x && x < p.x+(&s)->w && y > p.y && y < p.y+(&s)->h) {
		return 1;
	}
	return 0;
}
/// la boucle principale du NOTRE Jeu

    while (continuer) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                continuer = 0;
                break;

            case SDL_MOUSEMOTION:
            	x_m = event.motion.x;
            	y_m = event.motion.y;

            	if (is_over(x_m, y_m, *JeuNiveau1, posJeuNiveau1)) {
            		SDL_BlitSurface(JeuNiveau1s, NULL, ecran, &posJeuNiveau1);
            	}
            	else if(is_over(x_m,y_m,*JeuNiveau2,posJeuNiveau2)){
            	    SDL_BlitSurface(JeuNiveau2s,NULL,ecran,&posJeuNiveau2);
            	}

            	else if (is_over(x_m, y_m, *OrdinateurDevineNiveau1, posOrdinateurDevineNiveau1)) {
            		SDL_BlitSurface(OrdinateurDevineNiveau1s, NULL, ecran, &posOrdinateurDevineNiveau1);
            	}

            	else if(is_over(x_m,y_m, *OrdinateurDevineNiveau2,posOrdinateurDevineNiveau2)){
                    SDL_BlitSurface(OrdinateurDevineNiveau2s,NULL,ecran,&posOrdinateurDevineNiveau2);
            	}
            	 else if (is_over(x_m, y_m, *m_stat, pos4)) {
            		SDL_BlitSurface(m_stats, NULL, ecran, &pos4);
            	} else if (is_over(x_m,y_m, *m_dupliquer,pos3)){
            	SDL_BlitSurface(m_dupliquers,NULL,ecran,&pos3);
            	} else if(is_over(x_m,y_m,*Quitter,posQuitter)){
            	SDL_BlitSurface(Quitters,NULL,ecran,&posQuitter);
            	}
            	 else {
            		SDL_BlitSurface(JeuNiveau1, NULL, ecran, &posJeuNiveau1);
            		SDL_BlitSurface(JeuNiveau2, NULL, ecran, &posJeuNiveau2);
            		SDL_BlitSurface(OrdinateurDevineNiveau1, NULL, ecran, &posOrdinateurDevineNiveau1);
            		SDL_BlitSurface(OrdinateurDevineNiveau2, NULL, ecran, &posOrdinateurDevineNiveau2);
            		SDL_BlitSurface(m_dupliquer,NULL,ecran,&pos3);
            		SDL_BlitSurface(m_stat, NULL, ecran, &pos4);

            		SDL_BlitSurface(Quitter,NULL,ecran,&posQuitter);
            	}
            	break;

            case SDL_MOUSEBUTTONUP://Ici on confirme notre Choix
            	x_m = event.button.x;
            	y_m = event.button.y;

            	if (is_over(x_m, y_m, *JeuNiveau1, posJeuNiveau1)) {
            		continuer = printJeuNiveau1(ecran);
            	}
            	else if(is_over(x_m,y_m,*JeuNiveau2,posJeuNiveau2)){
                    continuer=printJeuNiveau2(ecran);
            	}
                    else if (is_over(x_m, y_m, *OrdinateurDevineNiveau1, posOrdinateurDevineNiveau1)) {
            		continuer = printOrdinateurDevineNiveau1(ecran);
            	}
            	else if(is_over(x_m,y_m,*OrdinateurDevineNiveau2,posOrdinateurDevineNiveau2)){
                    continuer=printOrdinateurDevineNiveau2(ecran);
            	}
            	else if (is_over(x_m, y_m, *m_stat, pos4)) {
            		continuer = printStats(ecran);
            	}else if (is_over(x_m,y_m, *m_dupliquer,pos3)){
            	continuer=printDup(ecran);
            	}
            	else if(is_over(x_m,y_m,*Quitter,posQuitter)){
                    continuer=0;
            	}
            	break;

            default:
            	break;
        }

        while (continuer != 1 && continuer != 0) {
		    if (continuer == 2) {
		    	continuer = 1;
		    	SDL_BlitSurface(fond, NULL, ecran, &posFond);
		    	SDL_BlitSurface(mastermind,NULL,ecran,&pos0);

				SDL_BlitSurface(m_jouer, NULL, ecran, &pos1);
				SDL_BlitSurface(JeuNiveau1,NULL,ecran,&posJeuNiveau1);
				SDL_BlitSurface(JeuNiveau2,NULL,ecran,&posJeuNiveau2);

				SDL_BlitSurface(m_ordinateur, NULL, ecran, &pos2);
				SDL_BlitSurface(OrdinateurDevineNiveau1,NULL,ecran,&posOrdinateurDevineNiveau1);
				SDL_BlitSurface(OrdinateurDevineNiveau2,NULL,ecran,&posOrdinateurDevineNiveau2);

				SDL_BlitSurface(m_dupliquer,NULL,ecran,&pos3);
				SDL_BlitSurface(m_stat, NULL, ecran, &pos4);
				SDL_BlitSurface(Quitter,NULL,ecran,&posQuitter);
			} else if (continuer == 3) {
				continuer = printJeuNiveau1(ecran);
			}
		}

        SDL_Flip(ecran);
    }
    SDL_Quit();

    return EXIT_SUCCESS;
}
