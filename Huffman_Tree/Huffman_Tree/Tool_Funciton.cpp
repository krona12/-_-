#include "Tool_Funciton.h"
#include<string>
vector<int> String2vector_Converter(string str)
{
    vector<int> vec;
    for (int i = 0; i < str.size(); i++)
    {
        vec.push_back(str.at(i)-'0');
    }
    return vec;
}

string Vector2string_Converter(vector<int> vec)
{
    string str;
    for (int i = 0; i < vec.size(); i++)
    {
        str += to_string(vec[i]);
    }
    return str;
}



string Read_FromFile(string File_Name)
{
    string str;
    ifstream ifs;
    ifs.open(File_Name, ios::in);
    if (!ifs.is_open())
    {
        cout << File_Name << "�ļ���ȡʧ��," << "�����ļ��Ƿ����" << endl;
    }
    else
    {
        while (getline(ifs, str))
        {
            cout << File_Name << "�ļ���ȡ�ɹ���������:" << endl << str << "//" << endl;;
        }
    }
    ifs.close();
    return str;//����Ҫע��˳�򣬷����ȡ��ֵ���ز���
}
void Write_ToFile(string File_Name,string text,int mode)
{
    ofstream ofs;
    switch (mode)
    {
    case 1: ofs.open(File_Name, ios::app); break;
    case 2: ofs.open(File_Name, ios::out); break;
    }
    if (ofs.is_open())
    {
        switch (mode)
        {
        case 1: ofs << text << endl;
        case 2: ofs << text;
        }
        cout << File_Name << "�ļ�����д���У�" << text << "//";
    }
    else
    {
        cout <<File_Name<< "�ļ�������" << endl;
    }
    cout << "д�����" << endl;
    ofs.close();
}
