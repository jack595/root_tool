#pragma once
#include<TTree.h>
#include<TFile.h>
#include<string>
#include<iostream>
#include<dirent.h>
#include<string>
#include<stdio.h>
#include<fstream>
#include<TString.h>


void data_reorganize_txt2tree()
{
	TString j_str;
     	TFile f4("data_output.root","recreate");
   TTree* tree = new TTree("data","data");
	 Int_t n;
std::cout<<"how many file do you want to put in?"<<std::endl;
   std::cin>>n;//how many file to open
  Float_t *x_tmp=new Float_t[n];
  std::fstream *f0=new std::fstream[n];
   for (Int_t j=0;j<n;j++){
j_str=TString::Itoa(j+1,10);//the second parameter of Itoa means what the system is,for 
			//example, 2 means binary system.
std::cout<<"data_output"+j_str+".txt"<<std::endl;
    f0[j].open("data_output"+j_str+".txt",std::ios::in);
   tree->Branch("x"+j_str,&x_tmp[j],"F");
   }

   while(f0[0].eof()!=1)
    {

   for (Int_t j=0;j<n;j++){
	f0[j]>>x_tmp[j];
      std::cout<<x_tmp[j]<<' ';
   }

      std::cout<<std::endl;
if(f0[0].eof()!=1){	
      tree->Fill();
    }

    }
   for (Int_t j=0;j<n;j++){
   f0[j].close();} 


   tree->Write();
f4.Close();
delete [] f0;
delete [] x_tmp;
}

using namespace std;
void txt2tree_column2leaf(TString name_input_file,TString name_output_file,TString name_tree,vector<TString> v_name_leaves)
{
    //this function is used to load the data from txt into TTree.txt's data is organize by column,which means a column contain a vector
    //here we transform a vector into a leaf.
     ifstream f0(name_input_file);
   TFile f4(name_output_file,"recreate");
    vector<float> v_element_load;
    v_element_load.reserve(v_name_leaves.size());
   TTree* tree = new TTree(name_tree,name_tree);
   for(int i=0;i<v_name_leaves.size();i++)
   {
   tree->Branch(v_name_leaves[i],&v_element_load[i],"F");
   }

   while(f0.eof()!=1)
    {
      for(int i =0;i<v_name_leaves.size();i++)
      {
          f0>>v_element_load[i];
      }
      tree->Fill();
    }
   tree->Write();
   f0.close();
}

