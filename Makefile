SRC_DIR := ./src
OBJ_DIR := ./obj

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

CFLAGS := -lxcb -lxcb-util -lxcb-ewmh

lightclock: $(OBJ_FILES)
	gcc $(CFLAGS) -o $@ $^

create_obj_dir:
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	gcc $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR)
