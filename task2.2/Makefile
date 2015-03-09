FILE = main.cpp
SAVE = data.dat
CONFIG = config.p
RESULT = results.png
MAIN = main

all: NPADS.compact

runNsave:
	./$(MAIN) >> $(SAVE)

run:
	./$(MAIN)

buildExtra: $(FILE)
	$(CXX) --std=c++14 -Wall -Wextra -Werror -Weffc++ -O3 -o $(MAIN) $(FILE)

build: $(FILE)
	$(CXX) -DNPAD=${ARGS} --std=c++14 -o $(MAIN) $(FILE)

plot:
	gnuplot $(CONFIG) > $(RESULT)

clean.main:
	rm ./$(MAIN)

clean.data:
	rm ./$(SAVE)

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
	for number in 0 7 15 31 63 ; do \
		make ARGS=$$number build; \
		make runNsave; \
	done;
	make clean.main