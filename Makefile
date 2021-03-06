#
# Makefile
#
CC = gcc
CFLAGS = -Wall -Wshadow -Wundef -fbounds-check

LVGL_DIR = ${shell pwd}

CFLAGS += -O3 -g3 -I$(LVGL_DIR)/ -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/harfbuzz -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include
LDFLAGS += -lSDL2 -lm -lfreetype
BIN = demo

#Collect the files to compile
MAINSRC = ./main.c

include $(LVGL_DIR)/lvgl/lvgl.mk
include $(LVGL_DIR)/lv_drivers/lv_drivers.mk
# include $(LVGL_DIR)/lv_examples/lv_examples.mk

# CSRCS +=$(LVGL_DIR)/mouse_cursor_icon.c
CSRCS += ./freudian_font.c

OBJEXT ?= .o

AOBJS = $(ASRCS:.S=$(OBJEXT))
COBJS = $(CSRCS:.c=$(OBJEXT))

MAINOBJ = $(MAINSRC:.c=$(OBJEXT))

SRCS = $(ASRCS) $(MAINSRC)
OBJS = $(AOBJS) $(COBJS)

## MAINOBJ -> OBJFILES

all: clean default

%.o: %.c
	@$(CC)  $(CFLAGS) -c $< -o $@
	@echo "CC $<"
    
default: $(AOBJS) $(COBJS) $(MAINOBJ)
	$(CC) `pkg-config --cflags --libs libsystemd` -o $(BIN) $(MAINOBJ) $(AOBJS) $(COBJS) $(LDFLAGS)

clean: 
	rm -f $(BIN) $(AOBJS) $(COBJS) $(MAINOBJ)
