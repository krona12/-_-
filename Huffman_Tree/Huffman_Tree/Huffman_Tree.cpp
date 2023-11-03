#include"Huffman_Tree.h"
#include"Tool_Funciton.h"
#include<string>
#include<sstream>
#pragma once

string File_Name[4] = { "HfmTree.txt","ToBeTran.txt" ,"CodeFile.txt","TextFile.txt" };
void Initial_Huffman()
{
	for (int i = 0; i < num; i++)
	{
		Tree temp(weight_arr[i], name_arr[i], NULL, NULL, NULL);
		Huffman_Tree.push_back(temp);
	}
}
void Create_Huffman(int n)
{
	for (int i =n; i <2*n-1; i++)
	{
		Tree temp(0,'0', NULL, NULL, NULL);
		Huffman_Tree.push_back(temp);
	}
	for (int i = n; i < 2 * n - 1; i++)
	{
		int min1 = 1000; int min2 = 999;
		int index1 = 0;int  index2 = 0;
		for (int j = 0; j < i; j++)
		{
			if (Huffman_Tree[j].Parents == NULL)
			{
				if (Huffman_Tree[j].weight <= min2)
				{
					min1 = min2;
					index1 = index2;//先更新1再更新2
					min2 = Huffman_Tree[j].weight;
					index2 = j;
					//cout << "更新min2为" << min2 << endl;
				}
				 if ((Huffman_Tree[j].weight > min2) && (Huffman_Tree[j].weight <= min1))
				{
					min1 = Huffman_Tree[j].weight;
					index1 = j;
					//cout << "更新min1为" << min1 << endl;

				}
			}//得到权值最小的两个节点下标和权值
		}
		Huffman_Tree[index1].Parents = &Huffman_Tree[i]; 
		Huffman_Tree[index2].Parents = &Huffman_Tree[i];	

		Huffman_Tree[i].LChild = &Huffman_Tree[index1];// cout << "左孩子建立" << min1 << endl;
		Huffman_Tree[i].RChild = &Huffman_Tree[index2]; //cout << "右孩子建立" << min2<<endl<<endl;//更新当前节点的左孩，右孩
		Huffman_Tree[i].weight = Huffman_Tree[index1].weight + Huffman_Tree[index2].weight;
	}//完成哈夫曼树建立
	for (int i = 0; i < num; i++)
	{
		Tree* p = Huffman_Tree[i].Parents;
		Tree* c = &Huffman_Tree[i];
		while(1)
		{
			if (p->LChild == c)//这里犯了重大错误,错误1.没有用current代替当前，导致为定值判断，不能往上寻找父母
											//								错误2. 没有使用全等，而是一个等号，源码为：if (p->LChild = &Huffman_Tree[i])
			{
				Huffman_Tree[i].Code.push_back(0); //debug_code,cout << "第"<<i << "个导入" << 0 << endl;
			}
			if (p->RChild == c)
			{
				Huffman_Tree[i].Code.push_back(1); //debug_doce,cout << "第"<<i << "个导入" << 1<<endl;
			}
			c = p;
			p = p->Parents;
			if (p == NULL)
			{
				break;
			}
		}//完成哈夫曼编码，注意pushback此时倒序,show倒序输出即可实现正序。
		//debug_code,cout << "第"<< i << "Complete" << endl;
	}
}
vector<int> En_Code(string str)
{
	vector<int> RES;
	for (int i = 0; i < str.size(); i++)//遍历当前字符串每一个字符
	{
		for (int j = 0; j < num; j++)//在哈夫曼树搜寻匹配字符
		{
			if (Huffman_Tree[j].name == str.at(i))//判断相当
			{
				for (int k = Huffman_Tree[j].Code.size()-1; k>=0; k--)
				{
					RES.push_back(Huffman_Tree[j].Code[k]);//推入编码vector
				}
			}
		}
	}
	return RES;
}
string De_Code(vector<int> vec)
{
	string RES;
	Tree* c = &Huffman_Tree[2 * num - 1 - 1];
	int index = 0;
	while (index < vec.size())
	{
		if (vec[index] == 0&&c->LChild!=NULL&&c->RChild!=NULL)
		{
			c = c->LChild; index++; //debug,cout << "左搜寻" << endl;
		}
		else if (vec[index] == 1 && c->LChild != NULL && c->RChild != NULL)
		{
			c = c->RChild; index++; //debug,cout << "右搜寻" << endl;
		}
		 if(c->LChild == NULL||c->RChild==NULL)//这里如果添加else,将会导致错误
		{
			RES += c->name;  //debug,cout << "搜寻成功" << endl;
			c= &Huffman_Tree[2 * num - 1 - 1];//重设初态
		}
	}
	return RES;
}

void Save_Huffman_ToFile()
{
	for (int i = 0; i <num; i++)
	{
		ostringstream os; os << Huffman_Tree[i].name << ":" << Vector2string_Converter(Huffman_Tree[i].Code);//采取字符串拼接方式
		Write_ToFile(File_Name[0], os.str(),1);
	}
}
void Save_EnCode_ToFile()
{
	string str = Read_FromFile(File_Name[1]);
	string encode = Vector2string_Converter(En_Code(str));
	Write_ToFile(File_Name[2], encode,2);
}
void Save_DeCode_Tofile()
{
	vector<int> vec= String2vector_Converter(Read_FromFile(File_Name[2]));
	string decode = De_Code(vec);
	cout << decode << endl;
	Write_ToFile(File_Name[3],decode,2);
}
int main()
{
	Initial_Huffman();
	Create_Huffman(num);
	for (int i = 0; i < num; i++)
	{
		Huffman_Tree[i].Show_Code();
	}
	Save_Huffman_ToFile();
	Save_EnCode_ToFile();
	Save_DeCode_Tofile();
	/*vector<int> vec = String2vector_Converter(Read_FromFile(File_Name[2]));
	string decode = De_Code(vec);
	cout << decode;*/
	//cout << Read_FromFile(File_Name[2]);

}