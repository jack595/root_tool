#!/bin/bash
cp /afs/ihep.ac.cn/users/l/luoxj/workfs_5G/root_tool/CMakeLists_G4_here_run.txt /afs/ihep.ac.cn/users/l/luoxj/workfs_5G/root_tool/CMakeLists.txt
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
