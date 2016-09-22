CC=g++
CFLAGS=-pthread -std=gnu++11 -lraspicam -lpng -O2
RASPICAM_DEPENDS=raspicam_still.o #private_still_impl.o 

all: main.out
	sudo ldconfig
	#All Done. Just run "sudo ./main.out" to start it up
	#If you want, add the executable to the /etc/rc.local file to run on startup

main.out: build stdSocketTools.o fileSend.o
	$(CC)    -o main.out main.cpp $(CFLAGS) $(patsubst %,build/%,$^)

base:
	raspi-config #ENABLE THE CAMERA OPTION
	apt-get update
	apt-get upgrade
	#apt-get install build-essential cmake git g++-4.8
	#rm /usr/bin/g++
	#ln -s /usr/bin/g++-4.8 /usr/bin/g++
	make libpng
	make -B raspicam

build :
	- mkdir build

%.o: %.cpp
	$(CC) -c -o build/$@ $^ $(CFLAGS)

%.o: ../libs/%.cpp
	$(CC) -c -o build/$@ $^ $(CFLAGS)

#---------------------------------------------
%.o: raspicam/src/%.cpp
	$(CC) -c -o build/$@ $^ $(CFLAGS)
%.o: raspicam/src/private/%.cpp
	$(CC) -c -o build/$@ $^ $(CFLAGS)
%.o: raspicam/src/private_still/%.cpp
	$(CC) -c -o build/$@ $^ $(CFLAGS)
#----------------------------------------------
%.o: raspicam/src/dependencies/mmal/core/%.c
	$(CC) -c -o build/$@ $^ $(CFLAGS)
%.o: raspicam/src/dependencies/mmal/util/%.c
	$(CC) -c -o build/$@ $^ $(CFLAGS)
%.o: raspicam/src/dependencies/mmal/%.c
	$(CC) -c -o build/$@ $^ $(CFLAGS)

clean:
	- rm build/*.o
	- rm *.out
	cd libpng-1.2.52 && make clean
	cd raspicam/build && make clean

test: $(RASPICAM_DEPENDS)
	$(CC)    -o test.out test.cpp $(patsubst %,build/%,$^) -lraspicam -I/usr/local/include

libpng:
	if ! [ -a libpng-1.2.52/Makefile ] ; then cd libpng-1.2.52 && ./configure; fi
	cd libpng-1.2.52 && make && sudo make install

raspicam:
	sudo apt-get -y install cmake
	#make the build dir
	if ! [ -d raspicam/build ]; then mkdir raspicam/build; fi
	#do the install
	cd raspicam/build && cmake .. && make && sudo make install

.PHONY: raspicam
