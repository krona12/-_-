#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
vector<int> String2vector_Converter(string str);//stirng µ½vector<int>×ª»»
string Vector2string_Converter(vector<int> vec);
string Read_FromFile(string File_Name);
void Write_ToFile(string File_Name, string text,int mode);