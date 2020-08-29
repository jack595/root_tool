#!/bin/bash
if  [ -f "C_File_target" ] ;then
	rm C_File_target
fi
make -j4
#./exampleB1

if  [ ! -n "$1" ] ;then
	./C_File_target
else
	./C_File_target $1
fi
