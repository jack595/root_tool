#include<TH2F.h>
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

