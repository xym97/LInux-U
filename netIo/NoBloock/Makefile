#all: main testselect
#
#testselect:select.c
#	gcc -o $@ $^
#
#main:main.c
#	gcc -o $@ $^

all:tcp_select tcp_poll

tcp_select:tcp_select.c
	gcc -o $@ $^

tcp_poll:tcp_poll.c
	gcc -o $@ $^

.PHONY:clean

clean:
	rm tcp_select tcp_poll
#	rm main testselect
