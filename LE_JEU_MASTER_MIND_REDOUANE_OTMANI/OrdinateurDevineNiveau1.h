#ifndef HELPER_H
#define HELPER_H
void nb_decompoOrdinateurDevineNiveau1(int nb, int a[4]);

void decodeOrdinateurDevineNiveau1(int code, int a[4]);

int nb_remainOrdinateurDevineNiveau1 (int * tab[10][2], int n, int * poss);


void init_pos_fleOrdinateurDevineNiveau1 (SDL_Rect pos[4], int n);

void init_pos_evaOrdinateurDevineNiveau1 (SDL_Rect pos[2], int n);

void init_pos_evoOrdinateurDevineNiveau1 (SDL_Rect pos[2], int n);

void init_pos_nbOrdinateurDevineNiveau1 (SDL_Rect pos[4], int n);

int ready_togoOrdinateurDevineNiveau1 (int code[4], int n_past[2], int n, int sens);

void assistOrdinateurDevineNiveau1 (int * tab[10][2], int n, int * poss, int s, int conseil[4]);

int printOrdinateurDevineNiveau1(SDL_Surface *ecran);


#endif
