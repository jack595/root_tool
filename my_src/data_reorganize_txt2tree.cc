#pragma once
#include<TTree.h>
#include<TFile.h>
#include<string>
#include<iostream>
#include<dirent.h>
#include<string>
#include<stdio.h>
#include<fstream>


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
//   ifstream f0("data_output"+j_str+".txt");
   //ifstream f0("data_output1.txt");
//   const Int_t record_length =50001;
//   Float_t ch0[record_length];
//   std::vector<Float_t> x;
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

