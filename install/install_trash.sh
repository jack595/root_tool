#!/bin/bash
if [[ $(grep -c "/root_tool/install/rm_turn_trash.sh" ~/.bashrc) == 1 ]]
then
	echo "deleting $(grep "/root_tool/install/rm_turn_trash.sh" ~/.bashrc) in ~/.bashrc"
	i=$(grep -n "/root_tool/install/rm_turn_trash.sh" ~/.bashrc | cut -d ":" -f 1) 
	sed $i"d" -i ~/.bashrc
fi
echo 'append .bashrc with source'$(pwd)/rm_turn_trash.sh
echo  'source '$(pwd)'/rm_turn_trash.sh' >>~/.bashrc
echo "the install of trash done,please reboot this terminal"

