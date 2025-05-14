CC=SDCC
PACKIHX = packihx
CFLAGS = -mmcs51 -Isrc
BUILD_DIR = build

SRCS = src/core/main.c \

OBJS = $(patsubst src/%, $(BUILD_DIR)/%, $(SRCS:.c=.rel))


TARGET = $(BUILD_DIR)/main.ihx
TARGET_HEX = $(BUILD_DIR)/main.hex


all: $(TARGET)


$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)
	$(PACKIHX) $(TARGET) > $(TARGET_HEX)


$(BUILD_DIR)/%.rel: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)


.PHONY: all clean
