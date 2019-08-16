#ifndef JEU_H
#define JEU_H


void chx_codeJeuNiveau1(int code[4]);

void init_pos_chxJeuNiveau1 (SDL_Rect pos[4], int n);

int is_overJeuNiveau1(int x, int y, SDL_Surface s, SDL_Rect p);

int all_fillJeuNiveau1(int code[4]);

void init_pos_optJeuNiveau1 (SDL_Rect pos[2], int n);

void eval_codeJeuNiveau1(int code[4], int prop[4], int res[2]);

void init_pos_resJeuNiveau1 (SDL_Rect pos[4], int n);

int printJeuNiveau1(SDL_Surface *ecran);
#endif
