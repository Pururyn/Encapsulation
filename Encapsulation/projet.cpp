#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include<list>
#include<time.h>
using namespace std;

int fps = 60;
int desiredDelta = 1000 / fps;
int frameCount = 0;
int fpsTimer = SDL_GetTicks();

class Balles {
private:
    int x;
    int y;
    int rayon;
    int vitessex;
    int vitessey;
public:
    Balles(int x1, int y1, int r) {
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

        if ((x - rayon < 0) || (x + rayon > 960)) {
            vitessex = -vitessex;
        }
        if ((y - rayon < 0) || (y + rayon > 540)) {
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
    srand(time(NULL));

    // Initialise SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Error initializing SDL: " << SDL_GetError() << endl;
        return -1;
    }

    // Cr�ation de la fen�tre
    window = SDL_CreateWindow("Rebond de balles", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 960, 540, SDL_WINDOW_SHOWN);

    // Message en cas d'erreur de cr�ation
    if (!window) {
        cout << "Error creating window: " << SDL_GetError() << endl;
        SDL_Quit();
        return -1;
    }

    // Obtenir le renderer de la fen�tre
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Message en cas d'erreur d'obtention
    if (!renderer) {
        cout << "Error getting renderer: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    list<Balles> ballesList;
    Uint32 lastBallAddedTime = SDL_GetTicks();  // Timer to track time since last ball was added

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        int starttick = SDL_GetTicks();

        // Nettoyage de l'�cran
        SDL_SetRenderDrawColor(renderer, 63, 63, 105, 255);
        SDL_RenderClear(renderer);

        // Ajouter une nouvelle balle toutes les 2 secondes (2000 ms)
        if (SDL_GetTicks() - lastBallAddedTime > 2000) {
            if (ballesList.size() < 100) {
                ballesList.push_back(Balles(rand() % 950, rand() % 530, 25));
            }
            lastBallAddedTime = SDL_GetTicks();
        }

        // Dessiner et d�placer chaque balle
        for (auto it = ballesList.begin(); it != ballesList.end(); ++it) {
            SDL_SetRenderDrawColor(renderer, 143, 219, 177, 255);
            it->drawCircle(renderer);
            it->moveCircle(renderer);
        }

        // Afficher � l'�cran
        SDL_RenderPresent(renderer);

        int delta = SDL_GetTicks() - starttick; // Temps �coul� depuis le d�but de la frame

        // Calcul du temps restant pour atteindre 60 FPS
        int remainingTime = desiredDelta - delta;
        if (remainingTime > 0) {
            SDL_Delay(remainingTime);
        }
        else {
            SDL_Delay(1);
        }

        // Compter les frames
        frameCount++;

        // Affichage des FPS
        if (SDL_GetTicks() - fpsTimer >= 1000) {
            std::cout << "FPS: " << frameCount << std::endl;
            frameCount = 0;  // R�initialiser le compteur de frames
            fpsTimer += 1000; // R�initialiser le timer
        }
        
    }


    // D�truit tout avant de quitter
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}