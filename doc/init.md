# Init System

## Window Initialization

### Description

This stage sets up the primary rendering surface and OpenGL context through SDL. It defines how the window behaves (fullscreen, input capture, etc.) and initializes any platform-level graphics requirements.

### Window Flags
- `SDL_WINDOW_FULLSCREEN`
  - forces the display into fullscreen mode 
- `SDL_WINDOW_OPENGL`
  - required for OpenGL context creation.
- `SDL_WINDOW_MOUSE_GRABBED`
  - confines mouse input to the window.

### Object System
