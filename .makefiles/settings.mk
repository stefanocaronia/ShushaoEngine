# Universal MakeFile v1.4
# Compatible with Code::blocks

# Declaration of variables
CC = g++
DB = gdb
RM = rm
MD = mkdir
CP = cp
MAKE = mingw32-make
BUILD = Debug
DEBUG = true
COLORS = true

BULLET = "* "
BULLET2 = ""
TAB = "  "

# Black        0;30     Dark Gray     1;30
# Red          0;31     Light Red     1;31
# Green        0;32     Light Green   1;32
# Brown/Orange 0;33     Yellow        1;33
# Blue         0;34     Light Blue    1;34
# Purple       0;35     Light Purple  1;35
# Cyan         0;36     Light Cyan    1;36
# Light Gray   0;37     White         1;37

ifeq ($(COLORS),true)
	CRED 	= "\033[1;31m"
	CBLUE 	= "\033[1;34m"
	CYELLOW = "\033[1;33m"
	CGREEN 	= "\033[1;32m"
	CGREY 	= "\033[1;30m"
	CLGREY 	= "\033[0;37m"
	CCYAN 	= "\033[1;36m"
	CEND 	= "\033[0m"
else
	CRED 	= ""
	CBLUE 	= ""
	CYELLOW = ""
	CGREEN 	= ""
	CGREY 	= ""
	CLGREY 	= ""
	CCYAN 	= ""
	CEND 	= ""
endif

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
COMFLAGS =  -MMD -MP -std=c++11 -fexceptions -DGLEW_STATIC -g -DDEBUG=$(DEBUG)
LNKFLAGS =
LIBDIRS	 = -L$(BASE_LIBS)/glew/lib -L$(BASE_LIBS)/freetype/lib -L$(BASE_LIBS)/SDL2/lib -L$(BASE_LIBS)/SDL2_image/lib -L$(BASE_LIBS)/SDL2_ttf/lib -L$(BASE_LIBS)/SDL2_mixer/lib -L$(BASE_LIBS)/Box2D/lib
LIB 	 = -lglew32 -lmingw32 -lopengl32 -lgdi32 -lglu32 -lfreetype -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lBox2D
INCDIRS  = -I$(BASE_LIBS)/glew/include -I$(BASE_LIBS)/glm -I$(BASE_LIBS)/freetype/include -I$(BASE_LIBS)/SDL2/include/SDL2 -I$(BASE_LIBS)/SDL2_image/include/SDL2 -I$(BASE_LIBS)/SDL2_ttf/include/SDL2 -I$(BASE_LIBS)/SDL2_mixer/include/SDL2 -I$(BASE_LIBS)/Box2D/include -I$(ROOT_DIR)/engine -I$(ROOT_DIR)

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
DEPENDS = $(OBJECTS:.o=.d)

