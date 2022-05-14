all: openMP posix serial

openMP:
	gcc -Include/ -Iinclude/ src/primecount_openmp.c -o primeOpenmp.exe -fopenmp
posix:
	gcc -Include/ -Iinclude/ src/primecount_posix.c -o primePosix.exe -lpthread
serial:
	gcc -Include/ -Iinclude/ src/primecount_serial.c -o primeSerial.exe
