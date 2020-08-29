//save_file()is used to save 1D data,and generate a tree named "data",
//usage:save_file(saved_name,1D data,1D data's length(string))
//
//load()is used to load the 1D data saved by save_file()
//usage:load(loaded_file's name,1D vector used to get the data,name_of_branch)
void save(TString file_name,std::vector<Double_t> x,TString name_branch)
{
TFile *f =new TFile(file_name,"recreate");
TTree* tree = new TTree("data","data");
//Int_t length_int=(Int_t)length.Atoi();
Double_t x_save;
Int_t length_int=x.size();
tree->Branch(name_branch,&x_save,name_branch+"/D");
for(int i=0;i<length_int;i++){
	x_save=x[i];
	tree->Fill();}
tree->Write();
f->Close();

}
void test_save()
{
//Double_t x[3]={1,2,3};
	std::vector<Double_t> x{1,2,3};
save("test.root",x,"E");

}

void load(TString name_file,std::vector<Double_t> &x,TString name_Branch)
{
TFile *f = new TFile(name_file);
TTree *tree=(TTree*)f->Get("data");
Double_t x_load;
tree->SetBranchAddress(name_Branch,&x_load);
x.reserve(tree->GetEntries());
for(int i=0;i<tree->GetEntries();i++){
tree->GetEntry(i);
x.push_back(x_load);
cout<<x_load<<endl;
}
f->Close();
}

int test_load(){
Int_t length;
std::vector<Double_t> x;
load("test.root",x,'E');
for(int i =0;i<x.size();i++)
{cout<<x[i]<<endl;
}
return 0;
}
