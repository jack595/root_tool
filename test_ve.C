#include<vec_op.hh>
#include<iostream>
#include<plot.hh>
#include<TTree.h>
#include<TString.h>
#include<type_transform.hh>
int main()
{
    using namespace std;
    std::vector<float> x={1.5,1.6,20};
    vector<float> y={200,7,1.1,9,100};
    vector<vector<float>> series;
    series.push_back(x);
    series.push_back(y);
    cout<<min_series(series)<<endl;
    return 0;

}
