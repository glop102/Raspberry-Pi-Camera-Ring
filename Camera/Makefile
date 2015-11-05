CC=g++
CFLAGS=-pthread -std=gnu++11 -lraspicam -lpng
BUILD_DIR=build
RASPICAM_DEPENDS=raspicam_still.o #private_still_impl.o 

all: stdSocketTools.o fileSend.o
	$(CC)    -o main.out main.cpp $(CFLAGS) $(patsubst %,$(BUILD_DIR)/%,$^)

%.o: %.cpp
	$(CC) -c -o $(BUILD_DIR)/$@ $^ $(CFLAGS)

%.o: ../libs/%.cpp
	$(CC) -c -o $(BUILD_DIR)/$@ $^ $(CFLAGS)

#---------------------------------------------
%.o: raspicam/src/%.cpp
	$(CC) -c -o $(BUILD_DIR)/$@ $^ $(CFLAGS)
%.o: raspicam/src/private/%.cpp
	$(CC) -c -o $(BUILD_DIR)/$@ $^ $(CFLAGS)
%.o: raspicam/src/private_still/%.cpp
	$(CC) -c -o $(BUILD_DIR)/$@ $^ $(CFLAGS)
#----------------------------------------------
%.o: raspicam/src/dependencies/mmal/core/%.c
	$(CC) -c -o $(BUILD_DIR)/$@ $^ $(CFLAGS)
%.o: raspicam/src/dependencies/mmal/util/%.c
	$(CC) -c -o $(BUILD_DIR)/$@ $^ $(CFLAGS)
%.o: raspicam/src/dependencies/mmal/%.c
	$(CC) -c -o $(BUILD_DIR)/$@ $^ $(CFLAGS)

clean:
	rm build/*.o
	rm *.out

test: $(RASPICAM_DEPENDS)
	$(CC)    -o test.out test.cpp $(patsubst %,$(BUILD_DIR)/%,$^) -lraspicam -I/usr/local/include
