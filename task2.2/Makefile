FILE = main.cpp
CONFIG = config.p
RESULT = results.png
MAIN = main

all: NPADS.compact plot

run:
	./$(MAIN)

buildExtra: $(FILE)
	$(CXX) --std=c++14 -Wall -Wextra -Werror -Weffc++ -O3 -o $(MAIN) $(FILE)

build: $(FILE)
	$(CXX) -DNPAD=${ARGS} --std=c++14 -O3 -o $(MAIN) $(FILE)

plot:
	gnuplot $(CONFIG) > $(RESULT)

clean.main:
	rm ./$(MAIN)

clean.dat:
	rm *.dat

clean: clean.dat clean.main

n ?= 0
NPADS.all:
	n=$(n); \
	while [ $${n} -lt 32 ] ; do \
		echo $$n ; \
		make ARGS=$$n build; \
		make run; \
		n=`expr $$n + 1`; \
	done; \
	true

NPADS.compact:
	for number in 0 7 15 31 ; do \
		make ARGS=$$number build --no-print-directory; \
		./$(MAIN) > $$number.dat --no-print-directory; \
		make clean.main --no-print-directory; \
	done;