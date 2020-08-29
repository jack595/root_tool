#! /bin/bash
oldOwner=$(sed -n "1p" ../command/Readme|cut -d ":" -f 2)
#echo $oldOwner
cd ../
#echo $(pwd)
sed -i "s#$oldOwner#$(pwd)#g" $(pwd)/command/*
#sed -i "s#$oldOwner#pwd_install_try#g" $(pwd)/*
if [[ $(grep -c "/root_tool/command" ~/.bashrc) == 1 ]]
then
	echo "deleting $(grep "/root_tool/command" ~/.bashrc) in ~/.bashrc"
	i=$(grep -n "/root_tool/command" ~/.bashrc | cut -d ":" -f 1) 
	sed $i"d" -i ~/.bashrc 
fi
echo 'append .bashrc with export PATH=$PATH:'$(pwd)/command/
echo 'export PATH=$PATH:'$(pwd)'/command/' >>~/.bashrc
echo "install done,please reboot this terminal"

#make a link for root_tool
ln -s $(pwd) ~/root_tool
