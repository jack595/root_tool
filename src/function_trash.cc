
//TH1F *turn_bins(TH1F *h,int bins_new,TString name_h_new)
//{
//    TH1F *hnew = new TH1F(name_h_new,"h_new",bins_new,h->GetXaxis()->GetXmin(),h->GetXaxis()->GetXmax());
//    for(int i=h->GetXaxis()->GetXmin();i<h->GetXaxis()->GetXmax();i++)
//    {
//        hnew->Fill(i,h->GetBinContent(i));
//    }
//    return hnew;
//}

//int find_boom_up(TH1F *h,float boom_criterion,float step,int start_bin)
//{
//    TH1F *hnew = (TH1F*)h->Clone("hnew");
//    hnew->Smooth(50);
//    float slop_temp;
//    float boom_criterion_shrink=boom_criterion/2.;
//    for(int i=start_bin;i<hnew->GetNbinsX()-1;i++)
//    {
//       slop_temp=hnew->GetBinContent(int(step)+i)-hnew->GetBinContent(i);
//        if(slop_temp>=boom_criterion)
//        {
//            while (boom_criterion_shrink<boom_criterion/500.)
//            {
//                slop_temp=hnew->GetBinContent(int(step)+i)-hnew->GetBinContent(i);
//                if(slop_temp<=boom_criterion_shrink) boom_criterion_shrink=boom_criterion_shrink/2.;
//                else{
//                    i++;
//                }

//            }
//            return i;
//        }
//    }
//    return 0;
//}


//            TH1F *h_diff=TH1F_diff(h,"h_diff"+v_voltage_str[j]+v_loc_str[i]);
//            h_diff->Scale(100);
//            h->Scale(1/500.);
//            TH1F_plus(h,0.05);
//            h_diff->Smooth(10);
//            TF1 *fit_h_diff=new TF1("f"+v_voltage_str[j]+"V_268ppm_"+v_loc_str[i]+"cm","gaus",h_diff->GetMaximumBin()-10000,h_diff->GetMaximumBin()-2000);
//            h_diff->Fit(fit_h_diff,"RN");
//            double par[3];
//            fit_h_diff->GetParameters(par);
//            TF1 *fit_h_diff_again=new TF1("f"+v_voltage_str[j]+"V_268ppm_"+v_loc_str[i]+"cm_again","gaus",par[1]-4*par[2],par[1]+4*par[2]);
//            fit_h_diff_again->SetParameters(par);
//            h_diff->Fit(fit_h_diff_again,"R");
//            fit_h_diff_again->SetParameters(par);
//            cout<<hnew->GetXaxis()->GetBinCenter(2000)<<endl;
//            cout<<v_loc_str[i]<<" "<<v_voltage_str[j]<<fit_h_diff_again->GetParameter(1)-fit_h_diff_again->GetParameter(2)*3<<endl;
//            v_start.push_back(fit_h_diff_again->GetParameter(1));
//            vector<float> v_max_2nd=Max_subbin(h_diff,h_diff->GetMaximumBin()-10000,h_diff->GetMaximumBin()-2000);
//            v_max.push_back(v_max_2nd[0]);
//            cout<<v_loc_str[i]<<" "<<v_max_2nd[0]<<endl;

//        TCanvas *c1=new TCanvas("c","v_gaus",800,600);
//       TGraph* g1=new TGraph(v_x.size(),&*v_x.begin(),&*v_start.begin());
//       TGraph* g2=new TGraph(v_x.size(),&*v_x.begin(),&*v_max.begin());
//       g1->SetMarkerColor(2);

//       g2->SetMarkerColor(1);
//       g1->Draw();
//        TCanvas *c2=new TCanvas("c1","v_max",800,600);
//       g2->Draw();


//#include<TApplication.h>
//#include<TCanvas.h>
//#include<TH1F.h>
//#include<TFile.h>
//#include<TH1_tool.hh>
//#include<TH1_tool.hh>
//#include<vec_op.hh>
//#include<plot.hh>
//using namespace std;
//vector<float> find_boom_start(vector<TString>v_loc_str,vector<TString>v_voltage_str,float trigger)
//{

//     vector<float> v_start;
//        for(int i =0;i<v_loc_str.size();i++)
//     {
//        TCanvas *c1=new TCanvas("c"+v_voltage_str[i]+"cm","c1",800,600);
//          for(int j=0;j<v_voltage_str.size();j++)
////     for(int j=0;j<1;j++)
//         {
//            TFile *f = new TFile("./"+v_loc_str[i]+"cm/"+v_voltage_str[j]+\
//                                 "V_PMT_268ppm/anode_mean_cut.root");
//            TH1F *h=(TH1F*)f->Get("h_anode");
//            TH1F *hnew=(TH1F*)h->Rebin(5,"h"+v_voltage_str[j]+"V_268ppm_"+v_loc_str[i]+"cm");
//            int bin_boom=find_boom_up(hnew,1.,400,1500);
//           v_start.push_back(bin_boom);
//           if(j+1==5)
//            {
//            hnew->SetLineColor(38);
//            }
//            else{
//            hnew->SetLineColor(j+1);
//            }
//            hnew->SetTitle("signal shape_"+v_voltage_str[j]+"V_268ppm_"+v_loc_str[i]+"cm");
//            if (j==0)hnew->DrawCopy();
//            else hnew->DrawCopy("same");
//            delete h;
//            delete hnew;
//        }
//        c1->BuildLegend();
//     }
//        return v_start;
//}
//int main(int argc, char** arg)
//{
//     TApplication app("ROOT Application", &argc, arg);
//     vector<TString> v_loc_str={"4.3","5.3","6.3"};
//     vector<TString> v_voltage_str={"2500","3000","4000","5000","6000"};
//     vector<float> v_start=find_boom_start(v_loc_str,v_voltage_str,1);
//        vector<float>v_x=vec_op::range(float(0.),float(v_start.size()));        plot(v_x,v_start,"null","x","time[ns]","find_start_bin");



//    app.Run();
//    return 0;
//}

//vector<TH1 *>get_FFT_backup(TH1 *h_input)
//{
//            TH1 *h_FFT=0;
//            TVirtualFFT::SetTransform(0);
//            h_FFT=h_input->FFT(h_FFT,"MAG");
//            h_FFT=h_input->FFT(h_FFT,"PH");
//            int n=h_input->GetNbinsX();
////            TVirtualFFT *fft=TVirtualFFT::FFT(1,&n,"R2C");

//            TVirtualFFT *fft = TVirtualFFT::GetCurrentTransform();
//            vector<double> re_full(n);
//            vector<double> im_full(n);

//            fft->GetPointsComplex(&*re_full.begin(),&*im_full.begin());
//           TH1 *h_re=v2TH1(re_full,"re_full");
//           TH1 *h_im=v2TH1(im_full,"im_full");
//           vector<TH1*> v_return={h_re,h_im};
//            return v_return;
//}

                    /*
                if (x_index==71)
                {
                    TFile* file_tset=new TFile("test_extremum.root","recreate");
                    h_wave->Write();
                    file_tset->Close();
                }
*/


//            vector<float>N_max=v_max*float(N0/20./45.);
//            TGraph *g=new TGraph(L_d_f.size(),&*L_d_f.begin(),&*v_max.begin());
//            TF1 *f1=new TF1("f1","expo",0,20);
//            g->Fit(f1,"RN");
//            g->SetLineWidth(0);
//            g->SetMarkerStyle(21);
//            if(j+1==5)
//            {
//                g->SetMarkerColor(38);
//                f1->SetLineColor(38);
//            }
//            else{
//                g->SetMarkerColor(j+1);
//                f1->SetLineColor(j+1);
//            }
//            f1->SetTitle("fitting_curve_"+voltage[j]+"V");
//            g->SetTitle("experiment data_"+voltage[j]+"V");
//            v_att.push_back(f1->GetParameter(1));

////            if(j==0)
////            {
////                f1->DrawCopy();
////            }
////            else f1->DrawCopy("plsame");
////                g->GetXaxis()->SetTitle("loction[cm]");
////                g->GetYaxis()->SetTitle("number of electrons");
////            g->DrawClone("psame");

//            //      plot(L_d_f,N_max,"expo","loction[cm]","number of electrons","attenuation efficiency_"+voltage[j]+"V");
//            v_max.clear();
//            g->Delete();
//            f1->Delete();
//            c1->BuildLegend();
//        }

        //      c1->SetTitle(O2_s[i]+"ppm");
//              c1->BuildLegend();
//              vector<float> v_voltage_f=v_str2v_float(voltage);
//              v_att=v_att*float(-1.);
//              plot(v_voltage_f,v_att,"null","voltage[V]","adsorption coefficient[cm^{-1}]");


                //          for(int k=0;k<1;k++)


//                TFile *f = new TFile("./"+O2_s[i]+"ppm/"+voltage[j]+\
//                                              "V/"+L_d_s[k]+"cm/energy.root");
//                TF1 *f2 = (TF1*)f->Get("f2");

//                if(k+1==5)
//                {
//                    f2->SetLineColor(38);
//                }
//                else{
//                    f2->SetLineColor(k+1);
//                }
////                f2->SetTitle(voltage[j]+"V_"+L_d_s[k]+"cm");
////                            if(k==0)f2->DrawCopy();
////                            else f2->DrawCopy("same");
//                v_max.push_back(f2->GetParameter(1));
//                f2->Delete();
