FILE = main.cpp
SAVE = heaps.dat
CONFIG = config.p
RESULT = results.png
MAIN = main

all: build run clean

run:
	./$(MAIN)

build: $(FILE)
	$(CXX) --std=c++14 -Wall -Wextra -Werror -Weffc++ -O3 -o $(MAIN) $(FILE)

build2: $(FILE)
	$(CXX) --std=c++14 -o $(MAIN) $(FILE)

plot:
	gnuplot $(CONFIG) > $(RESULT)

clean:
	rm ./$(MAIN)