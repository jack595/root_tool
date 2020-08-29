#include"TreeManager.hh"

TreeManager::~TreeManager()
{
    for (int i=0;i<FileNumber;i++)
        delete file[i];
    delete [] file;
}

TreeManager::TreeManager(const char *file_name ,name_list &treename_list,name_list title,Option_t * option,const char* path)
:TreeName_list(treename_list),TreeTitle_list(title)
{
    FileNumber=1;
    file=new TFile* ;
    int treenumber=TreeName_list.size();
    std::string s=std::string(path)+std::string(file_name);
    const char* fullpath=s.data();
    Tree_list.push_back(Trees());
    bool flag=true;
    if(std::string(option).compare("read")==0)
    {
        file[0]=new TFile(fullpath,"read");
        for(int Ntree=0;Ntree<treenumber;Ntree++)
        {
            TTree*t=(TTree*)file[0]->Get(TreeName_list[Ntree].data());
            Tree_list[0].push_back(t);
            TreeTitle_list.push_back(std::string(t->GetTitle()));
        }
        create=false;
        flag=false;
    }
    if(std::string(option).compare("write")==0)
    {
        file[0]=new TFile(fullpath,"recreate");
        for(int Ntree=0;Ntree<treenumber;Ntree++)
        {
            Tree_list[0].push_back(new TTree(TreeName_list[Ntree].data(),title[Ntree].data()));
        }
        create=true;
        flag=false;
    }
    if(flag)
        std::cout<<"TreeManager::TreeManager error: not found option"<<std::endl;
}
void TreeManager::CloseFile()
{
    file[0]->Write();
    file[0]->Close();
}


TreeManager::TreeManager(name_list &treename_list,const char* path)
:TreeName_list(treename_list)
{
    //FileNumber=FileNumber1;
    int TreeNumber=TreeName_list.size();


    DIR *directory_pointer;
    struct dirent *entry;
    std::vector<char*> FileName;
    if((directory_pointer=opendir(path))==NULL)
    {
        printf("Error open\n");
    }
    else
    {
        while((entry=readdir(directory_pointer))!=NULL)
        {
            char *p=entry->d_name;
            if(entry->d_name[0]=='.') continue;
            if(surffix(&(entry->d_name[0])))
            FileName.push_back(p);
        }
    }

    FileNumber=FileName.size();
    file=new TFile*[FileNumber];
    for(int i=0;i<FileNumber;i++)
    {
        std::string Path(path);
        std::string name=Path+std::string(FileName[i]);
        const char* p=name.data();
        //std::cout<<p<<std::endl;
        file[i]=new TFile(p);
        Tree_list.push_back(std::vector<TTree*>());
        for(int j=0;j<TreeNumber;j++)
        {
            const char* treename=TreeName_list[j].data();
            TTree* tree=(TTree*)(file[i])->Get(treename);
            Tree_list[i].push_back(tree);
        }
    }

    for(int Ntree=0;Ntree<TreeNumber;Ntree++)
    {
        std::string s=std::string(Tree_list[0][Ntree]->GetTitle());
        TreeTitle_list.push_back(s);
    }
}

int TreeManager::GetFileNumber()
{
    return FileNumber;
}
Trees_list* TreeManager::GetTreesList()
{
    return &Tree_list;
}

int TreeManager::GetSubscriptOfTree(const char* p)
{
    int n=TreeName_list.size();
    for(int i=0;i<n;i++)
        if(!TreeName_list[i].compare(p))
            return i;
    std::cout<<"TreeManager::GetSubscriptOfTree error: "<<'"'<<p<<'"'<<" don't exit"<<std::endl;
    return -1;
}
bool TreeManager::surffix( char* filePath)
{
    bool flag=false;
    for(int i=0;filePath[i]=='\0';i++)
        if(filePath[i]=='.')
            flag=true;
    if(flag)
        return false;
    std::string filename(filePath);
    std::string suffixStr = filename.substr(filename.find_last_of('.') + 1);//获取文件后缀
    //std::cout<<"file name: "<<filename<<"  file type: "<<suffixStr<<std::endl;
    if (!suffixStr.compare("root"))
        return true;
    else
        return false;
        
}

name_list* TreeManager::GetTreeNameList()
{
    return &TreeName_list;
}

name_list* TreeManager::GetTreeTitleList()
{
    return &TreeTitle_list;
}
Trees* TreeManager::GetTrees(const char* treename)
{
    return &Tree_list[GetSubscriptOfTree(treename)];
}

void TreeManager::SetBranch(const char *Treename,name_list &branchname_list,name_list &type_list)
{
    int Ntree=GetSubscriptOfTree(Treename);
    int Branchnumber=branchname_list.size();
    void* p;
    for(int Nbranch=0;Nbranch<Branchnumber;Nbranch++)
    {
        Tree_list[0][Ntree]->Branch(branchname_list[Nbranch].data(),p,("p/"+type_list[Nbranch]).data());
    }
}



TObjArray* TreeManager::GetBranch(const char* Treename)
{
    int Ntree=GetSubscriptOfTree(Treename);
    return Tree_list[0][Ntree]->GetListOfBranches();
}
