void plot(std::vector<Double_t> x,std::vector<Double_t> y,TString fit_name="null",TString x_title="x",TString y_title="y",TString title="Graph")
{
TCanvas *c1=new TCanvas("c1","c1",800,600);
//const int n=10;
//double O2[n]={1039,116,1240,20.7,242,372,49.5,507,687,829};
//double att[n]={0.0251963,0.0024336,0.0301287,-0.000201875,0.00476683,0.00867768,0.000378589,0.011154,0.0167816,0.0197824};
//sort(O2,O2+10);
//sort(att,att+10);
for(int i=0;i<x.size();i++){
std::cout<<x[i]<<",";}
TGraph *gr1=new TGraph(x.size(),&*x.begin(),&*y.begin());
if(fit_name!="null"){
TF1 *f1=new TF1("f1",fit_name,0,1300);
gr1->Fit(f1);}
//gr1->SetLineColor(2);
gr1->SetMarkerStyle(21);
gr1->SetLineWidth(0);
gr1->GetXaxis()->SetTitle(x_title);
gr1->GetYaxis()->SetTitle(y_title);
gr1->SetTitle(title);
gr1->Draw();
}
void test_plot()
{
	std::vector<Double_t> x{1,2,3};
	std::vector<Double_t> y{4,5,6};
	plot(x,y,"expo");



}
