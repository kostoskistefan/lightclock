SRC_DIR := ./src
OBJ_DIR := ./obj

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

CFLAGS := -Wall \
		  -Wextra \
		  -Werror \
		  -fno-exceptions \
		  -lrt \
		  -lxcb \
		  -lxcb-util \
		  -lxcb-ewmh \
		  -lxcb-icccm

all: $(OBJ_FILES)
	gcc -o lightclock $^ $(CFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	gcc -c -o $@ $< $(CFLAGS)

clean:
	rm -rf $(OBJ_DIR) lightclock

$(shell mkdir -p $(OBJ_DIR))
