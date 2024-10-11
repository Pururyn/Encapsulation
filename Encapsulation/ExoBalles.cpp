#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
using namespace std;

class Balles {
private:
    int x;      
    int y;      
    int rayon;  
    int vitessex;
    int vitessey;
public:
    Balles (int x1, int y1, int r) {
        x = x1;      
        y = y1;      
        rayon = r;   
        vitessex = 4;
        vitessey = 4;
    }

    // Fonction pour dessiner un cercle
    void drawCircle(SDL_Renderer* renderer) {
        
        for (int w = 0; w < rayon * 2; w++) {
            for (int h = 0; h < rayon * 2; h++) {
                int dx = rayon - w; // Distance horizontale par rapport au centre
                int dy = rayon - h; // Distance verticale par rapport au centre
                if ((dx * dx + dy * dy) <= (rayon * rayon)) {
                    SDL_RenderDrawPoint(renderer, x + dx, y + dy);
                }
            }
        }
    }
    void moveCircle(SDL_Renderer* renderer) {
        x += vitessex;
        y += vitessey;

        if ((x - rayon < 0)||(x + rayon > 960)) {
            vitessex = -vitessex;
        }
        if ((y - rayon < 0) ||(y + rayon > 540)) {
            vitessey = -vitessey;
        }
    }
    void collisionBalls(Balles& b2) {
        float dx = x - b2.x;
        float dy = y - b2.y;
        float distance = sqrt(dx * dx + dy * dy);

        float distancemin = rayon + b2.rayon;

        if (distance <= distancemin) {
            if (abs(dx) > abs(dy)) {
                vitessex = -vitessex;
            }
            else {
                vitessey = -vitessey;
            }
        }
    }
};

int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    // Initialise SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Error initializing SDL: " << SDL_GetError() << endl;
        return -1;
    }

    // Création de la fenêtre
    window = SDL_CreateWindow("Rebond de balles", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 960, 540, SDL_WINDOW_SHOWN);

    // Message en cas d'erreur de création
    if (!window) {
        cout << "Error creating window: " << SDL_GetError() << endl;
        SDL_Quit();
        return -1;
    }

    // Obtenir le renderer de la fenêtre
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Message en cas d'erreur d'obtention
    if (!renderer) {
        cout << "Error getting renderer: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    Balles b (100, 250, 25);
    Balles c (850, 50, 25);
    

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Nettoyage de l'écran
        SDL_SetRenderDrawColor(renderer, 63, 63, 105, 255);
        SDL_RenderClear(renderer);

        // Dessiner le cercle et faire bouger
        SDL_SetRenderDrawColor(renderer, 143, 219, 177, 255); // Couleur du cercle
        b.drawCircle(renderer);
        b.moveCircle(renderer);
        //Cercle 2
        SDL_SetRenderDrawColor(renderer, 143, 192, 219, 255);
        c.drawCircle(renderer);
        c.moveCircle(renderer);
        b.collisionBalls(c);

        // Afficher à l'écran
        SDL_RenderPresent(renderer);
    }

    // Détruit tout avant de quitter
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}