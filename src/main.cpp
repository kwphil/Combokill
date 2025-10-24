#include <SDL3/SDL_oldnames.h>
#include <cstdlib>
#include <glm/ext/vector_float3.hpp>
#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>

#include <GL/glew.h>

#include "error.h"
#include "poly.h"
#include "keys.hpp"
#include "camera.hpp"

int main();
int init();
void quit();
void poll_event(SDL_Event* event, bool* running);

static struct {
        SDL_Window* window;
        SDL_GLContext context;
        SDL_Event event;
} sdl_data;

Camera* camera;

int main() {
        int status = init();

        if(status != 0) {
                return status;
        }

// --- TEMP ---
        float _vertices[] = {
                1.0, 1.0, 1.0,
                -1.0, -1.0, -1.0,
                1.0, -1.0, 1.0
        };

        Renderable* test_obj = make_renderable<Renderable>(
                glm::vec3(0.0, 0.0, 0.0),
                _vertices,
                9
        );
// --- TEMP ---

        bool running = true;

        while(running) {
                poll_event(&sdl_data.event, &running);
                
                draw_poly();

                move_camera();

                SDL_GL_SwapWindow(sdl_data.window);

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

                if(sdl_data.event.type == SDL_EVENT_KEY_DOWN) {
                        update_key(sdl_data.event.key.scancode, true);
                }

                if(sdl_data.event.type == SDL_EVENT_KEY_UP) {
                        update_key(sdl_data.event.key.scancode, false);
                }
        }
}

int init() {
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
                return ERROR_SDL_INIT;
        }

        glewExperimental = GL_TRUE;

        GLenum err = glewInit();
        if(err != GLEW_OK) {
                std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(err) << "\n";
                return ERROR_GLEW_INIT;
        }

        SDL_GL_MakeCurrent(window, context);

        sdl_data.window = window;
        sdl_data.context = context;
 
        // Done initializing window, set camera
        camera = make_object<Camera>(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -5.0f));

        // Done initializing camera, start drawing
        draw_poly_init();


        return 0;
}

void quit() {
        std::cout << "Exiting successfully";
        SDL_DestroyWindow(sdl_data.window);
        SDL_GL_CreateContext(sdl_data.window);
        SDL_Quit();
}
