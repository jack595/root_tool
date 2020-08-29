#include "TH1D.h"
#include "TVirtualFFT.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TMath.h"
#include<TH1_tool.hh>
using namespace std;
vector<TH1 *>get_FFT(TH1 *h_input,TString name_h="h_FFT")
{
            TH1 *h_FFT=0;
            TVirtualFFT::SetTransform(0);
            int n=h_input->GetNbinsX();
            TVirtualFFT *fft=TVirtualFFT::FFT(1,&n,"R2C");
            vector<double> v_input=TH12v(h_input);

            fft->SetPoints(&*v_input.begin());
            fft->Transform();
            TH1* h_re=0;
            TH1* h_im=0;
            h_re=TH1::TransformHisto(fft,h_re,"RE "+name_h);
            h_im=TH1::TransformHisto(fft,h_im,"IM "+name_h);
            vector<TH1*> v_return={h_re,h_im};
            fft->Delete();
            v_input.clear();
            return v_return;
}


TH1 * get_FFT_backward(TH1* h_re,TH1* h_im,TString name_h="h_FFTb")
{
    int n=h_re->GetNbinsX();
    TVirtualFFT *fft_back=TVirtualFFT::FFT(1,&n,"C2R M K");
    vector<double>v_re=TH12v(h_re);
    vector<double>v_im=TH12v(h_im);
    fft_back->SetPointsComplex(&*v_re.begin(),&*v_im.begin());
    fft_back->Transform();
    TH1 *hb=0;
    hb=TH1::TransformHisto(fft_back,hb,"RE "+name_h);
    hb->Scale(1/float(n));
    fft_back->Delete();
    v_re.clear();
    v_im.clear();
    return hb;


}

TH1 *set_zero(TH1* h_FFT,double begin_set_zero,double end_set_zero,TString name_h="zero")
{
    int bin_begin=h_FFT->GetBinCenter(begin_set_zero);
    int bin_end=h_FFT->GetBinCenter(end_set_zero);

    for(int i = bin_begin;i<bin_end;i++)
    {
        h_FFT->SetBinContent(i,0);
    }
    return h_FFT;
}

TH1 *get_TH1_range(TH1* h_FFT,double begin_set_nonzero,double end_set_nonzero,TString name_h="h_range")
{
        int bin_begin=h_FFT->GetBinCenter(begin_set_nonzero);
    int bin_end=h_FFT->GetBinCenter(end_set_nonzero);
    TH1* h_return=new TH1F(h_FFT->GetTitle()+name_h,h_FFT->GetTitle(),h_FFT->GetNbinsX(),0,h_FFT->GetXaxis()->GetXmax());
    for(int i=bin_begin;i<bin_end;i++)
    {
       h_return->SetBinContent(i,h_FFT->GetBinContent(i));
    }
    return h_return;
}

TH1 *filter(TH1 * h,double begin_FFT,double end_FFT,TString name_h="range")
{
            vector<TH1*> v_old_FFT=get_FFT(h,name_h);
            vector<TH1*>v_FFT;
            v_FFT.resize(2);
            v_FFT[0]=get_TH1_range(v_old_FFT[0],begin_FFT,end_FFT,name_h+" 0");
            v_FFT[1]=get_TH1_range(v_old_FFT[1],begin_FFT,end_FFT,name_h+" 1");
            TH1 *hnew=get_FFT_backward(v_FFT[0],v_FFT[1],name_h+" b");
            v_FFT[0]->Delete();
            v_FFT[1]->Delete();
            v_old_FFT[0]->Delete();
            v_old_FFT[1]->Delete();
            v_FFT.clear();
            v_old_FFT.clear();
            return hnew;
}

TH1 *earaser(TH1 * h,double begin_FFT,double end_FFT)
{
            vector<TH1*> v_old_FFT=get_FFT(h);
            vector<TH1*>v_FFT;
            v_FFT.resize(2);
            v_FFT[0]=set_zero(v_old_FFT[0],begin_FFT,end_FFT);
            v_FFT[1]=set_zero(v_old_FFT[1],begin_FFT,end_FFT);
            TH1 *hnew=get_FFT_backward(v_FFT[0],v_FFT[1]);
            delete v_FFT[0];
            delete v_FFT[1];
            delete v_old_FFT[0];
            delete v_old_FFT[1];
            return hnew;
}
