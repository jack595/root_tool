#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
 
using namespace std;
//删除字符串中空格，制表符tab等无效字符
string Trim(string& str)
{
	//str.find_first_not_of(" \t\r\n"),在字符串str中从索引0开始，返回首次不匹配"\t\r\n"的位置
	str.erase(0,str.find_first_not_of(" \t\r\n"));
	str.erase(str.find_last_not_of(" \t\r\n") + 1);
	return str;
}
 
vector<vector<double>> GetPMTIDmap()
// void GetPMTIDmap()
{
	bool check_Map=true;
	ifstream fin("/cvmfs/juno.ihep.ac.cn/sl6_amd64_gcc830/Pre-Release/J20v1r0-Pre2/offline/Simulation/DetSimV2/DetSimOptions/data/PMTPos_Acrylic_with_chimney.csv"); //打开文件流操作
	string line; 
	int i=0;
	vector<double> v_loc(5);
	vector<vector<double>> PMTID_ToLoc;
	while (getline(fin, line))   //整行读取，换行符“\n”区分，遇到文件尾标志eof终止读取
	{
		i++;
		if(i<10)cout <<"原始字符串："<< line << endl; //整行输出
		istringstream sin(line); //将整行字符串line读入到字符串流istringstream中
		vector<string> fields; //声明一个字符串向量
		string field;
		while (getline(sin, field, ' ')) //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
		{
			fields.push_back(field); //将刚刚读取的字符串添加到向量fields中
		}
		for (int j = 0; j < 5; j++)
		{
			v_loc[j]=atof(fields[j+1].c_str());
		}
		
		// ={atof(fields[1].c_str()),atof(fields[2].c_str()),atof(fields[3].c_str()),atof(fields[4].c_str()),atof(fields[5].c_str())};
		PMTID_ToLoc.push_back(v_loc);
		// string name = Trim(fields[0]); //清除掉向量fields中第一个元素的无效字符，并赋值给变量name
		// string age = Trim(fields[1]); //清除掉向量fields中第二个元素的无效字符，并赋值给变量age
		// string birthday = Trim(fields[2]); //清除掉向量fields中第三个元素的无效字符，并赋值给变量birthday
		// cout <<"处理之后的字符串："<< name << "\t" << age << "\t" << birthday << endl; 
	}
	if (check_Map==true)
	{
		for (int j = 0; j <PMTID_ToLoc.size(); j++)
		{
			if ( j<10 )
			{
				cout<<j<<" ";
				for (int k = 0; k < PMTID_ToLoc[j].size(); k++)
				{
					cout<<PMTID_ToLoc[j][k]<<" ";
				}
				cout<<endl;
			}
		}
	}
	cout<< "csv file length:  "<<i<<endl;
	cout<< "output length:  "<<PMTID_ToLoc.size()<<endl; 
		
	return PMTID_ToLoc;
}