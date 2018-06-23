rm -rf build/
mkdir build/
g++ -std=c++11 -Wall -o build/rpi_TLC5971_test main.c TLC5971.cpp -lwiringPi
