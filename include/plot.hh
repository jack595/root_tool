#pragma once
#include<TH2D.h>
#include "TH1D.h"
#include<TTree.h>
#include<TFile.h>
#include<TCanvas.h>
#include<TF1.h>
#include<TGraph.h>
#include<TGraphErrors.h>
#include<iostream>
#include<dirent.h>
#include<TAxis.h>
#include<TLegend.h>
#include"TGraph2D.h"
#include<vector>
#include"type_transform.hh"
using namespace std;
template <class T>
T max_series(vector<vector<T>> v_series)
{
    //this function is used to find the vector_series' maximiun,which is a vector contain same type vectors.
    //this function is used to function "mutipolt_error"

    vector<T> max;
    max.reserve(v_series.size());
    for(int i=0;i<v_series.size();i++)
    {
        max.push_back(*max_element(v_series[i].begin(),v_series[i].end()));
    }
    return *max_element(max.begin(),max.end());
}
template <class T>
T min_series(vector<vector<T>> v_series)
{
    //this function is used to find the vector_series' maximiun,which is a vector contain same type vectors.

    vector<T> min;
    min.reserve(v_series.size());
    for(int i=0;i<v_series.size();i++)
    {
        min.push_back(*min_element(v_series[i].begin(),v_series[i].end()));
    }
    return *min_element(min.begin(),min.end());

}

template <class T>
vector<double> plot(std::vector<T> x,std::vector<T> y,TString fit_name="null",TString x_title="x",TString y_title="y",TString title="Graph")
{
TCanvas *c1=new TCanvas("c"+title+" "+n2str(x[0]),"c1",800,600);
//for(int i=0;i<x.size();i++){
//std::cout<<x[i]<<",";
//if(i==x.size()-1)std::cout<<endl;}
//for(int i=0;i<x.size();i++){
//std::cout<<y[i]<<",";}
TGraph *gr1=new TGraph(x.size(),&*x.begin(),&*y.begin());
vector<double> v_par(10);
if(fit_name!="null"){
TF1 *f1=new TF1("f1",fit_name,0,1300);
gr1->Fit(f1);
f1->GetParameters(&*v_par.begin());
}
//gr1->SetLineColor(2);
gr1->SetMarkerStyle(21);
gr1->SetMarkerSize(0.5);
gr1->SetLineWidth(0);
gr1->GetXaxis()->SetTitle(x_title);
gr1->GetYaxis()->SetTitle(y_title);
gr1->SetTitle(title);
gr1->DrawClone();
//TFile *f=new TFile(title+".root","recreate");
//c1->Write();
//f->Close();
//c1->SaveAs(title+".root");
gr1->Delete();
return v_par;
}
template <class T>
vector<double> plot_errorbar(std::vector<T> x,std::vector<T> y,std::vector<T> ex,std::vector<T> ey,TString fit_name="null",TString x_title="x",TString y_title="y",TString title="Graph")
{
TCanvas *c1=new TCanvas("c_"+title,"c1",800,600);
//const int n=10;
//double O2[n]={1039,116,1240,20.7,242,372,49.5,507,687,829};
//double att[n]={0.0251963,0.0024336,0.0301287,-0.000201875,0.00476683,0.00867768,0.000378589,0.011154,0.0167816,0.0197824};
//sort(O2,O2+10);
//sort(att,att+10);
//for(int i=0;i<x.size();i++){
//std::cout<<x[i]<<",";}
TGraphErrors *gr1=new TGraphErrors(x.size(),&*x.begin(),&*y.begin(),&*ex.begin(),&*ey.begin());
vector<double> v_par(10);
gr1->SetLineWidth(1);
if(fit_name!="null"){
TF1 *f1=new TF1("f1",fit_name,0,1300);
//gr1->SetLineWidth(0);
gr1->Fit(f1,"V");
f1->GetParameters(&*v_par.begin());
}
//gr1->SetLineColor(2);
gr1->SetMarkerStyle(21);
gr1->SetMarkerColor(4);
gr1->GetXaxis()->SetTitle(x_title);
gr1->GetYaxis()->SetTitle(y_title);
gr1->SetTitle(title);
gr1->Draw("AP");
c1->SaveAs(title+".root");
return v_par;
}

using namespace std;
template <class T>
void mutiplot_errorbar(std::vector<vector<T>> x_series,std::vector<vector<T>> y_series,\
                       std::vector<vector<T>> ex_series={0},std::vector<vector<T>> ey_series={0},\
                   TString fit_name="null",TString x_title="x",TString y_title="y",TString title="Graph",
                       vector<TString>v_legend={""})
{
    //this function is used to plot many error graphs in the same canvas,what is needed is a vector contain many vectors
    TCanvas *c1=new TCanvas("c1","c1",800,600);
    vector<TGraphErrors*> gr_series(x_series.size());
    vector<TF1*> f_series(x_series.size());
    T x_max,x_min,y_max,y_min;
    x_max=max_series(x_series);
    x_min=min_series(x_series);
    y_max=max_series(y_series);
    cout<<"x_max:"<<x_max<<endl<<"x_min:"<<x_min<<endl;
    y_min=min_series(y_series);
    vector<T> vx_assist={x_min,x_max};
    vector<T> vy_assist={y_min,y_max};
    vector<T> ex_assist={0,0};
    vector<T> ey_assist={0,0};
    TGraphErrors *g_assist=new TGraphErrors (2,&*vx_assist.begin(),&*vy_assist.begin(),&*ex_assist.begin(),&*ey_assist.begin());
    g_assist->Draw("AP");
    g_assist->GetXaxis()->SetTitle(x_title);
    g_assist->GetYaxis()->SetTitle(y_title);
    g_assist->SetTitle(title);
//        g_assist->SetMarkerStyle(21);
//        g_assist->SetMarkerColor(5);
//        g_assist->SetLineWidth(1);
//     TLegend *legend1=new TLegend(0.1533281,0.186514,0.3553009,0.478903,NULL,"brNDC");
     TLegend *legend1=new TLegend();
     legend1->SetTextFont(62);
     legend1->SetTextSize(0.03);
    for(int i=0;i<x_series.size();i++)
    {
        gr_series[i]=new TGraphErrors(x_series[i].size(),&*x_series[i].begin(),&*y_series[i].begin(),&*ex_series[i].begin(),&*ey_series[i].begin());
        if(fit_name!="null")
        {
            f_series[i]=new TF1("f1",fit_name,0,2000);
            gr_series[i]->Fit(f_series[i],"+");
            f_series[i]->SetLineColor(i+5);
        }
        gr_series[i]->SetMarkerStyle(21);
        gr_series[i]->SetMarkerColor(i+1);
        gr_series[i]->SetLineWidth(1);
        gr_series[i]->SetLineColor(i+1);
        if(title!="Graph")legend1->AddEntry(gr_series[i],v_legend[i],"lp");
        if(i==0){gr_series[i]->Draw("psame");
            //attention!!!:when draw a lot of graphs in the same canvas,should use Draw("psame"),otherwise,there are a lot of problem.
            //if you want to plot the line ,you should use Draw("lpsame"),otherwise it will not show the line.
        }
        else{
            gr_series[i]->Draw("psame");
    }

    }
    legend1->Draw();

}

void test_plot()
{
    std::vector<Double_t> x;
for(int i=310;i<430;i+=10)x.push_back(i);
	std::vector<Double_t> y{55.62,89.04,137.44,209.71,317.91,482.15,726.78,1105.6,1664.75,2490.30,3467.75,5303.04};
    std::vector<Double_t> ex(x.size(),5);
    std::vector<Double_t> ey{17.18,25.65,39.82,55.15,75.06,103.54,\
        140.66,209.79,154.66,342.97,14.84,48.42};

    plot_errorbar(x,y,ex,ey);
}


template <class T>
vector<double> plot_3D(std::vector<T> x,std::vector<T> y,std::vector<T> z,TString x_title="x",TString y_title="y",TString z_title="z",TString title="Graph")
{
TCanvas *c1=new TCanvas("c_3D_"+title,"c1",800,600);
TGraph2D *g = new TGraph2D(x.size(), &*x.begin(), &*y.begin(), &*z.begin());
g->SetTitle(title+";"+x_title+";"+y_title+";"+z_title);
//g->GetXaxis()->SetTitle(x_title);
//g->GetYaxis()->SetTitle(y_title);
//g->GetZaxis()->SetTitle(z_title);
g->DrawClone("P0");
g->Delete();
}

//This function aims to plot the input vector<vector<TH1D*>> into pdf,which means the first index is the line index,and the second index is the comlumm index
//  TH1D[0][0] TH1D[0][1] TH1D[0][2]
//  TH1D[1][0] TH1D[1][1] TH1D[1][2] 
//  ..........  ......... ..........
void plot_into_pdf(vector<vector<TH1D*>> v2D_TH1D, const TString name_savePDF="figout.pdf")
{
    cout<< "Plotting into PDF......" <<endl;
    //Initial the TCanvas and get the relative pars.
    int n_comlum=v2D_TH1D[0].size();
    int n_line=v2D_TH1D.size();
    cout<< "n_comlum:   " <<n_comlum<< "    n_line:   "<<n_line<<endl;
    // TCanvas* c = new TCanvas("c", "c",800, 600);
    // v2D_TH1D[1][0]->DrawCopy();
    // TCanvas* c1 = new TCanvas("c1", "c1",800, 600);
    // v2D_TH1D[1][1]->DrawCopy();
    
    TCanvas* outc = new TCanvas("outc", "outc",800 * n_comlum, 600);
    outc->Divide(n_comlum,1);
    outc->Print(name_savePDF+"[");

    //Loop to Draw the TH1 into the pdf
    for (int i = 0; i < n_line  ; i++)
    {
        for (int j = 0; j < v2D_TH1D[i].size(); j++)
        {
            outc->cd(j+1);
            // v2D_TH1D[i][j]->GetYaxis()->SetLimits( v2D_TH1D[i][j]->GetMinimum(), v2D_TH1D[i][j]->GetMaximum() );
            // cout<<"check Min and Max:   "<<v2D_TH1D[i][j]->GetMinimumBin()<< "   "<< v2D_TH1D[i][j]->GetMaximum()<<endl; 
            v2D_TH1D[i][j]->DrawCopy();
        }
        
        cout<< i <<endl;
        outc->Print(name_savePDF);
        outc->Clear();
        outc->Divide(n_comlum,1);
        
    }
    
    //End the process of outputting to pdf
    outc->Print(name_savePDF+"]");
}

//This function is to reform the 1D vector of TH1Ds into 2D vector, then input to the function "plot_into_pdf(vector<vector<TH1D*>>)"
void plot_into_pdf( vector<TH1D*> v1D_TH1D, const TString name_savePDF="figout.pdf", const int n_comlum_Format=4 )
{
    //Reformming v1D_TH1D
    vector<vector<TH1D*>> v2D_TH1D( v1D_TH1D.size()/n_comlum_Format+1 );
    for (int i = 0; i < v1D_TH1D.size() ; i++)
    {
        v2D_TH1D[ i/n_comlum_Format ].push_back( v1D_TH1D[i] );   
    }
    plot_into_pdf( v2D_TH1D, name_savePDF );
          
}

void plot_into_pdf(TH1D* h_toPDF, const TString name_savePDF="figout.pdf")
{
    vector<vector<TH1D*>> v2D_TH1D(1);
    v2D_TH1D[0].push_back(h_toPDF);
    plot_into_pdf(v2D_TH1D,name_savePDF);
}

void plot_into_pdf(vector<vector<TH2D*>> v2D_h2D_toPDF, const TString name_savePDF="figout.pdf")
{
    cout<< "Plotting into PDF......" <<endl;
    //Initial the TCanvas and get the relative pars.
    int n_comlum=v2D_h2D_toPDF[0].size();
    int n_line=v2D_h2D_toPDF.size();
    cout<< "n_comlum:   " <<n_comlum<< "    n_line:   "<<n_line<<endl;

    TCanvas* outc = new TCanvas("outc", "outc",800 * n_comlum, 600);
    outc->Divide(n_comlum,1);
    outc->Print(name_savePDF+"[");

    //Loop to Draw the TH1 into the pdf
    for (int i = 0; i < n_line  ; i++)
    {
        for (int j = 0; j < v2D_h2D_toPDF[i].size(); j++)
        {
            outc->cd(j+1);
            // v2D_TH1D[i][j]->GetYaxis()->SetLimits( v2D_TH1D[i][j]->GetMinimum(), v2D_TH1D[i][j]->GetMaximum() );
            // cout<<"check Min and Max:   "<<v2D_TH1D[i][j]->GetMinimumBin()<< "   "<< v2D_TH1D[i][j]->GetMaximum()<<endl; 
            v2D_h2D_toPDF[i][j]->DrawCopy("colz");
        }
        
        cout<< i <<endl;
        outc->Print(name_savePDF);
        outc->Clear();
        outc->Divide(n_comlum,1);
        
    }
    
    //End the process of outputting to pdf
    outc->Print(name_savePDF+"]");    
}

void plot_into_pdf(TH2D* h_toPDF, const TString name_savePDF="figout.pdf")
{
    vector<vector<TH2D*>> v2D_TH2D(1);
    v2D_TH2D[0].push_back(h_toPDF);
    plot_into_pdf(v2D_TH2D,name_savePDF);
}

//This function is to reform the 1D vector of TH1Ds into 2D vector, then input to the function "plot_into_pdf(vector<vector<TH1D*>>)"
void plot_into_pdf( vector<TH2D*> v1D_TH2D, const TString name_savePDF="figout.pdf", const int n_comlum_Format=4 )
{
    //Reformming v1D_TH1D
    vector<vector<TH2D*>> v2D_TH2D( v1D_TH2D.size()/n_comlum_Format+1 );
    for (int i = 0; i < v1D_TH2D.size() ; i++)
    {
        v2D_TH2D[ i/n_comlum_Format ].push_back( v1D_TH2D[i] );   
    }
    plot_into_pdf( v2D_TH2D, name_savePDF );
          
}

void test_plot_into_pdf()
{
    const int n_line_to_pdf=2;
    vector<vector<TH1D*>> v2D_TH1D_toPDF(n_line_to_pdf);
    TH1D* h = new TH1D("h","h",100,0,100);
    for (int i = 0; i < 1000; i++)
    {
        h->Fill(i);
    }
    for (int j = 0; j < 3; j++)
    {
        v2D_TH1D_toPDF[0].push_back((TH1D*) h->Clone( "wd" ));
        // v2D_TH1D_toPDF[0].push_back((TH1D*) h->Clone(  (TString)n2str(j)+"wd" )));
        v2D_TH1D_toPDF[1].push_back(h);
    }
    v2D_TH1D_toPDF.resize(n_line_to_pdf);
    plot_into_pdf(v2D_TH1D_toPDF);

}
