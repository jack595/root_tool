#include"TFile.h"
#include"TTree.h"

class ReadTree
{
public:
    ReadTree(std::string filename,std::string treename,std::string branchname)
    {
        file=new TFile(filename.data());
        tree=(TTree*)file->Get(treename.data());
        tree->SetBranchAddress(branchname.data(),&x);
        Size=tree->GetEntries();
    }
    int size(){return Size;}
    double operator[](int n)
    {
        tree->GetEntry(n);
        return x;
    }
    ~ReadTree(){file->Close();}
private:
    TFile* file;
    TTree* tree;
    double x;
    int Size;
};
