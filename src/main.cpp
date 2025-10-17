#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_events.h>

int main() {
        SDL_Init(SDL_INIT_VIDEO);

        SDL_Window* window = SDL_CreateWindow("Combokill", 800, 600, 
                SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
        );

        SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

        if(!window) {
                std::cerr << SDL_GetError() << std::endl;
                SDL_Quit();
                return EXIT_FAILURE;
        }

        if(!renderer) {
                std::cerr << SDL_GetError() << std::endl;
                SDL_Quit();
                return EXIT_FAILURE;
        }

        SDL_Event event;
        bool running = true;

        while(running) {
                while(SDL_PollEvent(&event)) {
                        if(event.type == SDL_EVENT_QUIT) {
                                running = false;
                        }
                }

                SDL_UpdateWindowSurface(window);
                SDL_RenderClear(renderer);
                SDL_RenderPresent(renderer);

                SDL_Delay(16);
        }

        std::cout << "Exiting successfully";
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return EXIT_SUCCESS;
}

