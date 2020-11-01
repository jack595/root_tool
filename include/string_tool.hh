#pragma once
#include"TCanvas.h"
#include<vector>
#include"TString.h"
#include<iostream>
#include<string.h>
using namespace std;
std::string getfilename_FullPath(std::string name_FullPath)
{
    std::string::size_type iPos = name_FullPath.find_last_of('/')+1;
    std::string filename = name_FullPath.substr(iPos, name_FullPath.length()-iPos);
//cout<<filename<<endl;
    string name = filename.substr(0, filename.rfind("."));
  //  cout << name << endl; 
    return name;

}
