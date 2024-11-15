# Makefile

# Define the compiler
CC = gcc

# Define the compiler flags
CFLAGS = -Wall -Wextra -g

# Define the linker flags
LDFLAGS =

# Directories
OBJ_DIR = obj
BIN_DIR = bin

# Source directory
SRC_DIR = .  # Changed from /home/INSA/PROG_SYS/mini_lib_c to .

# Define the shared library source files
LIB_SRCS = mini_memory.c mini_string.c mini_io.c

# Define the library object files
LIB_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(LIB_SRCS))

# Define the executable names and their corresponding main source files
EXECS = $(BIN_DIR)/prog_sys $(BIN_DIR)/wc $(BIN_DIR)/mini_cat $(BIN_DIR)/mini_clean \
        $(BIN_DIR)/mini_cp $(BIN_DIR)/mini_echo $(BIN_DIR)/mini_grep $(BIN_DIR)/mini_head \
        $(BIN_DIR)/mini_tail $(BIN_DIR)/mini_touch $(BIN_DIR)/mini_ls $(BIN_DIR)/mini_chmod \
        $(BIN_DIR)/mini_ln $(BIN_DIR)/mini_quickdiff $(BIN_DIR)/mini_mkdir $(BIN_DIR)/mini_mv \
        $(BIN_DIR)/mini_rm $(BIN_DIR)/mini_rmdir

# Define the main source files for each executable
PROG_SYS_SRCS = main.c
WC_SRCS = wc.c
MINI_CAT_SRCS = mini_cat.c
MINI_CLEAN_SRCS = mini_clean.c
MINI_CP_SRCS = mini_cp.c
MINI_ECHO_SRCS = mini_echo.c
MINI_GREP_SRCS = mini_grep.c
MINI_HEAD_SRCS = mini_head.c
MINI_TAIL_SRCS = mini_tail.c
MINI_TOUCH_SRCS = mini_touch.c
MINI_LS_SRCS = mini_ls.c
MINI_CHMOD_SRCS = mini_chmod.c
MINI_LN_SRCS = mini_ln.c
MINI_QUICKDIFF_SRCS = mini_quickdiff.c
MINI_MKDIR_SRCS = mini_mkdir.c
MINI_MV_SRCS = mini_mv.c
MINI_RM_SRCS = mini_rm.c
MINI_RMDIR_SRCS = mini_rmdir.c

# Convert main source files to object files
PROG_SYS_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(PROG_SYS_SRCS))
WC_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(WC_SRCS))
MINI_CAT_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(MINI_CAT_SRCS))
MINI_CLEAN_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(MINI_CLEAN_SRCS))
MINI_CP_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(MINI_CP_SRCS))
MINI_ECHO_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(MINI_ECHO_SRCS))
MINI_GREP_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(MINI_GREP_SRCS))
MINI_HEAD_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(MINI_HEAD_SRCS))
MINI_TAIL_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(MINI_TAIL_SRCS))
MINI_TOUCH_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(MINI_TOUCH_SRCS))
MINI_LS_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(MINI_LS_SRCS))
MINI_CHMOD_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(MINI_CHMOD_SRCS))
MINI_LN_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(MINI_LN_SRCS))
MINI_QUICKDIFF_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(MINI_QUICKDIFF_SRCS))
MINI_MKDIR_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(MINI_MKDIR_SRCS))
MINI_MV_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(MINI_MV_SRCS))
MINI_RM_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(MINI_RM_SRCS))
MINI_RMDIR_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(MINI_RMDIR_SRCS))

# Default target to build all executables
all: create_dirs $(EXECS)

# Rule to create directories if they do not exist
create_dirs:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Rule to build prog_sys
$(BIN_DIR)/prog_sys: $(PROG_SYS_OBJS) $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build wc
$(BIN_DIR)/wc: $(WC_OBJS) $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build mini_cat
$(BIN_DIR)/mini_cat: $(MINI_CAT_OBJS) $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build mini_clean
$(BIN_DIR)/mini_clean: $(MINI_CLEAN_OBJS) $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build mini_cp
$(BIN_DIR)/mini_cp: $(MINI_CP_OBJS) $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build mini_echo
$(BIN_DIR)/mini_echo: $(MINI_ECHO_OBJS) $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build mini_grep
$(BIN_DIR)/mini_grep: $(MINI_GREP_OBJS) $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build mini_head
$(BIN_DIR)/mini_head: $(MINI_HEAD_OBJS) $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build mini_tail
$(BIN_DIR)/mini_tail: $(MINI_TAIL_OBJS) $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build mini_touch
$(BIN_DIR)/mini_touch: $(MINI_TOUCH_OBJS) $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build mini_ls
$(BIN_DIR)/mini_ls: $(MINI_LS_OBJS) $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build mini_chmod
$(BIN_DIR)/mini_chmod: $(MINI_CHMOD_OBJS) $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build mini_ln
$(BIN_DIR)/mini_ln: $(MINI_LN_OBJS) $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build mini_quickdiff
$(BIN_DIR)/mini_quickdiff: $(MINI_QUICKDIFF_OBJS) $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build mini_mkdir
$(BIN_DIR)/mini_mkdir: $(MINI_MKDIR_OBJS) $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build mini_mv
$(BIN_DIR)/mini_mv: $(MINI_MV_OBJS) $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build mini_rm
$(BIN_DIR)/mini_rm: $(MINI_RM_OBJS) $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build mini_rmdir
$(BIN_DIR)/mini_rmdir: $(MINI_RMDIR_OBJS) $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Pattern rule to compile .c files to .o files
$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove all object files and executables
clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/*

# Declare phony targets
.PHONY: all clean create_dirs rebuild

rebuild: clean all
