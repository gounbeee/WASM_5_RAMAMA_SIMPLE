
TARGET_EXEC := RAMAMA


# CXX := g++
CC := emcc

SRC_DIRS := src
HEADER_DIRS := header


BUILD_DIR := build_emcc
BUILD_PATH := $(shell pwd)/$(BUILD_DIR)


# SETTING ENVIRONMENT PATH FOR COMPILING
export PATH := $(shell pwd)/$(HEADER_DIRS):$(PATH)



# NATIVE APP
# SDL2_INC_FLAGS := -I./$(HEADER_DIRS) -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE
# SDL2_LIB_FLAGS := -L/opt/homebrew/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lz -lzstd



# emcc main.c \
# 	-s WASM=1 \
# 	-s USE_SDL=2 \
# 	-s USE_SDL_IMAGE=2 \
# 	-s SDL2_IMAGE_FORMATS='["png"]' \
# 	--preload-file assets \
# 	-o index.js



# emcc -O2 -s WASM=1 -s SIDE_MODULE=1 -o adder.wasm




# WASM APP
#WASM_FLAGS     := -s WASM=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file assets
WASM_FLAGS     := -s WASM=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file resources
#SDL2_INC_FLAGS := -I./$(HEADER_DIRS) -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE
SDL2_INC_FLAGS := -I./$(HEADER_DIRS) -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE
#SDL2_LIB_FLAGS := -L/opt/homebrew/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lz -lzstd
#SDL2_LIB_FLAGS := -L/opt/homebrew/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lz -lzstd






# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. Make will incorrectly expand these otherwise.
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')

# String substitution for every C/C++ file.
# As an example, hello.cpp turns into ./build/hello.cpp.o
#OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)





# # The final build step.
# $(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
# 	$(CXX) -std=c++17 $(OBJS) -o $@ $(SDL2_LIB_FLAGS)
# 	# COPY REQUIRED CONTENTS TO BUILD FOLDER
# 	$(shell cp -R ./\[NEED_TO_DISTRIBUTE]/* ./build )




$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) $(WASM_FLAGS) -o $(TARGET_EXEC).html 



$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(SDL2_INC_FLAGS) $(WASM_FLAGS) -c $< -o $@




.PHONY: run
run:
	cd $(BUILD_PATH) ; \
	$(BUILD_PATH)/$(TARGET_EXEC)
	


.PHONY: clean
clean:
	rm -r $(BUILD_DIR)



# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
#-include $(DEPS)