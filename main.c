//clang --target=wasm32 -nostdlib -Wl,--no-entry -Wl,--export-all -o main.wasm main.c


const char* getString() {
  return "Hello World!";
}
