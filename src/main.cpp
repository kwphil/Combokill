#include <cstdlib>
#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_events.h>

int main();
bool init();
void quit();

static struct SdlData {
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Event* event;
} sdl_data;

int main() {
        if(init()) {
                std::cerr << SDL_GetError() << std::endl;
                SDL_Quit();
                return EXIT_FAILURE;
        }

        bool running = true;

        while(running) {
                while(SDL_PollEvent(sdl_data.event)) {
                        if(sdl_data.event->type == SDL_EVENT_QUIT) {
                                running = false;
                        }
                }

                SDL_UpdateWindowSurface(sdl_data.window);
                SDL_RenderClear(sdl_data.renderer);
                SDL_RenderPresent(sdl_data.renderer);

                SDL_Delay(16);
        }

        quit();

        return EXIT_SUCCESS;
}

bool init() {
        SDL_Init(SDL_INIT_VIDEO);

        SDL_Window* window = SDL_CreateWindow("Combokill", 800, 600, 
                SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
        );

        SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

        if(!window) {
                std::cerr << SDL_GetError() << std::endl;
                return 1;
        }

        if(!renderer) {
                std::cerr << SDL_GetError() << std::endl;
                return 1;
        }

        sdl_data.window = window;
        sdl_data.renderer = renderer;
        return 0;
}

void quit() {
        std::cout << "Exiting successfully";
        SDL_DestroyWindow(sdl_data.window);
        SDL_DestroyRenderer(sdl_data.renderer);
        SDL_Quit();
}
