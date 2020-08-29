#include"combine.hh"


void combine(TreeManager* treemanager,const char* FileName,bool Time)
{
    typedef std::vector<TObjArray*> Branchs;

    //creator file
    std::string filename(FileName);
    time_t tt = time(NULL);//这句返回的只是一个时间
    tm* t= localtime(&tt);
    std::stringstream s;
    s<<'.'<<t->tm_mon+1<<'.'<<t->tm_mday<<'.'<<t->tm_hour<<':'<<t->tm_min<<':'<<t->tm_min<<".root";
    std::string time=s.str();
    if(Time)
    filename=filename+time;
    else
    filename=filename+".root";

    name_list* treename_list=treemanager->GetTreeNameList();
    name_list* treetitle_list=treemanager->GetTreeTitleList();

    TreeManager treemanager_file(filename.data(),*treename_list,*treetitle_list,"write");


    double entries=0;
    int treenumber=(*treemanager->GetTreesList())[0].size();
    int filenumber=treemanager->GetFileNumber();



    for(int Ntree=0;Ntree<treenumber;Ntree++)
    {
        const char* treename=(*(treemanager->GetTreeNameList()))[Ntree].data();
        //std::cout<<"treename "<<treename<<std::endl;
        int branchnumber=treemanager->GetBranch(treename)->GetEntries();
        TObjArray* branch_list=treemanager->GetBranch((*treename_list)[Ntree].data());
        name_list branchname_list;
        name_list branchtype_list;
        for(int Nbranch=0;Nbranch<branchnumber;Nbranch++)
        {
            const char* branchname=(*branch_list)[Nbranch]->GetName();
           // std::cout<<"branchname "<<branchname<<std::endl;
            branchname_list.push_back(std::string(branchname));
            branchtype_list.push_back(std::string("D"));
        }

        //create branch
        treemanager_file.SetBranch(treename,branchname_list,branchtype_list);

        //fill branch
        for(int Nfile=0;Nfile<filenumber;Nfile++)
        {
            if(std::string(treename).compare("Number")==0)
            {
                 entries+=treemanager->ReadBranch<double>(treename,"n",0,Nfile);
            }
            else
            {
                int entry_number=(*(treemanager->GetTreesList()))[Nfile][Ntree]->GetEntries();

                for(int Nentry=0;Nentry<entry_number;Nentry++)
                {
                    std::vector<double> data;
                    for(int Nbranch=0;Nbranch<branchnumber;Nbranch++)
                    {
                        double d=treemanager->ReadBranch<double>(treename,branchname_list[Nbranch].data(),Nentry,Nfile);
                        data.push_back(d);
                    }
                    treemanager_file.FillBranch(treename,branchname_list,data);
                }

            }
        }

    }

    if(entries!=0.)
    {
        std::vector<double> data;
        data.push_back(entries);
        name_list branch_list;
        std::string s("n");
        branch_list.push_back(s);
        treemanager_file.FillBranch("Number",branch_list,data);
    }

    treemanager_file.CloseFile();
}

