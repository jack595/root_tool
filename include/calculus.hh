#include<TH1F.h>
#include<TF1.h>
#include<TString.h>
#include<TCanvas.h>
TH1F *get_2diff_TH1F(TF1 *f,TString h_name,int n_bin,float h_min,float h_max)
{
    TH1F *h_2diff=new TH1F(h_name,"h_diff",n_bin,h_min,h_max);
    for (int i=0;i<n_bin;i++)
    {
        h_2diff->SetBinContent(i,f->Derivative2(i));

    }
//        TCanvas *c1=new TCanvas("c"+h_name,"c1",800,600);
//        h_2diff->DrawCopy();

    return h_2diff;
}
