# Universal MakeFile v1.2

# Declaration of variables
CC = g++
DB = gdb
RM = rm
MD = mkdir
CP = cp
BUILD = Debug

#The Target Binary Program
ROOT_DIR = $(CURDIR)
THIS_DIR = $(shell basename "$(CURDIR)")
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
CFLAGS		= -std=c++11 -DGLEW_STATIC -g -DDEBUG=$(DEBUG)
LIB			= -L$(BASE_LIBS)/glew/lib -L$(BASE_LIBS)/freetype/lib -L$(BASE_LIBS)/SDL2/lib -L$(BASE_LIBS)/SDL2_image/lib -L$(BASE_LIBS)/SDL2_ttf/lib -L$(BASE_LIBS)/SDL2_mixer/lib -L$(BASE_LIBS)/Box2D/lib -lglew32 -lmingw32 -lopengl32 -lgdi32 -lglu32 -lfreetype -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lBox2D
INC			= -I$(BASE_LIBS)/glew/include/GL -I$(BASE_LIBS)/glm -I$(BASE_LIBS)/freetype/include -I$(BASE_LIBS)/SDL2/include/SDL2 -I$(BASE_LIBS)/SDL2_image/include/SDL2 -I$(BASE_LIBS)/SDL2_ttf/include/SDL2 -I$(BASE_LIBS)/SDL2_mixer/include/SDL2 -I$(BASE_LIBS)/Box2D/include -I$(ROOT_DIR)/engine -I$(ROOT_DIR)

#Condizioni
ifeq ($(DEBUG),true)
	CFLAGS += -Wall -g -fexceptions
else
	CFLAGS += -mwindows
endif

subdirs = $(wildcard $(SRCDIR)/*/)
SOURCES = $(wildcard $(SRCDIR)/*.$(SRCEXT)) $(wildcard $(addsuffix *.$(SRCEXT),$(subdirs)))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

#Defauilt Make
all: directories resources $(TARGET)
	@echo - $(BUILD) Compilation done!! Yee!

#Release Make
release: relasesettings directories resources $(TARGET)
	@echo - $(BUILD) Compilation done!! Yee!

relasesettings:
	BUILD = Release

#Rebuild
rebuild: clean all

#Copy Resources from Resources Directory to Target Directory
#@$(CP) -r $(RESDIR)/* $(TARGETDIR)/
resources: directories
	@echo - Copying resources
	@rescopy $(BUILD)

#Make the Directories
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
	@echo - [$(CC)] Linking $(TARGET)
	@$(CC) $(CFLAGS) -o $(TARGETDIR)/$(TARGET) $(OBJECTS) $(LIB)

#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@echo - [$(CC)] Compiling: $<
	@$(MD) -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

run: all
	@echo - Running $(TARGET)
	@cd $(TARGETDIR) && ./$(TARGET)

debug: all
	@echo [$(DB)] Running Debug of $(TARGET)
	@cd $(TARGETDIR) && $(DB) $(TARGET)

cls:
	@cls

#Non-File Targets
.PHONY: all release releasesettings rebuild clean resources directories run debug cls
