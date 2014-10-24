#assn3 makefile

#Variables
COMPILE = g++
FLAGS = -g -W -Wall -Werror -ansi -pedantic
OBJS = map.o

#Targets
all: main.cpp $(OBJS)
	$(COMPILE) $(FLAGS) -o a.out main.cpp $(OBJS)

map.o: map.cpp map.h
	$(COMPILE) $(FLAGS) -c map.cpp

clean:
	rm -rf *~ *.o a.out
