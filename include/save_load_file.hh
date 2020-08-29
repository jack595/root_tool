#pragma once
#include<TTree.h>
#include<TFile.h>
#include<string>
#include<iostream>
#include<dirent.h>
#include<stdio.h>
#include<TH1F.h>
#include<TH1_tool.hh>
#include<cut_criterion.hh>
#include<fstream>
#include<TCanvas.h>

//save_file()is used to save 1D data,and generate a tree named "data",
//usage:save_file(saved_name,1D data,1D data's length(string))
//
//load()is used to load the 1D data saved by save_file()
//usage:load(loaded_file's name,1D vector used to get the data,name_of_branch)
void save(TString file_name,std::vector<Double_t> x,TString name_branch)
{
TFile *f =new TFile(file_name,"recreate");
TTree* tree = new TTree("data","data");
//Int_t length_int=(Int_t)length.Atoi();
Double_t x_save;
Int_t length_int=x.size();
tree->Branch(name_branch,&x_save,name_branch+"/D");
//Branch must be set after TFile created,otherwise the Branch would not be set properly!!!
for(int i=0;i<length_int;i++){
	x_save=x[i];
	tree->Fill();}
tree->Write();
f->Close();

}
void test_save()
{
//Double_t x[3]={1,2,3};
    std::vector<Double_t> x{1,2,3};
save("test.root",x,"E");

}

using namespace std;
template <class T>
void load(TString name_file,std::vector<T> &x,TString name_Branch)
{
TFile *f = new TFile(name_file);
TTree *tree=(TTree*)f->Get("data");
T x_load;
tree->SetBranchAddress(name_Branch,&x_load);
x.reserve(tree->GetEntries());
for(int i=0;i<tree->GetEntries();i++){
tree->GetEntry(i);
x.push_back(x_load);
std::cout<<x_load<<std::endl;
}
f->Close();
}

using namespace std;
vector<vector<double>> load_tree_v(TString name_file,TString name_tree,TString name_Branch,Int_t length)
{
    //this function is used to load the TTree's data into a vector series,whose element is a vector.for example,v_return[0] is the
    //first vector in the TTree
TFile *f = new TFile(name_file);
TTree *tree=(TTree*)f->Get(name_tree);
vector<double> x_load(length);
tree->SetBranchAddress(name_Branch,&*x_load.begin());
vector<vector<double>> v_return;
v_return.reserve(tree->GetEntries());
for(int i=0;i<tree->GetEntries();i++){
//for(int i=0;i<2;i++){
tree->GetEntry(i);
v_return.push_back(x_load);
}
f->Close();
return v_return;
}

using namespace std;
vector<TH1F*> load_tree_v_TH1F(TString name_file,TString name_tree,TString name_Branch,Int_t length,int length_h_series)
{
    //this function is used to load the TTree's data into a vector which contain many histogram,h_series[0] is the first histogram.used to check some data histogram
TFile *f = new TFile(name_file);
TTree *tree=(TTree*)f->Get(name_tree);
vector<float> x_load(length);
tree->SetBranchAddress(name_Branch,&*x_load.begin());
vector<TH1F*> h_series;
h_series.reserve(tree->GetEntries());
for(int i=0;i<length_h_series;i++){
//for(int i=0;i<2;i++){
tree->GetEntry(i);

h_series.push_back(v2TH1F(x_load,"h"));
}
f->Close();
return h_series;

}

TH1 *load_single_TH1(TString name_file,TString name_h)
{
    TFile *f=new TFile(name_file);
    TH1 *h_return =(TH1*)f->Get(name_h);
    return h_return;
}

using namespace std;
TH1F* load_tree_v_TH1F_mean(TString name_file,TString name_tree,TString name_Branch,Int_t length)
{
    //this function is used to load the tree's data into histogram,because the memory may be out of range ,so
    //it return all the histograms' mean which is also a histogram.
TFile *f = new TFile(name_file);
TTree *tree=(TTree*)f->Get(name_tree);
vector<float> x_load(length);
tree->SetBranchAddress(name_Branch,&*x_load.begin());
TH1F *h_sum=new TH1F("h","h",x_load.size(),0,x_load.size());
TH1F *h_load;
for(int i=0;i<tree->GetEntries();i++){
//for(int i=0;i<2;i++){
tree->GetEntry(i);
h_load=v2TH1F(x_load,"h");
h_sum->Add(h_sum,h_load);
delete h_load;
}
h_sum->Scale(1./(tree->GetEntries()));
f->Close();
return h_sum;

}

using namespace std;
TH1F* load_tree_v_TH1F_mean_max_trigger(TString name_file,TString name_tree,TString name_Branch,Int_t length,float trigger)
{
    //this function is used to load the tree's data into histogram,because the memory may be out of range ,so
    //it return all the histograms' mean which is also a histogram.
TFile *f = new TFile(name_file);
TTree *tree=(TTree*)f->Get(name_tree);
vector<float> x_load(length);
tree->SetBranchAddress(name_Branch,&*x_load.begin());
TH1F *h_sum=new TH1F("h","h",x_load.size(),0,x_load.size());
TH1F *h_load;
float n_added_TH1F=0;
for(int i=0;i<tree->GetEntries();i++){
//for(int i=0;i<2;i++){
tree->GetEntry(i);
h_load=v2TH1F(x_load,"h");
h_load=TH1F_plus(h_load,-h_load->GetBinContent(0));
if(h_load->GetMaximum()>=trigger){
    h_sum->Add(h_sum,h_load);
    n_added_TH1F+=1;
}
delete h_load;
}
cout<<n_added_TH1F<<endl;
h_sum->Scale(1./n_added_TH1F);
f->Close();
return h_sum;

}


int test_load(){
Int_t length;
std::vector<Double_t> x;
load("test.root",x,'E');
for(int i =0;i<x.size();i++)
{std::cout<<x[i]<<std::endl;
}
return 0;
}
template <class T>
void vector2array_2d_adjust_with_save_2d_v(vector<vector<T>> v_2d,T array_return[][120])
{
    //this function is to convert the 2d vector to 2d array ,but unfortunately,we have to
    //assign the array's size whenever we use it.this may be optimize in the furture.
    for (int i=0;i<v_2d.size();i++)
    {
        for(int j=0;j<v_2d[0].size();j++)
        {
            array_return[i][j]=v_2d[i][j];
        }
    }
}

void save_2d_v(TString file_name,std::vector<vector<int>> v_2d,TString name_branch,TString name_tree="data")
{
    //this function is to offer a model to save 2d vector,you shall copy it to the main function to save
    //more 2d vector
    TFile *f=new TFile(file_name,"recreate");
    TTree *tree=new TTree(name_tree,name_tree);
   int i_max=v_2d.size();
   int j_max=v_2d[0].size();
   int array_2d[2][120];
     vector2array_2d_adjust_with_save_2d_v(v_2d,array_2d);
//    cout<<array_2d[0][1]<<endl;
    tree->Branch(name_branch,array_2d,name_branch+"[2][3]/I");
   tree->Fill();
   tree->Write();
   f->Close();
}

void save_TCanvas(TCanvas *c_save,TString name_file)
{
    TFile *f=new TFile(name_file,"recreate");
    c_save->Write();
    f->Close();

}
