#include <SDL3/SDL.h>
#include <iostream>

int main(){
    //initialisation de SDL 

    if (SDL_Init(SDL_INIT_VIDEO) < 0)//demarre le module video SDL pour l'affichage 
    {
         std::cerr <<"Erreur" << SDL_GetError() << std::endl;
        return 1;
    }
    //creation de la fenetre d'affichage windows
    SDL_Windows* windows = SDL_CreateWindow("carre bleu SDL3", 1000, 850, 1);//c'est une fenetre de 1000*850 pixels
    if(!windows) {
        std::cerr <<"erreur" <<SDL_GetError() <<std::endl;
        return 1;
    }

    //creation du renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(windows, nullptr);
    if(!renderer){
        std::cerr <<"erreur" <<SDL_GetError() <<std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    //Gestionnaire de position et de taille
    SDL_FRect carre = {
        200.f, 200.f, 100.f, 100.f
    };
    float vitesse = 10.f;
    bool sortir = false;
    SDL_Event evenement;

    while(!sortir) {
        while(SDL_PollEvent(&evenement)) {
            if (evenement.type == SDL_EVENT_QUIT){
                sortir = true;
            }
            else if(evenement.type == SDL_EVENT_KEY_DOWN){
                switch(evenement.key.keysym.sym){
                    case SDLK_UP: carre.y -= vitesse; break;
                    case SDLK_DOWN: carre.y += vitesse; break;
                    case SDLK_LEFT: carre.x -= vitesse; break;
                    case SDLK_RIGHT: carre.x += vitesse; break;
                }
            }
        }

        //suppression de l'ecran noir en fond
        SDL_SetRenderDrawcolor(renderer, 0, 0, 0, 300);
        SDL_RenderClear(renderer);

        //Dessiner notre carre bleu
        SDL_SetRenderDrawnColor(renderer, 0, 0, 300, 300);
        SDL_RenderFillRect(renderer, carre);
        SDL_RenderPresent(renderer);
        SDL_Delay(17); 
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
    
}