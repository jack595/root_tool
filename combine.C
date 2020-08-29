//#pragma once
#include"TreeManager.hh"
#include"combine.hh"

int main()
{
    name_list name;

    name.push_back("Generate");
    name.push_back("Absorb");
    name.push_back("Path");
    //name.push_back("Number");
    TreeManager treemanager(name,"../Project4_C/");

    combine(&treemanager,"Project4_C",false);


    return 0;
}
