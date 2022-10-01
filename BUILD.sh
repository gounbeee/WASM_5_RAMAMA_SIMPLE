#clang++ --target=wasm32 -nostdlib -Wl,--no-entry -Wl,--export-all -o main.wasm main.cpp
#wasm2wat ./main.wasm -o ./main.wat


# emcc -c sdl_2_0_sample.c -o sdl_2_0_sample.o -s USE_SDL=2
# emcc sdl_2_0_sample.o -o sdl_2_0_sample.html -s USE_SDL=2

emcc main.c \
	-s WASM=1 \
	-s USE_SDL=2 \
	-s USE_SDL_IMAGE=2 \
	-s SDL2_IMAGE_FORMATS='["png"]' \
	--preload-file resources \
	-o index.js


wasm2wat ./index.wasm -o ./index.wat