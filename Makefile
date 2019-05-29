SRC_DIR     := src
BUILD_DIR   := build
INCLUDE_DIR := include
TARGET      := simple-ls
OBJS        := util file-info
TESTS       := util-test file-info-test

CC          := gcc
CFLAGS      := -g -Wall -Werror -std=c11
IFLAGS      := -I ./include


all: $(OBJS) $(TARGET)

tests: $(TESTS)

$(TARGET):
	@echo "Building $@ ...";
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(IFLAGS) -o $(BUILD_DIR)/$(TARGET) $(BUILD_DIR)/file-info.o $(BUILD_DIR)/util.o $(SRC_DIR)/main.c

util:
	@echo "Building $@ ...";
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $(BUILD_DIR)/$@.o $(SRC_DIR)/$@.c

file-info:
	@echo "Building $@ ...";
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $(BUILD_DIR)/$@.o $(SRC_DIR)/$@.c

util-test:
	@mkdir -p $(BUILD_DIR)/tests
	@echo "Building $@ ..."; 
	@$(CC) $(CFLAGS) $(IFLAGS) -o $(BUILD_DIR)/tests/$@ tests/$@.c $(BUILD_DIR)/util.o -lcmocka

file-info-test:
	@mkdir -p $(BUILD_DIR)/tests
	@echo "Building $@ ..."; 
	@$(CC) $(CFLAGS) $(IFLAGS) -o $(BUILD_DIR)/tests/$@ tests/$@.c $(BUILD_DIR)/file-info.o $(BUILD_DIR)/util.o -lcmocka

clean:
	@echo "Cleaning $(BUILD_DIR) ...";
	@rm -Rf $(BUILD_DIR)
