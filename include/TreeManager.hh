#pragma once
#include<TTree.h>
#include<TFile.h>
#include<string>
#include<iostream>
#include<dirent.h>
#include<string>
#include<stdio.h>
typedef std::vector<std::string> name_list;
typedef std::vector<std::vector<TTree*>> Trees_list;
typedef std::vector<TTree*> Trees;

class TreeManager
{
public:
    ~TreeManager();
    TreeManager(name_list &treename_list,const char* path="../");
    TreeManager(const char *file_name ,name_list &treename_list,name_list title=name_list(),Option_t * option = "read",const char* path="");


    int GetFileNumber();
    Trees_list* GetTreesList();
    Trees* GetTrees(const char* treename);
    name_list* GetTreeNameList();
    name_list* GetTreeTitleList();
    int GetSubscriptOfTree(const char* name);
    bool surffix( char* filePath);

    //还没写完的
    void SetBranch(const char *Treename,name_list &branchname_list,name_list &type_list);

    template<class T>
    void FillBranch(const char *Treename,name_list &branchname_list,std::vector<T> &data);
    template<class T>
    void FillBranch(const char* vector,const char *Treename,name_list &branchname_list,std::vector<std::vector<T>> &data);

    template<class T>
    T ReadBranch(const char* Treename,const char* Branchname,long entry,int Nfile=0);
    template<class T>
    std::vector<T> ReadBranch(const char* vector,const char* Treename,const char* Branchname,long entry,int lenth,int Nfile=0);
    TObjArray* GetBranch(const char* Treename);

    template<class T>
    void Transpose(std::vector<std::vector<T>> &data);

    void CloseFile();
private:
    TFile** file;
    Trees_list Tree_list;//t[file][tree]
    int FileNumber;
    name_list TreeName_list;
    name_list TreeTitle_list;
    bool create;
};



//********************************************************************************************
template<class T>
void TreeManager::FillBranch(const char *Treename,name_list &branchname_list,std::vector<T> &data)
{
    int Ntree=GetSubscriptOfTree(Treename);
    int branchnumber=branchname_list.size();
    T* data_address=new T[branchnumber];
    for(int Nbranch=0;Nbranch<branchnumber;Nbranch++)
    {
        Tree_list[0][Ntree]->SetBranchAddress(branchname_list[Nbranch].data(),&data_address[Nbranch]);
        data_address[Nbranch]=data[Nbranch];
    }
    Tree_list[0][Ntree]->Fill();
    delete [] data_address;
}

template<class T>
void TreeManager::FillBranch(const char* vector,const char *Treename,name_list &branchname_list,std::vector<std::vector<T>> &data)
{
    int lenth=data.size();
    for(int i=0;i<lenth;i++)
    {
        FillBranch(Treename,branchname_list,data[i]);
    }
}

template<class T>
T TreeManager::ReadBranch(const char* Treename,const char* Branchname,long entry,int Nfile)
{
    int Ntree=GetSubscriptOfTree(Treename);
    T data_adress;
    long entry_max=Tree_list[Nfile][Ntree]->GetEntries();
    if(entry_max<=entry)
        std::cout<<"TreeManager::ReadBranch error: Invalid leaft"<<std::endl;
    else
    {
        Tree_list[Nfile][Ntree]->SetBranchAddress(Branchname,&data_adress);
        Tree_list[Nfile][Ntree]->GetEntry(entry);
        Tree_list[Nfile][Ntree]->ResetBranchAddress(Tree_list[Nfile][Ntree]->GetBranch(Branchname));
    }
    return data_adress;
}

template<class T>
std::vector<T> TreeManager::ReadBranch(const char* vector,const char* Treename,const char* Branchname,long entry,int lenth,int Nfile)
{
    std::vector<T> data;
    for(;lenth>0;entry++,lenth--)
    {
        data.push_back(ReadBranch<T>(Treename,Branchname,entry,Nfile));
    }
    return data;
}

template<class T>
void TreeManager::Transpose(std::vector<std::vector<T>> &data)
{
    std::vector<std::vector<T>> a=data;
    data.clear();
    for(int i=0;i<a[0].size();i++)
    {
        std::vector<T> c;
        for(int j=0;j<a.size();j++)
        {
            c.push_back(a[j][i]);
        }
        data.push_back(c);
    }
}
