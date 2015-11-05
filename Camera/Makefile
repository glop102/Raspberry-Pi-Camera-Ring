CC=g++
CFLAGS=-pthread -std=gnu++11 -lraspicam -lpng
BUILD_DIR=build
RASPICAM_DEPENDS=raspicam_still.o #private_still_impl.o 

all: libpng raspicam main.out
	#nothing to see here

main.out: stdSocketTools.o fileSend.o
	$(CC)    -o main.out main.cpp $(CFLAGS) $(patsubst %,$(BUILD_DIR)/%,$^)

%.o: %.cpp
	if ! [-d $(BUILD_DIR)]; then mdir $(BUILD_DIR); fi
	$(CC) -c -o $(BUILD_DIR)/$@ $^ $(CFLAGS)

%.o: ../libs/%.cpp
	if ! [-d $(BUILD_DIR)]; then mdir $(BUILD_DIR); fi
	$(CC) -c -o $(BUILD_DIR)/$@ $^ $(CFLAGS)

#---------------------------------------------
%.o: raspicam/src/%.cpp
	if ! [-d $(BUILD_DIR)]; then mdir $(BUILD_DIR); fi
	$(CC) -c -o $(BUILD_DIR)/$@ $^ $(CFLAGS)
%.o: raspicam/src/private/%.cpp
	if ! [-d $(BUILD_DIR)]; then mdir $(BUILD_DIR); fi
	$(CC) -c -o $(BUILD_DIR)/$@ $^ $(CFLAGS)
%.o: raspicam/src/private_still/%.cpp
	if ! [-d $(BUILD_DIR)]; then mdir $(BUILD_DIR); fi
	$(CC) -c -o $(BUILD_DIR)/$@ $^ $(CFLAGS)
#----------------------------------------------
%.o: raspicam/src/dependencies/mmal/core/%.c
	if ! [-d $(BUILD_DIR)]; then mdir $(BUILD_DIR); fi
	$(CC) -c -o $(BUILD_DIR)/$@ $^ $(CFLAGS)
%.o: raspicam/src/dependencies/mmal/util/%.c
	if ! [-d $(BUILD_DIR)]; then mdir $(BUILD_DIR); fi
	$(CC) -c -o $(BUILD_DIR)/$@ $^ $(CFLAGS)
%.o: raspicam/src/dependencies/mmal/%.c
	if ! [-d $(BUILD_DIR)]; then mdir $(BUILD_DIR); fi
	$(CC) -c -o $(BUILD_DIR)/$@ $^ $(CFLAGS)

clean:
	rm build/*.o
	rm *.out
	cd libpng-1.2.52 && make clean
	cd raspicam/build && make clean

test: $(RASPICAM_DEPENDS)
	$(CC)    -o test.out test.cpp $(patsubst %,$(BUILD_DIR)/%,$^) -lraspicam -I/usr/local/include

libpng:
	cd libpng-1.2.52 && make && sudo make install

raspicam:
	#make the build dir
	if ! [-d raspicam/build]; then mdir raspicam/build; fi
	#do the install
	cd raspicam/build && cmake .. && make && sudo make install