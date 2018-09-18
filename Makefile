CC=g++
CFLAGS=-Wall -g -std=c++11
TARGET=build/twitch-bot
ENTRY=main.cpp

TEST_FILE=todo

SRCS = $(wildcard src/*.cpp)

build:
	@echo "Building source files"
	$(CC) $(CFLAGS) -I include/ -o $(TARGET) src/$(ENTRY)

wasm: 
	emcc $(CFLAGS) -I include/ -s WASM=1 -s EXTRA_EXPORTED_RUNTIME_METHODS=["ccall"] -o wasm/twitch-bot.js src/$(ENTRY)

run: build
	@echo "Running target ($(TARGET))"
	./$(TARGET)

tests: 
	${CC} ${CFLAGS} -I/include -o bin/$(TEST_FILE) test/$(TEST_FILE).cpp
	bin/$(TEST_FILE) --reporter compact --success

clean:
	rm -rf $(TARGET) *.o
	rm -rf wasm/*

print-%  : ; @echo $* = $($*)
	
.PHONY: all build wasm clean