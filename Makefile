CC 		:= gcc
#CFLAGS  := -std=c11 -Wall -Wextra -g -DDEBUG
CFLAGS  := -std=c11
#BFLAGS  := -Wcounterexamples
BFLAGS  :=

BUILD_DIR := build

NALAB_DIR	  := nalab
NALAB_SRC_DIR := $(NALAB_DIR)/src
NALAB_OBJ_DIR := $(BUILD_DIR)/objs/nalab
NALAB_SRC 	  := $(shell find $(NALAB_SRC_DIR) -name '*.c')
NALAB_OBJ 	  := $(patsubst   $(NALAB_SRC_DIR)/%.c, $(NALAB_OBJ_DIR)/%.o, $(NALAB_SRC))

NALAC_DIR	  := nalac
NALAC_SRC_DIR := $(NALAC_DIR)/src
NALAC_OBJ_DIR := $(BUILD_DIR)/objs/nalac
NALAC_SRC 	  := $(shell find $(NALAC_SRC_DIR) -name '*.c')
NALAC_OBJ 	  := $(patsubst   $(NALAC_SRC_DIR)/%.c, $(NALAC_OBJ_DIR)/%.o, $(NALAC_SRC))

.PHONY: default nalac nalab clean

default: nalac nalab

check_tools:
	@command -v flex  >/dev/null || (echo "You must install GNU Flex (see https://github.com/westes/flex).";  	   exit 1)
	@command -v bison >/dev/null || (echo "You must install GNU Bison (see https://www.gnu.org/software/bison/)."; exit 1)

nalac: check_tools clean
	@flex     			-o $(NALAC_SRC_DIR)/gen/lex.yy.c 	  $(NALAC_DIR)/parser/lexer.l
	@bison $(BFLAGS) -d -o $(NALAC_SRC_DIR)/gen/parser.tab.c $(NALAC_DIR)/parser/parser.y
	@$(MAKE) nalac_build

nalac_build: $(NALAC_OBJ)
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)/nalac $^

$(NALAC_OBJ_DIR)/%.o: $(NALAC_SRC_DIR)/%.c | $(NALAC_OBJ_DIR)
	@mkdir 			 -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NALAC_OBJ_DIR):
	@mkdir -p $(NALAC_OBJ_DIR)

nalab: check_tools clean
	@flex     -o $(NALAB_SRC_DIR)/gen/lex.yy.c 	   $(NALAB_DIR)/parser/lexer.l
	@bison -d -o $(NALAB_SRC_DIR)/gen/parser.tab.c $(NALAB_DIR)/parser/parser.y
	@$(MAKE) nalab_build

nalab_build: $(NALAB_OBJ)
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)/nalab $^

$(NALAB_OBJ_DIR)/%.o: $(NALAB_SRC_DIR)/%.c | $(NALAB_OBJ_DIR)
	@mkdir 			 -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NALAB_OBJ_DIR):
	@mkdir -p $(NALAB_OBJ_DIR)

clean:
	@rm -rf $(BUILD_DIR)/*
