CC=g++
CFLAGS=-pthread -std=gnu++11 -lpng -O2 #-lraspicam
RASPICAM_DEPENDS=build/raspicam_still.o #private_still_impl.o 
MMAL = -L/opt/vc/lib/ -lmmal -lmmal_util -lmmal_core

all: main.out
	sudo ldconfig
	#All Done. Just run "sudo ./main.out" to start it up
	#If you want, add the executable to the /etc/rc.local file to run on startup
.PHONY: all

main.out: main.cpp cameraCommands.h globals.h tcpCommands.h udpCommands.h build build/stdSocketTools.o build/fileSend.o build/raspicam.o image.a
	$(CC)    -o main.out main.cpp $(CFLAGS) build/*.o $(MMAL) image.a

base:
	#raspi-config #ENABLE THE CAMERA OPTION
	sudo apt-get update
	sudo apt-get upgrade
	#apt-get install build-essential cmake git g++-4.8
	#rm /usr/bin/g++
	#ln -s /usr/bin/g++-4.8 /usr/bin/g++
	make libpng
	make -B raspicam

build :
	#Creating Build Directory
	- mkdir build

build/stdSocketTools.o: ../libs/stdSocketTools.cpp
	$(CC) -c -o $@ $^ $(CFLAGS)
build/fileSend.o: ../libs/fileSend.cpp
	$(CC) -c -o $@ $^ $(CFLAGS)

image.a:
	cd ../glopLibs/imageLibrary && make image.a
	cp ../glopLibs/imageLibrary/image.a .

#---------------------------------------------
#  Raspi Cam
#---------------------------------------------
build/raspicam.o: RaspiCam/src/raspicam.cpp build/private_impl.o build/threadcondition.o
	$(CC) -c -o $@ $^ $(CFLAGS)
build/private_impl.o: RaspiCam/src/private/private_impl.cpp
	$(CC) -c -o $@ $^ $(CFLAGS)
build/threadcondition.o: RaspiCam/src/private/threadcondition.cpp
	$(CC) -c -o $@ $^ $(CFLAGS)



clean:
	#PI-Ring Clean
	- rm build/*.o
	- rm *.out
	cd ../glopLibs/imageLibrary && make clean

	#LIB PNG
	#cd libpng-1.2.52 && make clean

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
