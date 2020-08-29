#!/bin/bash
for i in $(ls)
do
	if [ -d $i ]
	then
	cp try.C $i/
	fi
done
