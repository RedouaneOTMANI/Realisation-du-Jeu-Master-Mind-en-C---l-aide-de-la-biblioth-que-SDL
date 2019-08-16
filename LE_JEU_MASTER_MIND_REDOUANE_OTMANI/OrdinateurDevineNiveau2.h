#ifndef HELPER_H
#define HELPER_H


void init_pos_fleOrdinateurDevineNiveau2 (SDL_Rect pos[4], int n);
void init_pos_evaOrdinateurDevineNiveau2 (SDL_Rect pos[2], int n);
void init_pos_evoOrdinateurDevineNiveau2 (SDL_Rect pos[2], int n);
void init_pos_nbOrdinateurDevineNiveau2 (SDL_Rect pos[4], int n);
int ready_togoOrdinateurDevineNiveau2 (int code[4], int n_past[2], int n, int sens);
void assistOrdinateurDevineNiveau2 (int * tab[10][2], int n, int * poss, int s, int conseil[4]);
int nb_remainOrdinateurDevineNiveau2 (int * tab[10][2], int n, int * poss);
void decodeOrdinateurDevineNiveau2(int code, int a[4]);
void nb_decompoOrdinateurDevineNiveau2(int nb, int a[4]);

int printOrdinateurDevineNiveau2(SDL_Surface *ecran);
#endif
