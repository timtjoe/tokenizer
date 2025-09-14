# Compiler and flags
CC = clang
# Added -fPIE to make the executable position-independent
CFLAGS = -g -fPIE

# Directory for object files
OBJDIR = lib

# Source files
SRCS = main.c tokenizer.c linkedlist.c talloc.c

# Object files are now prefixed with the object directory
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

# All header files
HDRS = linkedlist.h value.h talloc.h tokenizer.h

# Main target to build the tokenizer executable
tokenizer: $(OBJS)
	# Link the object files to create the executable
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Pattern rule to compile .c files into .o files inside the lib directory
$(OBJDIR)/%.o: %.c
	# Create the object file in the correct directory
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to remove generated files and directories
clean:
	# Remove the object file directory and the executable
	rm -rf $(OBJDIR) tokenizer

.PHONY: clean