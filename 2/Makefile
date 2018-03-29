all:test1 Factory

test1:test1.cc
	g++ -g -o $@ $^ -std=c++11

Factory:Factory.cc
	g++ -g -o $@ $^ -std=c++11

.PHONY:clean

clean:
	rm -f test1 Factory
