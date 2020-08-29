#! /bin/bash
sed ':a;N;$!ba;s/ /\t/g' $1>temp.exe
for ((i=1;i<=$2;i++))
do
	#cut -f $i temp.exe|sed ':a;N;$!ba;s/\n/,/g'>data_output$i.txt
	
	cut -f $i temp.exe>data_output$i.txt
done
