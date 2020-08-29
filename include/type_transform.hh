#pragma once
#include<string.h>
#include<sstream>
#include<vector>
#include <algorithm>
#include<TString.h>
using namespace std;
template <class T>
std::string n2str(T num)
{
using namespace std;
/*this function is used to transform number (such as int,float and double)into string */

    stringstream ss;
    ss<<num;
    return ss.str();
}

template <class T>
vector<T> array2vector(T *x,int length)
{
    vector<T> v_return(length);
    for(int i=0;i<length;i++)
    {
        v_return[i]=x[i];
    }
    return v_return;
}

vector<float> v_str2v_float(vector<TString> v_str)
{
    vector<float> v_float;
    for(int i=0;i<v_str.size();i++)v_float.push_back(v_str[i].TString::Atof());
    return v_float;

}

template <class T>
T retain_n_float(T f,int n_retain)
{
    return round(f*10^n_retain)/float(10^n_retain);
}
