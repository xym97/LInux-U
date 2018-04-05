#all: main testselect
#
#testselect:select.c
#	gcc -o $@ $^
#
#main:main.c
#	gcc -o $@ $^

all:tcp_select tcp_poll epoll_LT epoll_ET

epoll_ET:epoll_ET.c
	gcc -o $@ $^

epoll_LT:epoll_LT.c
	gcc -o $@ $^

tcp_select:tcp_select.c
	gcc -o $@ $^

tcp_poll:tcp_poll.c
	gcc -o $@ $^

.PHONY:clean

clean:
	rm -f  tcp_select tcp_poll epoll_LT epoll_ET
#	rm main testselect
