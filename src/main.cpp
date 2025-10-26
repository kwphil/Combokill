#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_stdinc.h>
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

#define WINDOW_FLAGS \
        (SDL_WINDOW_FULLSCREEN \
         | SDL_WINDOW_OPENGL \
         | SDL_WINDOW_MOUSE_GRABBED \
         | SDL_WINDOW_MOUSE_GRABBED \
         )

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
                5.0, -1.0, 5.0, 1.0, 1.0, 1.0,
                5.0, -1.0, -5.0, 0.0, 1.0, 1.0,
                -5.0, -1.0, 5.0, 1.0, 1.0, 0.0,
                -5.0, -1.0, -5.0, 1.0, 0.0, 1.0,
                -5.0, -1.0, 5.0, 0.0, 0.0, 1.0,
                5.0, -1.0, -5.0, 1.0, 0.0, 0.0
        };

        Renderable* test_obj = make_renderable<Renderable>(
                glm::vec3(0.0, 0.0, 0.0),
                _vertices,
                36
        );
// --- TEMP ---

        bool running = true;

        while(running) {
                mouse_x = 0.0f;
                mouse_y = 0.0f;

                poll_event(&sdl_data.event, &running);
                
                draw_poly();

                move_camera();
                process_mouse(0.1);
                        
                SDL_GL_SwapWindow(sdl_data.window);

                SDL_Delay(16);
        }

        quit();

        return EXIT_SUCCESS;
}

void event_match(SDL_Event* event, bool* running) {
        switch(event->type) {
        case(SDL_EVENT_QUIT):
                *running = false;
                return;
        case(SDL_EVENT_KEY_DOWN):
                update_key(event->key.scancode, true);
                return;
        case(SDL_EVENT_KEY_UP):
                update_key(event->key.scancode, false);
                return;
        case(SDL_EVENT_MOUSE_MOTION):
                mouse_x = event->motion.xrel;
                mouse_y = event->motion.yrel;
                return;
        }
}

void poll_event(SDL_Event* event, bool* running) {
        while(SDL_PollEvent(event)) {
                if(keymap[SDL_SCANCODE_LALT] && keymap[SDL_SCANCODE_F4]) {
                        SDL_Event quit;
                        SDL_zero(quit);

                        quit.type = SDL_EVENT_QUIT;

                        SDL_PushEvent(&quit);
                }

                event_match(event, running);
        }
}

int init() {
        SDL_Init(SDL_INIT_VIDEO);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        SDL_DisplayID display_id = SDL_GetPrimaryDisplay();
        if(!display_id) {
                std::cerr << "Failed to get primary display: " << SDL_GetError() << std::endl;
                return ERROR_SDL_DISPLAY;
        }

        const SDL_DisplayMode* display_mode = SDL_GetCurrentDisplayMode(display_id);
        if(!display_mode) {
                std::cerr << "Failed to get current display mode: " << SDL_GetError() << std::endl;
                return ERROR_SDL_DISPLAY_MODE;
        }

        SDL_Log("Display resolution: %dx%d @ %.2f Hz", display_mode->w, display_mode->h, display_mode->refresh_rate);

        SDL_Window* window = SDL_CreateWindow("Combokill", display_mode->w, display_mode->h, WINDOW_FLAGS);

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
 
        if(!SDL_SetWindowRelativeMouseMode(sdl_data.window, true)) {
                std::cerr << SDL_GetError() << std::endl;
                return ERROR_SDL_INIT;
        }

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
