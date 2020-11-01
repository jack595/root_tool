#!/bin/bash
get_filename()
{
    full_path=$1
    start_num=`echo ${full_path}| grep -b -o "/" | cut -d: -f1`
    #两个#是去掉最后一个符号/左边的内容
    filename=${full_path##*/}
    #filename=$(basename $full_path)
    echo $filename
}
get_dir()
{
    full_path=$1
    dir=${full_path%/*}
    #dir=$(dirname $full_path)
    #echo 就是bash脚本返回参数的一种方法
    echo $dir
}
