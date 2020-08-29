#include<vector>
#include<TString.h>
#include<dirent.h>
#include<iostream>
using namespace std;
bool surffix( char* filePath,char* suffix_str)
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
    if (!suffixStr.compare(suffix_str))
        return true;
    else
        return false;

}
vector<TString> get_current_dir_files_name(const char *path,char *suffix_str)
{
    //this function is used to get the names of all files ended with suffix_str in the dirtionary defined by the path
    DIR *directory_pointer;
    struct dirent *entry;
    std::vector<TString> FileName;
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
            if(surffix(&(entry->d_name[0]),suffix_str))
                FileName.push_back(TString(p));
        }

    }
    return FileName;
}

float get_num_in_file_name(TString str)
{
    //this function is  used to transform the file name's num into float to quick get the relavent
    //parameters
    int loc_of_point=0;
    for(int i =0;i<str.Sizeof();i++)
    {
        if(str[i]=='.')loc_of_point=i;
    }
    for(int i =0;i<loc_of_point;i++)
    {
        if(!(str[i]>='0'&&str[i]<='9') and str[i]!='.')str[i]='\0';
    }
    //    cout<<str.Sizeof()<<endl;
    return str.TString::Atof();
}

vector<TString> get_bash_parameters(int argc, char** arg,int argc_expected=2\
                                    ,vector<TString> v_title_arg={"name_file"})
{
    //this function should be used in front of TApplication,otherwise ,arg will be a mess;
    vector<TString> v_file_name;
    cout<<argc<<endl;
    if (argc != argc_expected)
    {
        cout << "Usage: ./*.C_exe ";
        for(int i=0;i<v_title_arg.size();i++)cout<<v_title_arg[i]<<" ";
        cout<<endl;
        exit(0);
    }
    else
    {
        for(int i=0;i<v_title_arg.size();i++)
        {
            v_file_name.push_back(arg[i+1]);
        }
    }
    return v_file_name;
}
















