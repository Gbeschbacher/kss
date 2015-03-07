FILE = main.cpp
SAVE = heaps.dat
CONFIG = config.p
RESULT = results.png
MAIN = main

all: build run plot clean

run:
	./$(MAIN) > $(SAVE)

build: $(FILE)
	$(CXX) --std=c++14 -Wall -Wextra -Werror -Weffc++ -pedandic  -O3 -o $(MAIN) $(FILE)

plot:
	gnuplot $(CONFIG) > $(RESULT)

clean:
	rm ./$(MAIN)