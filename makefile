# Universal MakeFile v1.3

# Declaration of variables
CC = g++
DB = gdb
RM = rm
MD = mkdir
CP = cp
BUILD = Debug
DEBUG = true

ifeq ($(BUILD),Debug)
	DEBUG = true
else
	DEBUG = false
endif

#The Target Binary Program
ROOT_DIR = "$(CURDIR)"
THIS_DIR = "$(shell basename "$(CURDIR)")"
#TARGET = $(THIS_DIR).exe
TARGET = ShushaoGame.exe

#PATHS
BASE_LIBS	= ../../mingw-dev-libs

#The Directories, Source, Includes, Objects, Binary and Resources
BUILDDIR = obj/$(BUILD)
TARGETDIR = bin/$(BUILD)

SRCDIR		= .
RESDIR		= res
SRCEXT		= cpp
OBJEXT		= o

#Flags, Libraries and Includes
COMFLAGS = -std=c++11 -fexceptions -DGLEW_STATIC -g -DDEBUG=$(DEBUG)
LNKFLAGS =
LIBDIRS	 = -L$(BASE_LIBS)/glew/lib -L$(BASE_LIBS)/freetype/lib -L$(BASE_LIBS)/SDL2/lib -L$(BASE_LIBS)/SDL2_image/lib -L$(BASE_LIBS)/SDL2_ttf/lib -L$(BASE_LIBS)/SDL2_mixer/lib -L$(BASE_LIBS)/Box2D/lib
LIB 	 = -lglew32 -lmingw32 -lopengl32 -lgdi32 -lglu32 -lfreetype -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lBox2D
INCDIRS  = -I$(BASE_LIBS)/glew/include/GL -I$(BASE_LIBS)/glm -I$(BASE_LIBS)/freetype/include -I$(BASE_LIBS)/SDL2/include/SDL2 -I$(BASE_LIBS)/SDL2_image/include/SDL2 -I$(BASE_LIBS)/SDL2_ttf/include/SDL2 -I$(BASE_LIBS)/SDL2_mixer/include/SDL2 -I$(BASE_LIBS)/Box2D/include -I$(ROOT_DIR)/engine -I$(ROOT_DIR)

#Condizioni
ifeq ($(DEBUG),true)
	COMFLAGS += -Wall -g
else
	COMFLAGS += -O2
	LNKFLAGS += -s -mwindows
endif

subdirs = $(wildcard $(SRCDIR)/*/)
SOURCES = $(wildcard $(SRCDIR)/*.$(SRCEXT)) $(wildcard $(addsuffix *.$(SRCEXT),$(subdirs)))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

#Defauilt
all: resources $(TARGET)
	@echo - $(BUILD) Compilation done!! Yee!

#Rebuild
rebuild: clean all

#Copy Resources from Resources Directory to Target Directory
#@$(CP) -r $(RESDIR)/* $(TARGETDIR)/
resources: directories
	@echo - Copying resources
	@rescopy $(BUILD)

#Make the directories
directories:
	@echo - Creating build directories
	@$(MD) -p $(TARGETDIR)
	@$(MD) -p $(BUILDDIR)

#Clean only Objecst
clean:
	@echo - Cleaning build
	@$(RM) -rf obj/*
	@$(RM) -rf bin/*

#Link
$(TARGET): $(OBJECTS)
	@echo - Linking $(TARGET)
	@$(CC) $(LNKFLAGS) -o $(TARGETDIR)/$(TARGET) $(OBJECTS) $(LIBDIRS) $(LIB)

#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@echo - Compiling: $<
	@$(MD) -p $(dir $@)
	@$(CC) $(COMFLAGS) $(INCDIRS) -c $< -o $@

run: all
	@echo - Running $(TARGET)
	@cd $(TARGETDIR) && ./$(TARGET)

debug: all
	@echo - Running Debug of $(TARGET)
	@cd $(TARGETDIR) && $(DB) $(TARGET)

cls:
	@cls

#Non-File Targets
.PHONY: all release rebuild clean resources directories run debug cls
