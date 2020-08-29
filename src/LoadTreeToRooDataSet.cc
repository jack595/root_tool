#include<TTree.h>
#include<TFile.h>
#include<TCanvas.h>
#include<RooDataSet.h>
#include<vector>
#include"TString.h"
#include<RooRealVar.h>
#include"LoadTreeToRooDataSet.hh"
#include"RooArgSet.h"
#include"RooPlot.h"
#include"TCanvas.h"
using namespace std;
LoadTreeToRooDataSet::LoadTreeToRooDataSet(TString name_file_input,
                                           const vector<TString> v_name_tree_input,
                                           const vector<TString> v_name_branch_input,
                                           const vector<vector<vector<Double_t>>> v2D_CutRange_input,
                                           const vector<TString> v_unit_input,
                                           const TString extra_label_for_hist)
{
    name_file=name_file_input;
    v_unit=v_unit_input;
    f=new TFile(name_file_input);
    v_name_trees=v_name_tree_input;
    v2D_CutRange=v2D_CutRange_input;
    v_name_branch=v_name_branch_input;
    for(int i=0;i<v_name_tree_input.size();i++)  //index i is for tree index,j is for branch index
    {
        v_trees.push_back((TTree*)f->Get(v_name_tree_input[i]));
        v_name_branch=v_name_branch_input;
        vector<RooRealVar> v_RooRealVar_A_tree;
        for(int j=0;j<v_name_branch.size();j++)
        {
            RooRealVar RooRealVar_branch(v_name_branch[j],v_name_branch[j]+" ( "+v_unit[j]+" )",
                                v2D_CutRange[i][j][0],
                                v2D_CutRange[i][j][1]);
            v_RooRealVar_A_tree.push_back(RooRealVar_branch);

        }
        v2D_RooRealVar.push_back(v_RooRealVar_A_tree);


        RooDataSet* data=new RooDataSet("dataset_"+v_name_tree_input[i],
                        "dataset_"+v_name_tree_input[i],
                        v_trees[i],
                        RooArgSet(v2D_RooRealVar[i][0]));
        for(int j=1;j<v2D_RooRealVar[i].size();j++)
        {
            RooDataSet* data_add=new RooDataSet("dataset_add_"+v_name_tree_input[i],
                                "dataset_add_"+v_name_tree_input[i],
                                v_trees[i],
                                RooArgSet(v2D_RooRealVar[i][j]));
            data->merge(data_add);
        }
        v_RooDataSet.push_back(data);
    }
//    cout<<v2D_RooRealVar.size()<<" "<<v2D_RooRealVar[0].size()<<endl;
//    cout<<v2D_RooRealVar[1][1].getValV()<<endl;

    CreateV2dHist(extra_label_for_hist);
}

LoadTreeToRooDataSet::LoadTreeToRooDataSet(TString name_file_input,
                                           const vector<TString> v_name_tree_input,
                                           const vector<TString> v_name_branch_input,
                                           const vector<vector<Double_t> > v2D_CutRange_input,
                                           const vector<TString> v_unit_input,
                                           const TString extra_label_for_hist)
{
    name_file=name_file_input;
    v_unit=v_unit_input;
    f=new TFile(name_file_input);
    v_name_trees=v_name_tree_input;
    for(int i=0;i<v_name_tree_input.size();i++)  //index i is for tree index,j is for branch index
    {v2D_CutRange.push_back(v2D_CutRange_input);}
    v_name_branch=v_name_branch_input;
    for(int i=0;i<v_name_tree_input.size();i++)  //index i is for tree index,j is for branch index
    {
        v_trees.push_back((TTree*)f->Get(v_name_tree_input[i]));
        v_name_branch=v_name_branch_input;
        vector<RooRealVar> v_RooRealVar_A_tree;
        for(int j=0;j<v_name_branch.size();j++)
        {
            RooRealVar RooRealVar_branch(v_name_branch[j],v_name_branch[j]+" ( "+v_unit[j]+" )",
                                v2D_CutRange[i][j][0],
                                v2D_CutRange[i][j][1]);
            v_RooRealVar_A_tree.push_back(RooRealVar_branch);

        }
        v2D_RooRealVar.push_back(v_RooRealVar_A_tree);


        RooDataSet* data=new RooDataSet("dataset_"+v_name_tree_input[i],
                        "dataset_"+v_name_tree_input[i],
                        v_trees[i],
                        RooArgSet(v2D_RooRealVar[i][0]));
        for(int j=1;j<v2D_RooRealVar[i].size();j++)
        {
            RooDataSet* data_add=new RooDataSet("dataset_add_"+v_name_tree_input[i],
                                "dataset_add_"+v_name_tree_input[i],
                                v_trees[i],
                                RooArgSet(v2D_RooRealVar[i][j]));
            data->merge(data_add);
        }
        v_RooDataSet.push_back(data);
    }
    //    cout<<v2D_RooRealVar.size()<<" "<<v2D_RooRealVar[0].size()<<endl;
    //    cout<<v2D_RooRealVar[1][1].getValV()<<endl;

        CreateV2dHist(extra_label_for_hist);
}

LoadTreeToRooDataSet::~LoadTreeToRooDataSet()
{
    f->Close();
    v2D_TH1.clear();
    v_RooDataSet.clear();
    v2D_RooRealVar.clear();

}

void LoadTreeToRooDataSet::DrawAllHist()
{
    for(int i=0;i<v_trees.size();i++)  //index i is for tree index,j is for branch index
    {
        for(int j=0;j<v_name_branch.size();j++)
        {
            TCanvas *c1=new TCanvas("c_"+name_file+"_"+(TString)v_trees[i]->GetName()+" "+v_name_branch[j],
                                    "c1",800,600);
//            RooPlot* frame=v2D_RooRealVar[i][j].frame();
//            v_RooDataSet[i]->plotOn(frame);
//            frame->DrawClone();
            v2D_TH1[i][j]->DrawClone();

        }

    }

}

void LoadTreeToRooDataSet::DrawAllHist(const vector<TString> v_draw_option)
{
    for(int i=0;i<v_trees.size();i++)  //index i is for tree index,j is for branch index
    {
        for(int j=0;j<v_name_branch.size();j++)
        {
            TCanvas *c1=new TCanvas("c_"+name_file+"_"+(TString)v_trees[i]->GetName()+" "+v_name_branch[j],
                                    "c1",800,600);
//            RooPlot* frame=v2D_RooRealVar[i][j].frame();
//            v_RooDataSet[i]->plotOn(frame);
//            frame->DrawClone();
            v2D_TH1[i][j]->DrawClone(v_draw_option[j]);

        }

    }
}

vector<vector<TH1 *> > LoadTreeToRooDataSet::CreateV2dHist(const TString extra_label)
{
    for(int i=0;i<v_trees.size();i++)  //index i is for tree index,j is for branch index
    {
        vector<TH1*> v_TH1;
        for(int j=0;j<v_name_branch.size();j++)
        {
            v_TH1.push_back(v_RooDataSet[i]->createHistogram("h_"+v_name_trees[i]+"_"+extra_label,
                            v2D_RooRealVar[i][j]));
        }
        v2D_TH1.push_back(v_TH1);

    }
    return v2D_TH1;

}

vector<vector<RooRealVar> > LoadTreeToRooDataSet::getV2D_RooRealVar() const
{
    return v2D_RooRealVar;
}

vector<RooDataSet *> LoadTreeToRooDataSet::getV_RooDataSet() const
{
    return v_RooDataSet;
}

//RooArgSet LoadTreeToRooDataSet::CreatRooArgSet()
//{
//    int len_RooArgSet=v_name_branch.size();
//    if(len_RooArgSet==1)return RooArgSet(v);

//}
