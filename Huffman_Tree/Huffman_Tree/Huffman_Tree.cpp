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
					index1 = index2;//�ȸ���1�ٸ���2
					min2 = Huffman_Tree[j].weight;
					index2 = j;
					//cout << "����min2Ϊ" << min2 << endl;
				}
				 if ((Huffman_Tree[j].weight > min2) && (Huffman_Tree[j].weight <= min1))
				{
					min1 = Huffman_Tree[j].weight;
					index1 = j;
					//cout << "����min1Ϊ" << min1 << endl;

				}
			}//�õ�Ȩֵ��С�������ڵ��±��Ȩֵ
		}
		Huffman_Tree[index1].Parents = &Huffman_Tree[i]; 
		Huffman_Tree[index2].Parents = &Huffman_Tree[i];	

		Huffman_Tree[i].LChild = &Huffman_Tree[index1];// cout << "���ӽ���" << min1 << endl;
		Huffman_Tree[i].RChild = &Huffman_Tree[index2]; //cout << "�Һ��ӽ���" << min2<<endl<<endl;//���µ�ǰ�ڵ���󺢣��Һ�
		Huffman_Tree[i].weight = Huffman_Tree[index1].weight + Huffman_Tree[index2].weight;
	}//��ɹ�����������
	for (int i = 0; i < num; i++)
	{
		Tree* p = Huffman_Tree[i].Parents;
		Tree* c = &Huffman_Tree[i];
		while(1)
		{
			if (p->LChild == c)//���ﷸ���ش����,����1.û����current���浱ǰ������Ϊ��ֵ�жϣ���������Ѱ�Ҹ�ĸ
											//								����2. û��ʹ��ȫ�ȣ�����һ���Ⱥţ�Դ��Ϊ��if (p->LChild = &Huffman_Tree[i])
			{
				Huffman_Tree[i].Code.push_back(0); //debug_code,cout << "��"<<i << "������" << 0 << endl;
			}
			if (p->RChild == c)
			{
				Huffman_Tree[i].Code.push_back(1); //debug_doce,cout << "��"<<i << "������" << 1<<endl;
			}
			c = p;
			p = p->Parents;
			if (p == NULL)
			{
				break;
			}
		}//��ɹ��������룬ע��pushback��ʱ����,show�����������ʵ������
		//debug_code,cout << "��"<< i << "Complete" << endl;
	}
}
vector<int> En_Code(string str)
{
	vector<int> RES;
	for (int i = 0; i < str.size(); i++)//������ǰ�ַ���ÿһ���ַ�
	{
		for (int j = 0; j < num; j++)//�ڹ���������Ѱƥ���ַ�
		{
			if (Huffman_Tree[j].name == str.at(i))//�ж��൱
			{
				for (int k = Huffman_Tree[j].Code.size()-1; k>=0; k--)
				{
					RES.push_back(Huffman_Tree[j].Code[k]);//�������vector
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
			c = c->LChild; index++; //debug,cout << "����Ѱ" << endl;
		}
		else if (vec[index] == 1 && c->LChild != NULL && c->RChild != NULL)
		{
			c = c->RChild; index++; //debug,cout << "����Ѱ" << endl;
		}
		 if(c->LChild == NULL||c->RChild==NULL)//����������else,���ᵼ�´���
		{
			RES += c->name;  //debug,cout << "��Ѱ�ɹ�" << endl;
			c= &Huffman_Tree[2 * num - 1 - 1];//�����̬
		}
	}
	return RES;
}

void Save_Huffman_ToFile()
{
	for (int i = 0; i <num; i++)
	{
		ostringstream os; os << Huffman_Tree[i].name << ":" << Vector2string_Converter(Huffman_Tree[i].Code);//��ȡ�ַ���ƴ�ӷ�ʽ
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