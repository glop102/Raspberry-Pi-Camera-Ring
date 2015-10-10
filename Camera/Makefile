CC=g++
CFLAGS=-pthread -std=gnu++11
BUILD_DIR=build

all: stdSocketTools.o
	$(CC)    -o main.out main.cpp $(CFLAGS) $(patsubst %,$(BUILD_DIR)/%,$^)

%.o: %.cpp
	$(CC) -c -o $(BUILD_DIR)/$@ $^ $(CFLAGS)

%.o: ../libs/%.cpp
	$(CC) -c -o $(BUILD_DIR)/$@ $^ $(CFLAGS)

clean:
	rm build/*.o
	rm *.out