# C and C++ compilers
CC = gcc
CXX = g++

# Commands
MKDIR = mkdir
RM = rm -f
FIND_DIR = $(shell find $(1) -type d)
FIND_FILES = $(shell find $(1) -type f -name $(2))

SLH = /
EXE = out
# Correct slash for commands depending of OS
ifeq ($(OS),Windows_NT)
	RM = del
	SLH = \\
	EXE = exe
	FIND_DIR = $(shell dir /s /b /a:d $(1))
	FIND_FILES = $(shell dir /s /b /a-d $(1)$(2))
endif


# Directories where source, objects, and binaries are/will be located
SRCDIR = src
OBJDIR = obj
BINDIR = bin

VPATH = $(SRCDIR)/ $(call FIND_DIR, $(SRCDIR)$(SLH)*)

# Target name
TARGET := $(BINDIR)/chip8.$(EXE)

# Source and object files
c_files := $(call FIND_FILES, $(SRCDIR)$(SLH), *.c)
cxx_files := $(call FIND_FILES, $(SRCDIR)$(SLH), *.cpp)
src := $(c_files) $(cxx_files)
obj := $(addprefix $(OBJDIR)/, $(notdir $(addsuffix .o, $(basename $(src)))))


# Include and Library paths
INCLUDE := -I$(CURDIR)/include/ -I$(CURDIR)/$(SRCDIR)
LIB := -L$(CURDIR)/lib/

# Compiler and Linker flags
CFLAGS := -Wall $(INCLUDE)
CXXFLAGS := -Wall -std=c++14 $(INCLUDE)

LDFLAGS := $(LIB)
LDLIBS = -lSDL2 -ldl -lpthread


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
	 $(RM) $(subst /,$(SLH), $(TARGET)) $(subst /,$(SLH), $(obj))

# Create directories if necessary
.PHONY : directories
directories : $(OBJDIR) $(BINDIR)
$(BINDIR) :
	@$(MKDIR) $@
$(OBJDIR) :
	@$(MKDIR) $@
