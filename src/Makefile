TARGET=GraphicsAreFun
OBJECTS=main.o color.o graphics_lib.o matrix_stack.o projection.o transform_matrix.o vector2.o vector3.o vector3h.o vertex.o draw_routines.o
HEADERS=$(patsubst %.o, %.h, $(OBJECTS))
SRC_FILES=$(patsubst %.o, %.cpp, $(OBJECTS))
INC_DIR=../include
TEST_DIR=../test
CXXFLAGS=-I$(INC_DIR) -I/usr/include/SDL2 
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
