#pragma once
#include "TH2F.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TString.h"
#include <vector>
using namespace std;
void fillbinx(TH2F *h_input,float xbin,int weight=1)
{
   for(int i=h_input->GetYaxis()->GetXmin();i<h_input->GetYaxis()->GetXmax();i++)
   {
       h_input->Fill(xbin,i,weight);
   }
}

void fillbiny(TH2F *h_input,float ybin,int weight=1)
{
   for(int i=h_input->GetXaxis()->GetXmin();i<h_input->GetXaxis()->GetXmax();i++)
   {
       h_input->Fill(i,ybin,weight);
   }
}
TH1D* GetTH2DProfile( TH2D* h2D )
{
    TProfile* profile_h2D = h2D->ProfileX();
    TH1D* h_out = new TH1D( (TString)h2D->GetTitle()+"_h_profile",(TString) h2D->GetTitle()+"_h_profile",
    h2D->GetNbinsX() , h2D->GetXaxis()->GetXmin(), h2D->GetXaxis()->GetXmax());
    for (int i = 0; i < h2D->GetNbinsX() ; i++)
    {
        h_out->SetBinContent( i, profile_h2D->GetBinContent(i) );
    }
    return h_out;
}

TH1D* GetTH2DMaxProfile( TH2D* h2D )
{
    TH1D* h_out = new TH1D( (TString)h2D->GetTitle()+"_h_profile",(TString) h2D->GetTitle()+"_h_profile",
    h2D->GetNbinsX() , h2D->GetXaxis()->GetXmin(), h2D->GetXaxis()->GetXmax());
    vector<TH1D*> projh;
    TString name;
    for (int i = 0; i < h2D->GetNbinsX(); i++) {
        name = "projyh_";
        name += i;
        projh.push_back( h2D->ProjectionY(name, i + 1, i + 1, "") );
        projh[i]->Smooth(3);
        h_out->SetBinContent(i + 1, projh[i]->GetBinCenter(projh[i]->GetMaximumBin()));
    }
    return h_out;
}
