# Init

`bool init()`

Initializes the program. Will return 0 if ok, and 1 if error.

Sets data in `sdl_data`

`sdl_data.window` is an `SDL_Window*` object. 
`sdl_data.renderer` is an `SDL_Renderer*` object.
`sdl_data.event` is an `SDL_Event`, but it is not set by init().

---

`void quit()`

Simply destroys all unused data. Does not exit, you will need to do that.

