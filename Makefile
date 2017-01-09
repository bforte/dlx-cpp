CXX ?= g++
CXXFLAGS += -Iinclude -I/usr/include/python2.7 -std=c++11 -pedantic -Wall -O3 -fPIC

all: dlx-cpp wrapper shared_library

no_dlx-cpp: wrapper shared_library

dlx-cpp:
	mkdir -p build
	$(CXX) $(CXXFLAGS) -c src/AlgorithmDLX.cpp -o build/AlgorithmDLX.o
	$(CXX) $(CXXFLAGS) -c src/ExactCoverProblem.cpp -o build/ExactCoverProblem.o
	$(CXX) $(CXXFLAGS) -c src/LinkedMatrix.cpp -o build/LinkedMatrix.o

wrapper:
	mkdir -p build
	$(CXX) $(CXXFLAGS) -c src/libexactcover.cpp -o build/libexactcover.o

shared_library:
	mkdir -p dlx_python
	touch dlx_python/__init__.py
	$(CXX) $(CXXFLAGS) -shared build/*.o -I/usr/include/python2.7 -lboost_python -o dlx_python/libexactcover.so

clean:
	rm -rf build
	rm -rf dlx_python
