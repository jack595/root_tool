/*
// this function is used to load the data from DT5751,whose organization is a line contain a vector,so using this
 //function you should change the record_length which is a vector's size to match the setting of DT5751.
void txt_tree()
{
   ifstream f0("ch0.txt");
   TFile f4("event.root","recreate");
   const Int_t record_length =50001;
   Float_t ch0[record_length];
//   Float_t Baseline,MinVal;
//   Int_t MinID;
   TTree* tree = new TTree("data","data");
   tree->Branch("ch0",ch0,"ch0[50001]/F");
//   tree->Branch("Baseline",Baseline,"Baseline/F");
//   tree->Branch("MinID",MinID,"MinID/I");
//   tree->Branch("MinVal",MinVal,"MinVal/F");

   while(f0.eof()!=1)
    {
//      TH1F *h0=new TH1F(1000,0,1000);
//      Float_t a=1000;
      for(int i=0; i<record_length;i++)
        {
          f0>>ch0[i];
        }
      tree->Fill();
    }
   tree->Write();
   f0.close();
}
*/

//TH1F* multi_channel_txt2TH1F()
//{
//    TCanvas *c = new TCanvas("c", "c", 800, 600);

//    ifstream filename;
//    filename.open("400V.Spe");
//    Double_t count;
//    string str;
//    TH1F* h=new TH1F("h"," 400V energy Spectrum",8192,0,8192);
//    int i=0,N=0;

//    while(filename.good() )
//    {
//        if(i<12){getline(filename,str);}
//        if(i>11&&i<8204)
//        {
//            getline(filename,str);
//            count=TString(str).Atof();
//            h->SetBinContent(i,count*1.349-3.129);
//            N=N+count;
//        }
//        if(i>8203){getline(filename,str);}
//        i++;
//    }
//    return h;
//}
