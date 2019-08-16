#ifndef JEU_H
#define JEU_H


void chx_codeJeuNiveau2(int code[4]);
void init_pos_chxJeuNiveau2 (SDL_Rect pos[4], int n);
int is_overJeuNiveau2(int x, int y, SDL_Surface s, SDL_Rect p);
int all_fillJeuNiveau2(int code[4]);
void init_pos_optJeuNiveau2 (SDL_Rect pos[2], int n);
void eval_codeJeuNiveau2(int code[4], int prop[4], int res[2]);
void init_pos_resJeuNiveau2 (SDL_Rect pos[4], int n);
int printJeuNiveau2(SDL_Surface *ecran);
#endif
