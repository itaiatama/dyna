CFLAGS = -Wall -Wextra -pedantic -ggdb -std=c11
SRC    = $(wildcard src/*.c)
LIBS   = -lSDL2
BUILD  = ./build
EXEC   = dyna

build: $(SRC)
	@mkdir -p $(BUILD)
	@$(CC) $(CFLAGS) $(SRC) -o $(BUILD)/$(EXEC) $(LIBS)

run: $(SRC) build
	@$(BUILD)/$(EXEC)

clean:
	@rm -r $(BUILD)