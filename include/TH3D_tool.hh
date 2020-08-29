#pragma once
#include"TH3D.h"
#include"TCanvas.h"
#include"TH2D.h"
#include<vector>
#include"TString.h"
#include<iostream>
using namespace std;
void DrawAllProjection(TH3D* h3)
{
    vector<TString> v_name_projection={"xy","yz","xz"};
    TH2D* h2;
    for(auto name_projection:v_name_projection)
    {
        TCanvas *c1=new TCanvas("c_"+(TString)h3->GetName()+name_projection,
                                "c1",800,600);
//        cout<<name_projection<<endl;
        h2=(TH2D*)h3->Project3D(name_projection);
        h2->DrawClone("colz");
        h2->Delete();
    }
}
