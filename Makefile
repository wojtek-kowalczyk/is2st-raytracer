appname := program

CXX := g++
CXXFLAGS := -Wall -g

libsrc := $(shell find Raytracer/src/ -name "*.cpp")
libobjects  := $(patsubst %.cpp, %.o, $(libsrc))

headsrc := $(shell find RaytracerHead/ -name "*.cpp")
headobjects  := $(patsubst %.cpp, %.o, $(headsrc))

all: $(appname)

$(appname): $(objects)
	$(CXX) -c $(CXXFLAGS) $(LDFLAGS) -o libraytracer.o $(libsrc) $(LDLIBS)
	ar rcs Raytracer/bin/lib/libraytracer.a libraytracer.o
	$(CXX) $(CXXFLAGS) -IRaytracer/src/ -o $(appname) $(headsrc) -LRaytracer/bin/lib -lraytracer

clean:
	rm -f $(headobjects)
	rm -f $(libobjects)
	rm $(appname)
	rm Raytracer/bin/lib/*
	rm libraytracer.o
