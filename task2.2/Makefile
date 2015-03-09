FILE = main.cpp
SAVE = data.dat
CONFIG = config.p
RESULT = results.png
MAIN = main

#all: build2 run clean

all: all.NPADS

run:
	./$(MAIN) >> $(SAVE)

buildExtra: $(FILE)
	$(CXX) --std=c++14 -Wall -Wextra -Werror -Weffc++ -O3 -o $(MAIN) $(FILE)

build: $(FILE)
	$(CXX) -DNPAD=${ARGS} --std=c++14 -o $(MAIN) $(FILE) \

plot:
	gnuplot $(CONFIG) > $(RESULT)

clean:
	rm ./$(MAIN)

n ?= 0
all.NPADS:
	n=$(n); \
	while [ $${n} -lt 32 ] ; do \
		echo $$n ; \
		make ARGS=$$n build; \
		make run; \
		n=`expr $$n + 1`; \
	done; \
	true
