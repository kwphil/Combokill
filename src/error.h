#ifndef ERROR_H
#define ERROR_H

enum ErrorCodes {
        ERROR_OK,
        ERROR_SDL_DISPLAY,
        ERROR_SDL_DISPLAY_MODE,
        ERROR_SDL_INIT,
        ERROR_GLEW_INIT,
        _ERROR_RESERVED0,
        ERROR_SHADER_NOT_FOUND,
        ERROR_SHADER_NOT_LOADED
};

#endif
