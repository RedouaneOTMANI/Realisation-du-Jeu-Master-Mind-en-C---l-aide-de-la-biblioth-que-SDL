#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include <math.h>
#include "JeuNiveau1.h"
#include "OrdinateurDevineNiveau1.h"
#include "JeuNiveau2.h"
#include "OrdinateurDevineNiveau2.h"
#include "Score.h"
#include"DUP.h"


int printDup (SDL_Surface *ecran) {


	printJeuNiveau1(ecran);
	printOrdinateurDevineNiveau1(ecran);


}
