TARGET = cosmo

.SRCS   =               src/actor.c \
                        src/main.c \
                        src/player.c \
                        src/game.c src/palette.c src/util.c \
                        src/map.c src/input.c src/dialog.c src/tile.c \
                        src/files/vol.c src/files/file.c src/video.c \
                        src/sound/music.c src/backdrop.c src/save.c \
                        src/status.c src/actor_worktype.c \
                        src/effects.c src/actor_collision.c src/actor_toss.c \
                        src/font.c src/sound/sfx.c src/sound/audio.c \
                        src/platforms.c src/sound/opl.c src/fullscreen_image.c \
                        src/cartoon.c src/config.c src/high_scores.c \
                        src/demo.c src/b800.c \

OBJS = $(.SRCS:.c=.o)

%.o: %.c 
	ppc-morphos-gcc-9 -O2 -c -o $@ $< -I./src -I/usr/local/include/SDL2 -noixemul

all: $(TARGET)

clean:
	-rm -f $(TARGET) $(OBJS) 

$(TARGET): $(OBJS)
	gcc -O2 -s  -o $(TARGET) $(OBJS) -noixemul  -lSDL2_Mixer -lSDL2 -lc -lm -L/usr/local/lib

run: $(TARGET)
	$(KOS_LOADER) $(TARGET)

dist:
	rm -f $(OBJS)
	$(KOS_STRIP) $(TARGET)
