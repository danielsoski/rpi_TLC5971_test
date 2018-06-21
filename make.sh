rm -rf build/
mkdir build/
gcc -Wall -o build/rpi_TLC5971_test main.c -lwiringPi
