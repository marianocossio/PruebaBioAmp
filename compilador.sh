#!/bin/sh

clear

rm Makefile
rm pruebabioamp_plugin_import.cpp
rm PruebaBioAmp
rm PruebaBioAmp.pro.user

make clean

PATH=/home/mariano/QtStatic/QtStatic/bin:$PATH
export PATH

qmake -config release

make

ldd ./PruebaBioAmp

./PruebaBioAmp
