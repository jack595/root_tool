#!/bin/bash
mkdir -p ~/.trash
alias rm=trash
alias r=trash
alias rl='ls ~/.trash/'
alias ur=undelfile

undelfile()
{
if [ ! -z "$@" ]
then
    mv -i ~/.trash/$@ ./
else
    echo "Please input at least one parameter! for example : ur try.sh"
fi
}

is_empty_dir(){ 
    return `ls -A $1|wc -w`
}


trash()
{
FILE=$1
FILE_SIZE=`du -s $FILE | awk '{print $1}'`
if [ $FILE_SIZE -gt 102400 ] 
then
	echo "The size of $1 is greater 100M,do you want to mv $1 totally?(y/n)"
	read choice
	case $choice in
	y)
	/bin/rm -rf $1
	;;
	n)
	;;
	esac
elif [ ! -s ./$1 ]
then
	/bin/rm $1
elif is_empty_dir $1
then
	/bin/rm -rf $1
else
	mv -f $@ ~/.trash/
fi
checktrash
}

checktrash()
{
FILE2="/home/luoxj/.trash"
FILE_SIZE=`du -s $FILE2 | awk '{print $1}'`
#change the size of trash here
if [ $FILE_SIZE -gt 102400 ] 
then
        echo "The size of $FILE2 is greater 100M,do you want to clear the trash?(y/n)"
        read choice
        case $choice in
        y)
	cleartrash
        ;;
        n)
        ;;
        esac
fi

}

cleartrash()
{
  /bin/rm -rf ~/.trash/*
}
