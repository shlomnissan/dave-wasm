# dave-wasm

Compiling C/SDL demo of Dangerous Dave (originally designed, created and ported to DOS by John Romero)

Live demo: https://shlomnissan.github.io/dave-wasm

## Installation:

1. Install Emscripten:<br/>
https://emscripten.org/docs/getting_started/downloads.html

2. Clone the repository:<br/>
`git clone https://github.com/shlomnissan/dave-wasm`<br/>
`cd sdl-wasm`

3. Run `make` or build manually:<br/>
`
emcc main.c system.c textures.c map.c player.c font.c -s WASM=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file assets -o index.js
`

4. Chrome doesn't support file XHR requests so you need to open index.html from a web server. You can use Emscripten for that too: 
`emrun index.html`

5. 🕹Use the arrow keys to move Dave around.
<br/>

![dave-wasm](https://user-images.githubusercontent.com/3165988/58176944-3fbfa000-7c58-11e9-98a5-e4f1f4a10183.gif)
