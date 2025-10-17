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
void poll_event(SDL_Event* event, bool* running);

static struct SdlData {
        SDL_Window* window;
        SDL_GLContext context;
        SDL_Event event;
} sdl_data;

int main() {
        if(init()) {
                std::cerr << SDL_GetError() << std::endl;
                SDL_Quit();
                return EXIT_FAILURE;
        }

        bool running = true;

        while(running) {
                poll_event(&sdl_data.event, &running);

                SDL_UpdateWindowSurface(sdl_data.window);

                SDL_Delay(16);
        }

        quit();

        return EXIT_SUCCESS;
}

void poll_event(SDL_Event* event, bool* running) {
        while(SDL_PollEvent(&sdl_data.event)) {
                if(sdl_data.event.type == SDL_EVENT_QUIT) {
                        *running = false;
                }
        }
}

bool init() {
        SDL_Init(SDL_INIT_VIDEO);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        
        SDL_Window* window = SDL_CreateWindow("Combokill", 800, 600, 
                SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
        );

        SDL_GLContext context = SDL_GL_CreateContext(window);

        if(!(window || context)) {
                std::cerr << SDL_GetError() << std::endl;
                return 1;
        }

        SDL_GL_MakeCurrent(window, context);

        sdl_data.window = window;
        sdl_data.context = context;
        
        return 0;
}

void quit() {
        std::cout << "Exiting successfully";
        SDL_DestroyWindow(sdl_data.window);
        SDL_GL_CreateContext(sdl_data.window);
        SDL_Quit();
}
