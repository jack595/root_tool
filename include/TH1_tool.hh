
#pragma once
#include<TH1F.h>
#include<TString.h>
#include<type_transform.hh>
#include<TF1.h>
#include "TH1D.h"
//if TH1F want to add legend,we can use c->BuidLegend,where c is TCanvas,and use h->SetTitle to set the entries.
using namespace std;

int TH1_center2bin(TH1 *h,float center)
{
    double min=h->GetXaxis()->GetXmin();
    double max=h->GetXaxis()->GetXmax();
    int bin=(center-min)*h->GetNbinsX()/(max-min)+1;
    return bin;
}
int TH1F_center2bin(TH1F *h,float center)
{
    double min=h->GetXaxis()->GetXmin();
    double max=h->GetXaxis()->GetXmax();
    int bin=(center-min)*h->GetNbinsX()/(max-min)+1;
    return bin;
}


template <class T>
TH1F *v2TH1F(vector<T> v,TString h_title)
{
    TH1F* h_return=new TH1F(h_title,h_title,v.size(),0,v.size());
    for(int i=0;i<v.size();i++)
    {
        h_return->SetBinContent(i,float(v[i]));
    }
    return h_return;
}

template <class T>
TH1 *v2TH1(vector<T> v,TString h_title)
{
    TH1D* h_return=new TH1D(h_title,h_title,v.size(),0,v.size());
    for(int i=0;i<v.size();i++)
    {
        h_return->SetBinContent(i,double(v[i]));

    }
    return (TH1*)h_return;
}
vector<double> TH12v(TH1* h)
{
    vector<double> v_return;
    v_return.reserve(h->GetNbinsX());
    for(int i=1;i<h->GetNbinsX();i++)
    {
        v_return.push_back(h->GetBinContent(i));
    }
    return v_return;
}

std::vector<float> Max_subbin(TH1F *h1,float min_range,float max_range)
{
//this function is used to find the maxmium point's location of histgram,return(x_max,y_min)
    float max,max_loc;
    TH1F *h=(TH1F*) h1;
    int h_min_bin=h1->GetXaxis()->GetXmin();
    int h_max_bin=h1->GetXaxis()->GetXmax();
    h->GetXaxis()->SetRangeUser(min_range,max_range);
//    h->Draw();
    max=h->GetMaximum();
    float max_bin=h->GetMaximumBin();
    max_loc=h->GetBinCenter(max_bin);
    std::vector<float> max_series={max_loc,max};
    h->GetXaxis()->SetRangeUser(h_min_bin,h_max_bin);
    return max_series;
}
std::vector<float> Min_subbin(TH1F *h1,float min_range,float max_range)
{
//this function is used to find the maxmium point's location of histgram,return(x_max,y_min)
    float min,min_loc;
    TH1F *h=(TH1F*) h1;
    int h_min_bin=h1->GetXaxis()->GetXmin();
    int h_max_bin=h1->GetXaxis()->GetXmax();
    h->GetXaxis()->SetRange(min_range,max_range);
//    h->Draw();
    min=h->GetMinimum();
    float min_bin=h->GetMaximumBin();
    min_loc=h->GetBinCenter(min_bin);
    std::vector<float> min_series={min_loc,min};
    h->GetXaxis()->SetRange(h_min_bin,h_max_bin);
    return min_series;
}

vector<float>find_max_extremum(TH1F *h,int scan_step=1)
{
    int bin_extremum=h->GetNbinsX();
    vector<float> v_max;
    vector<float> v_error_return={-1,-1};
    int bin_min_range=1;
    int bin_max_range=h->GetNbinsX();
    v_max=Max_subbin(h,bin_min_range,bin_max_range);
    bin_extremum=(TH1_center2bin((TH1*)h,v_max[0]))+1;
//    bin_extremum=h->GetMaximumBin();
//    cout<<bin_extremum<<" "<<h->GetNbinsX()<<endl;
    while (bin_extremum==bin_max_range or bin_extremum==bin_min_range)
    {

        bin_min_range=bin_min_range+scan_step;
        bin_max_range=bin_max_range-scan_step;
        if(bin_min_range>=bin_max_range) return v_error_return;
        v_max=Max_subbin(h,bin_min_range,bin_max_range);
        bin_extremum=TH1_center2bin((TH1*)h,v_max[0]);
//        cout<<bin_extremum<<" "<<h->GetNbinsX()<<endl;

    }
    vector<float> v_return={(float)h->GetBinCenter(bin_extremum),v_max[1]};
    return v_return;
}

TH1F *cut_TH1F(TH1F *h,float min_range,float max_range)
{
    //this function is to uesd to cut a histogram into another histogram which contain a subrange of the first histogram .
        TH1F *h1=new TH1F("h1","h1",Int_t(max_range-min_range)+1,0,Int_t(max_range-min_range)+1);
    for(int i=int(min_range);i<max_range+1;i++)
    {
        h1->SetBinContent(Int_t(i-min_range),h->GetBinContent(i));
    }
    return h1;
}

TH1F *TH1F_plus(TH1F *h,float constant,TString function_str="1")
{
    //this function is used to add histogram a constant ,if you want to add a function ,you can imitate the function below
    //just change the definition of TF1
     TF1 *f=new TF1("f",function_str,h->GetXaxis()->GetXmin(),h->GetXaxis()->GetXmax());

     h->Add(f,constant);
     h->Sumw2();
    return h;
}

void TH1_plus(TH1 *h,float constant,TString function_str="1")
{
    //this function is used to add histogram a constant ,if you want to add a function ,you can imitate the function below
    //just change the definition of TF1
     TF1 *f=new TF1("f",function_str,h->GetXaxis()->GetXmin(),h->GetXaxis()->GetXmax());

     h->Add(f,constant);
     h->Sumw2();
}


TH1F *TH1F_diff(TH1F *h,TString name_h="h_diff",int n_rebin=10,float step=1)
{
    TH1F *h_copy = (TH1F*)h->Clone("hnew");
//    h_copy->Smooth();
    TH1F *hnew=(TH1F*)h_copy;
    TH1F *h_dif=new TH1F(name_h,name_h,hnew->GetNbinsX(),hnew->GetXaxis()->GetXmin(),hnew->GetXaxis()->GetXmax());
    float slop_temp;
    for(int i=1;i<hnew->GetNbinsX()-2;i++)
    {
        slop_temp=(hnew->GetBinContent(i+1)-hnew->GetBinContent(i))/step;
        h_dif->SetBinContent(i,slop_temp);

    }
    h_dif->Smooth();
    return h_dif;
}

TH1* fill_TH1_xy(TH1* h_x,TH1* h_y,TString name_h)
{
    TH1D *h_return = new TH1D(name_h,"h_xy",h_x->GetBinContent(h_x->GetNbinsX())\
                              -h_x->GetBinContent(1),h_x->GetBinContent(1)\
                            ,h_x->GetBinContent(h_x->GetNbinsX()));
    for(int i =1;i<h_x->GetNbinsX();i++)
    {
        h_return->SetBinContent(i,h_y->GetBinContent(i));
    }
    return (TH1*)h_return;
}

float find_boom_up(TH1F *h,float trigger,int increase_range_bin,int bin_begin=0)
{

    TH1F *hnew = (TH1F*)h->Clone("hnew");
    hnew->Smooth();
    int n_increase=0;
//    std::cout<<hnew->GetNbinsX()<<endl;
    for(int i=bin_begin;i<hnew->GetNbinsX();i++)
//    for(int i=2000;i<3000;i++)
    {
//        std::cout<<hnew->GetBinContent(i)<<" "<<hnew->GetBinContent(1)<<endl;
        if(hnew->GetBinContent(i)-hnew->GetBinContent(1)>=trigger)
        {
            n_increase=0;
            for(int j=i;j-i<=increase_range_bin;j++)
            {
                if(hnew->GetBinContent(j+1)-hnew->GetBinContent(j)>=0)
                {
                    n_increase=n_increase+1;
//                    std::cout<<n_increase<<endl;
                }
//        std::cout<<j-i<<endl;
            }
            if(n_increase>=increase_range_bin) return float(hnew->GetBinCenter(i));
        }
//        std::cout<<i<<endl;
    }
    return -1;
}

int find_bin_boom_up(TH1F *h,float trigger,int increase_range,int bin_begin=0)
{

    TH1F *hnew = (TH1F*)h->Clone("hnew");
    hnew->Smooth();
    int n_increase=0;
//    std::cout<<hnew->GetNbinsX()<<endl;
    for(int i=bin_begin;i<hnew->GetNbinsX();i++)
//    for(int i=2000;i<3000;i++)
    {
//        std::cout<<hnew->GetBinContent(i)<<" "<<hnew->GetBinContent(1)<<endl;
        if(hnew->GetBinContent(i)-hnew->GetBinContent(1)>=trigger)
        {
            n_increase=0;
            for(int j=i;j-i<=increase_range;j++)
            {
                if(hnew->GetBinContent(j+1)-hnew->GetBinContent(j)>0)
                {
                    n_increase=n_increase+1;
//                    std::cout<<n_increase<<endl;
                }
//        std::cout<<j-i<<endl;
            }
            if(n_increase>=increase_range) return i;
        }
//        std::cout<<i<<endl;
    }
    return -1;
}



float find_boom_down(TH1F *h,float trigger,int decrease_range,int bin_begin=0)
{

    TH1F *hnew = (TH1F*)h->Clone("hnew");
    hnew->Smooth();
    int n_decrease=0;
//    std::cout<<hnew->GetNbinsX()<<endl;
    for(int i=bin_begin;i<hnew->GetNbinsX();i++)
//    for(int i=2000;i<3000;i++)
    {
//        std::cout<<hnew->GetBinContent(i)<<" "<<hnew->GetBinContent(1)<<endl;
        if(hnew->GetBinContent(i)-hnew->GetBinContent(1)<=trigger)
        {
            n_decrease=0;
            for(int j=i;j-i<=decrease_range;j++)
            {
                if(hnew->GetBinContent(j+1)-hnew->GetBinContent(j)<0)
                {
                    n_decrease=n_decrease+1;
//                    std::cout<<n_decrease<<endl;
                }
//        std::cout<<j-i<<endl;
            }
            if(n_decrease>=decrease_range) return float(hnew->GetBinCenter(i));
        }
//        std::cout<<i<<endl;
    }
    return -1;
}

template <class T>
float find_base(TH1* h_input,T base_begin,T base_end)
{
    int bin_base_begin=TH1_center2bin(h_input,base_begin);
    int bin_base_end=TH1_center2bin(h_input,base_end);
    float sum=0;
    for(int i=bin_base_begin;i<bin_base_end;i++)
    {
        sum+=h_input->GetBinContent(i);
    }
    return sum/float(bin_base_end-bin_base_begin);
}








































