TARGET=GraphicsAreFun
OBJECTS= color.o graphics_lib.o matrix_stack.o projection.o transform_matrix.o vector2.o vector3.o vector3h.o vertex.o draw_routines.o
HEADERS= $(patsubst %.o, %.h, $(OBJECTS)) main.h
SRC_FILES= $(patsubst %.o, %.cpp, $(OBJECTS))
INC_DIR= ../include
CXXFLAGS= -I$(INC_DIR) -I/usr/local/include/SDL2 
LIBS= -L/usr/local/lib -lSDL2
CXX=g++

$(TARGET): $(OBJECTS)
	$(CXX) main.cpp -ggdb -o $@ $^ $(CXXFLAGS) $(LIBS)

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
