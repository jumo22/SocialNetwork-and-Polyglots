all: build

build-socialnetwork:
	g++ socialnetwork.cpp -o socialnetwork --std=c++11 -O2

build-polyglots:
	g++ polyglots.cpp -o polyglots --std=c++11 -O2

build: build-socialnetwork build-polyglots
    
run-p1:
	./socialnetwork
	
run-p2:
	./polyglots

clean:
	rm -f socialnetwork polyglots *.in *.out