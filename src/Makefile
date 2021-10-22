TARGET=GraphicsAreFun
OBJECTS=main.o color.o graphics_lib.o matrix_stack.o projection.o transform_matrix.o vector2.o vector3.o vector3h.o vertex.o draw_routines.o
HEADERS=$(patsubst %.o, %.h, $(OBJECTS))
SRC_FILES=$(patsubst %.o, %.cpp, $(OBJECTS))
INC_DIR=../include
TEST_DIR=../test

ifeq ($(OS),Windows_NT)     # is Windows_NT on XP, 2000, 7, Vista, 10...
    detected_OS := Windows
else
    detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif

CXXFLAGS=-I$(INC_DIR) 

ifeq ($(detected_OS),Darwin)        # Mac OS X
CXXFLAGS+= -I/usr/local/include/SDL2 
endif
ifeq ($(detected_OS),Linux)
CXXFLAGS+= -I/usr/include/SDL2 
endif

LIBS=-L/usr/local/lib -lSDL2
CXX=g++

all: $(TARGET) 

$(TARGET): $(OBJECTS)
	$(CXX) -ggdb -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: env 

env:
	$(info TARGET=$(TARGET))
	$(info OBJECTS=$(OBJECTS))
	$(info HEADERS=$(HEADERS))
	$(info INC_DIR=$(INC_DIR))
	$(info CXXFLAGS=$(CXXFLAGS))
	$(info LIBS=$(LIBS))
	$(info CXX=$(CXX))

.PHONY: clean

clean:
	rm *.o $(TARGET)
