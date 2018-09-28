# C and C++ compilers
CC = gcc
CXX = g++

# Commands
MKDIR = mkdir
RM = rm

SLASH = /
# Correct slash for commands depending of OS
ifeq ($(OS),Windows_NT)
	RM = del
	SLASH = \\
endif


# Directories where source, objects, and binaries are/will be located
SRCDIR = src
OBJDIR = obj
BINDIR = bin

VPATH = $(SRCDIR)/ $(shell find $(SRCDIR)/* -type d)

# Target name
TARGET := $(BINDIR)/chip8.out

# Source and object files
c_files := $(shell find $(SRCDIR)/ -type f -name '*.c')
cxx_files := $(shell find $(SRCDIR)/ -type f -name '*.cpp')
src := $(c_files) $(cxx_files)
obj := $(addprefix $(OBJDIR)/, $(notdir $(addsuffix .o, $(basename $(src)))))


# Include and Library paths
INCLUDE := -I$(CURDIR)/include/ -I$(CURDIR)/$(SRCDIR)
LIB := -L$(CURDIR)/lib/

# Compiler and Linker flags
CFLAGS := -Wall $(INCLUDE)
CXXFLAGS := -Wall -std=c++11 $(INCLUDE)

LDFLAGS := $(LIB)
LDLIBS = -lSDL2main -lSDL2


############### RULES #################

# Linking
$(TARGET) : $(obj)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

# Check if any directories must be created
$(obj) : | directories


# Rule for .c files compilation
$(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for .cpp files compilation
$(OBJDIR)/%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


############### PHONY #################

# Clean executable and objects
.PHONY : clean
clean :
	 $(RM) $(subst /,$(SLASH), $(TARGET)) $(subst /,$(SLASH), $(obj))

# Create directories if necessary
.PHONY : directories
directories : $(OBJDIR) $(BINDIR)
$(BINDIR) :
	@$(MKDIR) $@
$(OBJDIR) :
	@$(MKDIR) $@
