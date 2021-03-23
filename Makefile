GCC=g++
 
  
all: snake.cpp
	$(GCC) -g -Wall -o snake snake.cpp

clean: 
	$(RM) snake

