#ifndef STATS_H
#define STATS_H

void lire_score (char data[3][6]);
void ecrire_score (char data[3][6]);
void inc_score (int a, int b, int c);
void reset_score ();
int printScore (SDL_Surface *ecran);

#endif
