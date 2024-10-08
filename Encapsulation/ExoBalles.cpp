#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <iostream>
using namespace std;

class Balles{
private:
	int x;
	int y;
	int posx;
	int posy;
public:
	void bal(int x1, int y1, int pos1, int pos2) {
		x = x1;
		y = y1;
		posx = pos1;
		posy = pos2;
	}
	void ball(SDL_Renderer* renderer) {
		SDL_Rect r;
		r.x = posx;
		r.y = posy;
		r.w = x;
		r.h = y;

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &r);
	}
};

int main(int argc, char* args[]) {
	
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	
	// Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "Error initializing SDL: " << SDL_GetError() << endl;
		system("pause");
	}

	// Creation de la fenêtre
	window = SDL_CreateWindow("Rebond de balles", SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, 960, 540, SDL_WINDOW_SHOWN);

	//Message en cas d'erreur de création
	if (!window) {
		cout << "Error creating window: " << SDL_GetError() << endl;
		system("pause");
	}

	// Obtenir la surface de la fenêtre
	renderer = SDL_CreateRenderer(window, 0,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//Message en cas d'erreur d'obtention
	if (!renderer) {
		cout << "Error getting surface: " << SDL_GetError() << endl;
		system("pause");
	}

	Balles b;	
	b.bal(50, 50, 50, 80);

	//Carre
	while (1)
	{
		SDL_SetRenderDrawColor(renderer, 63, 63, 105, 255);
		SDL_RenderClear(renderer);
		b.ball(renderer);
		SDL_RenderPresent(renderer);
		
	}

	//Détruit tout avant de quitter la fenêtre
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}