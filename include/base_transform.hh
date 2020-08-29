#include<iostream>
#include<vector>
#include<TString.h>

std::vector<int> decimalism2binary_find_non_zero_position(unsigned long long a)
{
    std::vector<int> out;
    for(int i=0;i<64;i++)
    {
        if(a%2==1)
        out.push_back(i);
        a/=2;
    }
    return out;
}
unsigned long HextoDec(TString s, int length)
{
    unsigned long sum = 0;
    int x;
    for (int j = 0; j < length; j++)
    {
        if(s[j]<='9'&&s[j]>='0')
            x=s[j]-'0';
        else if(s[j]<='f'&&s[j]>'9')
            x=s[j]-'a'+10;
        sum=sum*16+x;

    }
    return sum;
}
