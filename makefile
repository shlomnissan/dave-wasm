sdl-wasm:
	emcc main.c system.c textures.c map.c player.c font.c \
	-s WASM=1 \
	-s USE_SDL=2 \
	-s USE_SDL_IMAGE=2 \
	-s SDL2_IMAGE_FORMATS='["png"]' \
	--preload-file assets \
	-o index.js