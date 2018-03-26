ROOT_PATH=$(shell pwd)
CONF=$(ROOT_PATH)/conf
PLUGIN=$(ROOT_PATH)/plugin
WWWROOT=$(ROOT_PATH)/wwwroot

CC=gcc
flags=#
LDFLAGS=-lpthread #-static
bin=httpd
src=httpd.c main.c
obj=$(shell echo $(src) | sed 's/\.c/\.o/g')
FLAGS=-D_STDOUT_ #-D_DEBUG_

$(bin):$(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

#$(obj):$(src)
%.o:%.c
	$(CC) -c $< $(FLAGS)

#%.o:%.c

.PHONY:clean

clean:
	rm -f *.o $(bin)

.PHONY:debug

debug:
	echo $(obj)

