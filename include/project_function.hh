#pragma once
#include<TH1F.h>
#include<TH1_tool.hh>
#include<TCanvas.h>
#include<iostream>
#include<vector>
#include<fstream>
#include<map>
//this file is uesed to save the functions of specific projects,which could be generally used in other projects
using namespace std;
vector<float> find_time_start_of_anode(TH1F *h_anode,float trigger,float increase_range)
{
    TH1F *hnew=h_anode;
//    TH1F *hnew=(TH1F*)h_anode->Rebin(5,"h_new");
   int x_boom=find_boom_up(hnew,trigger,TH1F_center2bin(hnew,increase_range));
//   cout<<"x_boom:"<<x_boom<<endl;
    TH1F *h_diff=TH1F_diff(h_anode,"h_diff");
    h_diff->Smooth();
    TH1F *h_diff_new=(TH1F*)h_diff->Rebin(10,"h_diff_new");
   float x_boom_down=find_boom_down(h_diff_new,h_diff_new->GetMaximum(),\
                                    TH1F_center2bin(h_diff_new,100)\
                                    ,TH1F_center2bin(h_diff_new,x_boom));
   cout<<"x_boom_down:"<<x_boom_down<<endl;
   float y_boom_down=h_diff_new->GetBinContent(TH1F_center2bin(h_diff_new,\
                       x_boom_down));
   float x_max=h_diff_new->GetBinCenter(h_diff_new->GetMaximumBin());
   vector<float> loc_boom_down={x_boom_down,y_boom_down,x_max};
//  TCanvas *c1=new TCanvas("c","c1",800,600);
//  h_diff_new->DrawCopy("histsame");
//  hnew->DrawCopy("histsame");
//    cout<<TH1F_center2bin(h_anode,1500)<<endl;
//    cout<<x_boom<<" "<<x_boom_down<<endl;
//   vector<float> max_series=Max_subbin(h_diff_new,x_boom,x_boom_down+200);
//   cout<<max_series[0]<<endl;

   return loc_boom_down;
}
vector<float> find_time_start_of_anode_without_peak(TH1F *h_anode,float trigger,float increase_range)
{
    TH1F *hnew=(TH1F*)h_anode->Rebin(5,"h_new");    TH1F *h_diff=TH1F_diff(h_anode,"h_diff");
    h_diff->Smooth();
    TH1F *h_diff_new=(TH1F*)h_diff->Rebin(10,"h_diff_new");
    float x_boom=find_boom_up(h_diff_new,trigger,TH1F_center2bin(h_diff_new,increase_range));
    float y_boom_down=h_diff_new->GetBinContent(TH1F_center2bin(h_diff_new,\
                       x_boom));
   float x_max=h_diff_new->GetBinCenter(h_diff_new->GetMaximumBin());
   vector<float> loc_boom_down={x_boom,y_boom_down,x_max};
   return loc_boom_down;
}


std::vector<int> find_signal(int a)
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

using namespace std;
map<int,int>  create_map(TString name_file)
{
    map<int,int> map_TIN_x;
    ifstream f_map;
    f_map.open(name_file);
    int l=0;
    string TIN_str;
    string x_str;
    while (f_map.good())
    {
     if(l==0)
     {
         f_map>>TIN_str>>x_str;
//        cout<<TIN_str<<" "<<x_str<<endl;
     }
     else
     {
         f_map>>TIN_str>>x_str;
         map_TIN_x[TString(TIN_str).TString::Atoi()]=TString(x_str).TString::Atoi();
     }

    l++;

    }
    return map_TIN_x;
}
