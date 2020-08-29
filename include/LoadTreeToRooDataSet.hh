#pragma once
#include<TTree.h>
#include<RooRealVar.h>
#include<TH1.h>
#include<vector>
#include"TFile.h"
using namespace std;
class LoadTreeToRooDataSet
{

public:
    LoadTreeToRooDataSet(TString name_file_input,
                         const vector<TString> v_name_tree_input,
                         const vector<TString> v_name_branch_input,
                         const vector<vector<vector<Double_t> > > v2D_CutRange_input,
                         const vector<TString> v_unit_input,
                         const TString extra_label_for_hist);
    LoadTreeToRooDataSet(TString name_file_input,
                         const vector<TString> v_name_tree_input,
                         const vector<TString> v_name_branch_input,
                         const vector<vector<Double_t> > v2D_CutRange_input,
                         const vector<TString> v_unit_input,
                         const TString extra_label_for_hist);
    ~LoadTreeToRooDataSet();
    void DrawAllHist();
    void DrawAllHist(const vector<TString> v_draw_option);
    vector<vector<TH1 *> > CreateV2dHist(const TString extra_label);
    vector<vector<RooRealVar> > getV2D_RooRealVar() const;
    vector<RooDataSet *> getV_RooDataSet() const;
public:
    TString name_file;
    vector<TString> v_unit;
    TFile* f;
    vector<TString> v_name_trees;
    vector<vector<vector<Double_t> > > v2D_CutRange;
    vector<TString> v_name_branch;
    vector<TTree*> v_trees;
    vector<vector<RooRealVar>>v2D_RooRealVar;
    vector<RooDataSet*>v_RooDataSet ;
    vector<vector<TH1*>>v2D_TH1;
};
