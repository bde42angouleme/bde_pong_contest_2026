CC := cc
CFLAGS := -Wall -Wextra -Werror
LDFLAGS = -lncursesw -lm

NAME := pong

OUTPUT_DIR := output

SRC_DIR := src

SRC := $(SRC_DIR)/main.c $(SRC_DIR)/inputs.c $(SRC_DIR)/physic.c $(SRC_DIR)/rendering.c $(SRC_DIR)/setup.c $(SRC_DIR)/utils.c

INCLUDES := includes

OBJ := $(SRC:$(SRC_DIR)/%.c=$(OUTPUT_DIR)/%.o)

$(NAME): $(OUTPUT_DIR) $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) -o $@

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

$(OUTPUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDES)

all: $(NAME)

clean:
	rm -rf $(OUTPUT_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all re fclean
