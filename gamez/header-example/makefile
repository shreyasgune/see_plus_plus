CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g $(shell root-config --cflags)
LDFLAGS=-g $(shell root-config --ldflags)
LDLIBS=$(shell root-config --libs)

SRCS=my_program.cpp my_class.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: my_program

my_program: $(OBJS)
    $(CXX) $(LDFLAGS) -o my_program $(OBJS) $(LDLIBS)

my_program.o: my_program.cc my_class.hh

my_class.o: my_class.hh my_class.cc

clean:
    $(RM) $(OBJS)

distclean: clean
    $(RM) my_program