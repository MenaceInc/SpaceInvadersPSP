TARGET = SpaceInvaders

OBJS = src/main.o src/graphics.o src/framebuffer.o src/game.o src/highscores.o src/options.o src/functions.o
	   
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LIBS = -lpspgu -lpng -lz -lm
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Space Invaders v0.9
PSP_EBOOT_ICON= ICON0.png

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
